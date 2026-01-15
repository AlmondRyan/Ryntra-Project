#include "IRGenerator/IRGenerator.h"

#include <iostream>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <vector>

namespace Ryntra::Compiler {

    IRGenerator::IRGenerator() 
        : context(std::make_unique<llvm::LLVMContext>()),
          module(std::make_unique<llvm::Module>("RyntraModule", *context)),
          builder(std::make_unique<llvm::IRBuilder<>>(*context)) {
    }

    std::string IRGenerator::getIR() const {
        std::string str;
        llvm::raw_string_ostream os(str);
        module->print(os, nullptr);
        return str;
    }

    void IRGenerator::visitProgram(std::shared_ptr<ProgramNode> node) {
        for (auto i : node->getFunctions()) {
            visit(i);
        }
    }

    namespace {
        llvm::Type* mapType(llvm::LLVMContext& context, const std::string& typeName) {
            if (typeName == "int") return llvm::Type::getInt32Ty(context);
            if (typeName == "string") return llvm::PointerType::get(context, 0);
            if (typeName == "void") return llvm::Type::getVoidTy(context);
            if (typeName == "bool") return llvm::Type::getInt1Ty(context);
            return llvm::Type::getVoidTy(context);
        }
    }

    void IRGenerator::visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) {
        // 1. Prepare parameter types
        std::vector<llvm::Type*> paramTypes;
        for (const auto& param : node->getParameters()) {
            paramTypes.push_back(mapType(*context, param->getType()));
        }

        // 2. Create Function Type and Function
        llvm::FunctionType* funcType = llvm::FunctionType::get(
            mapType(*context, node->getReturnType()),
            paramTypes,
            false
        );

        llvm::Function* func = llvm::Function::Create(
            funcType,
            llvm::Function::ExternalLinkage,
            node->getFunctionName(),
            module.get()
        );

        // 3. Create Entry Basic Block
        llvm::BasicBlock* entryBB = llvm::BasicBlock::Create(*context, "entry", func);
        builder->SetInsertPoint(entryBB);

        // 4. Handle Parameters (Allocation and Storage)
        symbolTable.enterScope();
        namedValues.clear();
        unsigned idx = 0;
        for (auto& arg : func->args()) {
            auto paramNode = node->getParameters()[idx++];
            arg.setName(paramNode->getName());
            
            // Create alloca for parameter
            llvm::AllocaInst* alloca = builder->CreateAlloca(arg.getType(), nullptr, paramNode->getName() + ".addr");
            builder->CreateStore(&arg, alloca);
            
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
            }
        }
    }

    void IRGenerator::visitBlock(std::shared_ptr<BlockNode> node) {
        for (auto& stmt : node->getStatements()) {
            visit(stmt);
        }
    }

    void IRGenerator::visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) {
    }

    void IRGenerator::visitIfStatement(std::shared_ptr<IfStatementNode> node) {
        llvm::Value* condValue = evaluate(node->getCondition());
        if (!condValue) return;

        llvm::Function* func = builder->GetInsertBlock()->getParent();

        llvm::BasicBlock* thenBB = llvm::BasicBlock::Create(*context, "then", func);
        llvm::BasicBlock* elseBB = llvm::BasicBlock::Create(*context, "else");
        llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(*context, "ifcont");

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
                std::vector<llvm::Type*> argsTypes;
                argsTypes.push_back(llvm::PointerType::get(*context, 0));

                llvm::FunctionType* printfType = llvm::FunctionType::get(
                    llvm::Type::getInt32Ty(*context), // return int
                    argsTypes,
                    true // varargs
                );
                
                llvm::FunctionCallee printfFunc = module->getOrInsertFunction("printf", printfType);
                
                std::vector<llvm::Value*> args;
                std::vector<llvm::Value*> stringsToFree; // Track temporary strings from intToString
                
                for (auto argNode : node->getArguments()) {
                    // Check if this argument is a call to __builtin_intToString
                    bool isTempString = false;
                    if (auto callNode = std::dynamic_pointer_cast<FunctionCallNode>(argNode)) {
                        if (callNode->getFunctionName() == "__builtin_intToString") {
                            isTempString = true;
                        }
                    }

                    llvm::Value* val = evaluate(argNode);
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
                         llvm::FunctionType* freeType = llvm::FunctionType::get(
                             llvm::Type::getVoidTy(*context),
                             {llvm::PointerType::get(*context, 0)},
                             false
                         );
                         llvm::FunctionCallee freeFunc = module->getOrInsertFunction("rcrt_builtin_free", freeType);
                         for (auto strPtr : stringsToFree) {
                             builder->CreateCall(freeFunc, {strPtr});
                         }
                     }
                     return;
                }
            } else if (funcName == "__builtin_intToString") {
                // Declare rcrt_builtin_intToString if not exists: char* rcrt_builtin_intToString(int)
                std::vector<llvm::Type*> argsTypes;
                argsTypes.push_back(llvm::Type::getInt32Ty(*context));

                llvm::FunctionType* toStringType = llvm::FunctionType::get(
                    llvm::PointerType::get(*context, 0), // return char*
                    argsTypes,
                    false
                );
                
                llvm::FunctionCallee toStringFunc = module->getOrInsertFunction("rcrt_builtin_intToString", toStringType);
                
                std::vector<llvm::Value*> args;
                for (auto arg : node->getArguments()) {
                    llvm::Value* val = evaluate(arg);
                    if (val) {
                        args.push_back(val);
                    }
                }
                
                lastValue = builder->CreateCall(toStringFunc, args);
                return;
            } else {
                // Non-builtin function lookup in Module
                llvm::Function* callee = module->getFunction(funcName);
                if (callee) {
                    std::vector<llvm::Value*> args;
                    for (auto argNode : node->getArguments()) {
                        llvm::Value* val = evaluate(argNode);
                        if (val) {
                            args.push_back(val);
                        }
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
        llvm::Value* v = namedValues[node->getName()];
        if (!v) {
            lastValue = nullptr;
            return;
        }
        lastValue = builder->CreateLoad(((llvm::AllocaInst*)v)->getAllocatedType(), v, node->getName());
    }

    void IRGenerator::visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) {
        lastValue = llvm::ConstantInt::get(*context, llvm::APInt(32, node->getValue()));
    }

    void IRGenerator::visitParameter(std::shared_ptr<ParameterNode> node) {
    }

    void IRGenerator::visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) {
        llvm::Value* val = evaluate(node->getReturnValue());
        if (val) {
            builder->CreateRet(val);
        } else {
            builder->CreateRetVoid();
        }
    }

    void IRGenerator::visitStringLiteral(std::shared_ptr<StringLiteralNode> node) {
        lastValue = builder->CreateGlobalStringPtr(node->getValue());
    }

    void IRGenerator::visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) {
        llvm::Value* val = evaluate(node->getInitialValue());

        llvm::Type* type = mapType(*context, node->getVarType());
        llvm::AllocaInst* alloca = builder->CreateAlloca(type, nullptr, node->getVarName());

        if (val) {
            builder->CreateStore(val, alloca);
        }

        namedValues[node->getVarName()] = alloca;
    }

    void IRGenerator::visitBinaryExpression(std::shared_ptr<BinaryExpressionNode> node) {
        std::string op = node->getOp();

        // Handle logical AND/OR with short-circuiting
        if (op == "&&") {
            llvm::Value* lhsValue = evaluate(node->getLeft());
            llvm::Function* func = builder->GetInsertBlock()->getParent();
            
            llvm::BasicBlock* rhsBB = llvm::BasicBlock::Create(*context, "and.rhs", func);
            llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(*context, "and.merge", func);
            
            llvm::BasicBlock* entryBB = builder->GetInsertBlock();
            builder->CreateCondBr(lhsValue, rhsBB, mergeBB);
            
            builder->SetInsertPoint(rhsBB);
            llvm::Value* rhsValue = evaluate(node->getRight());
            llvm::BasicBlock* rhsEndBB = builder->GetInsertBlock();
            builder->CreateBr(mergeBB);
            
            builder->SetInsertPoint(mergeBB);
            llvm::PHINode* phi = builder->CreatePHI(llvm::Type::getInt1Ty(*context), 2, "andtmp");
            phi->addIncoming(llvm::ConstantInt::getFalse(*context), entryBB);
            phi->addIncoming(rhsValue, rhsEndBB);
            
            lastValue = phi;
            return;
        }

        if (op == "||") {
            llvm::Value* lhsValue = evaluate(node->getLeft());
            llvm::Function* func = builder->GetInsertBlock()->getParent();
            
            llvm::BasicBlock* rhsBB = llvm::BasicBlock::Create(*context, "or.rhs", func);
            llvm::BasicBlock* mergeBB = llvm::BasicBlock::Create(*context, "or.merge", func);
            
            llvm::BasicBlock* entryBB = builder->GetInsertBlock();
            builder->CreateCondBr(lhsValue, mergeBB, rhsBB);
            
            builder->SetInsertPoint(rhsBB);
            llvm::Value* rhsValue = evaluate(node->getRight());
            llvm::BasicBlock* rhsEndBB = builder->GetInsertBlock();
            builder->CreateBr(mergeBB);
            
            builder->SetInsertPoint(mergeBB);
            llvm::PHINode* phi = builder->CreatePHI(llvm::Type::getInt1Ty(*context), 2, "ortmp");
            phi->addIncoming(llvm::ConstantInt::getTrue(*context), entryBB);
            phi->addIncoming(rhsValue, rhsEndBB);
            
            lastValue = phi;
            return;
        }

        llvm::Value *leftValue = evaluate(node->getLeft());
        llvm::Value *rightValue = evaluate(node->getRight());

        if (op == "+") {
            lastValue = builder->CreateAdd(leftValue, rightValue, "addTemp");
            return;
        }
        if (op == "-") {
            lastValue = builder->CreateSub(leftValue, rightValue, "subTemp");
            return;
        }
        if (op == "*") {
            lastValue = builder->CreateMul(leftValue, rightValue, "mulTemp");
            return;
        }
        if (op == "/") {
            lastValue = builder->CreateSDiv(leftValue, rightValue, "subDiv");
            return;
        }

        // Comparison operators
        if (op == "==") {
            lastValue = builder->CreateICmpEQ(leftValue, rightValue, "eqtmp");
            return;
        }
        if (op == "!=") {
            lastValue = builder->CreateICmpNE(leftValue, rightValue, "netmp");
            return;
        }
        if (op == "<") {
            lastValue = builder->CreateICmpSLT(leftValue, rightValue, "lttmp");
            return;
        }
        if (op == "<=") {
            lastValue = builder->CreateICmpSLE(leftValue, rightValue, "letmp");
            return;
        }
        if (op == ">") {
            lastValue = builder->CreateICmpSGT(leftValue, rightValue, "gttmp");
            return;
        }
        if (op == ">=") {
            lastValue = builder->CreateICmpSGE(leftValue, rightValue, "getmp");
            return;
        }

        lastValue = nullptr;
    }

    void IRGenerator::visitAssignmentExpression(std::shared_ptr<AssignmentExpressionNode> node) {
        std::string idName = node->getIdentifier();
        llvm::Value* alloca = namedValues[idName];
        
        if (!alloca) {
            lastValue = nullptr;
            return;
        }

        llvm::Value* val = evaluate(node->getExpression());
        if (val) {
            builder->CreateStore(val, alloca);
            lastValue = val;
            return;
        }

        lastValue = nullptr;
    }

    void IRGenerator::visitUnaryExpression(std::shared_ptr<UnaryExpressionNode> node) {
        llvm::Value* value = evaluate(node->getExpression());
        std::string op = node->getOp();

        if (!value) {
            lastValue = nullptr;
            return;
        }

        if (op == "!") {
            lastValue = builder->CreateNot(value, "nottmp");
            return;
        }

        if (op == "-") {
            llvm::Value* zero = llvm::ConstantInt::get(*context, llvm::APInt(32, 0));
            lastValue = builder->CreateSub(zero, value, "negtmp");
            return;
        }

        lastValue = value;
    }

    void IRGenerator::visitBooleanLiteral(std::shared_ptr<BooleanLiteralNode> node) {
        lastValue = llvm::ConstantInt::get(*context, llvm::APInt(1, node->getValue() ? 1 : 0));
    }

    void IRGenerator::visitWhileStatement(std::shared_ptr<WhileStatementNode> node) {
        llvm::Function* func = builder->GetInsertBlock()->getParent();

        llvm::BasicBlock* loopCondBB = llvm::BasicBlock::Create(*context, "while.cond", func);
        llvm::BasicBlock* loopBodyBB = llvm::BasicBlock::Create(*context, "while.body");
        llvm::BasicBlock* afterLoopBB = llvm::BasicBlock::Create(*context, "while.end");

        builder->CreateBr(loopCondBB);

        builder->SetInsertPoint(loopCondBB);
        llvm::Value* condValue = evaluate(node->getCondition());
        if (!condValue) return;
        builder->CreateCondBr(condValue, loopBodyBB, afterLoopBB);

        func->insert(func->end(), loopBodyBB);
        builder->SetInsertPoint(loopBodyBB);
        visit(node->getBody());
        
        if (!builder->GetInsertBlock()->getTerminator()) {
            builder->CreateBr(loopCondBB);
        }

        func->insert(func->end(), afterLoopBB);
        builder->SetInsertPoint(afterLoopBB);
    }

    void IRGenerator::visitForStatement(std::shared_ptr<ForStatementNode> node) {
        llvm::Function* func = builder->GetInsertBlock()->getParent();

        symbolTable.enterScope();

        // 1. Initializer
        if (node->getInit()) {
            visit(node->getInit());
        }

        // 2. Create blocks
        llvm::BasicBlock* loopCondBB = llvm::BasicBlock::Create(*context, "for.cond", func);
        llvm::BasicBlock* loopBodyBB = llvm::BasicBlock::Create(*context, "for.body");
        llvm::BasicBlock* loopIncBB = llvm::BasicBlock::Create(*context, "for.inc");
        llvm::BasicBlock* afterLoopBB = llvm::BasicBlock::Create(*context, "for.end");

        builder->CreateBr(loopCondBB);

        // 3. Condition check block
        builder->SetInsertPoint(loopCondBB);
        if (node->getCondition()) {
            llvm::Value* condValue = evaluate(node->getCondition());
            if (!condValue) return;
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

        symbolTable.exitScope();
    }

    void IRGenerator::visitPostfixExpression(std::shared_ptr<PostfixExpressionNode> node) {
        llvm::Value* v = namedValues[node->getVarName()];
        if (!v) {
            lastValue = nullptr;
            return;
        }

        llvm::Value* oldVal = builder->CreateLoad(((llvm::AllocaInst*)v)->getAllocatedType(), v, node->getVarName() + ".load");
        llvm::Value* newVal;
        if (node->getOp() == "++") {
            newVal = builder->CreateAdd(oldVal, llvm::ConstantInt::get(*context, llvm::APInt(32, 1)), "inc");
        } else {
            newVal = builder->CreateSub(oldVal, llvm::ConstantInt::get(*context, llvm::APInt(32, 1)), "dec");
        }
        builder->CreateStore(newVal, v);
        lastValue = oldVal;
    }
} // namespace Ryntra::Compiler
