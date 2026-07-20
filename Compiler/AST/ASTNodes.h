#pragma once

#include "ASTVisitor.h"
#include "SourceLocation/SourceLocation.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace Ryntra::Compiler {
    class IASTNode : public std::enable_shared_from_this<IASTNode> {
    public:
        virtual ~IASTNode() = default;
        virtual void accept(IVisitor &visitor) = 0;
        virtual std::string toString() const = 0;

        SourceLocation getLocation() const {
            return location;
        }

        void setLocation(const SourceLocation newLocation) {
            location = newLocation;
        }

    private:
        SourceLocation location;
    };

    class ExpressionNode : public IASTNode {};
    class StatementNode : public IASTNode {};

    class TypeSpecifierNode : public IASTNode {
    public:
        TypeSpecifierNode(const std::string &name) : name(name) {}
        const std::string &getName() const { return name; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::string name;
    };

    class ArrayTypeNode : public IASTNode {
    public:
        ArrayTypeNode(std::shared_ptr<TypeSpecifierNode> elementType) : elementType(std::move(elementType)) {}
        std::shared_ptr<TypeSpecifierNode> getElementType() const { return elementType; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<TypeSpecifierNode> elementType;
    };

    class ReferenceTypeNode : public IASTNode {
    public:
        ReferenceTypeNode(std::shared_ptr<TypeSpecifierNode> elementType) : elementType(std::move(elementType)) {}
        std::shared_ptr<TypeSpecifierNode> getElementType() const { return elementType; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<TypeSpecifierNode> elementType;
    };

    class NullLiteralNode : public ExpressionNode {
    public:
        NullLiteralNode() = default;
        void accept(IVisitor &visitor) override;
        std::string toString() const override;
    };

    class BoolLiteralNode : public ExpressionNode {
    public:
        BoolLiteralNode(bool value) : value(value) {}
        bool getValue() const { return value; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        bool value;
    };

    class StringLiteralNode : public ExpressionNode {
    public:
        StringLiteralNode(const std::string &value) : value(value) {}
        const std::string &getValue() const { return value; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::string value;
    };

    class IntegerLiteralNode : public ExpressionNode {
    public:
        IntegerLiteralNode(int value) : value(value) {}
        int getValue() const { return value; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        int value; // I think programmers should explicitly mark `L/l` suffix to make the
                   // literal as long literal.
    };

    class LongLiteralNode : public ExpressionNode {
    public:
        LongLiteralNode(int64_t value) : value(value) {}
        int64_t getValue() const { return value; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        int64_t value;
    };

    class IdentifierNode : public ExpressionNode {
    public:
        IdentifierNode(const std::string &name) : name(name) {}
        const std::string &getName() const { return name; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::string name;
    };

    class FunctionCallNode : public ExpressionNode {
    public:
        FunctionCallNode(std::shared_ptr<IdentifierNode> name, std::vector<std::shared_ptr<ExpressionNode>> args)
            : functionName(std::move(name)), arguments(std::move(args)) {}
        std::shared_ptr<IdentifierNode> getFunctionName() const { return functionName; }
        const std::vector<std::shared_ptr<ExpressionNode>> &getArguments() const { return arguments; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<IdentifierNode> functionName;
        std::vector<std::shared_ptr<ExpressionNode>> arguments;
    };

    class ExpressionStatementNode : public StatementNode {
    public:
        ExpressionStatementNode(std::shared_ptr<ExpressionNode> expr) : expression(std::move(expr)) {}
        std::shared_ptr<ExpressionNode> getExpression() const { return expression; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> expression;
    };

    class ReturnNode : public StatementNode {
    public:
        ReturnNode(std::shared_ptr<ExpressionNode> value) : value(std::move(value)) {}
        std::shared_ptr<ExpressionNode> getValue() const { return value; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> value;
    };

    class BlockNode : public StatementNode {
    public:
        BlockNode(std::vector<std::shared_ptr<StatementNode>> stmts) : statements(std::move(stmts)) {}
        const std::vector<std::shared_ptr<StatementNode>> &getStatements() const { return statements; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::vector<std::shared_ptr<StatementNode>> statements;
    };

    class IfNode : public StatementNode {
    public:
        IfNode(std::shared_ptr<ExpressionNode> condition,
               std::shared_ptr<BlockNode> thenBlock,
               std::shared_ptr<StatementNode> elseBranch)
            : condition(std::move(condition)), thenBlock(std::move(thenBlock)), elseBranch(std::move(elseBranch)) {}
        std::shared_ptr<ExpressionNode> getCondition() const { return condition; }
        std::shared_ptr<BlockNode> getThenBlock() const { return thenBlock; }
        std::shared_ptr<StatementNode> getElseBranch() const { return elseBranch; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> condition;
        std::shared_ptr<BlockNode> thenBlock;
        std::shared_ptr<StatementNode> elseBranch; // IfNode, BlockNode, or nullptr
    };

    class WhileNode : public StatementNode {
    public:
        WhileNode(std::shared_ptr<ExpressionNode> condition,
                  std::shared_ptr<BlockNode> body)
            : condition(std::move(condition)), body(std::move(body)) {}
        std::shared_ptr<ExpressionNode> getCondition() const { return condition; }
        std::shared_ptr<BlockNode> getBody() const { return body; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> condition;
        std::shared_ptr<BlockNode> body;
    };

    class BreakNode : public StatementNode {
    public:
        void accept(IVisitor &visitor) override;
        std::string toString() const override;
    };

    class ContinueNode : public StatementNode {
    public:
        void accept(IVisitor &visitor) override;
        std::string toString() const override;
    };

    enum class IncDecOpType : uint8_t {
        Increment, // ++
        Decrement  // --
    };

    class PrefixOpNode : public ExpressionNode {
    public:
        PrefixOpNode(IncDecOpType op, std::shared_ptr<ExpressionNode> operand)
            : op(op), operand(std::move(operand)) {}
        IncDecOpType getOp() const { return op; }
        std::shared_ptr<ExpressionNode> getOperand() const { return operand; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        IncDecOpType op;
        std::shared_ptr<ExpressionNode> operand;
    };

    class PostfixOpNode : public ExpressionNode {
    public:
        PostfixOpNode(IncDecOpType op, std::shared_ptr<ExpressionNode> operand)
            : op(op), operand(std::move(operand)) {}
        IncDecOpType getOp() const { return op; }
        std::shared_ptr<ExpressionNode> getOperand() const { return operand; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        IncDecOpType op;
        std::shared_ptr<ExpressionNode> operand;
    };

    class ForNode : public StatementNode {
    public:
        ForNode(std::shared_ptr<StatementNode> init,
                std::shared_ptr<ExpressionNode> condition,
                std::shared_ptr<ExpressionNode> operation,
                std::shared_ptr<BlockNode> body)
            : init(std::move(init)), condition(std::move(condition)), operation(std::move(operation)), body(std::move(body)) {}
        std::shared_ptr<StatementNode> getInit() const { return init; }
        std::shared_ptr<ExpressionNode> getCondition() const { return condition; }
        std::shared_ptr<ExpressionNode> getOperation() const { return operation; }
        std::shared_ptr<BlockNode> getBody() const { return body; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<StatementNode> init;
        std::shared_ptr<ExpressionNode> condition;
        std::shared_ptr<ExpressionNode> operation;
        std::shared_ptr<BlockNode> body;
    };

    class ParameterNode : public IASTNode {
    public:
        ParameterNode(std::shared_ptr<TypeSpecifierNode> type, std::shared_ptr<IdentifierNode> name)
            : type(std::move(type)), name(std::move(name)) {}
        std::shared_ptr<TypeSpecifierNode> getType() const { return type; }
        std::shared_ptr<IdentifierNode> getName() const { return name; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<TypeSpecifierNode> type;
        std::shared_ptr<IdentifierNode> name;
    };

    class FunctionDefinitionNode : public IASTNode {
    public:
        FunctionDefinitionNode(std::shared_ptr<TypeSpecifierNode> type, std::shared_ptr<IdentifierNode> name,
                               std::vector<std::shared_ptr<ParameterNode>> params, std::shared_ptr<BlockNode> body)
            : returnType(std::move(type)), name(std::move(name)), parameters(std::move(params)), body(std::move(body)) {}
        std::shared_ptr<TypeSpecifierNode> getReturnType() const { return returnType; }
        std::shared_ptr<IdentifierNode> getName() const { return name; }
        const std::vector<std::shared_ptr<ParameterNode>> &getParameters() const { return parameters; }
        std::shared_ptr<BlockNode> getBody() const { return body; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<TypeSpecifierNode> returnType;
        std::shared_ptr<IdentifierNode> name;
        std::vector<std::shared_ptr<ParameterNode>> parameters;
        std::shared_ptr<BlockNode> body;
    };

    class ProgramNode : public IASTNode {
    public:
        ProgramNode(std::vector<std::shared_ptr<FunctionDefinitionNode>> funcs) : functions(std::move(funcs)) {}
        const std::vector<std::shared_ptr<FunctionDefinitionNode>> &getFunctions() const { return functions; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::vector<std::shared_ptr<FunctionDefinitionNode>> functions;
    };

    class VariableDeclarationNode : public StatementNode {
    public:
        VariableDeclarationNode(std::shared_ptr<TypeSpecifierNode> type, std::shared_ptr<IdentifierNode> name, std::shared_ptr<ExpressionNode> init)
            : type(std::move(type)), name(std::move(name)), initializer(std::move(init)) {}
        std::shared_ptr<TypeSpecifierNode> getType() const { return type; }
        std::shared_ptr<IdentifierNode> getName() const { return name; }
        std::shared_ptr<ExpressionNode> getInitializer() const { return initializer; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<TypeSpecifierNode> type;
        std::shared_ptr<IdentifierNode> name;
        std::shared_ptr<ExpressionNode> initializer;
    };

    class ArrayDeclarationNode : public StatementNode {
    public:
        ArrayDeclarationNode(std::shared_ptr<ArrayTypeNode> arrayType,
                              std::shared_ptr<IdentifierNode> name,
                              std::shared_ptr<TypeSpecifierNode> elementType,
                              std::shared_ptr<ExpressionNode> size)
            : arrayType(std::move(arrayType)), name(std::move(name)), elementType(std::move(elementType)), size(std::move(size)) {}
        std::shared_ptr<ArrayTypeNode> getArrayType() const { return arrayType; }
        std::shared_ptr<IdentifierNode> getName() const { return name; }
        std::shared_ptr<TypeSpecifierNode> getElementType() const { return elementType; }
        std::shared_ptr<ExpressionNode> getSize() const { return size; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ArrayTypeNode> arrayType;
        std::shared_ptr<IdentifierNode> name;
        std::shared_ptr<TypeSpecifierNode> elementType;
        std::shared_ptr<ExpressionNode> size;
    };

    class VariableNode : public ExpressionNode {
    public:
        VariableNode(std::shared_ptr<IdentifierNode> name) : name(std::move(name)) {}
        std::shared_ptr<IdentifierNode> getName() const { return name; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<IdentifierNode> name;
    };

    enum class BinaryOpType : uint8_t {
        Add,
        Sub,
        Mul,
        Div,
        Mod,
        BitAnd,
        BitOr,
        BitXor,
        Shl,
        Shr
    };

    class BinaryOpNode : public ExpressionNode {
    public:
        BinaryOpNode(std::shared_ptr<ExpressionNode> left, BinaryOpType op, std::shared_ptr<ExpressionNode> right)
            : left(std::move(left)), op(op), right(std::move(right)) {}
        std::shared_ptr<ExpressionNode> getLeft() const { return left; }
        std::shared_ptr<ExpressionNode> getRight() const { return right; }
        BinaryOpType getOp() const { return op; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> left;
        BinaryOpType op;
        std::shared_ptr<ExpressionNode> right;
    };

    enum class UnaryOpType : uint8_t {
        BitNot, // ~
        LogicalNot, // !
        Negate // -
    };

    class UnaryOpNode : public ExpressionNode {
    public:
        UnaryOpNode(UnaryOpType op, std::shared_ptr<ExpressionNode> operand)
            : op(op), operand(std::move(operand)) {}
        UnaryOpType getOp() const { return op; }
        std::shared_ptr<ExpressionNode> getOperand() const { return operand; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        UnaryOpType op;
        std::shared_ptr<ExpressionNode> operand;
    };

    class CastNode : public ExpressionNode {
    public:
        CastNode(std::shared_ptr<TypeSpecifierNode> targetType, std::shared_ptr<ExpressionNode> operand)
            : targetType(std::move(targetType)), operand(std::move(operand)) {}
        std::shared_ptr<TypeSpecifierNode> getTargetType() const { return targetType; }
        std::shared_ptr<ExpressionNode> getOperand() const { return operand; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<TypeSpecifierNode> targetType;
        std::shared_ptr<ExpressionNode> operand;
    };

    enum class ComparisonOpType : uint8_t {
        Eq,  // ==
        Ne,  // !=
        Lt,  // <
        Gt,  // >
        Le,  // <=
        Ge   // >=
    };

    class ComparisonNode : public ExpressionNode {
    public:
        ComparisonNode(std::shared_ptr<ExpressionNode> left, ComparisonOpType op, std::shared_ptr<ExpressionNode> right)
            : left(std::move(left)), op(op), right(std::move(right)) {}
        std::shared_ptr<ExpressionNode> getLeft() const { return left; }
        std::shared_ptr<ExpressionNode> getRight() const { return right; }
        ComparisonOpType getOp() const { return op; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> left;
        ComparisonOpType op;
        std::shared_ptr<ExpressionNode> right;
    };

    class ConditionalAndNode : public ExpressionNode {
    public:
        ConditionalAndNode(std::shared_ptr<ExpressionNode> left, std::shared_ptr<ExpressionNode> right)
            : left(std::move(left)), right(std::move(right)) {}
        std::shared_ptr<ExpressionNode> getLeft() const { return left; }
        std::shared_ptr<ExpressionNode> getRight() const { return right; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> left;
        std::shared_ptr<ExpressionNode> right;
    };

    class ConditionalOrNode : public ExpressionNode {
    public:
        ConditionalOrNode(std::shared_ptr<ExpressionNode> left, std::shared_ptr<ExpressionNode> right)
            : left(std::move(left)), right(std::move(right)) {}
        std::shared_ptr<ExpressionNode> getLeft() const { return left; }
        std::shared_ptr<ExpressionNode> getRight() const { return right; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> left;
        std::shared_ptr<ExpressionNode> right;
    };

    class AssignmentNode : public ExpressionNode {
    public:
        AssignmentNode(std::shared_ptr<IdentifierNode> lhs, std::shared_ptr<ExpressionNode> rhs)
            : lhs(std::move(lhs)), rhs(std::move(rhs)) {}
        std::shared_ptr<IdentifierNode> getLHS() const { return lhs; }
        std::shared_ptr<ExpressionNode> getRHS() const { return rhs; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<IdentifierNode> lhs;
        std::shared_ptr<ExpressionNode> rhs;
    };

    class UnsafeBlockNode : public StatementNode {
    public:
        UnsafeBlockNode(std::shared_ptr<BlockNode> body) : body(std::move(body)) {}
        std::shared_ptr<BlockNode> getBody() const { return body; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<BlockNode> body;
    };

    class PtrExpressionNode : public ExpressionNode {
    public:
        PtrExpressionNode(std::shared_ptr<ExpressionNode> operand) : operand(std::move(operand)) {}
        std::shared_ptr<ExpressionNode> getOperand() const { return operand; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> operand;
    };

    class PtrLoadNode : public ExpressionNode {
    public:
        PtrLoadNode(std::shared_ptr<ExpressionNode> ptrExpr) : ptrExpr(std::move(ptrExpr)) {}
        std::shared_ptr<ExpressionNode> getPtrExpression() const { return ptrExpr; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> ptrExpr;
    };

    class PtrStoreNode : public ExpressionNode {
    public:
        PtrStoreNode(std::shared_ptr<ExpressionNode> ptrExpr, std::shared_ptr<ExpressionNode> value)
            : ptrExpr(std::move(ptrExpr)), value(std::move(value)) {}
        std::shared_ptr<ExpressionNode> getPtrExpression() const { return ptrExpr; }
        std::shared_ptr<ExpressionNode> getValue() const { return value; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> ptrExpr;
        std::shared_ptr<ExpressionNode> value;
    };

    class RefExpressionNode : public ExpressionNode {
    public:
        RefExpressionNode(std::shared_ptr<ExpressionNode> operand) : operand(std::move(operand)) {}
        std::shared_ptr<ExpressionNode> getOperand() const { return operand; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> operand;
    };

    class ArrayIndexAccessNode : public ExpressionNode {
    public:
        ArrayIndexAccessNode(std::shared_ptr<ExpressionNode> arrayExpr, std::shared_ptr<ExpressionNode> index)
            : arrayExpr(std::move(arrayExpr)), index(std::move(index)) {}
        std::shared_ptr<ExpressionNode> getArrayExpr() const { return arrayExpr; }
        std::shared_ptr<ExpressionNode> getIndex() const { return index; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> arrayExpr;
        std::shared_ptr<ExpressionNode> index;
    };

    class ArrayIndexAssignmentNode : public ExpressionNode {
    public:
        ArrayIndexAssignmentNode(std::shared_ptr<ExpressionNode> arrayExpr,
                                  std::shared_ptr<ExpressionNode> index,
                                  std::shared_ptr<ExpressionNode> value)
            : arrayExpr(std::move(arrayExpr)), index(std::move(index)), value(std::move(value)) {}
        std::shared_ptr<ExpressionNode> getArrayExpr() const { return arrayExpr; }
        std::shared_ptr<ExpressionNode> getIndex() const { return index; }
        std::shared_ptr<ExpressionNode> getValue() const { return value; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> arrayExpr;
        std::shared_ptr<ExpressionNode> index;
        std::shared_ptr<ExpressionNode> value;
    };

    class NewExpressionNode : public ExpressionNode {
    public:
        NewExpressionNode(std::shared_ptr<TypeSpecifierNode> elementType,
                          std::shared_ptr<ExpressionNode> initializer)
            : elementType(std::move(elementType)), initializer(std::move(initializer)) {}
        std::shared_ptr<TypeSpecifierNode> getElementType() const { return elementType; }
        std::shared_ptr<ExpressionNode> getInitializer() const { return initializer; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<TypeSpecifierNode> elementType;
        std::shared_ptr<ExpressionNode> initializer;
    };

    class DeleteStatementNode : public StatementNode {
    public:
        DeleteStatementNode(std::shared_ptr<ExpressionNode> expr) : expression(std::move(expr)) {}
        std::shared_ptr<ExpressionNode> getExpression() const { return expression; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<ExpressionNode> expression;
    };

    class FixedNode : public StatementNode {
    public:
        FixedNode(std::shared_ptr<TypeSpecifierNode> ptrType,
                  std::shared_ptr<IdentifierNode> name,
                  std::shared_ptr<ExpressionNode> init,
                  std::shared_ptr<BlockNode> body)
            : ptrType(std::move(ptrType)), name(std::move(name)), init(std::move(init)), body(std::move(body)) {}
        std::shared_ptr<TypeSpecifierNode> getPtrType() const { return ptrType; }
        std::shared_ptr<IdentifierNode> getName() const { return name; }
        std::shared_ptr<ExpressionNode> getInit() const { return init; }
        std::shared_ptr<BlockNode> getBody() const { return body; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<TypeSpecifierNode> ptrType;
        std::shared_ptr<IdentifierNode> name;
        std::shared_ptr<ExpressionNode> init;
        std::shared_ptr<BlockNode> body;
    };
} // namespace Ryntra::Compiler
