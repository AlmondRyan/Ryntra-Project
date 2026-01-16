#include "IRGenerator/IRGenerator.h"

#include <iostream>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Type.h>
#include <llvm/Support/raw_ostream.h>
#include <vector>

namespace Ryntra::Compiler {
    IRGenerator::IRGenerator()
        : context(std::make_unique<llvm::LLVMContext>()),
          module(std::make_unique<llvm::Module>("RyntraModule", *context)),
          builder(std::make_unique<llvm::IRBuilder<>>(*context)) {
    }

    std::string IRGenerator::getIR() const {
        std::string              str;
        llvm::raw_string_ostream os(str);
        module->print(os, nullptr);
        return str;
    }

    void IRGenerator::visitProgram(std::shared_ptr<ProgramNode> node) {
        for (const auto& i : node->getFunctions()) {
            visit(i);
        }
    }

    namespace {
        llvm::Type *mapType(llvm::LLVMContext &context, const std::string &typeName) {
            if (typeName == "int")
                return llvm::Type::getInt32Ty(context);
            if (typeName == "long")
                return llvm::Type::getInt64Ty(context);
            if (typeName == "long long")
                return llvm::Type::getInt64Ty(context);
            if (typeName == "string")
                return llvm::PointerType::get(context, 0);
            if (typeName == "void")
                return llvm::Type::getVoidTy(context);
            if (typeName == "bool")
                return llvm::Type::getInt1Ty(context);
            if (typeName == "float")
                return llvm::Type::getFloatTy(context);
            if (typeName == "double")
                return llvm::Type::getDoubleTy(context);
            return llvm::Type::getVoidTy(context);
        }
    } // namespace

