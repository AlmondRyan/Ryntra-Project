#pragma once

#include "TypeSystem.h"
#include "SourceLocation/SourceLocation.h"
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
        virtual void visit(TypedStringLiteralNode &node) = 0;
        virtual void visit(TypedIdentifierNode &node) = 0;
        virtual void visit(TypedFunctionCallNode &node) = 0;
    };

    class ITypedASTNode {
    public:
        virtual ~ITypedASTNode() = default;
        virtual void accept(ITypedVisitor &visitor) = 0;
        virtual std::string toString() const = 0;
        
        SourceLocation getLocation() const { return location; }
        void setLocation(SourceLocation loc) { location = loc; }

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

    private:
        std::string value;
    };

    class TypedIdentifierNode : public TypedExpressionNode {
    public:
        TypedIdentifierNode(std::string name, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), name(std::move(name)) {}
            
        const std::string &getName() const { return name; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedIdentifier(" + name + "): " + type->toString(); }

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

    private:
        std::shared_ptr<TypedExpressionNode> expression;
    };

    class TypedBlockNode : public TypedStatementNode {
    public:
        explicit TypedBlockNode(std::vector<std::shared_ptr<TypedStatementNode>> stmts)
            : statements(std::move(stmts)) {}
            
        const std::vector<std::shared_ptr<TypedStatementNode>> &getStatements() const { return statements; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedBlock"; }

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
        std::string toString() const override { return "TypedFunctionDefinition(" + name + ")"; }

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

    private:
        std::vector<std::shared_ptr<TypedFunctionDefinitionNode>> functions;
    };

} // namespace Ryntra::Compiler::Semantic
