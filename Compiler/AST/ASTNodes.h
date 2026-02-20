#pragma once

#include "ASTVisitor.h"
#include "SourceLocation/SourceLocation.h"

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
        int value;
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

    class BlockNode : public IASTNode {
    public:
        BlockNode(std::vector<std::shared_ptr<StatementNode>> stmts) : statements(std::move(stmts)) {}
        const std::vector<std::shared_ptr<StatementNode>> &getStatements() const { return statements; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::vector<std::shared_ptr<StatementNode>> statements;
    };

    class FunctionDefinitionNode : public IASTNode {
    public:
        FunctionDefinitionNode(std::shared_ptr<TypeSpecifierNode> type, std::shared_ptr<IdentifierNode> name, std::shared_ptr<BlockNode> body)
            : returnType(std::move(type)), name(std::move(name)), body(std::move(body)) {}
        std::shared_ptr<TypeSpecifierNode> getReturnType() const { return returnType; }
        std::shared_ptr<IdentifierNode> getName() const { return name; }
        std::shared_ptr<BlockNode> getBody() const { return body; }
        void accept(IVisitor &visitor) override;
        std::string toString() const override;

    private:
        std::shared_ptr<TypeSpecifierNode> returnType;
        std::shared_ptr<IdentifierNode> name;
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
} // namespace Ryntra::Compiler