#pragma once

#include "AST/ASTVisitor.h"
#include "SymbolTable.h"

namespace Ryntra::Compiler {
    class SemanticAnalyzer : public IASTVisitor {
    public:
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
    private:
        SymbolTable symbolTable;
        TypeKind currentExpectedReturningType = TypeKind::Void;
        Type lastTypeResult = {TypeKind::Void, ""};

        void visit(std::shared_ptr<IASTNode> node) {
            if (node) node->accept(this);
        }

        Type evaluate(std::shared_ptr<IASTNode> node) {
            if (!node) return {TypeKind::Void, ""};
            node->accept(this);
            return lastTypeResult;
        }

        std::string mapTypeToString(TypeKind kind) {
            switch (kind) {
            case TypeKind::Int: return "int";
            case TypeKind::String: return "string";
            case TypeKind::Void: return "void";
            case TypeKind::Custom:
            default: return "custom";
            }
        }

        TypeKind mapStringToType(std::string kind) {
            if (kind == "int") return TypeKind::Int;
            if (kind == "string") return TypeKind::String;
            if (kind == "void") return TypeKind::Void;
            if (kind == "custom") return TypeKind::Custom;
        }
    };
}