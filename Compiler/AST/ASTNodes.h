#pragma once
#include <memory>
#include <string>
#include <vector>
#include <variant>
#include <any>

namespace Ryntra::Compiler {
    class IASTVisitor;
    /**
     * @brief Abstract AST Node Type Base Class, defined @c toString() function to debug.
     */
    class IASTNode : public std::enable_shared_from_this<IASTNode> {
    public:
        virtual ~IASTNode() = default;
        virtual std::string toString() const = 0;
        virtual std::any accept(IASTVisitor* visitor) = 0;
    };

    /**
     * @brief Base class for literal nodes. Defines the @c getValue()
     * function to retrieve the literal's value.
     */
    class LiteralNode : public IASTNode {
    public:
        virtual std::variant<int, std::string> getValue() const = 0;
    };

    /**
     * @brief Integer literal node, inheriting from the @c LiteralNode base class,
     * overrides the @c getValue() function to return the internal integer value.
     */
    class IntegerLiteralNode : public LiteralNode {
    public:
        IntegerLiteralNode(int val) : value(val) {}
        std::variant<int, std::string> getValue() const override {
            return value;
        }

        std::string toString() const override {
            return "IntegerLiteral(" + std::to_string(value) + ")";
        }

        std::any accept(IASTVisitor* visitor) override;
    private:
        int value;
    };

    /**
     * @brief String literal node, inheriting from the @c LiteralNode base class,
     * overrides the @c getValue() function to retrieve the internal string value.
     */
    class StringLiteralNode : public LiteralNode {
    public:
        StringLiteralNode(std::string val) : value(val) {}
        std::variant<int, std::string> getValue() const override {
            return value;
        }

        std::string toString() const override {
            return "StringLiteral(" + value + ")";
        }

        std::any accept(IASTVisitor* visitor) override;
    private:
        std::string value;
    };

    /**
     * @brief Identifier node, defining the @c getName() function to return the identifier
     */
    class IdentifierNode : public IASTNode {
    public:
        IdentifierNode(const std::string &n) : name(n) {}
        std::string toString() const override {
            return "Identifier(" + name + ")";
        }

        const std::string &getName() const {
            return name;
        }

        std::any accept(IASTVisitor* visitor) override;
    private:
        std::string name;
    };

    /**
     * @brief Function call node, using @c std::vector<std::shared_ptr>> to store parameter nodes
     * @details Why choose `@c std::shared_ptr<>`? Because it supports polymorphism and automatic memory management,
     * allowing us to store AST nodes of different types.
     */
    class FunctionCallNode : public IASTNode {
    public:
        FunctionCallNode(const std::string &n, std::vector<std::shared_ptr<IASTNode>> arg)
                : functionName(n), arguments(arg) {}

        std::string toString() const override {
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

        std::any accept(IASTVisitor* visitor) override;

        std::string getFunctionName() const {
            return functionName;
        }

        std::vector<std::shared_ptr<IASTNode>> getArguments() const {
            return arguments;
        }
    private:
        std::string functionName;
        std::vector<std::shared_ptr<IASTNode>> arguments;
    };

    class StatementNode : public IASTNode {};

    class VariableDeclarationNode : public StatementNode {
    public:
        VariableDeclarationNode(const std::string &name, std::shared_ptr<IASTNode> init = nullptr)
            : varName(name), initialValue(std::move(init)) {}

        std::string toString() const override {
            if (initialValue) {
                return "VariableDeclaration(" + varName + ", " + initialValue->toString() + ")";
            }
            return "VariableDeclaration(" + varName + ")";
        }

        std::any accept(IASTVisitor* visitor) override;
    private:
        std::string varName;
        std::shared_ptr<IASTNode> initialValue; // WARN: Possible be nullptr if there are no parameters
    };

    class ReturnStatementNode : public StatementNode {
    public:
        ReturnStatementNode(std::shared_ptr<IASTNode> value) : returnValue(std::move(value)) {}
        std::string toString() const override {
            return "ReturnStatement(" + returnValue->toString() + ")";
        }

