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

    std::any IRGenerator::visitProgram(std::shared_ptr<ProgramNode> node) {
        for (auto i : node->getFunctions()) {
            visit(i);
        }
        return {};
    }

    namespace {
        llvm::Type* mapType(llvm::LLVMContext& context, const std::string& typeName) {
            if (typeName == "int") return llvm::Type::getInt32Ty(context);
            if (typeName == "string") return llvm::PointerType::get(context, 0);
            if (typeName == "void") return llvm::Type::getVoidTy(context);
            return llvm::Type::getVoidTy(context);
        }
    }

    std::any IRGenerator::visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) {
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

        return func;
    }

    std::any IRGenerator::visitBlock(std::shared_ptr<BlockNode> node) {
        for (auto& stmt : node->getStatements()) {
            visit(stmt);
        }
        return {};
    }

    std::any IRGenerator::visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) {
        return {};
    }

    std::any IRGenerator::visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) {
        return visit(node->getExpression());
    }

    std::any IRGenerator::visitFunctionCall(std::shared_ptr<FunctionCallNode> node) {
        std::string funcName = node->getFunctionName();
        
        // 1. Symbol Table Lookup
        if (symbolTable.lookupFunction(funcName)) {
            // 2. Builtin Handling
            if (funcName == "__builtin_print") {
                // Declare printf if not exists: int printf(i8*, ...)
                std::vector<llvm::Type*> argsTypes;
                // argsTypes.push_back(llvm::Type::getInt8PtrTy(*context)); // char*
                argsTypes.push_back(llvm::PointerType::get(*context, 0));

                llvm::FunctionType* printfType = llvm::FunctionType::get(
                    llvm::Type::getInt32Ty(*context), // return int
                    argsTypes,
                    true // varargs
                );
                
                llvm::FunctionCallee printfFunc = module->getOrInsertFunction("printf", printfType);
                
                std::vector<llvm::Value*> args;
                for (auto arg : node->getArguments()) {
                    std::any argVal = visit(arg);
                    if (argVal.has_value()) {
                        try {
                            args.push_back(std::any_cast<llvm::Value*>(argVal));
                        } catch (const std::bad_any_cast&) {
                            // Should not happen if Semantic Analysis passed
                        }
                    }
                }
                
                if (!args.empty()) {
                     return (llvm::Value*)builder->CreateCall(printfFunc, args);
                }
            } else {
                // Non-builtin function lookup in Module
                llvm::Function* callee = module->getFunction(funcName);
                if (callee) {
                    std::vector<llvm::Value*> args;
                    for (auto argNode : node->getArguments()) {
                        std::any argVal = visit(argNode);
                        if (argVal.has_value()) {
                            args.push_back(std::any_cast<llvm::Value*>(argVal));
                        }
                    }
                    return (llvm::Value*)builder->CreateCall(callee, args);
                }
            }
        }
        return {};
    }

    std::any IRGenerator::visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) {
        return visit(node->getFunctionCall());
    }

    std::any IRGenerator::visitIdentifier(std::shared_ptr<IdentifierNode> node) {
        llvm::Value* v = namedValues[node->getName()];
        if (!v) return {};
        return (llvm::Value*)builder->CreateLoad(((llvm::AllocaInst*)v)->getAllocatedType(), v, node->getName());
    }

    std::any IRGenerator::visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) {
        return (llvm::Value*)llvm::ConstantInt::get(*context, llvm::APInt(32, std::get<int>(node->getValue())));
    }

    std::any IRGenerator::visitParameter(std::shared_ptr<ParameterNode> node) {
        return {};
    }

    std::any IRGenerator::visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) {
        std::any val = visit(node->getReturnValue());
        if (val.has_value()) {
            return (llvm::Value*)builder->CreateRet(std::any_cast<llvm::Value*>(val));
        }
        return (llvm::Value*)builder->CreateRetVoid();
    }

    std::any IRGenerator::visitStringLiteral(std::shared_ptr<StringLiteralNode> node) {
        return (llvm::Value*)builder->CreateGlobalStringPtr(std::get<std::string>(node->getValue()));
    }

    std::any IRGenerator::visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) {
        std::any initVal = visit(node->getInitialValue());
        llvm::Value* val = nullptr;
        if (initVal.has_value()) {
            val = std::any_cast<llvm::Value*>(initVal);
        }

        // Default to int for now as we don't have type info in VariableDeclarationNode yet
        llvm::Type* type = val ? val->getType() : llvm::Type::getInt32Ty(*context);
        llvm::AllocaInst* alloca = builder->CreateAlloca(type, nullptr, node->getVarName());
        
        if (val) {
            builder->CreateStore(val, alloca);
        }
        
        namedValues[node->getVarName()] = alloca;
        return (llvm::Value*)alloca;
    }
}
