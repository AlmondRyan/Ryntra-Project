#pragma once
#include "AST/ASTNodes.h"

namespace Ryntra::Compiler {
    /**
     * @brief The Statement Node, inherited from IASTNode.
     * @details Design this class as an empty class can be really helpful
     * to implement the Visitor mode.
     * It not only be a placeholder, but also can clarify the statement
     * and expression.
     */
    class StatementNode : public IASTNode {
    };

    /**
     * @brief The Return Statement Node.
     * @details A Return Statement is formed like `return [Value]`.
     */
    class ReturnStatementNode : public StatementNode {
    public:
        /**
         * @brief The Constructor.
         * @param value The value that returns.
         */
        ReturnStatementNode(std::shared_ptr<IASTNode> value) : returnValue(std::move(value)) {}

        /**
         * @brief Get the string representation of the Node.
         * @return A string that formed like `ReturnStatement(Value)`
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

        /**
         * @brief Get the returning value.
         * @return The returning value.
         */
        std::shared_ptr<IASTNode> getReturnValue() const { return returnValue; }

    private:
        std::shared_ptr<IASTNode> returnValue;
    };

    /**
     * @brief The Function Call Statement Node.
     * @details It is different between FunctionCallNode. FunctionCallStatement
     * is formed like `foo(value);` and end with a semicolon;
     */
    class FunctionCallStatementNode : public StatementNode {
    public:
        /**
         * @brief The Constructor.
         * @param fcall The main function call that contains in.
         */
        FunctionCallStatementNode(std::shared_ptr<FunctionCallNode> fcall) : functionCall(std::move(fcall)) {}

        /**
         * @brief Get the string representation of the FunctionCallStatement.
         * @return A string that formed like: `FunctionCallStatement(function)`
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

        /**
         * @brief Get the Function Call that contains.
         * @return The Function Call that contains in.
         */
        std::shared_ptr<FunctionCallNode> getFunctionCall() const { return functionCall; }

    private:
        std::shared_ptr<FunctionCallNode> functionCall;
    };

    /**
     * @brief The Empty Statement Node.
     * @details Represents an empty statement in AST. Typically corresponds
     * to a standalone semicolon. Used for cases like an empty loop bodies or an
     * empty conditional blocks.
     */
    class EmptyStatementNode : public StatementNode {
    public:
        /**
         * @brief Get the string representation of the Empty Statement Node.
         * @return A string that formed like "EmptyStatement".
         */
        std::string toString() const override { return "EmptyStatement"; }

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;
    };

    /**
     * @brief The Expression Statement Node.
     * @details Represents an expression followed by a semicolon that forms
     * a statement. Such as `x + y;` where the result might not be stored.
     */
    class ExpressionStatementNode : public StatementNode {
    public:
        /**
         * @brief The Constructor.
         * @param expr The expression that forms the statement.
         */
        ExpressionStatementNode(std::shared_ptr<IASTNode> expr) : expression(std::move(expr)) {}

        /**
         * @brief Get the string representation of the Expression Statement Node.
         * @return A string that formed like "ExpressionStatement(Expression)".
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

        /**
         * @brief Get the Expression contained in the statement.
         * @return The expression node.
         */
        std::shared_ptr<IASTNode> getExpression() const { return expression; }

    private:
        std::shared_ptr<IASTNode> expression;
    };

    /**
     * @brief The Block Node.
     * @details Represents a block of statement that closed in braces `{}`.
     * Contains a collection of statements that forms a scope.
     */
    class BlockNode : public IASTNode {
    public:
        /**
         * @brief The Constructor.
         * @param stmts The vector of statements that compose the block.
         */
        BlockNode(std::vector<std::shared_ptr<StatementNode>> stmts) : statements(std::move(stmts)) {}

        /**
         * @brief Add a statement to the block.
         * @param stmt The statement will be added.
         */
        void addStatement(std::shared_ptr<StatementNode> stmt) {
            statements.push_back(std::move(stmt));
        }

        /**
         * @brief Get the string representation of the Block Node.
         * @return A string that formed like "Block([statement1, statement2, ...])".
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

        /**
         * @brief Get the statements that closed in braces.
         * @return The statements.
         */
        std::vector<std::shared_ptr<StatementNode>> getStatements() const {
            return statements;
        }

    private:
        std::vector<std::shared_ptr<StatementNode>> statements;
    };

    class IfStatementNode : public StatementNode {
    public:
        IfStatementNode(std::shared_ptr<IASTNode> cond, std::shared_ptr<BlockNode> then, std::shared_ptr<IASTNode> els = nullptr)
            : condition(std::move(cond)), thenBody(std::move(then)), elseBody(std::move(els)) {}

        std::string toString() const override;

        void accept(IASTVisitor *visitor) override;

        std::shared_ptr<IASTNode>  getCondition() const { return condition; }
        std::shared_ptr<BlockNode> getThenBody() const { return thenBody; }
        std::shared_ptr<IASTNode>  getElseBody() const { return elseBody; }

    private:
        std::shared_ptr<IASTNode>  condition;
        std::shared_ptr<BlockNode> thenBody;
        std::shared_ptr<IASTNode>  elseBody; ///< This could be nullptr if there's no else
    };

    class WhileStatementNode : public StatementNode {
    public:
        WhileStatementNode(std::shared_ptr<IASTNode> cond, std::shared_ptr<BlockNode> body)
            : condition(std::move(cond)), body(std::move(body)) {}

        std::string toString() const override;
        void        accept(IASTVisitor *visitor) override;

        std::shared_ptr<IASTNode>  getCondition() const { return condition; }
        std::shared_ptr<BlockNode> getBody() const { return body; }

    private:
        std::shared_ptr<IASTNode>  condition;
        std::shared_ptr<BlockNode> body;
    };

    class ForStatementNode : public StatementNode {
    public:
        ForStatementNode(std::shared_ptr<IASTNode> init, std::shared_ptr<IASTNode> cond, std::shared_ptr<IASTNode> inc, std::shared_ptr<BlockNode> body)
            : init(std::move(init)), condition(std::move(cond)), increment(std::move(inc)), body(std::move(body)) {}

        std::string toString() const override;
        void        accept(IASTVisitor *visitor) override;

        std::shared_ptr<IASTNode>  getInit() const { return init; }
        std::shared_ptr<IASTNode>  getCondition() const { return condition; }
        std::shared_ptr<IASTNode>  getIncrement() const { return increment; }
        std::shared_ptr<BlockNode> getBody() const { return body; }

    private:
        std::shared_ptr<IASTNode>  init;
        std::shared_ptr<IASTNode>  condition;
        std::shared_ptr<IASTNode>  increment;
        std::shared_ptr<BlockNode> body;
    };

    class BreakStatementNode : public StatementNode {
    public:
        std::string toString() const override;
        void        accept(IASTVisitor *visitor) override;
    };

    class ContinueStatementNode : public StatementNode {
    public:
        std::string toString() const override;
        void        accept(IASTVisitor *visitor) override;
    };
} // namespace Ryntra::Compiler