#pragma once

#include "AST/ASTVisitor.h"
#include "SymbolTable.h"
#include <unordered_map>

namespace Ryntra::Compiler {
    class SemanticAnalyzer : public IASTVisitor {
    public:
        void visitProgram(std::shared_ptr<ProgramNode> node) override;
        void visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) override;

        void visitBlock(std::shared_ptr<BlockNode> node) override;
        void visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) override;
        void visitIfStatement(std::shared_ptr<IfStatementNode> node) override;
        void visitFunctionCall(std::shared_ptr<FunctionCallNode> node) override;
        void visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) override;
        void visitIdentifier(std::shared_ptr<IdentifierNode> node) override;
        void visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) override;
        void visitParameter(std::shared_ptr<ParameterNode> node) override;
        void visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) override;
        void visitStringLiteral(std::shared_ptr<StringLiteralNode> node) override;
        void visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) override;
        void visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) override;

        void visitAssignmentExpression(std::shared_ptr<AssignmentExpressionNode> node) override;
        void visitBinaryExpression(std::shared_ptr<BinaryExpressionNode> node) override;

        void visitBooleanLiteral(std::shared_ptr<BooleanLiteralNode> node) override;
        void visitUnaryExpression(std::shared_ptr<UnaryExpressionNode> node) override;

        void visitWhileStatement(std::shared_ptr<WhileStatementNode> node) override;
        void visitForStatement(std::shared_ptr<ForStatementNode> node) override;
        void visitPostfixExpression(std::shared_ptr<PostfixExpressionNode> node) override;

        void visitBreakStatement(std::shared_ptr<BreakStatementNode> node) override;
        void visitContinueStatement(std::shared_ptr<ContinueStatementNode> node) override;

        Type getType(std::shared_ptr<IASTNode> node) {
            if (nodeTypes.find(node) != nodeTypes.end()) {
                return nodeTypes[node];
            }
            return {TypeKind::Void, ""};
        }

    private:
        SymbolTable symbolTable;
        TypeKind currentExpectedReturningType = TypeKind::Void;
        Type lastTypeResult = {TypeKind::Void, ""};
        std::unordered_map<std::shared_ptr<IASTNode>, Type> nodeTypes;
        int loopDepth = 0;

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
            case TypeKind::Long: return "long";
            case TypeKind::LongLong: return "long long";
            case TypeKind::String: return "string";
            case TypeKind::Void: return "void";
            case TypeKind::Boolean: return "bool";
            case TypeKind::Custom:
            default: return "custom";
            }
        }

        TypeKind mapStringToType(std::string kind) {
            if (kind == "int") return TypeKind::Int;
            if (kind == "long") return TypeKind::Long;
            if (kind == "long long") return TypeKind::LongLong;
            if (kind == "string") return TypeKind::String;
            if (kind == "void") return TypeKind::Void;
            if (kind == "bool") return TypeKind::Boolean;
            if (kind == "custom") return TypeKind::Custom;
            return TypeKind::ErrorType;
        }
    };
}