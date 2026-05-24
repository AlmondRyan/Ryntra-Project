#pragma once

#include "../AST/ASTNodes.h"
#include "SourceLocation/SourceLocation.h"
#include "TypeSystem.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Ryntra::Compiler::Semantic {

    class TypedExpressionNode;
    class TypedStatementNode;
    class TypedProgramNode;
    class TypedFunctionDefinitionNode;
    class TypedBlockNode;
    class TypedIfNode;
    class TypedWhileNode;
    class TypedForNode;
    class TypedBreakNode;
    class TypedContinueNode;
    class TypedPrefixOpNode;
    class TypedPostfixOpNode;
    class TypedStringLiteralNode;
    class TypedBoolLiteralNode;
    class TypedIntegerLiteralNode;
    class TypedLongLiteralNode;
    class TypedIdentifierNode;
    class TypedFunctionCallNode;
    class TypedExpressionStatementNode;
    class TypedReturnNode;
    class TypedVariableNode;
    class TypedVariableDeclarationNode;
    class TypedArrayDeclarationNode;
    class TypedArrayIndexAccessNode;
    class TypedArrayIndexAssignmentNode;
    class TypedBinaryOpNode;
    class TypedUnaryOpNode;
    class TypedCastNode;
    class TypedComparisonNode;
    class TypedConditionalAndNode;
    class TypedConditionalOrNode;
    class TypedAssignmentNode;
    class TypedRefCreateNode;
    class TypedRefLoadNode;
    class TypedRefAssignNode;
    class TypedUnsafeBlockNode;
    class TypedPtrCreateNode;
    class TypedPtrLoadNode;
    class TypedPtrStoreNode;
    class TypedNullLiteralNode;
    class TypedPtrOffsetNode;
    class TypedPtrDiffNode;
    class TypedNewNode;
    class TypedDeleteNode;
    class TypedFixedNode;
    class TypedPtrIndexAccessNode;
    class TypedPtrIndexAssignmentNode;
    class TypedPtrFromArrayNode;

    class ITypedVisitor {
    public:
        virtual ~ITypedVisitor() = default;
        virtual void visit(TypedProgramNode &node) = 0;
        virtual void visit(TypedFunctionDefinitionNode &node) = 0;
        virtual void visit(TypedBlockNode &node) = 0;
        virtual void visit(TypedIfNode &node) = 0;
        virtual void visit(TypedWhileNode &node) = 0;
        virtual void visit(TypedForNode &node) = 0;
        virtual void visit(TypedBreakNode &node) = 0;
        virtual void visit(TypedContinueNode &node) = 0;
        virtual void visit(TypedPrefixOpNode &node) = 0;
        virtual void visit(TypedPostfixOpNode &node) = 0;
        virtual void visit(TypedExpressionStatementNode &node) = 0;
        virtual void visit(TypedReturnNode &node) = 0;
        virtual void visit(TypedStringLiteralNode &node) = 0;
        virtual void visit(TypedBoolLiteralNode &node) = 0;
        virtual void visit(TypedIntegerLiteralNode &node) = 0;
        virtual void visit(TypedLongLiteralNode &node) = 0;
        virtual void visit(TypedIdentifierNode &node) = 0;
        virtual void visit(TypedFunctionCallNode &node) = 0;
        virtual void visit(TypedVariableNode &node) = 0;
        virtual void visit(TypedVariableDeclarationNode &node) = 0;
        virtual void visit(TypedArrayDeclarationNode &node) = 0;
        virtual void visit(TypedArrayIndexAccessNode &node) = 0;
        virtual void visit(TypedArrayIndexAssignmentNode &node) = 0;
        virtual void visit(TypedBinaryOpNode &node) = 0;
        virtual void visit(TypedUnaryOpNode &node) = 0;
        virtual void visit(TypedCastNode &node) = 0;
        virtual void visit(TypedComparisonNode &node) = 0;
        virtual void visit(TypedConditionalAndNode &node) = 0;
        virtual void visit(TypedConditionalOrNode &node) = 0;
        virtual void visit(TypedAssignmentNode &node) = 0;
        virtual void visit(TypedRefCreateNode &node) = 0;
        virtual void visit(TypedRefLoadNode &node) = 0;
        virtual void visit(TypedRefAssignNode &node) = 0;
        virtual void visit(TypedUnsafeBlockNode &node) = 0;
        virtual void visit(TypedPtrCreateNode &node) = 0;
        virtual void visit(TypedPtrLoadNode &node) = 0;
        virtual void visit(TypedPtrStoreNode &node) = 0;
        virtual void visit(TypedNullLiteralNode &node) = 0;
        virtual void visit(TypedPtrOffsetNode &node) = 0;
        virtual void visit(TypedPtrDiffNode &node) = 0;
        virtual void visit(TypedNewNode &node) = 0;
        virtual void visit(TypedDeleteNode &node) = 0;
        virtual void visit(TypedFixedNode &node) = 0;
        virtual void visit(TypedPtrIndexAccessNode &node) = 0;
        virtual void visit(TypedPtrIndexAssignmentNode &node) = 0;
        virtual void visit(TypedPtrFromArrayNode &node) = 0;
    };

    class ITypedASTNode {
    public:
        virtual ~ITypedASTNode() = default;
        virtual void accept(ITypedVisitor &visitor) = 0;
        virtual std::string toString() const = 0;
        virtual void dump(int indent = 0) const = 0;

        SourceLocation getLocation() const { return location; }
        void setLocation(SourceLocation loc) { location = loc; }

    protected:
        void printIndent(int indent) const {
            for (int i = 0; i < indent; ++i)
                std::cout << "  ";
        }

    private:
        SourceLocation location;
    };

    class TypedExpressionNode : public ITypedASTNode {
    public:
        explicit TypedExpressionNode(std::shared_ptr<Type> type) : type(std::move(type)) {}
        std::shared_ptr<Type> getType() const { return type; }

    protected:
        std::shared_ptr<Type> type;
    };

    class TypedStatementNode : public ITypedASTNode {};

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

    class TypedRefCreateNode : public TypedExpressionNode {
    public:
        TypedRefCreateNode(std::string variableName, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), variableName(std::move(variableName)) {}

        const std::string &getVariableName() const { return variableName; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedRefCreate(" + variableName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string variableName;
    };

    class TypedRefLoadNode : public TypedExpressionNode {
    public:
        TypedRefLoadNode(std::string variableName, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), variableName(std::move(variableName)) {}

        const std::string &getVariableName() const { return variableName; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedRefLoad(" + variableName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string variableName;
    };

    class TypedRefAssignNode : public TypedExpressionNode {
    public:
        TypedRefAssignNode(std::string variableName, std::shared_ptr<TypedExpressionNode> rhs, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), variableName(std::move(variableName)), rhs(std::move(rhs)) {}

        const std::string &getVariableName() const { return variableName; }
        std::shared_ptr<TypedExpressionNode> getRHS() const { return rhs; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedRefAssign(" + variableName + "): " + type->toString(); }
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

    class TypedBlockNode : public TypedStatementNode {
    public:
        explicit TypedBlockNode(std::vector<std::shared_ptr<TypedStatementNode>> stmts)
            : statements(std::move(stmts)) {}

        const std::vector<std::shared_ptr<TypedStatementNode>> &getStatements() const { return statements; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedBlock"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            for (const auto &stmt : statements) {
                stmt->dump(indent + 1);
            }
        }

    private:
        std::vector<std::shared_ptr<TypedStatementNode>> statements;
    };

    class TypedUnsafeBlockNode : public TypedStatementNode {
    public:
        explicit TypedUnsafeBlockNode(std::shared_ptr<TypedBlockNode> body)
            : body(std::move(body)) {}

        std::shared_ptr<TypedBlockNode> getBody() const { return body; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedUnsafeBlock"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            body->dump(indent + 1);
        }

    private:
        std::shared_ptr<TypedBlockNode> body;
    };

    class TypedPtrCreateNode : public TypedExpressionNode {
    public:
        TypedPtrCreateNode(std::string variableName, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), variableName(std::move(variableName)) {}

        const std::string &getVariableName() const { return variableName; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrCreate(" + variableName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string variableName;
    };

    class TypedPtrLoadNode : public TypedExpressionNode {
    public:
        TypedPtrLoadNode(std::string ptrVarName, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), ptrVarName(std::move(ptrVarName)) {}

        const std::string &getPtrVarName() const { return ptrVarName; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrLoad(" + ptrVarName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string ptrVarName;
    };

    class TypedPtrStoreNode : public TypedExpressionNode {
    public:
        TypedPtrStoreNode(std::string ptrVarName, std::shared_ptr<TypedExpressionNode> rhs, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), ptrVarName(std::move(ptrVarName)), rhs(std::move(rhs)) {}

        const std::string &getPtrVarName() const { return ptrVarName; }
        std::shared_ptr<TypedExpressionNode> getRHS() const { return rhs; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrStore(" + ptrVarName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "RHS:" << std::endl;
            rhs->dump(indent + 2);
        }

    private:
        std::string ptrVarName;
        std::shared_ptr<TypedExpressionNode> rhs;
    };

    class TypedNullLiteralNode : public TypedExpressionNode {
    public:
        explicit TypedNullLiteralNode(std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)) {}

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedNullLiteral: " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }
    };

    class TypedNewNode : public TypedExpressionNode {
    public:
        TypedNewNode(std::shared_ptr<Type> elementType,
                     std::shared_ptr<TypedExpressionNode> initializer,
                     std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)),
              elementType(std::move(elementType)),
              initializer(std::move(initializer)) {}

        std::shared_ptr<Type> getElementType() const { return elementType; }
        std::shared_ptr<TypedExpressionNode> getInitializer() const { return initializer; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override {
            return "TypedNew(" + elementType->toString() + "): " + type->toString();
        }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            if (initializer) {
                printIndent(indent + 1);
                std::cout << "Initializer:" << std::endl;
                initializer->dump(indent + 2);
            }
        }

    private:
        std::shared_ptr<Type> elementType;
        std::shared_ptr<TypedExpressionNode> initializer;
    };

    class TypedDeleteNode : public TypedStatementNode {
    public:
        explicit TypedDeleteNode(std::shared_ptr<TypedExpressionNode> ptrExpr)
            : ptrExpr(std::move(ptrExpr)) {}

        std::shared_ptr<TypedExpressionNode> getPtrExpr() const { return ptrExpr; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedDelete"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Ptr:" << std::endl;
            ptrExpr->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> ptrExpr;
    };

    class TypedFixedNode : public TypedStatementNode {
    public:
        TypedFixedNode(std::string varName,
                       std::shared_ptr<Type> ptrType,
                       std::shared_ptr<TypedExpressionNode> initExpr,
                       std::shared_ptr<TypedBlockNode> body)
            : varName(std::move(varName)), ptrType(std::move(ptrType)),
              initExpr(std::move(initExpr)), body(std::move(body)) {}

        const std::string &getVarName() const { return varName; }
        std::shared_ptr<Type> getPtrType() const { return ptrType; }
        std::shared_ptr<TypedExpressionNode> getInitExpr() const { return initExpr; }
        std::shared_ptr<TypedBlockNode> getBody() const { return body; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedFixed(" + varName + "): " + ptrType->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Init:" << std::endl;
            initExpr->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Body:" << std::endl;
            body->dump(indent + 2);
        }

    private:
        std::string varName;
        std::shared_ptr<Type> ptrType;
        std::shared_ptr<TypedExpressionNode> initExpr;
        std::shared_ptr<TypedBlockNode> body;
    };

    class TypedPtrIndexAccessNode : public TypedExpressionNode {
    public:
        TypedPtrIndexAccessNode(std::shared_ptr<TypedExpressionNode> ptrExpr,
                                std::shared_ptr<TypedExpressionNode> index,
                                std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), ptrExpr(std::move(ptrExpr)), index(std::move(index)) {}

        std::shared_ptr<TypedExpressionNode> getPtrExpr() const { return ptrExpr; }
        std::shared_ptr<TypedExpressionNode> getIndex() const { return index; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrIndexAccess: " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Ptr:" << std::endl;
            ptrExpr->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Index:" << std::endl;
            index->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> ptrExpr;
        std::shared_ptr<TypedExpressionNode> index;
    };

    class TypedPtrIndexAssignmentNode : public TypedExpressionNode {
    public:
        TypedPtrIndexAssignmentNode(std::shared_ptr<TypedExpressionNode> ptrExpr,
                                    std::shared_ptr<TypedExpressionNode> index,
                                    std::shared_ptr<TypedExpressionNode> value,
                                    std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), ptrExpr(std::move(ptrExpr)), index(std::move(index)), value(std::move(value)) {}

        std::shared_ptr<TypedExpressionNode> getPtrExpr() const { return ptrExpr; }
        std::shared_ptr<TypedExpressionNode> getIndex() const { return index; }
        std::shared_ptr<TypedExpressionNode> getValue() const { return value; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrIndexAssign: ptr[index]: " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Ptr:" << std::endl;
            ptrExpr->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Index:" << std::endl;
            index->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Value:" << std::endl;
            value->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> ptrExpr;
        std::shared_ptr<TypedExpressionNode> index;
        std::shared_ptr<TypedExpressionNode> value;
    };

    class TypedPtrFromArrayNode : public TypedExpressionNode {
    public:
        TypedPtrFromArrayNode(std::string arrayName, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), arrayName(std::move(arrayName)) {}

        const std::string &getArrayName() const { return arrayName; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrFromArray(" + arrayName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string arrayName;
    };

    class TypedPtrOffsetNode : public TypedExpressionNode {
    public:
        TypedPtrOffsetNode(std::string ptrVarName, std::shared_ptr<TypedExpressionNode> offset, bool isAdd, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), ptrVarName(std::move(ptrVarName)), offset(std::move(offset)), isAdd(isAdd) {}

        const std::string &getPtrVarName() const { return ptrVarName; }
        std::shared_ptr<TypedExpressionNode> getOffset() const { return offset; }
        bool getIsAdd() const { return isAdd; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrOffset(" + ptrVarName + ", " + (isAdd ? "+" : "-") + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Offset:" << std::endl;
            offset->dump(indent + 2);
        }

    private:
        std::string ptrVarName;
        std::shared_ptr<TypedExpressionNode> offset;
        bool isAdd;
    };

    class TypedPtrDiffNode : public TypedExpressionNode {
    public:
        TypedPtrDiffNode(std::string leftPtrName, std::string rightPtrName, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), leftPtrName(std::move(leftPtrName)), rightPtrName(std::move(rightPtrName)) {}

        const std::string &getLeftPtrName() const { return leftPtrName; }
        const std::string &getRightPtrName() const { return rightPtrName; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrDiff(" + leftPtrName + " - " + rightPtrName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string leftPtrName;
        std::string rightPtrName;
    };

    class TypedIfNode : public TypedStatementNode {
    public:
        TypedIfNode(std::shared_ptr<TypedExpressionNode> condition,
                    std::shared_ptr<TypedBlockNode> thenBlock,
                    std::shared_ptr<TypedStatementNode> elseBranch)
            : condition(std::move(condition)), thenBlock(std::move(thenBlock)), elseBranch(std::move(elseBranch)) {}

        std::shared_ptr<TypedExpressionNode> getCondition() const { return condition; }
        std::shared_ptr<TypedBlockNode> getThenBlock() const { return thenBlock; }
        std::shared_ptr<TypedStatementNode> getElseBranch() const { return elseBranch; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedIf"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Condition:" << std::endl;
            condition->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Then:" << std::endl;
            thenBlock->dump(indent + 2);
            if (elseBranch) {
                printIndent(indent + 1);
                std::cout << "Else:" << std::endl;
                elseBranch->dump(indent + 2);
            }
        }

    private:
        std::shared_ptr<TypedExpressionNode> condition;
        std::shared_ptr<TypedBlockNode> thenBlock;
        std::shared_ptr<TypedStatementNode> elseBranch;
    };

    class TypedWhileNode : public TypedStatementNode {
    public:
        TypedWhileNode(std::shared_ptr<TypedExpressionNode> condition,
                       std::shared_ptr<TypedBlockNode> body)
            : condition(std::move(condition)), body(std::move(body)) {}

        std::shared_ptr<TypedExpressionNode> getCondition() const { return condition; }
        std::shared_ptr<TypedBlockNode> getBody() const { return body; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedWhile"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Condition:" << std::endl;
            condition->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Body:" << std::endl;
            body->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> condition;
        std::shared_ptr<TypedBlockNode> body;
    };

    class TypedForNode : public TypedStatementNode {
    public:
        TypedForNode(std::shared_ptr<TypedStatementNode> init,
                     std::shared_ptr<TypedExpressionNode> condition,
                     std::shared_ptr<TypedExpressionNode> operation,
                     std::shared_ptr<TypedBlockNode> body)
            : init(std::move(init)), condition(std::move(condition)), operation(std::move(operation)), body(std::move(body)) {}

        std::shared_ptr<TypedStatementNode> getInit() const { return init; }
        std::shared_ptr<TypedExpressionNode> getCondition() const { return condition; }
        std::shared_ptr<TypedExpressionNode> getOperation() const { return operation; }
        std::shared_ptr<TypedBlockNode> getBody() const { return body; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedFor"; }
        void dump(const int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            if (init) {
                printIndent(indent + 1);
                std::cout << "Init:" << std::endl;
                init->dump(indent + 2);
            }
            if (condition) {
                printIndent(indent + 1);
                std::cout << "Condition:" << std::endl;
                condition->dump(indent + 2);
            }
            if (operation) {
                printIndent(indent + 1);
                std::cout << "Operation:" << std::endl;
                operation->dump(indent + 2);
            }
            printIndent(indent + 1);
            std::cout << "Body:" << std::endl;
            body->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedStatementNode> init;
        std::shared_ptr<TypedExpressionNode> condition;
        std::shared_ptr<TypedExpressionNode> operation;
        std::shared_ptr<TypedBlockNode> body;
    };

    class TypedBreakNode : public TypedStatementNode {
    public:
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedBreak"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }
    };

    class TypedContinueNode : public TypedStatementNode {
    public:
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedContinue"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }
    };

    class TypedFunctionDefinitionNode : public ITypedASTNode {
    public:
        TypedFunctionDefinitionNode(std::string name,
                                    std::shared_ptr<Type> returnType,
                                    std::shared_ptr<TypedBlockNode> body)
            : name(std::move(name)), returnType(std::move(returnType)), body(std::move(body)) {}

        const std::string &getName() const { return name; }
        std::shared_ptr<Type> getReturnType() const { return returnType; }
        std::shared_ptr<TypedBlockNode> getBody() const { return body; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedFunctionDefinition(" + name + "): " + returnType->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            body->dump(indent + 1);
        }

    private:
        std::string name;
        std::shared_ptr<Type> returnType;
        std::shared_ptr<TypedBlockNode> body;
    };

    class TypedProgramNode : public ITypedASTNode {
    public:
        explicit TypedProgramNode(std::vector<std::shared_ptr<TypedFunctionDefinitionNode>> funcs)
            : functions(std::move(funcs)) {}

        const std::vector<std::shared_ptr<TypedFunctionDefinitionNode>> &getFunctions() const { return functions; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedProgram"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            for (const auto &func : functions) {
                func->dump(indent + 1);
            }
        }

    private:
        std::vector<std::shared_ptr<TypedFunctionDefinitionNode>> functions;
    };

} // namespace Ryntra::Compiler::Semantic
