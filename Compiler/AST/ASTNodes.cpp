#include "ASTNodes.h"
#include "ASTVisitor.h"

namespace Ryntra::Compiler {
    std::any IntegerLiteralNode::accept(IASTVisitor *visitor) {
        return visitor->visitIntegerLiteral(std::static_pointer_cast<IntegerLiteralNode>(shared_from_this()));
    }

    std::any StringLiteralNode::accept(IASTVisitor *visitor) {
        return visitor->visitStringLiteral(std::static_pointer_cast<StringLiteralNode>(shared_from_this()));
    }

    std::any IdentifierNode::accept(IASTVisitor *visitor) {
        return visitor->visitIdentifier(std::static_pointer_cast<IdentifierNode>(shared_from_this()));
    }

    std::any FunctionCallNode::accept(IASTVisitor *visitor) {
        return visitor->visitFunctionCall(std::static_pointer_cast<FunctionCallNode>(shared_from_this()));
    }

    std::any VariableDeclarationNode::accept(IASTVisitor *visitor) {
        return visitor->visitVariableDeclaration(std::static_pointer_cast<VariableDeclarationNode>(shared_from_this()));
    }

    std::any ReturnStatementNode::accept(IASTVisitor *visitor) {
        return visitor->visitReturnStatement(std::static_pointer_cast<ReturnStatementNode>(shared_from_this()));
    }

    std::any FunctionCallStatementNode::accept(IASTVisitor *visitor) {
        return visitor->visitFunctionCallStatement(std::static_pointer_cast<FunctionCallStatementNode>(shared_from_this()));
    }

    std::any EmptyStatementNode::accept(IASTVisitor *visitor) {
        return visitor->visitEmptyStatement(std::static_pointer_cast<EmptyStatementNode>(shared_from_this()));
    }

    std::any ExpressionStatementNode::accept(IASTVisitor *visitor) {
        return visitor->visitExpressionStatement(std::static_pointer_cast<ExpressionStatementNode>(shared_from_this()));
    }

    std::any ParameterNode::accept(IASTVisitor *visitor) {
        return visitor->visitParameter(std::static_pointer_cast<ParameterNode>(shared_from_this()));
    }

    std::any BlockNode::accept(IASTVisitor *visitor) {
        return visitor->visitBlock(std::static_pointer_cast<BlockNode>(shared_from_this()));
    }

    std::any FunctionDefinitionNode::accept(IASTVisitor *visitor) {
        return visitor->visitFunctionDefinition(std::static_pointer_cast<FunctionDefinitionNode>(shared_from_this()));
    }

    std::any ProgramNode::accept(IASTVisitor *visitor) {
        return visitor->visitProgram(std::static_pointer_cast<ProgramNode>(shared_from_this()));
    }

    std::variant<int, std::string> IntegerLiteralNode::getValue() const {
        return value;
    }

    std::string IntegerLiteralNode::toString() const {
        return "IntegerLiteral(" + std::to_string(value) + ")";
    }

    std::variant<int, std::string> StringLiteralNode::getValue() const {
        return value;
    }

    std::string StringLiteralNode::toString() const {
        return "StringLiteral(" + value + ")";
    }

    std::string IdentifierNode::toString() const {
        return "Identifier(" + name + ")";
    }

    std::string FunctionCallNode::toString() const {
        std::string result = "FunctionCall(" + functionName + ", [";
        for (auto &arg : arguments) {
            result += arg->toString() + ", ";
        }

        if (!arguments.empty()) {
            result.pop_back();
            result.pop_back();
        }

        result += "])";
        return result;
    }

    std::string ProgramNode::toString() const {
        std::string result = "Program([";
        for (const auto &func : functions) {
            result += func->toString() + ", ";
        }
        if (!functions.empty()) {
            result.pop_back();
            result.pop_back();
        }
        result += "])";
        return result;
    }

    std::string FunctionDefinitionNode::toString() const {
        std::string result = "FunctionDef(" + returnType + " " + functionName + "(";
        for (const auto &param : parameters) {
            result += param->toString() + ", ";
        }
        if (!parameters.empty()) {
            result.pop_back();
            result.pop_back();
        }
        result += "), " + body->toString() + ")";
        return result;
    }

    std::string BlockNode::toString() const {
        std::string result = "Block([";
        for (auto &stmt : statements) {
            result += stmt->toString() + ", ";
        }

        if (!statements.empty()) {
            result.pop_back();
            result.pop_back();
        }
        result += "])";
        return result;
    }

    std::string VariableDeclarationNode::toString() const {
        if (initialValue) {
            return "VariableDeclaration(" + varType + " " + varName + ", " + initialValue->toString() + ")";
        }
        return "VariableDeclaration(" + varType + " " + varName + ")";
    }

    std::string BinaryExpressionNode::toString() const {
        return "BinaryExpression(" + left->toString() + ", " + operand + ", " + right->toString() + ")";
    }

    std::any BinaryExpressionNode::accept(IASTVisitor *visitor) {
        return visitor->visitBinaryExpression(std::static_pointer_cast<BinaryExpressionNode>(shared_from_this()));
    }

    std::any AssignmentExpressionNode::accept(IASTVisitor *visitor) {
        return visitor->visitAssignmentExpression(std::static_pointer_cast<AssignmentExpressionNode>(shared_from_this()));
    }

    std::string AssignmentExpressionNode::toString() const {
        return "AssignmentExpression(" + identifier + ", " + expression->toString() + ")";
    }
} // namespace Ryntra::Compiler
