#pragma once

#include "AST/ASTVisitor.h"
#include "Semantic/SymbolTable.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"

namespace Ryntra::Compiler {
    class IRGenerator : public IASTVisitor {
    public:
        IRGenerator();
        std::any visitProgram(std::shared_ptr<ProgramNode> node) override;
        std::any visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) override;
        std::any visitBlock(std::shared_ptr<BlockNode> node) override;
        std::any visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) override;
        std::any visitFunctionCall(std::shared_ptr<FunctionCallNode> node) override;
        std::any visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) override;
        std::any visitIdentifier(std::shared_ptr<IdentifierNode> node) override;
        std::any visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) override;
        std::any visitParameter(std::shared_ptr<ParameterNode> node) override;
        std::any visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) override;
        std::any visitStringLiteral(std::shared_ptr<StringLiteralNode> node) override;
        std::any visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) override;
        std::any visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) override;

        std::string getIR() const;
    private:
        std::unique_ptr<llvm::LLVMContext> context;
        std::unique_ptr<llvm::Module> module;
        std::unique_ptr<llvm::IRBuilder<>> builder;
        SymbolTable symbolTable;
        std::map<std::string, llvm::Value*> namedValues;
    };
}