        std::any accept(IASTVisitor* visitor) override;
    private:
        std::shared_ptr<IASTNode> returnValue;
    };

    class FunctionCallStatementNode : public StatementNode {
    public:
        FunctionCallStatementNode(std::shared_ptr<FunctionCallNode> fcall) : functionCall(std::move(fcall)) {}
        std::string toString() const override {
            return "FunctionCallStatement(" + functionCall->toString() + ")";
        }

        std::any accept(IASTVisitor* visitor) override;
    private:
        std::shared_ptr<FunctionCallNode> functionCall;
    };

    class EmptyStatementNode : public StatementNode {
    public:
        std::string toString() const override {
            return "EmptyStatement";
        }

        std::any accept(IASTVisitor* visitor) override;
    };

    class ExpressionStatementNode : public StatementNode {
    public:
        ExpressionStatementNode(std::shared_ptr<IASTNode> expr) : expression(std::move(expr)) {}
        std::string toString() const override {
            return "ExpressionStatement(" + expression->toString() + ")";
        }

        std::any accept(IASTVisitor* visitor) override;
    private:
        std::shared_ptr<IASTNode> expression;
    };

    class ParameterNode : public IASTNode {
    public:
        ParameterNode(const std::string &t, const std::string &n)
            : type(t), name(n) {}

        std::string toString() const override {
            return "Parameter(" + type + " " + name + ")";
        }

        std::any accept(IASTVisitor* visitor) override;
    private:
        std::string type;
        std::string name;
    };

    class BlockNode : public IASTNode {
    public:
        BlockNode(std::vector<std::shared_ptr<StatementNode>> stmts) : statements(std::move(stmts)) {}
        void addStatement(std::shared_ptr<StatementNode> stmt) {
            statements.push_back(std::move(stmt));
        }

        std::string toString() const override {
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

        std::any accept(IASTVisitor* visitor) override;
    private:
        std::vector<std::shared_ptr<StatementNode>> statements;
    };

    class FunctionDefinitionNode : public IASTNode {
    public:
        FunctionDefinitionNode(const std::string& retType,
                          const std::string& name,
                          std::vector<std::shared_ptr<ParameterNode>> params,
                          std::shared_ptr<BlockNode> b)
        : returnType(retType), functionName(name),
          parameters(std::move(params)), body(std::move(b)) {}

        std::string toString() const override {
            std::string result = "FunctionDef(" + returnType + " " + functionName + "(";
            for (const auto& param : parameters) {
                result += param->toString() + ", ";
            }
            if (!parameters.empty()) {
                result.pop_back();
                result.pop_back();
            }
            result += "), " + body->toString() + ")";
            return result;
        }

        std::any accept(IASTVisitor* visitor) override;

        std::string getReturnType() const {
            return returnType;
        }

        std::string getFunctionName() const {
            return functionName;
        }

        std::vector<std::shared_ptr<ParameterNode>> getParameters() const {
            return parameters;
        }
    private:
        std::string returnType;
        std::string functionName;
        std::vector<std::shared_ptr<ParameterNode>> parameters;
        std::shared_ptr<BlockNode> body;
    };

    class ProgramNode : public IASTNode {
    public:
        ProgramNode(std::vector<std::shared_ptr<FunctionDefinitionNode>> funcs)
            : functions(std::move(funcs)) {}

        void addFunction(std::shared_ptr<FunctionDefinitionNode> func) {
            functions.push_back(std::move(func));
        }

        std::string toString() const override {
            std::string result = "Program([";
            for (const auto& func : functions) {
                result += func->toString() + ", ";
            }
            if (!functions.empty()) {
                result.pop_back();
                result.pop_back();
            }
            result += "])";
            return result;
        }

        std::any accept(IASTVisitor* visitor) override;

        std::vector<std::shared_ptr<FunctionDefinitionNode>> getFunctions() const {
            return functions;
        }
    private:
        std::vector<std::shared_ptr<FunctionDefinitionNode>> functions;
    };
}
