#pragma once

#include "../../AST/ASTNodes.h"
#include "TypedASTBase.h"
#include <cstdint>

namespace Ryntra::Compiler::Semantic {
    class TypedStringLiteralNode : public TypedExpressionNode {
    public:
        TypedStringLiteralNode(std::string value, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), value(std::move(value)) {}

        const std::string &getValue() const { return value; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedStringLiteral(" + value + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string value;
    };

    class TypedBoolLiteralNode : public TypedExpressionNode {
    public:
        TypedBoolLiteralNode(bool value, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), value(value) {}

        bool getValue() const { return value; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedBoolLiteral(" + std::string(value ? "true" : "false") + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        bool value;
    };

    class TypedIntegerLiteralNode : public TypedExpressionNode {
    public:
        TypedIntegerLiteralNode(int value, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), value(value) {}

        int getValue() const { return value; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedIntegerLiteral(" + std::to_string(value) + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        int value;
    };

    class TypedLongLiteralNode : public TypedExpressionNode {
    public:
        TypedLongLiteralNode(int64_t value, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), value(value) {}

        int64_t getValue() const { return value; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedLongLiteral(" + std::to_string(value) + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        int64_t value;
    };

    class TypedIdentifierNode : public TypedExpressionNode {
    public:
        TypedIdentifierNode(std::string name, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), name(std::move(name)) {}

        const std::string &getName() const { return name; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedIdentifier(" + name + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string name;
    };

    class TypedFunctionCallNode : public TypedExpressionNode {
    public:
        TypedFunctionCallNode(std::shared_ptr<TypedIdentifierNode> funcName,
                               std::vector<std::shared_ptr<TypedExpressionNode>> args,
                               std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), functionName(std::move(funcName)), arguments(std::move(args)) {}

        std::shared_ptr<TypedIdentifierNode> getFunctionName() const { return functionName; }
        const std::vector<std::shared_ptr<TypedExpressionNode>> &getArguments() const { return arguments; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedFunctionCall: " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Function: " << functionName->toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Arguments:" << std::endl;
            for (const auto &arg : arguments) {
                arg->dump(indent + 2);
            }
        }

    private:
        std::shared_ptr<TypedIdentifierNode> functionName;
        std::vector<std::shared_ptr<TypedExpressionNode>> arguments;
    };

    class TypedVariableNode : public TypedExpressionNode {
    public:
        TypedVariableNode(std::string name, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), name(std::move(name)) {}

        const std::string &getName() const { return name; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedVariable(" + name + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string name;
    };

    class TypedExpressionStatementNode : public TypedStatementNode {
    public:
        explicit TypedExpressionStatementNode(std::shared_ptr<TypedExpressionNode> expr)
            : expression(std::move(expr)) {}

        std::shared_ptr<TypedExpressionNode> getExpression() const { return expression; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedExpressionStatement"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            expression->dump(indent + 1);
        }

    private:
        std::shared_ptr<TypedExpressionNode> expression;
    };

    class TypedReturnNode : public TypedStatementNode {
    public:
        explicit TypedReturnNode(std::shared_ptr<TypedExpressionNode> value)
            : value(std::move(value)) {}

        std::shared_ptr<TypedExpressionNode> getValue() const { return value; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedReturn"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            value->dump(indent + 1);
        }

    private:
        std::shared_ptr<TypedExpressionNode> value;
    };

    class TypedVariableDeclarationNode : public TypedStatementNode {
    public:
        TypedVariableDeclarationNode(std::string name, std::shared_ptr<Type> type, std::shared_ptr<TypedExpressionNode> init)
            : name(std::move(name)), type(std::move(type)), initializer(std::move(init)) {}

        const std::string &getName() const { return name; }
        std::shared_ptr<Type> getType() const { return type; }
        std::shared_ptr<TypedExpressionNode> getInitializer() const { return initializer; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedVariableDeclaration(" + name + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            if (initializer) {
                initializer->dump(indent + 1);
            }
        }

    private:
        std::string name;
        std::shared_ptr<Type> type;
        std::shared_ptr<TypedExpressionNode> initializer;
    };

    class TypedArrayDeclarationNode : public TypedStatementNode {
    public:
        TypedArrayDeclarationNode(std::string name,
                                    std::shared_ptr<Type> elementType,
                                    std::shared_ptr<TypedExpressionNode> size)
            : name(std::move(name)), elementType(std::move(elementType)), size(std::move(size)) {}

        const std::string &getName() const { return name; }
        std::shared_ptr<Type> getElementType() const { return elementType; }
        std::shared_ptr<TypedExpressionNode> getSize() const { return size; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedArrayDeclaration(" + name + "): " + elementType->toString() + "[]"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            if (size) {
                printIndent(indent + 1);
                std::cout << "Size:" << std::endl;
                size->dump(indent + 2);
            }
        }

    private:
        std::string name;
        std::shared_ptr<Type> elementType;
        std::shared_ptr<TypedExpressionNode> size;
    };

    class TypedArrayIndexAccessNode : public TypedExpressionNode {
    public:
        TypedArrayIndexAccessNode(std::string arrayName,
                                   std::shared_ptr<TypedExpressionNode> index,
                                   std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), arrayName(std::move(arrayName)), index(std::move(index)) {}

        const std::string &getArrayName() const { return arrayName; }
        std::shared_ptr<TypedExpressionNode> getIndex() const { return index; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedArrayIndexAccess(" + arrayName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Index:" << std::endl;
            index->dump(indent + 2);
        }

    private:
        std::string arrayName;
        std::shared_ptr<TypedExpressionNode> index;
    };

    class TypedArrayIndexAssignmentNode : public TypedExpressionNode {
    public:
        TypedArrayIndexAssignmentNode(std::string arrayName,
                                       std::shared_ptr<TypedExpressionNode> index,
                                       std::shared_ptr<TypedExpressionNode> value,
                                       std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), arrayName(std::move(arrayName)), index(std::move(index)), value(std::move(value)) {}

        const std::string &getArrayName() const { return arrayName; }
        std::shared_ptr<TypedExpressionNode> getIndex() const { return index; }
        std::shared_ptr<TypedExpressionNode> getValue() const { return value; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedArrayIndexAssign(" + arrayName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Index:" << std::endl;
            index->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Value:" << std::endl;
            value->dump(indent + 2);
        }

    private:
        std::string arrayName;
        std::shared_ptr<TypedExpressionNode> index;
        std::shared_ptr<TypedExpressionNode> value;
    };

    class TypedBinaryOpNode : public TypedExpressionNode {
    public:
        TypedBinaryOpNode(std::shared_ptr<TypedExpressionNode> left, BinaryOpType op, std::shared_ptr<TypedExpressionNode> right, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), left(std::move(left)), op(op), right(std::move(right)) {}

        std::shared_ptr<TypedExpressionNode> getLeft() const { return left; }
        std::shared_ptr<TypedExpressionNode> getRight() const { return right; }
        BinaryOpType getOp() const { return op; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override {
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
            return "TypedBinaryOp(" + opStr + "): " + type->toString();
        }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Left:" << std::endl;
            left->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Right:" << std::endl;
            right->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> left;
        BinaryOpType op;
        std::shared_ptr<TypedExpressionNode> right;
    };

    class TypedUnaryOpNode : public TypedExpressionNode {
    public:
        TypedUnaryOpNode(UnaryOpType op, std::shared_ptr<TypedExpressionNode> operand, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), op(op), operand(std::move(operand)) {}

        UnaryOpType getOp() const { return op; }
        std::shared_ptr<TypedExpressionNode> getOperand() const { return operand; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override {
            std::string opStr;
            switch (op) {
            case UnaryOpType::BitNot:
                opStr = "~";
                break;
            case UnaryOpType::LogicalNot:
                opStr = "!";
                break;
            }
            return "TypedUnaryOp(" + opStr + "): " + type->toString();
        }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Operand:" << std::endl;
            operand->dump(indent + 2);
        }

    private:
        UnaryOpType op;
        std::shared_ptr<TypedExpressionNode> operand;
    };

    class TypedPrefixOpNode : public TypedExpressionNode {
    public:
        TypedPrefixOpNode(std::string variableName, IncDecOpType op, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), variableName(std::move(variableName)), op(op) {}

        const std::string &getVariableName() const { return variableName; }
        IncDecOpType getOp() const { return op; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override {
            std::string opStr = (op == IncDecOpType::Increment) ? "++" : "--";
            return "TypedPrefixOp(" + opStr + " " + variableName + "): " + type->toString();
        }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string variableName;
        IncDecOpType op;
    };

    class TypedPostfixOpNode : public TypedExpressionNode {
    public:
        TypedPostfixOpNode(std::string variableName, IncDecOpType op, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), variableName(std::move(variableName)), op(op) {}

        const std::string &getVariableName() const { return variableName; }
        IncDecOpType getOp() const { return op; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override {
            std::string opStr = (op == IncDecOpType::Increment) ? "++" : "--";
            return "TypedPostfixOp(" + variableName + " " + opStr + "): " + type->toString();
        }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string variableName;
        IncDecOpType op;
    };

    class TypedCastNode : public TypedExpressionNode {
    public:
        TypedCastNode(std::shared_ptr<TypedExpressionNode> operand, std::shared_ptr<Type> targetType)
            : TypedExpressionNode(std::move(targetType)), operand(std::move(operand)) {}

        std::shared_ptr<TypedExpressionNode> getOperand() const { return operand; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedCast: " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Operand:" << std::endl;
            operand->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> operand;
    };

    class TypedComparisonNode : public TypedExpressionNode {
    public:
        TypedComparisonNode(std::shared_ptr<TypedExpressionNode> left, ComparisonOpType op, std::shared_ptr<TypedExpressionNode> right, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), left(std::move(left)), op(op), right(std::move(right)) {}

        std::shared_ptr<TypedExpressionNode> getLeft() const { return left; }
        std::shared_ptr<TypedExpressionNode> getRight() const { return right; }
        ComparisonOpType getOp() const { return op; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override {
            std::string opStr;
            switch (op) {
            case ComparisonOpType::Eq: opStr = "=="; break;
            case ComparisonOpType::Ne: opStr = "!="; break;
            case ComparisonOpType::Lt: opStr = "<"; break;
            case ComparisonOpType::Gt: opStr = ">"; break;
            case ComparisonOpType::Le: opStr = "<="; break;
            case ComparisonOpType::Ge: opStr = ">="; break;
            }
            return "TypedComparison(" + opStr + "): " + type->toString();
        }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Left:" << std::endl;
            left->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Right:" << std::endl;
            right->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> left;
        ComparisonOpType op;
        std::shared_ptr<TypedExpressionNode> right;
    };

    class TypedConditionalAndNode : public TypedExpressionNode {
    public:
        TypedConditionalAndNode(std::shared_ptr<TypedExpressionNode> left, std::shared_ptr<TypedExpressionNode> right, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), left(std::move(left)), right(std::move(right)) {}

        std::shared_ptr<TypedExpressionNode> getLeft() const { return left; }
        std::shared_ptr<TypedExpressionNode> getRight() const { return right; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedConditionalAnd(&&): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Left:" << std::endl;
            left->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Right:" << std::endl;
            right->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> left;
        std::shared_ptr<TypedExpressionNode> right;
    };

    class TypedConditionalOrNode : public TypedExpressionNode {
    public:
        TypedConditionalOrNode(std::shared_ptr<TypedExpressionNode> left, std::shared_ptr<TypedExpressionNode> right, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), left(std::move(left)), right(std::move(right)) {}

        std::shared_ptr<TypedExpressionNode> getLeft() const { return left; }
        std::shared_ptr<TypedExpressionNode> getRight() const { return right; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedConditionalOr(||): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Left:" << std::endl;
            left->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Right:" << std::endl;
            right->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> left;
        std::shared_ptr<TypedExpressionNode> right;
    };

    class TypedAssignmentNode : public TypedExpressionNode {
    public:
        TypedAssignmentNode(std::string variableName, std::shared_ptr<TypedExpressionNode> rhs, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), variableName(std::move(variableName)), rhs(std::move(rhs)) {}

        const std::string &getVariableName() const { return variableName; }
        std::shared_ptr<TypedExpressionNode> getRHS() const { return rhs; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedAssign(" + variableName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "RHS:" << std::endl;
            rhs->dump(indent + 2);
        }

    private:
        std::string variableName;
        std::shared_ptr<TypedExpressionNode> rhs;
    };

} // namespace Ryntra::Compiler::Semantic