    void IRGenerator::visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) {
        // 1. Prepare parameter types
        std::vector<llvm::Type *> paramTypes;
        for (const auto &param : node->getParameters()) {
            paramTypes.push_back(mapType(*context, param->getType()));
        }

        // 2. Create Function Type and Function
        llvm::FunctionType *funcType = llvm::FunctionType::get(
            mapType(*context, node->getReturnType()),
            paramTypes,
            false);

        llvm::Function *func = llvm::Function::Create(
            funcType,
            llvm::Function::ExternalLinkage,
            node->getFunctionName(),
            module.get());

        // 3. Create Entry Basic Block
        llvm::BasicBlock *entryBB = llvm::BasicBlock::Create(*context, "entry", func);
        builder->SetInsertPoint(entryBB);

        // 4. Handle Parameters (Allocation and Storage)
        symbolTable.enterScope();
        namedValues.clear();
        unsigned idx = 0;
        for (auto &arg : func->args()) {
            auto paramNode = node->getParameters()[idx++];
            arg.setName(paramNode->getName());

            // Create alloca for parameter
            llvm::AllocaInst *alloca = builder->CreateAlloca(arg.getType(), nullptr, paramNode->getName() + ".addr");
            unsigned          align = (arg.getType()->getPrimitiveSizeInBits() == 64) ? 8 : 4;
            alloca->setAlignment(llvm::Align(align));

            auto store = builder->CreateStore(&arg, alloca);
            store->setAlignment(llvm::Align(align));

            // Add to IR generator's local symbol map
            namedValues[paramNode->getName()] = alloca;
        }

        // 5. Visit Body
        visit(node->getBody());
        symbolTable.exitScope();
        namedValues.clear();

        // 6. Ensure Return
        if (builder->GetInsertBlock() && !builder->GetInsertBlock()->getTerminator()) {
            if (node->getReturnType() == "void") {
                builder->CreateRetVoid();
            } else if (node->getReturnType() == "int") {
                builder->CreateRet(llvm::ConstantInt::get(*context, llvm::APInt(32, 0)));
            } else if (node->getReturnType() == "long" || node->getReturnType() == "long long") {
                builder->CreateRet(llvm::ConstantInt::get(*context, llvm::APInt(64, 0)));
            } else if (node->getReturnType() == "float") {
                builder->CreateRet(llvm::ConstantFP::get(*context, llvm::APFloat(0.0f)));
            } else if (node->getReturnType() == "double") {
                builder->CreateRet(llvm::ConstantFP::get(*context, llvm::APFloat(0.0)));
            }
        }
    }

    void IRGenerator::visitBlock(std::shared_ptr<BlockNode> node) {
        for (auto &stmt : node->getStatements()) {
            visit(stmt);
        }
    }

    void IRGenerator::visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) {
    }

    void IRGenerator::visitIfStatement(std::shared_ptr<IfStatementNode> node) {
        llvm::Value *condValue = evaluate(node->getCondition());
        if (!condValue)
            return;

        llvm::Function *func = builder->GetInsertBlock()->getParent();

        llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(*context, "then", func);
        llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(*context, "else");
        llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(*context, "ifcont");

        if (node->getElseBody()) {
            builder->CreateCondBr(condValue, thenBB, elseBB);
        } else {
            builder->CreateCondBr(condValue, thenBB, mergeBB);
        }

        // Emit then block
        builder->SetInsertPoint(thenBB);
        visit(node->getThenBody());
        if (!builder->GetInsertBlock()->getTerminator()) {
            builder->CreateBr(mergeBB);
        }

        // Emit else block
        if (node->getElseBody()) {
            func->insert(func->end(), elseBB);
            builder->SetInsertPoint(elseBB);
            visit(node->getElseBody());
            if (!builder->GetInsertBlock()->getTerminator()) {
                builder->CreateBr(mergeBB);
            }
        }

        // Emit merge block
        func->insert(func->end(), mergeBB);
        builder->SetInsertPoint(mergeBB);
    }

    void IRGenerator::visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) {
        visit(node->getExpression());
    }

    void IRGenerator::visitFunctionCall(std::shared_ptr<FunctionCallNode> node) {
        std::string funcName = node->getFunctionName();

        // 1. Symbol Table Lookup
        if (symbolTable.lookupFunction(funcName)) {
            // 2. Builtin Handling
            if (funcName == "__builtin_print") {
                // Declare printf if not exists: int printf(i8*, ...)
                std::vector<llvm::Type *> argsTypes;
                argsTypes.push_back(llvm::PointerType::get(*context, 0));

                llvm::FunctionType *printfType = llvm::FunctionType::get(
                    llvm::Type::getInt32Ty(*context), // return int
                    argsTypes,
                    true // varargs
                );

                llvm::FunctionCallee printfFunc = module->getOrInsertFunction("printf", printfType);

                std::vector<llvm::Value *> args;
                std::vector<llvm::Value *> stringsToFree; // Track temporary strings from *ToString builtins

                for (auto argNode : node->getArguments()) {
                    // Check if this argument is a call to a builtin that returns a temporary string
                    bool isTempString = false;
                    if (auto callNode = std::dynamic_pointer_cast<FunctionCallNode>(argNode)) {
                        std::string calleeName = callNode->getFunctionName();
                        if (calleeName == "__builtin_intToString" ||
                            calleeName == "__builtin_longToString" ||
                            calleeName == "__builtin_longlongToString" ||
                            calleeName == "__builtin_floatToString" ||
                            calleeName == "__builtin_doubleToString") {
                            isTempString = true;
                        }
                    }

                    llvm::Value *val = evaluate(argNode);
                    if (val) {
                        args.push_back(val);
                        if (isTempString) {
                            stringsToFree.push_back(val);
                        }
                    }
                }

                if (!args.empty()) {
                    lastValue = builder->CreateCall(printfFunc, args);

                    // Insert free calls for temporary strings
                    if (!stringsToFree.empty()) {
                        llvm::FunctionType *freeType = llvm::FunctionType::get(
                            llvm::Type::getVoidTy(*context),
                            {llvm::PointerType::get(*context, 0)},
                            false);
                        llvm::FunctionCallee freeFunc = module->getOrInsertFunction("rcrt_builtin_free", freeType);
                        for (auto strPtr : stringsToFree) {
                            builder->CreateCall(freeFunc, {strPtr});
                        }
                    }
                    return;
                }
            } else if (funcName == "__builtin_intToString") {
                // Declare rcrt_builtin_intToString if not exists: char* rcrt_builtin_intToString(int)
                std::vector<llvm::Type *> argsTypes;
                argsTypes.push_back(llvm::Type::getInt32Ty(*context));

                llvm::FunctionType *toStringType = llvm::FunctionType::get(
                    llvm::PointerType::get(*context, 0), // return char*
                    argsTypes,
                    false);

                llvm::FunctionCallee toStringFunc = module->getOrInsertFunction("rcrt_builtin_intToString", toStringType);

                std::vector<llvm::Value *> args;
                for (auto arg : node->getArguments()) {
                    llvm::Value *val = evaluate(arg);
                    if (val) {
                        args.push_back(val);
                    }
                }

                lastValue = builder->CreateCall(toStringFunc, args);
                return;
            } else if (funcName == "__builtin_longToString") {
                // Declare rcrt_builtin_longToString if not exists: char* rcrt_builtin_longToString(long)
                std::vector<llvm::Type *> argsTypes;
                argsTypes.push_back(llvm::Type::getInt64Ty(*context));

                llvm::FunctionType *toStringType = llvm::FunctionType::get(
                    llvm::PointerType::get(*context, 0), // return char*
                    argsTypes,
                    false);

                llvm::FunctionCallee toStringFunc = module->getOrInsertFunction("rcrt_builtin_longToString", toStringType);

                std::vector<llvm::Value *> args;
                for (auto arg : node->getArguments()) {
                    llvm::Value *val = evaluate(arg);
                    if (val) {
                        // Ensure it's i64
                        if (val->getType()->isIntegerTy() && val->getType()->getIntegerBitWidth() < 64) {
                            val = builder->CreateSExt(val, llvm::Type::getInt64Ty(*context), "sext");
                        }
                        args.push_back(val);
                    }
                }

                lastValue = builder->CreateCall(toStringFunc, args);
                return;
            } else if (funcName == "__builtin_longlongToString") {
                // Declare rcrt_builtin_longlongToString if not exists: char* rcrt_builtin_longlongToString(long long)
                std::vector<llvm::Type *> argsTypes;
                argsTypes.push_back(llvm::Type::getInt64Ty(*context));

                llvm::FunctionType *toStringType = llvm::FunctionType::get(
                    llvm::PointerType::get(*context, 0), // return char*
                    argsTypes,
                    false);

                llvm::FunctionCallee toStringFunc = module->getOrInsertFunction("rcrt_builtin_longlongToString", toStringType);

                std::vector<llvm::Value *> args;
                for (auto arg : node->getArguments()) {
                    llvm::Value *val = evaluate(arg);
                    if (val) {
                        // Ensure it's i64
                        if (val->getType()->isIntegerTy() && val->getType()->getIntegerBitWidth() < 64) {
                            val = builder->CreateSExt(val, llvm::Type::getInt64Ty(*context), "sext");
                        }
                        args.push_back(val);
                    }
                }

                lastValue = builder->CreateCall(toStringFunc, args);
                return;
            } else if (funcName == "__builtin_floatToString") {
                // Declare rcrt_builtin_floatToString if not exists: char* rcrt_builtin_floatToString(float, int)
                std::vector<llvm::Type *> argsTypes;
                argsTypes.push_back(llvm::Type::getFloatTy(*context));
                argsTypes.push_back(llvm::Type::getInt32Ty(*context));

                llvm::FunctionType *toStringType = llvm::FunctionType::get(
                    llvm::PointerType::get(*context, 0), // return char*
                    argsTypes,
                    false);

                llvm::FunctionCallee toStringFunc = module->getOrInsertFunction("rcrt_builtin_floatToString", toStringType);

                std::vector<llvm::Value *> args;
                int                         idx = 0;
                for (auto arg : node->getArguments()) {
                    llvm::Value *val = evaluate(arg);
                    if (val) {
                        if (idx == 0) {
                            // Ensure first argument is float
                            if (val->getType()->isDoubleTy()) {
                                val = builder->CreateFPTrunc(val, llvm::Type::getFloatTy(*context), "fptrunc");
                            } else if (val->getType()->isIntegerTy()) {
                                val = builder->CreateSIToFP(val, llvm::Type::getFloatTy(*context), "sitofp");
                            }
                        } else if (idx == 1) {
                            // Ensure second argument is i32
                            llvm::Type *targetType = llvm::Type::getInt32Ty(*context);
                            if (val->getType()->isIntegerTy()) {
                                if (val->getType() != targetType) {
                                    unsigned valWidth = val->getType()->getIntegerBitWidth();
                                    unsigned targetWidth = targetType->getIntegerBitWidth();
                                    if (valWidth < targetWidth) {
                                        val = builder->CreateSExt(val, targetType, "sext");
                                    } else if (valWidth > targetWidth) {
                                        val = builder->CreateTrunc(val, targetType, "trunc");
                                    }
                                }
                            } else if (val->getType()->isFloatingPointTy()) {
                                val = builder->CreateFPToSI(val, targetType, "fptosi");
                            }
                        }
                        args.push_back(val);
                        ++idx;
                    }
                }

                lastValue = builder->CreateCall(toStringFunc, args);
                return;
            } else if (funcName == "__builtin_doubleToString") {
                // Declare rcrt_builtin_doubleToString if not exists: char* rcrt_builtin_doubleToString(double, int)
                std::vector<llvm::Type *> argsTypes;
                argsTypes.push_back(llvm::Type::getDoubleTy(*context));
                argsTypes.push_back(llvm::Type::getInt32Ty(*context));

                llvm::FunctionType *toStringType = llvm::FunctionType::get(
                    llvm::PointerType::get(*context, 0), // return char*
                    argsTypes,
                    false);

                llvm::FunctionCallee toStringFunc = module->getOrInsertFunction("rcrt_builtin_doubleToString", toStringType);

                std::vector<llvm::Value *> args;
                int                         idx = 0;
                for (auto arg : node->getArguments()) {
                    llvm::Value *val = evaluate(arg);
                    if (val) {
                        if (idx == 0) {
                            // Ensure first argument is double
                            if (val->getType()->isFloatTy()) {
                                val = builder->CreateFPExt(val, llvm::Type::getDoubleTy(*context), "fpext");
                            } else if (val->getType()->isIntegerTy()) {
                                val = builder->CreateSIToFP(val, llvm::Type::getDoubleTy(*context), "sitofp");
                            }
                        } else if (idx == 1) {
                            // Ensure second argument is i32
                            llvm::Type *targetType = llvm::Type::getInt32Ty(*context);
                            if (val->getType()->isIntegerTy()) {
                                if (val->getType() != targetType) {
                                    unsigned valWidth = val->getType()->getIntegerBitWidth();
                                    unsigned targetWidth = targetType->getIntegerBitWidth();
                                    if (valWidth < targetWidth) {
                                        val = builder->CreateSExt(val, targetType, "sext");
                                    } else if (valWidth > targetWidth) {
                                        val = builder->CreateTrunc(val, targetType, "trunc");
                                    }
                                }
                            } else if (val->getType()->isFloatingPointTy()) {
                                val = builder->CreateFPToSI(val, targetType, "fptosi");
                            }
                        }
                        args.push_back(val);
                        ++idx;
                    }
                }

                lastValue = builder->CreateCall(toStringFunc, args);
                return;
            } else if (funcName == "__builtin_free") {
                // Declare rcrt_builtin_free if not exists: void rcrt_builtin_free(void*)
                llvm::FunctionType *freeType = llvm::FunctionType::get(
                    llvm::Type::getVoidTy(*context),
                    {llvm::PointerType::get(*context, 0)},
                    false);
                llvm::FunctionCallee freeFunc = module->getOrInsertFunction("rcrt_builtin_free", freeType);

                std::vector<llvm::Value *> args;
                for (auto arg : node->getArguments()) {
                    llvm::Value *val = evaluate(arg);
                    if (val) {
                        args.push_back(val);
                    }
                }

                if (!args.empty()) {
                    builder->CreateCall(freeFunc, args[0]);
                }
                lastValue = nullptr;
                return;
            } else {
                // Non-builtin function lookup in Module
                llvm::Function *callee = module->getFunction(funcName);
                if (callee) {
                    std::vector<llvm::Value *> args;
                    unsigned                   idx = 0;
                    for (auto argNode : node->getArguments()) {
                        llvm::Value *val = evaluate(argNode);
                        if (val) {
                            // Handle argument type conversion
                            if (idx < callee->arg_size()) {
                                llvm::Type *targetType = callee->getFunctionType()->getParamType(idx);
                                if (val->getType() != targetType) {
                                    if (val->getType()->isIntegerTy() && targetType->isIntegerTy()) {
                                        unsigned valWidth = val->getType()->getIntegerBitWidth();
                                        unsigned targetWidth = targetType->getIntegerBitWidth();
                                        if (valWidth < targetWidth) {
                                            val = builder->CreateSExt(val, targetType, "sext");
                                        } else if (valWidth > targetWidth) {
                                            val = builder->CreateTrunc(val, targetType, "trunc");
                                        }
                                    } else if (val->getType()->isFloatingPointTy() && targetType->isFloatingPointTy()) {
                                        if (val->getType()->getPrimitiveSizeInBits() < targetType->getPrimitiveSizeInBits()) {
                                            val = builder->CreateFPExt(val, targetType, "fpext");
                                        } else {
                                            val = builder->CreateFPTrunc(val, targetType, "fptrunc");
                                        }
                                    } else if (val->getType()->isIntegerTy() && targetType->isFloatingPointTy()) {
                                        val = builder->CreateSIToFP(val, targetType, "sitofp");
                                    } else if (val->getType()->isFloatingPointTy() && targetType->isIntegerTy()) {
                                        val = builder->CreateFPToSI(val, targetType, "fptosi");
                                    }
                                }
                            }
                            args.push_back(val);
                        }
                        idx++;
                    }
                    lastValue = builder->CreateCall(callee, args);
                    return;
                }
            }
        }
        lastValue = nullptr;
    }

    void IRGenerator::visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) {
        visit(node->getFunctionCall());
    }

    void IRGenerator::visitIdentifier(std::shared_ptr<IdentifierNode> node) {
        llvm::Value *v = namedValues[node->getName()];
        if (!v) {
            lastValue = nullptr;
            return;
        }
        llvm::Type *type = ((llvm::AllocaInst *)v)->getAllocatedType();
        auto        load = builder->CreateLoad(type, v, node->getName());
        unsigned    align = (type->getPrimitiveSizeInBits() == 64) ? 8 : 4;
        load->setAlignment(llvm::Align(align));
        lastValue = load;
    }

    void IRGenerator::visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) {
        long long val = node->getValue();
        TypeKind  kind = node->getTypeKind();

        if (kind == TypeKind::Long || kind == TypeKind::LongLong) {
            lastValue = llvm::ConstantInt::get(*context, llvm::APInt(64, val, true));
        } else {
            // Even if it's marked as Int, check if it actually fits.
            // This handles cases where ASTBuilder might have promoted it but it's not explicitly suffixed.
            if (val > 2147483647LL || val < -2147483648LL) {
                lastValue = llvm::ConstantInt::get(*context, llvm::APInt(64, val, true));
            } else {
                lastValue = llvm::ConstantInt::get(*context, llvm::APInt(32, val, true));
            }
        }
    }

    void IRGenerator::visitFloatingLiteral(std::shared_ptr<FloatingLiteralNode> node) {
        double   val = node->getValue();
        TypeKind kind = node->getTypeKind();

        if (kind == TypeKind::Float) {
            lastValue = llvm::ConstantFP::get(*context, llvm::APFloat((float)val));
        } else {
            lastValue = llvm::ConstantFP::get(*context, llvm::APFloat(val));
        }
    }

    void IRGenerator::visitParameter(std::shared_ptr<ParameterNode> node) {
    }

    void IRGenerator::visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) {
        llvm::Value *val = evaluate(node->getReturnValue());
        if (val) {
            // Handle type conversion to function return type
            llvm::Type *retType = builder->GetInsertBlock()->getParent()->getReturnType();
            if (val->getType() != retType) {
                if (val->getType()->isIntegerTy() && retType->isIntegerTy()) {
                    unsigned valWidth = val->getType()->getIntegerBitWidth();
                    unsigned targetWidth = retType->getIntegerBitWidth();
                    if (valWidth < targetWidth) {
                        val = builder->CreateSExt(val, retType, "sext");
                    } else if (valWidth > targetWidth) {
                        val = builder->CreateTrunc(val, retType, "trunc");
                    }
                } else if (val->getType()->isFloatingPointTy() && retType->isFloatingPointTy()) {
                    if (val->getType()->getPrimitiveSizeInBits() < retType->getPrimitiveSizeInBits())
                        val = builder->CreateFPExt(val, retType, "fpext");
                    else if (val->getType()->getPrimitiveSizeInBits() > retType->getPrimitiveSizeInBits())
                        val = builder->CreateFPTrunc(val, retType, "fptrunc");
                } else if (val->getType()->isIntegerTy() && retType->isFloatingPointTy()) {
                    val = builder->CreateSIToFP(val, retType, "sitofp");
                } else if (val->getType()->isFloatingPointTy() && retType->isIntegerTy()) {
                    val = builder->CreateFPToSI(val, retType, "fptosi");
                }
            }
            builder->CreateRet(val);
        } else {
            builder->CreateRetVoid();
        }
    }

    void IRGenerator::visitStringLiteral(std::shared_ptr<StringLiteralNode> node) {
        lastValue = builder->CreateGlobalStringPtr(node->getValue());
    }

    void IRGenerator::visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) {
        llvm::Value *val = evaluate(node->getInitialValue());

        llvm::Type       *type = mapType(*context, node->getVarType());
        llvm::AllocaInst *alloca = builder->CreateAlloca(type, nullptr, node->getVarName());
        unsigned          align = (type->getPrimitiveSizeInBits() == 64) ? 8 : 4;
        alloca->setAlignment(llvm::Align(align));

        if (val) {
            // Handle type conversion (e.g. int to long, int to float)
            if (val->getType() != type) {
                if (val->getType()->isIntegerTy() && type->isIntegerTy()) {
                    unsigned valWidth = val->getType()->getIntegerBitWidth();
                    unsigned targetWidth = type->getIntegerBitWidth();
                    if (valWidth < targetWidth) {
                        val = builder->CreateSExt(val, type, "sext");
                    } else if (valWidth > targetWidth) {
                        val = builder->CreateTrunc(val, type, "trunc");
                    }
                } else if (val->getType()->isFloatingPointTy() && type->isFloatingPointTy()) {
                    if (val->getType()->getPrimitiveSizeInBits() < type->getPrimitiveSizeInBits()) {
                        val = builder->CreateFPExt(val, type, "fpext");
                    } else {
                        val = builder->CreateFPTrunc(val, type, "fptrunc");
                    }
                } else if (val->getType()->isIntegerTy() && type->isFloatingPointTy()) {
                    val = builder->CreateSIToFP(val, type, "sitofp");
                } else if (val->getType()->isFloatingPointTy() && type->isIntegerTy()) {
                    val = builder->CreateFPToSI(val, type, "fptosi");
                }
            }
            auto store = builder->CreateStore(val, alloca);
            store->setAlignment(llvm::Align(align));
        }

        namedValues[node->getVarName()] = alloca;
    }

    void IRGenerator::visitBinaryExpression(std::shared_ptr<BinaryExpressionNode> node) {
        std::string op = node->getOp();

        // Handle logical AND/OR with short-circuiting
        if (op == "&&") {
            llvm::Value    *lhsValue = evaluate(node->getLeft());
            llvm::Function *func = builder->GetInsertBlock()->getParent();

            llvm::BasicBlock *rhsBB = llvm::BasicBlock::Create(*context, "and.rhs", func);
            llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(*context, "and.merge", func);

            llvm::BasicBlock *entryBB = builder->GetInsertBlock();
            builder->CreateCondBr(lhsValue, rhsBB, mergeBB);

            builder->SetInsertPoint(rhsBB);
            llvm::Value      *rhsValue = evaluate(node->getRight());
            llvm::BasicBlock *rhsEndBB = builder->GetInsertBlock();
            builder->CreateBr(mergeBB);

            builder->SetInsertPoint(mergeBB);
            llvm::PHINode *phi = builder->CreatePHI(llvm::Type::getInt1Ty(*context), 2, "andtmp");
            phi->addIncoming(llvm::ConstantInt::getFalse(*context), entryBB);
            phi->addIncoming(rhsValue, rhsEndBB);

            lastValue = phi;
            return;
        }

        if (op == "||") {
            llvm::Value    *lhsValue = evaluate(node->getLeft());
            llvm::Function *func = builder->GetInsertBlock()->getParent();

            llvm::BasicBlock *rhsBB = llvm::BasicBlock::Create(*context, "or.rhs", func);
            llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(*context, "or.merge", func);

            llvm::BasicBlock *entryBB = builder->GetInsertBlock();
            builder->CreateCondBr(lhsValue, mergeBB, rhsBB);

            builder->SetInsertPoint(rhsBB);
            llvm::Value      *rhsValue = evaluate(node->getRight());
            llvm::BasicBlock *rhsEndBB = builder->GetInsertBlock();
            builder->CreateBr(mergeBB);

            builder->SetInsertPoint(mergeBB);
            llvm::PHINode *phi = builder->CreatePHI(llvm::Type::getInt1Ty(*context), 2, "ortmp");
            phi->addIncoming(llvm::ConstantInt::getTrue(*context), entryBB);
            phi->addIncoming(rhsValue, rhsEndBB);

            lastValue = phi;
            return;
        }

        llvm::Value *leftValue = evaluate(node->getLeft());
        llvm::Value *rightValue = evaluate(node->getRight());

        if (!leftValue || !rightValue)
            return;

        // Handle type promotion for arithmetic and bitwise operations
        if (op == "*" || op == "/" || op == "%" || op == "&" || op == "|" || op == "^" || op == "<<" || op == ">>" ||
            op == "+" || op == "-" || op == "<" || op == "<=" || op == ">" || op == ">=" || op == "==" || op == "!=") {

            llvm::Type *leftType = leftValue->getType();
            llvm::Type *rightType = rightValue->getType();

            if (leftType->isFloatingPointTy() || rightType->isFloatingPointTy()) {
                // Promote to double if either is double, or both are floating point
                llvm::Type *targetType = (leftType->isDoubleTy() || rightType->isDoubleTy()) 
                                         ? llvm::Type::getDoubleTy(*context) 
                                         : llvm::Type::getFloatTy(*context);
                
                if (leftType != targetType) {
                    if (leftType->isIntegerTy()) leftValue = builder->CreateSIToFP(leftValue, targetType, "sitofp");
                    else leftValue = builder->CreateFPExt(leftValue, targetType, "fpext");
                }
                if (rightType != targetType) {
                    if (rightType->isIntegerTy()) rightValue = builder->CreateSIToFP(rightValue, targetType, "sitofp");
                    else rightValue = builder->CreateFPExt(rightValue, targetType, "fpext");
                }
            } else if (leftType->isIntegerTy() && rightType->isIntegerTy()) {
                unsigned leftWidth = leftType->getIntegerBitWidth();
                unsigned rightWidth = rightType->getIntegerBitWidth();

                if (leftWidth < rightWidth) {
                    leftValue = builder->CreateSExt(leftValue, rightType, "sext");
                } else if (rightWidth < leftWidth) {
                    rightValue = builder->CreateSExt(rightValue, leftType, "sext");
                }
            }
        }

        if (op == "+") {
            if (leftValue->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFAdd(leftValue, rightValue, "faddtmp");
            } else {
                lastValue = builder->CreateAdd(leftValue, rightValue, "addtmp");
            }
            return;
        }
        if (op == "-") {
            if (leftValue->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFSub(leftValue, rightValue, "fsubtmp");
            } else {
                lastValue = builder->CreateSub(leftValue, rightValue, "subTemp");
            }
            return;
        }
        if (op == "*") {
            if (leftValue->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFMul(leftValue, rightValue, "fmultmp");
            } else {
                lastValue = builder->CreateMul(leftValue, rightValue, "mulTemp");
            }
            return;
        }
        if ("/" == op) {
            if (leftValue->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFDiv(leftValue, rightValue, "fdivtmp");
            } else {
                lastValue = builder->CreateSDiv(leftValue, rightValue, "subDiv");
            }
            return;
        }
        if (op == "%") {
            lastValue = builder->CreateSRem(leftValue, rightValue, "remtmp");
            return;
        }

        if (op == "&") {
            lastValue = builder->CreateAnd(leftValue, rightValue, "andtmp");
            return;
        }
        if (op == "|") {
            lastValue = builder->CreateOr(leftValue, rightValue, "ortmp");
            return;
        }
        if (op == "^") {
            lastValue = builder->CreateXor(leftValue, rightValue, "xortmp");
            return;
        }
        if (op == "<<") {
            lastValue = builder->CreateShl(leftValue, rightValue, "shltmp");
            return;
        }
        if (op == ">>") {
            lastValue = builder->CreateAShr(leftValue, rightValue, "ashrtmp");
            return;
        }

        // Comparison operators
        if ("==" == op) {
            if (leftValue->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFCmpOEQ(leftValue, rightValue, "feqtmp");
            } else {
                lastValue = builder->CreateICmpEQ(leftValue, rightValue, "eqtmp");
            }
            return;
        }
        if ("!=" == op) {
            if (leftValue->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFCmpONE(leftValue, rightValue, "fnetmp");
            } else {
                lastValue = builder->CreateICmpNE(leftValue, rightValue, "netmp");
            }
            return;
        }
        if (op == "<") {
            if (leftValue->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFCmpOLT(leftValue, rightValue, "flttmp");
            } else {
                lastValue = builder->CreateICmpSLT(leftValue, rightValue, "lttmp");
            }
            return;
        }
        if (op == "<=") {
            if (leftValue->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFCmpOLE(leftValue, rightValue, "fletmp");
            } else {
                lastValue = builder->CreateICmpSLE(leftValue, rightValue, "letmp");
            }
            return;
        }
        if (op == ">") {
            if (leftValue->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFCmpOGT(leftValue, rightValue, "fgttmp");
            } else {
                lastValue = builder->CreateICmpSGT(leftValue, rightValue, "gttmp");
            }
            return;
        }
        if (op == ">=") {
            if (leftValue->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFCmpOGE(leftValue, rightValue, "fgetmp");
            } else {
                lastValue = builder->CreateICmpSGE(leftValue, rightValue, "getmp");
            }
            return;
        }

        lastValue = nullptr;
    }

    void IRGenerator::visitAssignmentExpression(std::shared_ptr<AssignmentExpressionNode> node) {
        std::string  idName = node->getIdentifier();
        std::string  op = node->getOp();
        llvm::Value *alloca = namedValues[idName];

        if (!alloca) {
            lastValue = nullptr;
            return;
        }

        llvm::Value *val = evaluate(node->getExpression());
        if (val) {
            // Handle type conversion
            llvm::Type *targetType = ((llvm::AllocaInst *)alloca)->getAllocatedType();

            if (op != "=") {
                // Compound assignment: Load, Op, Store
                unsigned     align = (targetType->getPrimitiveSizeInBits() == 64) ? 8 : 4;
                llvm::Value *currentVal = builder->CreateLoad(targetType, alloca, idName + ".load");
                ((llvm::LoadInst *)currentVal)->setAlignment(llvm::Align(align));

                // Handle type promotion for the operation
                if (targetType->isFloatingPointTy() || val->getType()->isFloatingPointTy()) {
                    llvm::Type *opType = (targetType->isDoubleTy() || val->getType()->isDoubleTy())
                                         ? llvm::Type::getDoubleTy(*context)
                                         : llvm::Type::getFloatTy(*context);
                    if (currentVal->getType() != opType) {
                        if (currentVal->getType()->isIntegerTy()) currentVal = builder->CreateSIToFP(currentVal, opType, "sitofp");
                        else currentVal = builder->CreateFPExt(currentVal, opType, "fpext");
                    }
                    if (val->getType() != opType) {
                        if (val->getType()->isIntegerTy()) val = builder->CreateSIToFP(val, opType, "sitofp");
                        else val = builder->CreateFPExt(val, opType, "fpext");
                    }
                } else if (val->getType()->isIntegerTy() && targetType->isIntegerTy()) {
                    unsigned valWidth = val->getType()->getIntegerBitWidth();
                    unsigned targetWidth = targetType->getIntegerBitWidth();
                    if (valWidth < targetWidth) {
                        val = builder->CreateSExt(val, targetType, "sext");
                    }
                }

                if (op == "+=") {
                    if (currentVal->getType()->isFloatingPointTy()) val = builder->CreateFAdd(currentVal, val, "faddtmp");
                    else val = builder->CreateAdd(currentVal, val, "addtmp");
                } else if (op == "-=") {
                    if (currentVal->getType()->isFloatingPointTy()) val = builder->CreateFSub(currentVal, val, "fsubtmp");
                    else val = builder->CreateSub(currentVal, val, "subtmp");
                } else if (op == "*=") {
                    if (currentVal->getType()->isFloatingPointTy()) val = builder->CreateFMul(currentVal, val, "fmultmp");
                    else val = builder->CreateMul(currentVal, val, "multmp");
                } else if (op == "/=") {
                    if (currentVal->getType()->isFloatingPointTy()) val = builder->CreateFDiv(currentVal, val, "fdivtmp");
                    else val = builder->CreateSDiv(currentVal, val, "divtmp");
                } else if (op == "%=")
                    val = builder->CreateSRem(currentVal, val, "remtmp");
                else if (op == "&=")
                    val = builder->CreateAnd(currentVal, val, "andtmp");
                else if (op == "|=")
                    val = builder->CreateOr(currentVal, val, "ortmp");
                else if (op == "^=")
                    val = builder->CreateXor(currentVal, val, "xortmp");
                else if (op == "<<=")
                    val = builder->CreateShl(currentVal, val, "shltmp");
                else if (op == ">>=")
                    val = builder->CreateAShr(currentVal, val, "ashrtmp");
            }

            // Final conversion back to target type
            if (val->getType() != targetType) {
                if (val->getType()->isIntegerTy() && targetType->isIntegerTy()) {
                    unsigned valWidth = val->getType()->getIntegerBitWidth();
                    unsigned targetWidth = targetType->getIntegerBitWidth();
                    if (valWidth < targetWidth) val = builder->CreateSExt(val, targetType, "sext");
                    else if (valWidth > targetWidth) val = builder->CreateTrunc(val, targetType, "trunc");
                } else if (val->getType()->isFloatingPointTy() && targetType->isFloatingPointTy()) {
                    if (val->getType()->getPrimitiveSizeInBits() < targetType->getPrimitiveSizeInBits())
                        val = builder->CreateFPExt(val, targetType, "fpext");
                    else val = builder->CreateFPTrunc(val, targetType, "fptrunc");
                } else if (val->getType()->isIntegerTy() && targetType->isFloatingPointTy()) {
                    val = builder->CreateSIToFP(val, targetType, "sitofp");
                } else if (val->getType()->isFloatingPointTy() && targetType->isIntegerTy()) {
                    val = builder->CreateFPToSI(val, targetType, "fptosi");
                }
            }

            auto     store = builder->CreateStore(val, alloca);
            unsigned align = (targetType->getPrimitiveSizeInBits() == 64) ? 8 : 4;
            store->setAlignment(llvm::Align(align));
            lastValue = val;
            return;
        }

        lastValue = nullptr;
    }

    void IRGenerator::visitUnaryExpression(std::shared_ptr<UnaryExpressionNode> node) {
        llvm::Value *value = evaluate(node->getExpression());
        std::string  op = node->getOp();

        if (!value) {
            lastValue = nullptr;
            return;
        }

        if (op == "!") {
            lastValue = builder->CreateNot(value, "nottmp");
            return;
        }

        if (op == "~") {
            lastValue = builder->CreateNot(value, "bitnot");
            return;
        }

        if (op == "-") {
            if (value->getType()->isFloatingPointTy()) {
                lastValue = builder->CreateFNeg(value, "fnegtmp");
            } else {
                lastValue = builder->CreateNeg(value, "negtmp");
            }
            return;
        }

        lastValue = value;
    }

    void IRGenerator::visitBooleanLiteral(std::shared_ptr<BooleanLiteralNode> node) {
        lastValue = llvm::ConstantInt::get(*context, llvm::APInt(1, node->getValue() ? 1 : 0));
    }

    // void IRGenerator::visitFloatingLiteral(std::shared_ptr<FloatingLiteralNode> node) {
    //     if (node->isFloat()) {
    //         lastValue = llvm::ConstantFP::get(*context, llvm::APFloat(node->getValue()));
    //     } else {
    //         lastValue = llvm::ConstantFP::get(*context, llvm::APFloat((double)node->getValue()));
    //     }
    // }

    void IRGenerator::visitWhileStatement(std::shared_ptr<WhileStatementNode> node) {
        llvm::Function *func = builder->GetInsertBlock()->getParent();

        llvm::BasicBlock *loopCondBB = llvm::BasicBlock::Create(*context, "while.cond", func);
        llvm::BasicBlock *loopBodyBB = llvm::BasicBlock::Create(*context, "while.body");
        llvm::BasicBlock *afterLoopBB = llvm::BasicBlock::Create(*context, "while.end");

        // Break target is after loop, Continue target is condition check
        breakTargets.push_back(afterLoopBB);
        continueTargets.push_back(loopCondBB);

        builder->CreateBr(loopCondBB);

        builder->SetInsertPoint(loopCondBB);
        llvm::Value *condValue = evaluate(node->getCondition());
        if (!condValue) {
            breakTargets.pop_back();
            continueTargets.pop_back();
            return;
        }
        builder->CreateCondBr(condValue, loopBodyBB, afterLoopBB);

        func->insert(func->end(), loopBodyBB);
        builder->SetInsertPoint(loopBodyBB);
        visit(node->getBody());

        if (!builder->GetInsertBlock()->getTerminator()) {
            builder->CreateBr(loopCondBB);
        }

        func->insert(func->end(), afterLoopBB);
        builder->SetInsertPoint(afterLoopBB);

        breakTargets.pop_back();
        continueTargets.pop_back();
    }

    void IRGenerator::visitForStatement(std::shared_ptr<ForStatementNode> node) {
        llvm::Function *func = builder->GetInsertBlock()->getParent();

        symbolTable.enterScope();

        // 1. Initializer
        if (node->getInit()) {
            visit(node->getInit());
        }

        // 2. Create blocks
        llvm::BasicBlock *loopCondBB = llvm::BasicBlock::Create(*context, "for.cond", func);
        llvm::BasicBlock *loopBodyBB = llvm::BasicBlock::Create(*context, "for.body");
        llvm::BasicBlock *loopIncBB = llvm::BasicBlock::Create(*context, "for.inc");
        llvm::BasicBlock *afterLoopBB = llvm::BasicBlock::Create(*context, "for.end");

        // Break target is after loop, Continue target is increment block
        breakTargets.push_back(afterLoopBB);
        continueTargets.push_back(loopIncBB);

        builder->CreateBr(loopCondBB);

        // 3. Condition check block
        builder->SetInsertPoint(loopCondBB);
        if (node->getCondition()) {
            llvm::Value *condValue = evaluate(node->getCondition());
            if (!condValue) {
                breakTargets.pop_back();
                continueTargets.pop_back();
                symbolTable.exitScope();
                return;
            }
            builder->CreateCondBr(condValue, loopBodyBB, afterLoopBB);
        } else {
            builder->CreateBr(loopBodyBB);
        }

        // 4. Body block
        func->insert(func->end(), loopBodyBB);
        builder->SetInsertPoint(loopBodyBB);
        visit(node->getBody());

        if (!builder->GetInsertBlock()->getTerminator()) {
            builder->CreateBr(loopIncBB);
        }

        // 5. Increment block
        func->insert(func->end(), loopIncBB);
        builder->SetInsertPoint(loopIncBB);
        if (node->getIncrement()) {
            visit(node->getIncrement());
        }
        builder->CreateBr(loopCondBB);

        // 6. End block
        func->insert(func->end(), afterLoopBB);
        builder->SetInsertPoint(afterLoopBB);

        breakTargets.pop_back();
        continueTargets.pop_back();

        symbolTable.exitScope();
    }

    void IRGenerator::visitPostfixExpression(std::shared_ptr<PostfixExpressionNode> node) {
        llvm::Value *v = namedValues[node->getVarName()];
        if (!v) {
            lastValue = nullptr;
            return;
        }

        llvm::Type *type = ((llvm::AllocaInst *)v)->getAllocatedType();
        auto        load = builder->CreateLoad(type, v, node->getVarName() + ".load");
        unsigned    align = (type->getPrimitiveSizeInBits() == 64) ? 8 : 4;
        load->setAlignment(llvm::Align(align));

        llvm::Value *oldVal = load;
        llvm::Value *newVal;
        if (node->getOp() == "++") {
            if (type->isFloatingPointTy()) {
                newVal = builder->CreateFAdd(oldVal, llvm::ConstantFP::get(type, 1.0), "inc");
            } else {
                newVal = builder->CreateAdd(oldVal, llvm::ConstantInt::get(type, 1), "inc");
            }
        } else {
            if (type->isFloatingPointTy()) {
                newVal = builder->CreateFSub(oldVal, llvm::ConstantFP::get(type, 1.0), "dec");
            } else {
                newVal = builder->CreateSub(oldVal, llvm::ConstantInt::get(type, 1), "dec");
            }
        }
        auto store = builder->CreateStore(newVal, v);
        store->setAlignment(llvm::Align(align));
        lastValue = oldVal;
    }

    void IRGenerator::visitBreakStatement(std::shared_ptr<BreakStatementNode> node) {
        if (!breakTargets.empty()) {
            builder->CreateBr(breakTargets.back());

            // Create a dead block to satisfy LLVM IR structure after terminator
            llvm::Function   *func = builder->GetInsertBlock()->getParent();
            llvm::BasicBlock *deadBB = llvm::BasicBlock::Create(*context, "break.dead", func);
            builder->SetInsertPoint(deadBB);
        }
    }

    void IRGenerator::visitContinueStatement(std::shared_ptr<ContinueStatementNode> node) {
        if (!continueTargets.empty()) {
            builder->CreateBr(continueTargets.back());

            // Create a dead block to satisfy LLVM IR structure after terminator
            llvm::Function   *func = builder->GetInsertBlock()->getParent();
            llvm::BasicBlock *deadBB = llvm::BasicBlock::Create(*context, "continue.dead", func);
            builder->SetInsertPoint(deadBB);
        }
    }
} // namespace Ryntra::Compiler
