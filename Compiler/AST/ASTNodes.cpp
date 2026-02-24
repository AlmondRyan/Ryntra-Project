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

} // namespace Ryntra::Compiler
