#pragma once

#include "AST/ASTVisitor.h"
#include "Semantic/SymbolTable.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

namespace Ryntra::Compiler {
    class IRGenerator : public IASTVisitor {
    public:
        IRGenerator();
        void visitProgram(std::shared_ptr<ProgramNode> node) override;
        void visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) override;
        void visitBlock(std::shared_ptr<BlockNode> node) override;
        void visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) override;
        void visitIfStatement(std::shared_ptr<IfStatementNode> node) override;
        Type visitFunctionCall(std::shared_ptr<FunctionCallNode> node) override;
        void visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) override;
        Type visitIdentifier(std::shared_ptr<IdentifierNode> node) override;
        Type visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) override;
        void visitParameter(std::shared_ptr<ParameterNode> node) override;
        void visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) override;
        Type visitStringLiteral(std::shared_ptr<StringLiteralNode> node) override;
        void visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) override;
        void visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) override;

        Type visitAssignmentExpression(std::shared_ptr<AssignmentExpressionNode> node) override;
        Type visitBinaryExpression(std::shared_ptr<BinaryExpressionNode> node) override;

        [[nodiscard]] std::string getIR() const;

        Type visitBooleanLiteral(std::shared_ptr<BooleanLiteralNode> node) override;
        Type visitUnaryExpression(std::shared_ptr<UnaryExpressionNode> node) override;

        void visitWhileStatement(std::shared_ptr<WhileStatementNode> node) override;
        void visitForStatement(std::shared_ptr<ForStatementNode> node) override;
        Type visitPostfixExpression(std::shared_ptr<PostfixExpressionNode> node) override;
    private:
        std::unique_ptr<llvm::LLVMContext>   context;
        std::unique_ptr<llvm::Module>        module;
        std::unique_ptr<llvm::IRBuilder<>>   builder;
        SymbolTable                          symbolTable;
        std::map<std::string, llvm::Value *> namedValues;

        llvm::Value *lastValue = nullptr;

        void visit(std::shared_ptr<IASTNode> node) {
            if (node)
                node->accept(this);
        }

        llvm::Value *evaluate(std::shared_ptr<IASTNode> node) {
            if (!node)
                return nullptr;
            node->accept(this);
            return lastValue;
        }
    };
} // namespace Ryntra::Compiler