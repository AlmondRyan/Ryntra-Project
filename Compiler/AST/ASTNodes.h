#pragma once
#include "SourceLocation/SourceLocation.h"

#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace Ryntra::Compiler {
    // Forward Declaration
    class IASTVisitor;
    class UnaryExpressionNode;

    /**
     * @brief AST (Abstract Syntax Tree) Node Bass Class
     * @details The general interfaces for all AST Nodes. Provides visitor mode
     * and string representation.
     */
    class IASTNode : public std::enable_shared_from_this<IASTNode> {
    public:
        /**
         * @brief Virtual Destructor.
         */
        virtual ~IASTNode() = default;

        /**
         * @brief Get the string representation for the nodes.
         * @return The string representation.
         */
        virtual std::string toString() const = 0;

        /**
         * @brief Accept the visiting of visitor.
         * @param visitor The pointer that points to the visitor.
         */
        virtual void accept(IASTVisitor *visitor) = 0;

        /**
         * @brief Get Source Location of the Node.
         * @return Source Location that contains row and column information
         */
        SourceLocation getLocation() const { return location; }

        /**
         * @brief Set Source Location of the Node
         * @param loc Source Location that contains row and column information
         */
        void setLocation(SourceLocation loc) { location = loc; }

    private:
        SourceLocation location;
    };

    /**
     * @brief The abstract base class for Literal Nodes.
     * @details Inherited from IASTNode. All the Literal Nodes based on
     * this class.
     */
    class LiteralNode : public IASTNode {
    public:
    };

    /**
     * @brief Integer Literal Node.
     * @details Represent the Integer Constant in AST. Integer Literal
     * is the value of a int. Such as `int i = 10;` The 10 is the Integer
     * Literal.
     */
    class IntegerLiteralNode : public LiteralNode {
    public:
        /**
         * @brief The Constructor.
         * @param val The value of the Integer Node.
         */
        IntegerLiteralNode(int val) : value(val) {
        }

        /**
         * @brief Get the value.
         * @return The int that contains the value.
         */
        int getValue() const;

        /**
         * @brief The string representation of the Integer Literal Node.
         * @return The string representation. Forms like "IntegerLiteral(value)"
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         * @return The result.
         */
        void accept(IASTVisitor *visitor) override;

    private:
        int value;
    };

    /**
     * @brief The String Literal Node.
     * @details Represents the String Constant Node in AST. String Literal
     * is literally the value of a string. Such as `string str = "abc";`
     * The @c "abc" is the string literal.
     */
    class StringLiteralNode : public LiteralNode {
    public:
        /**
         * @brief The Constructor. Accepts the value of the node.
         * @param val The value of the node.
         */
        StringLiteralNode(std::string val) : value(val) {
        }

        /**
         * @brief Get the value of the string.
         * @return The string value.
         */
        std::string getValue() const;

        /**
         * @brief Get the string representation of the node.
         * @return The string forms like "StringLiteral(Value)".
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         * @return The result.
         */
        void accept(IASTVisitor *visitor) override;

    private:
        std::string value;
    };

    /**
     * @brief The Boolean Literal Node.
     * @details Represents the Boolean Constant Node in AST.
     */
    class BooleanLiteralNode : public LiteralNode {
    public:
        /**
         * @brief The Constructor.
         * @param val The value of the node.
         */
        BooleanLiteralNode(bool val) : value(val) {}

        /**
         * @brief Get the value.
         * @return The boolean value.
         */
        bool getValue() const { return value; }

        /**
         * @brief Get the string representation.
         * @return The string representation.
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

    private:
        bool value;
    };

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
        const std::string &getName() const { return name; }

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

    private:
        std::string name;
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
     * @brief The Variable Declaration Node.
     * @details A Variable Declaration is a statement that formed like
     * `[type] [name] (= [value])`.
     */
    class VariableDeclarationNode : public StatementNode {
    public:
        /**
         * @brief The Constructor. Accepts the variable type, name and variable
         * initial value.
         * @param type The variable type.
         * @param name The variable name.
         * @param init The variable initial value.
         */
        VariableDeclarationNode(const std::string &type, const std::string &name, std::shared_ptr<IASTNode> init = nullptr)
            : varType(type), varName(name), initialValue(std::move(init)) {}

        /**
         * @brief Get the string representation of VariableDeclaration
         * Node.
         * @return A string that formed like
         * VariableDeclaration(type name, value) or VariableDeclaration(type name)
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

        /**
         * @brief Get the type of the Variable.
         * @return The type of the variable.
         */
        const std::string &getVarType() const { return varType; }

        /**
         * @brief Get the name of the Variable.
         * @return The name of the variable.
         */
        const std::string &getVarName() const { return varName; }

        /**
         * @brief Get the initial value of the variable.
         * @return The initial value of the variable.
         */
        std::shared_ptr<IASTNode> getInitialValue() const { return initialValue; }

    private:
        std::string               varType;
        std::string               varName;
        std::shared_ptr<IASTNode> initialValue; // WARN: Possible be nullptr if there are no parameters
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
     * @brief The Parameter Node.
     * @details Represents a parameter in function declaration or definition.
     * Contains both the type and name of the parameter. Such as `foo(int a)` where
     * the `int a` is the parameter.
     */
    class ParameterNode : public IASTNode {
    public:
        /**
         * @brief The Constructor.
         * @param t The type of the parameter.
         * @param n The name of the parameter.
         */
        ParameterNode(const std::string &t, const std::string &n)
            : type(t), name(n) {}

        /**
         * @brief Get the string representation of the Parameter Node.
         * @return A string that formed like "Parameter(type name)".
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

        /**
         * @brief Get the type of the parameter.
         * @return The parameter type.
         */
        const std::string &getType() const { return type; }

        /**
         * @brief Get the name of the parameter.
         * @return The parameter name.
         */
        const std::string &getName() const { return name; }

    private:
        std::string type;
        std::string name;
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

    /**
     * @brief The Function Definition Node.
     * @details Represents a complete function definition including its
     * return type, name, parameters and the function body.
     */
    class FunctionDefinitionNode : public IASTNode {
    public:
        /**
         * @brief The Constructor.
         * @param retType The return type of the function.
         * @param name The name of the function.
         * @param params The parameters of the function.
         * @param b The body of the function. Which is a block.
         */
        FunctionDefinitionNode(const std::string                          &retType,
                               const std::string                          &name,
                               std::vector<std::shared_ptr<ParameterNode>> params,
                               std::shared_ptr<BlockNode>                  b)
            : returnType(retType), functionName(name),
              parameters(std::move(params)), body(std::move(b)) {}

        /**
         * @brief Get the string representation of the Function Definition Node.
         * @return A string that formed like "FunctionDef(returnType name(param1, param2, ...), body)".
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

        /**
         * @brief Get the return type of the function.
         * @return The return type as string.
         */
        std::string getReturnType() const { return returnType; }

        /**
         * @brief Get the name of the function.
         * @return The function name.
         */
        std::string getFunctionName() const { return functionName; }

        /**
         * @brief Get the parameters of the function.
         * @return Vector of parameter nodes.
         */
        std::vector<std::shared_ptr<ParameterNode>> getParameters() const {
            return parameters;
        }

        /**
         * @brief Get the body of the function.
         * @return The block node representing the function body.
         */
        std::shared_ptr<BlockNode> getBody() const { return body; }

    private:
        std::string                                 returnType;
        std::string                                 functionName;
        std::vector<std::shared_ptr<ParameterNode>> parameters;
        std::shared_ptr<BlockNode>                  body;
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
         */
        AssignmentExpressionNode(std::string id, std::shared_ptr<IASTNode> exp) : identifier(std::move(id)), expression(std::move(exp)) {}

        /**
         * @brief Get the string representation of the Assignment Expression Node.
         * @return A string representation of the form "AssignmentExpression(identifier = expression)".
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

    private:
        std::string               identifier; ///< The identifier (variable name) being assigned to
        std::shared_ptr<IASTNode> expression; ///< The expression providing the value for assignment
    };

    /**
     * @brief The Program Node representing the entire program structure.
     * @details This class represents the root node of the AST that contains all function definitions
     * in the program. It serves as the top-level container for the complete source code structure.
     */
    class ProgramNode : public IASTNode {
    public:
        /**
         * @brief Constructor that initializes the ProgramNode with a vector of functions.
         * @param funcs The vector containing all function definitions in the program.
         */
        ProgramNode(std::vector<std::shared_ptr<FunctionDefinitionNode>> funcs)
            : functions(std::move(funcs)) {}

        /**
         * @brief Adds a new function to the program.
         * @param func The function definition to be added to the program.
         */
        void addFunction(std::shared_ptr<FunctionDefinitionNode> func) {
            functions.push_back(std::move(func));
        }

        /**
         * @brief Get the string representation of the Program Node.
         * @return A string representation showing all functions in the program.
         */
        std::string toString() const override;

        /**
         * @brief Accepts the visiting from the visitor.
         * @param visitor The pointer that points to the visitor.
         */
        void accept(IASTVisitor *visitor) override;

        /**
         * @brief Get all functions defined in the program.
         * @return Vector containing all function definitions in the program.
         */
        std::vector<std::shared_ptr<FunctionDefinitionNode>> getFunctions() const {
            return functions;
        }

    private:
        std::vector<std::shared_ptr<FunctionDefinitionNode>> functions;
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
} // namespace Ryntra::Compiler
