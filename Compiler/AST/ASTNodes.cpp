#include "ASTNodes.h"
#include <sstream>

namespace Ryntra::Compiler {
    void TypeSpecifierNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<TypeSpecifierNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string TypeSpecifierNode::toString() const {
        return "(TypeSpecifier " + name + ")";
    }

    void BoolLiteralNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<BoolLiteralNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string BoolLiteralNode::toString() const {
        return value ? "(BoolLiteral true)" : "(BoolLiteral false)";
    }

    void StringLiteralNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<StringLiteralNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string StringLiteralNode::toString() const {
        return "(StringLiteral \"" + value + "\")";
    }

    void IntegerLiteralNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<IntegerLiteralNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string IntegerLiteralNode::toString() const {
        return "(IntegerLiteral " + std::to_string(value) + ")";
    }

    void LongLiteralNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<LongLiteralNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string LongLiteralNode::toString() const {
        return "(LongLiteral " + std::to_string(value) + ")";
    }

    void IdentifierNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<IdentifierNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string IdentifierNode::toString() const {
        return "(Identifier " + name + ")";
    }

    void FunctionCallNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<FunctionCallNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string FunctionCallNode::toString() const {
        std::stringstream ss;
        ss << "(FunctionCall " << functionName->toString();
        for (const auto &arg : arguments) {
            ss << " " << arg->toString();
        }
        ss << ")";
        return ss.str();
    }

    void ExpressionStatementNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<ExpressionStatementNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string ExpressionStatementNode::toString() const {
        return "(ExpressionStatement " + expression->toString() + ")";
    }

    void ReturnNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<ReturnNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string ReturnNode::toString() const {
        return "(Return " + value->toString() + ")";
    }

    void BlockNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<BlockNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string BlockNode::toString() const {
        std::stringstream ss;
        ss << "(Block";
        for (const auto &stmt : statements) {
            ss << " " << stmt->toString();
        }
        ss << ")";
        return ss.str();
    }

    void FunctionDefinitionNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<FunctionDefinitionNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string FunctionDefinitionNode::toString() const {
        return "(FunctionDefinition " + returnType->toString() + " " + name->toString() + " " + body->toString() + ")";
    }

    void ProgramNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<ProgramNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string ProgramNode::toString() const {
        std::stringstream ss;
        ss << "(Program";
        for (const auto &func : functions) {
            ss << " " << func->toString();
        }
        ss << ")";
        return ss.str();
    }

    void VariableDeclarationNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<VariableDeclarationNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string VariableDeclarationNode::toString() const {
        std::stringstream ss;
        ss << "(VariableDeclaration " << type->toString() << " " << name->toString();
        if (initializer) {
            ss << " " << initializer->toString();
        }
        ss << ")";
        return ss.str();
    }

    void VariableNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<VariableNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string VariableNode::toString() const {
        return "(Variable " + name->toString() + ")";
    }

    void BinaryOpNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<BinaryOpNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string BinaryOpNode::toString() const {
        std::string opStr;
        switch (op) {
        case BinaryOpType::Add:
            opStr = "+";
            break;
        case BinaryOpType::Sub:
            opStr = "-";
            break;
        case BinaryOpType::Mul:
            opStr = "*";
            break;
        case BinaryOpType::Div:
            opStr = "/";
            break;
        case BinaryOpType::Mod:
            opStr = "%";
            break;
        case BinaryOpType::BitAnd:
            opStr = "&";
            break;
        case BinaryOpType::BitOr:
            opStr = "|";
            break;
        case BinaryOpType::BitXor:
            opStr = "^";
            break;
        case BinaryOpType::Shl:
            opStr = "<<";
            break;
        case BinaryOpType::Shr:
            opStr = ">>";
            break;
        }
        return "(BinaryOp " + left->toString() + " " + opStr + " " + right->toString() + ")";
    }

    void UnaryOpNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<UnaryOpNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string UnaryOpNode::toString() const {
        std::string opStr;
        switch (op) {
        case UnaryOpType::BitNot:
            opStr = "~";
            break;
        }
        return "(UnaryOp " + opStr + " " + operand->toString() + ")";
    }

    void CastNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<CastNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string CastNode::toString() const {
        return "(Cast " + targetType->toString() + " " + operand->toString() + ")";
    }

    void AssignmentNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<AssignmentNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string AssignmentNode::toString() const {
        return "(Assign " + lhs->toString() + " " + rhs->toString() + ")";
    }

} // namespace Ryntra::Compiler
