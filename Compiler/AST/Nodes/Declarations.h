#pragma once
#include "AST/ASTNodes.h"

namespace Ryntra::Compiler {
    class StatementNode;

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
} // namespace Ryntra::Compiler