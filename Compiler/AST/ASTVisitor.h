#pragma once

#include "ASTNodes.h"
#include <any>

namespace Ryntra::Compiler {
    class IASTVisitor {
    public:
        ~IASTVisitor() = default;
        virtual std::any visit(std::shared_ptr<IASTNode> node) {
            if (!node) return std::any();
            return node->accept(this);
        }

        virtual std::any visitProgram(std::shared_ptr<ProgramNode> node) = 0;
        virtual std::any visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) = 0;
        virtual std::any visitBlock(std::shared_ptr<BlockNode> node) = 0;
        virtual std::any visitParameter(std::shared_ptr<ParameterNode> node) = 0;
        virtual std::any visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) = 0;
        virtual std::any visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) = 0;
        virtual std::any visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) = 0;
        virtual std::any visitFunctionCall(std::shared_ptr<FunctionCallNode> node) = 0;
        virtual std::any visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) = 0;
        virtual std::any visitIdentifier(std::shared_ptr<IdentifierNode> node) = 0;
        virtual std::any visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) = 0;
        virtual std::any visitStringLiteral(std::shared_ptr<StringLiteralNode> node) = 0;
        virtual std::any visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) = 0;
        virtual std::any visitBinaryExpression(std::shared_ptr<BinaryExpressionNode> node) = 0;
        virtual std::any visitAssignmentExpression(std::shared_ptr<AssignmentExpressionNode> node) = 0;
    };
}