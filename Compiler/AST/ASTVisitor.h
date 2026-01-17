#pragma once

#include "ASTNodes.h"
#include "Semantic/Symbol.h"
#include "AST/Nodes/Expressions.h"
#include "AST/Nodes/Statements.h"
#include "AST/Nodes/Declarations.h"
#include "AST/Nodes/Literals.h"

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
        virtual void visitFunctionCall(std::shared_ptr<FunctionCallNode> node) = 0;
        virtual void visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) = 0;
        virtual void visitIdentifier(std::shared_ptr<IdentifierNode> node) = 0;
        virtual void visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) = 0;
        virtual void visitFloatingLiteral(std::shared_ptr<FloatingLiteralNode> node) = 0;
        virtual void visitStringLiteral(std::shared_ptr<StringLiteralNode> node) = 0;
        virtual void visitBooleanLiteral(std::shared_ptr<BooleanLiteralNode> node) = 0;
        virtual void visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) = 0;
        virtual void visitIfStatement(std::shared_ptr<IfStatementNode> node) = 0;
        virtual void visitBinaryExpression(std::shared_ptr<BinaryExpressionNode> node) = 0;
        virtual void visitPostfixExpression(std::shared_ptr<PostfixExpressionNode> node) = 0;
        virtual void visitUnaryExpression(std::shared_ptr<UnaryExpressionNode> node) = 0;
        virtual void visitAssignmentExpression(std::shared_ptr<AssignmentExpressionNode> node) = 0;
        virtual void visitWhileStatement(std::shared_ptr<WhileStatementNode> node) = 0;
        virtual void visitForStatement(std::shared_ptr<ForStatementNode> node) = 0;
        virtual void visitBreakStatement(std::shared_ptr<BreakStatementNode> node) = 0;
        virtual void visitContinueStatement(std::shared_ptr<ContinueStatementNode> node) = 0;
    };
}