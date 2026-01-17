#pragma once
#include "AST/ASTNodes.h"

namespace Ryntra::Compiler {
    /**
     * @brief The Identifier Node.
     * @details Represents the Identifier in AST. The Identifier is the
     * "name" of the fields. Such as the name of the variable.
     */
    class IdentifierNode : public IASTNode {
    public:
        /**
         * @brief The Constructor. Accepts the value of the Identifier Node.
         * @param n The value of the node.
         */
        IdentifierNode(const std::string &n) : name(n) {}

        /**
         * @brief Get the string representation of the Node.
         * @return A string forms like "Identifier(Value)".
         */
        std::string toString() const override;

        /**
         * @brief Get the name of the identifier.
         * @return The name of the Identifier.
         */
        const std::string getName() const { return name; }

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

    private:
        std::string name;
    };

    /**
     * @brief The Binary Expression Node representing binary operations.
     * @details This class represents expressions that contain two operands and an operator,
     * such as arithmetic operations (addition, subtraction), comparison operations, etc.
     * Examples include expressions like `a + b`, `x > y`, `i == j`.
     */
    class BinaryExpressionNode : public IASTNode {
    public:
        /**
         * @brief Constructor that creates a binary expression node.
         * @param l The left operand of the binary expression.
         * @param r The right operand of the binary expression.
         * @param opr The operator symbol (e.g., "+", "-", "*", "/", "==", "<", etc.).
         */
        BinaryExpressionNode(std::shared_ptr<IASTNode> l, std::shared_ptr<IASTNode> r,
                             std::string opr) : left(std::move(l)), right(std::move(r)), operand(std::move(opr)) {}

        /**
         * @brief Get the string representation of the Binary Expression Node.
         * @return A string representation of the form "BinaryExpression(left op right)".
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

        /**
         * @brief Get the left operand of the binary expression.
         * @return The left operand node.
         */
        std::shared_ptr<IASTNode> getLeft() const { return left; }

        /**
         * @brief Get the right operand of the binary expression.
         * @return The right operand node.
         */
        std::shared_ptr<IASTNode> getRight() const { return right; }

        /**
         * @brief Get the operator of the binary expression.
         * @return The operator string (e.g., "+", "-", "==").
         */
        std::string getOp() const { return operand; }

    private:
        std::shared_ptr<IASTNode> left;  ///< The left operand of the binary expression
        std::shared_ptr<IASTNode> right; ///< The right operand of the binary expression
        std::string               operand;
    };

    /**
     * @brief The Unary Expression Node representing unary operations.
     * @details This class represents expressions that contain one operand and an operator,
     * such as logical NOT or arithmetic negation.
     * Examples include expressions like `!flag`, `-count`.
     */
    class UnaryExpressionNode : public IASTNode {
    public:
        /**
         * @brief Constructor that creates a unary expression node.
         * @param opr The operator symbol (e.g., "!", "-").
         * @param expr The operand of the unary expression.
         */
        UnaryExpressionNode(std::string opr, std::shared_ptr<IASTNode> expr)
            : operand(std::move(opr)), expression(std::move(expr)) {}

        /**
         * @brief Get the string representation of the Unary Expression Node.
         * @return A string representation of the form "UnaryExpression(op expression)".
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

        /**
         * @brief Get the operator of the unary expression.
         * @return The operator string.
         */
        std::string getOp() const { return operand; }

        /**
         * @brief Get the expression of the unary expression.
         * @return The operand expression node.
         */
        std::shared_ptr<IASTNode> getExpression() const { return expression; }

    private:
        std::string               operand;
        std::shared_ptr<IASTNode> expression;
    };

    /**
     * @brief The Assignment Expression Node representing assignment operations.
     * @details This class represents assignment expressions of the form `identifier = expression`,
     * where a value or result of an expression is assigned to a variable/identifier.
     * Example: `x = 5`, `y = a + b`, `counter = counter + 1`.
     */
    class AssignmentExpressionNode : public IASTNode {
    public:
        /**
         * @brief Constructor that creates an assignment expression node.
         * @param id The identifier (variable name) being assigned to.
         * @param exp The expression whose value will be assigned to the identifier.
         * @param opr The assignment operator (e.g., "=", "+=", etc.).
         */
        AssignmentExpressionNode(std::string id, std::shared_ptr<IASTNode> exp, std::string opr = "=")
            : identifier(std::move(id)), expression(std::move(exp)), operand(std::move(opr)) {}

        /**
         * @brief Get the string representation of the Assignment Expression Node.
         * @return A string representation of the form "AssignmentExpression(identifier op expression)".
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

        /**
         * @brief Get the identifier being assigned to.
         * @return The identifier name as a string reference.
         */
        const std::string &getIdentifier() const { return identifier; }

        /**
         * @brief Get the expression being assigned.
         * @return The expression node that provides the value for assignment.
         */
        std::shared_ptr<IASTNode> getExpression() const { return expression; }

        /**
         * @brief Get the operator used in assignment.
         * @return The operator string.
         */
        const std::string &getOp() const { return operand; }

    private:
        std::string               identifier; ///< The identifier (variable name) being assigned to
        std::shared_ptr<IASTNode> expression; ///< The expression providing the value for assignment
        std::string               operand;    ///< The assignment operator (e.g., "=", "+=", etc.)
    };

    /**
     * @brief The Function Call Node.
     * @details FunctionCall is an expression that forms like `foo(value)`
     * and NOT end with semicolon. Because the value is used.
     * FunctionCallStatement contains the FunctionCall.
     */
    class FunctionCallNode : public IASTNode {
    public:
        /**
         * @brief The Constructor.
         * @param n The name of the Function
         * @param arg The argument list of the Function
         */
        FunctionCallNode(const std::string &n, std::vector<std::shared_ptr<IASTNode>> arg)
            : functionName(n), arguments(arg) {}

        /**
         * @brief Get the string representation of the FunctionCall Node.
         * @details For example, a function that the signature like:
         * `foo(bar)`, the representation is like `FunctionCall(foo, [bar])`.
         * @return The string representation.
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

        /**
         * @brief Get the name of the function.
         * @return The name of the function.
         */
        std::string getFunctionName() const { return functionName; }

        /**
         * @brief Get the argument list of the function.
         * @return The argument list of the function.
         */
        std::vector<std::shared_ptr<IASTNode>> getArguments() const { return arguments; }

    private:
        std::string                            functionName;
        std::vector<std::shared_ptr<IASTNode>> arguments;
    };

    class PostfixExpressionNode : public IASTNode {
    public:
        PostfixExpressionNode(const std::string& name, const std::string& op)
            : varName(name), op(op) {}

        std::string toString() const override;
        void accept(IASTVisitor* visitor) override;

        const std::string& getVarName() const { return varName; }
        const std::string& getOp() const { return op; }

    private:
        std::string varName;
        std::string op;
    };
} // namespace Ryntra::Compiler