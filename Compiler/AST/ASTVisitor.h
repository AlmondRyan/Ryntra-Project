#pragma once

#include "ASTNodes.h"
#include <any>

namespace Ryntra::Compiler {
    class IASTVisitor {
    public:
        ~IASTVisitor() = default;
        virtual std::any visit(std::shared_ptr<IASTNode> node) {
            if (!node) return nullptr;
            if (auto program = std::dynamic_pointer_cast<ProgramNode>(node)) {
                return visitProgram(program);
            }

            if (auto functionDef = std::dynamic_pointer_cast<FunctionDefinitionNode>(node)) {
                return visitFunctionDefinition(functionDef);
            }

            if (auto block = std::dynamic_pointer_cast<BlockNode>(node)) {
                return visitBlock(block);
            }

            if (auto parameter = std::dynamic_pointer_cast<ParameterNode>(node)) {
                return visitParameter(parameter);
            }

            if (auto variableDecl = std::dynamic_pointer_cast<VariableDeclarationNode>(node)) {
                return visitVariableDeclaration(variableDecl);
            }

            if (auto returnStmt = std::dynamic_pointer_cast<ReturnStatementNode>(node)) {
                return visitReturnStatement(returnStmt);
            }

            if (auto functionCallStmt = std::dynamic_pointer_cast<FunctionCallStatementNode>(node)) {
                return visitFunctionCallStatement(functionCallStmt);
            }

            if (auto functionCall = std::dynamic_pointer_cast<FunctionCallNode>(node)) {
                return visitFunctionCall(functionCall);
            }

            if (auto expressionStmt = std::dynamic_pointer_cast<ExpressionStatementNode>(node)) {
                return visitExpressionStatement(expressionStmt);
            }

            if (auto identifier = std::dynamic_pointer_cast<IdentifierNode>(node)) {
                return visitIdentifier(identifier);
            }

            if (auto intLit = std::dynamic_pointer_cast<IntegerLiteralNode>(node)) {
                return visitIntegerLiteral(intLit);
            }

            if (auto stringLit = std::dynamic_pointer_cast<StringLiteralNode>(node)) {
                return visitStringLiteral(stringLit);
            }

            if (auto emptyStmt = std::dynamic_pointer_cast<EmptyStatementNode>(node)) {
                return visitEmptyStatement(emptyStmt);
            }
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
    };
}