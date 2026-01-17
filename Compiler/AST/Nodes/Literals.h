#pragma once
#include "AST/ASTNodes.h"

namespace Ryntra::Compiler {
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
     * is the value of a long long. Such as `long long i = 10;` The 10 is the Integer
     * Literal.
     */
    class IntegerLiteralNode : public LiteralNode {
    public:
        /**
         * @brief The Constructor.
         * @param val The value of the Integer Node.
         * @param kind The inferred type kind of the literal.
         */
        IntegerLiteralNode(long long val, TypeKind kind = TypeKind::Int) : value(val), typeKind(kind) {
        }

        /**
         * @brief Get the value.
         * @return The long long that contains the value.
         */
        long long getValue() const;

        /**
         * @brief Get the inferred type kind.
         * @return The TypeKind.
         */
        TypeKind getTypeKind() const { return typeKind; }

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
        long long value;
        TypeKind  typeKind;
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
     * @brief The Floating Literal Node.
     * @details Represents the Floating Constant Node in AST.
     */
    class FloatingLiteralNode : public LiteralNode {
    public:
        /**
         * @brief The Constructor.
         * @param val The value of the node.
         * @param kind The inferred type kind (Float or Double).
         */
        FloatingLiteralNode(double val, TypeKind kind = TypeKind::Double) : value(val), typeKind(kind) {}

        /**
         * @brief Get the value.
         * @return The double value.
         */
        double getValue() const { return value; }

        /**
         * @brief Get the inferred type kind.
         * @return The TypeKind.
         */
        TypeKind getTypeKind() const { return typeKind; }

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
        double   value;
        TypeKind typeKind;
    };
} // namespace Ryntra::Compiler