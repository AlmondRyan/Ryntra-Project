#pragma once
#include "Semantic/Symbol.h"
#include "SourceLocation/SourceLocation.h"

#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace Ryntra::Compiler {
    // Forward Declaration
    class IASTVisitor;
    class BlockNode;
    class ParameterNode;

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
} // namespace Ryntra::Compiler
