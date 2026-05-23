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

    void ArrayTypeNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<ArrayTypeNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string ArrayTypeNode::toString() const {
        return "(ArrayType " + elementType->toString() + ")";
    }

    void ReferenceTypeNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<ReferenceTypeNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string ReferenceTypeNode::toString() const {
        return "(ReferenceType " + elementType->toString() + ")";
    }

    void NullLiteralNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<NullLiteralNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string NullLiteralNode::toString() const {
        return "(NullLiteral)";
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

    void IfNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<IfNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string IfNode::toString() const {
        std::stringstream ss;
        ss << "(If " << condition->toString() << " " << thenBlock->toString();
        if (elseBranch) {
            ss << " " << elseBranch->toString();
        }
        ss << ")";
        return ss.str();
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

    void WhileNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<WhileNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string WhileNode::toString() const {
        return "(While " + condition->toString() + " " + body->toString() + ")";
    }

    void BreakNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<BreakNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string BreakNode::toString() const {
        return "(Break)";
    }

    void ContinueNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<ContinueNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string ContinueNode::toString() const {
        return "(Continue)";
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

    void ArrayDeclarationNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<ArrayDeclarationNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string ArrayDeclarationNode::toString() const {
        std::stringstream ss;
        ss << "(ArrayDeclaration " << arrayType->toString() << " " << name->toString()
           << " " << elementType->toString() << " " << size->toString() << ")";
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
        case UnaryOpType::LogicalNot:
            opStr = "!";
            break;
        case UnaryOpType::Negate:
            opStr = "-";
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

    void ComparisonNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<ComparisonNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string ComparisonNode::toString() const {
        std::string opStr;
        switch (op) {
        case ComparisonOpType::Eq: opStr = "=="; break;
        case ComparisonOpType::Ne: opStr = "!="; break;
        case ComparisonOpType::Lt: opStr = "<"; break;
        case ComparisonOpType::Gt: opStr = ">"; break;
        case ComparisonOpType::Le: opStr = "<="; break;
        case ComparisonOpType::Ge: opStr = ">="; break;
        }
        return "(Comparison " + left->toString() + " " + opStr + " " + right->toString() + ")";
    }

    void AssignmentNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<AssignmentNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string AssignmentNode::toString() const {
        return "(Assign " + lhs->toString() + " " + rhs->toString() + ")";
    }

    void UnsafeBlockNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<UnsafeBlockNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string UnsafeBlockNode::toString() const {
        return "(UnsafeBlock " + body->toString() + ")";
    }

    void PtrExpressionNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<PtrExpressionNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string PtrExpressionNode::toString() const {
        return "(Ptr " + operand->toString() + ")";
    }

    void PtrLoadNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<PtrLoadNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string PtrLoadNode::toString() const {
        return "(PtrLoad " + ptrExpr->toString() + ")";
    }

    void PtrStoreNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<PtrStoreNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string PtrStoreNode::toString() const {
        return "(PtrStore " + ptrExpr->toString() + " " + value->toString() + ")";
    }

    void RefExpressionNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<RefExpressionNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string RefExpressionNode::toString() const {
        return "(Ref " + operand->toString() + ")";
    }

    void ArrayIndexAccessNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<ArrayIndexAccessNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string ArrayIndexAccessNode::toString() const {
        return "(ArrayIndexAccess " + arrayExpr->toString() + " " + index->toString() + ")";
    }

    void ArrayIndexAssignmentNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<ArrayIndexAssignmentNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string ArrayIndexAssignmentNode::toString() const {
        return "(ArrayIndexAssign " + arrayExpr->toString() + " " + index->toString() + " " + value->toString() + ")";
    }

    void PrefixOpNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<PrefixOpNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string PrefixOpNode::toString() const {
        std::string opStr = (op == IncDecOpType::Increment) ? "++" : "--";
        return "(PrefixOp " + opStr + " " + operand->toString() + ")";
    }

    void PostfixOpNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<PostfixOpNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string PostfixOpNode::toString() const {
        std::string opStr = (op == IncDecOpType::Increment) ? "++" : "--";
        return "(PostfixOp " + operand->toString() + " " + opStr + ")";
    }

    void ForNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<ForNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string ForNode::toString() const {
        std::stringstream ss;
        ss << "(For";
        if (init) ss << " " << init->toString();
        if (condition) ss << " " << condition->toString();
        if (operation) ss << " " << operation->toString();
        ss << " " << body->toString();
        ss << ")";
        return ss.str();
    }

    void NewExpressionNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<NewExpressionNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string NewExpressionNode::toString() const {
        std::stringstream ss;
        ss << "(New " << elementType->toString();
        if (initializer) ss << " " << initializer->toString();
        ss << ")";
        return ss.str();
    }

    void DeleteStatementNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<DeleteStatementNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string DeleteStatementNode::toString() const {
        return "(Delete " + expression->toString() + ")";
    }

    void FixedNode::accept(IVisitor &visitor) {
        if (auto *v = dynamic_cast<Visitor<FixedNode> *>(&visitor)) {
            v->visit(*this);
        }
    }

    std::string FixedNode::toString() const {
        std::stringstream ss;
        ss << "(Fixed " << ptrType->toString() << " " << name->toString()
           << " = " << init->toString() << " " << body->toString() << ")";
        return ss.str();
    }

} // namespace Ryntra::Compiler
