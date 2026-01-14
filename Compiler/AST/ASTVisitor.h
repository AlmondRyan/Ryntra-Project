#pragma once

#include "ASTNodes.h"
#include "Semantic/Symbol.h"

namespace Ryntra::Compiler {
    class IASTVisitor {
    public:
        virtual ~IASTVisitor() = default;

        virtual void visitProgram(std::shared_ptr<ProgramNode> node) = 0;
        virtual void visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) = 0;
        virtual void visitBlock(std::shared_ptr<BlockNode> node) = 0;
        virtual void visitParameter(std::shared_ptr<ParameterNode> node) = 0;
        virtual void visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) = 0;
        virtual void visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) = 0;
        virtual void visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) = 0;
        virtual Type visitFunctionCall(std::shared_ptr<FunctionCallNode> node) = 0;
        virtual void visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) = 0;
        virtual Type visitIdentifier(std::shared_ptr<IdentifierNode> node) = 0;
        virtual Type visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) = 0;
        virtual Type visitStringLiteral(std::shared_ptr<StringLiteralNode> node) = 0;
        virtual void visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) = 0;
        virtual void visitIfStatement(std::shared_ptr<IfStatementNode> node) = 0;
        virtual Type visitBinaryExpression(std::shared_ptr<BinaryExpressionNode> node) = 0;
        virtual Type visitAssignmentExpression(std::shared_ptr<AssignmentExpressionNode> node) = 0;
    };
}