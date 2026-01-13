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

    void IRGenerator::visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) {
        visit(node->getExpression());
    }

    Type IRGenerator::visitFunctionCall(std::shared_ptr<FunctionCallNode> node) {
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
                     return {TypeKind::Int, ""};
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
                return {TypeKind::String, ""};
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
                    return {TypeKind::Custom, ""}; // Need actual return type here, but TypeKind::Custom is a placeholder
                }
            }
        }
        lastValue = nullptr;
        return {TypeKind::Void, ""};
    }

    void IRGenerator::visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) {
        visit(node->getFunctionCall());
    }

    Type IRGenerator::visitIdentifier(std::shared_ptr<IdentifierNode> node) {
        llvm::Value* v = namedValues[node->getName()];
        if (!v) {
            lastValue = nullptr;
            return {TypeKind::Void, ""};
        }
        lastValue = builder->CreateLoad(((llvm::AllocaInst*)v)->getAllocatedType(), v, node->getName());
        return {TypeKind::Custom, ""}; // Placeholder
    }

    Type IRGenerator::visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) {
        lastValue = llvm::ConstantInt::get(*context, llvm::APInt(32, node->getValue()));
        return {TypeKind::Int, ""};
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

    Type IRGenerator::visitStringLiteral(std::shared_ptr<StringLiteralNode> node) {
        lastValue = builder->CreateGlobalStringPtr(node->getValue());
        return {TypeKind::String, ""};
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

    Type IRGenerator::visitBinaryExpression(std::shared_ptr<BinaryExpressionNode> node) {
        llvm::Value *leftValue = evaluate(node->getLeft());
        llvm::Value *rightValue = evaluate(node->getRight());
        std::string op = node->getOp();

        if (op == "+") lastValue = builder->CreateAdd(leftValue, rightValue, "addTemp");
        if (op == "-") lastValue = builder->CreateSub(leftValue, rightValue, "subTemp");
        if (op == "*") lastValue = builder->CreateMul(leftValue, rightValue, "mulTemp");
        if (op == "/") lastValue = builder->CreateSDiv(leftValue, rightValue, "subDiv");

        return {TypeKind::Int, ""};
    }

    Type IRGenerator::visitAssignmentExpression(std::shared_ptr<AssignmentExpressionNode> node) {
        std::string idName = node->getIdentifier();
        llvm::Value* alloca = namedValues[idName];
        
        if (!alloca) {
            // This should be handled by semantic analyzer
            lastValue = nullptr;
            return {TypeKind::Void, ""};
        }

        llvm::Value* val = evaluate(node->getExpression());
        if (val) {
            builder->CreateStore(val, alloca);
            lastValue = val;
            return {TypeKind::Custom, ""}; // Placeholder
        }

        lastValue = nullptr;
        return {TypeKind::Void, ""};
    }
} // namespace Ryntra::Compiler
