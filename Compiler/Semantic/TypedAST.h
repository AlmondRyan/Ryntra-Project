#pragma once

#include "TypeSystem.h"
#include "SourceLocation/SourceLocation.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

namespace Ryntra::Compiler::Semantic {

    class TypedExpressionNode;
    class TypedStatementNode;
    class TypedProgramNode;
    class TypedFunctionDefinitionNode;
    class TypedBlockNode;
    class TypedStringLiteralNode;
    class TypedIntegerLiteralNode;
    class TypedIdentifierNode;
    class TypedFunctionCallNode;
    class TypedExpressionStatementNode;
    class TypedReturnNode;

    class ITypedVisitor {
    public:
        virtual ~ITypedVisitor() = default;
        virtual void visit(TypedProgramNode &node) = 0;
        virtual void visit(TypedFunctionDefinitionNode &node) = 0;
        virtual void visit(TypedBlockNode &node) = 0;
        virtual void visit(TypedExpressionStatementNode &node) = 0;
        virtual void visit(TypedReturnNode &node) = 0;
        virtual void visit(TypedStringLiteralNode &node) = 0;
        virtual void visit(TypedIntegerLiteralNode &node) = 0;
        virtual void visit(TypedIdentifierNode &node) = 0;
        virtual void visit(TypedFunctionCallNode &node) = 0;
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
            for (int i = 0; i < indent; ++i) std::cout << "  ";
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
