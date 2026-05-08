#pragma once

#include "TypeSystem.h"
#include "SourceLocation/SourceLocation.h"
#include "../AST/ASTNodes.h"
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
    class TypedVariableNode;
    class TypedVariableDeclarationNode;
    class TypedBinaryOpNode;
    class TypedAssignmentNode;

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
        virtual void visit(TypedVariableNode &node) = 0;
        virtual void visit(TypedVariableDeclarationNode &node) = 0;
        virtual void visit(TypedBinaryOpNode &node) = 0;
        virtual void visit(TypedAssignmentNode &node) = 0;
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

    class TypedVariableNode : public TypedExpressionNode {
    public:
        TypedVariableNode(std::string name, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), name(std::move(name)) {}

        const std::string &getName() const { return name; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedVariable(" + name + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string name;
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

    class TypedVariableDeclarationNode : public TypedStatementNode {
    public:
        TypedVariableDeclarationNode(std::string name, std::shared_ptr<Type> type, std::shared_ptr<TypedExpressionNode> init)
            : name(std::move(name)), type(std::move(type)), initializer(std::move(init)) {}

        const std::string &getName() const { return name; }
        std::shared_ptr<Type> getType() const { return type; }
        std::shared_ptr<TypedExpressionNode> getInitializer() const { return initializer; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedVariableDeclaration(" + name + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            if (initializer) {
                initializer->dump(indent + 1);
            }
        }

    private:
        std::string name;
        std::shared_ptr<Type> type;
        std::shared_ptr<TypedExpressionNode> initializer;
    };

    class TypedBinaryOpNode : public TypedExpressionNode {
    public:
        TypedBinaryOpNode(std::shared_ptr<TypedExpressionNode> left, BinaryOpType op, std::shared_ptr<TypedExpressionNode> right, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), left(std::move(left)), op(op), right(std::move(right)) {}

        std::shared_ptr<TypedExpressionNode> getLeft() const { return left; }
        std::shared_ptr<TypedExpressionNode> getRight() const { return right; }
        BinaryOpType getOp() const { return op; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override {
            std::string opStr;
            switch (op) {
            case BinaryOpType::Add: opStr = "+"; break;
            case BinaryOpType::Sub: opStr = "-"; break;
            case BinaryOpType::Mul: opStr = "*"; break;
            case BinaryOpType::Div: opStr = "/"; break;
            case BinaryOpType::Mod: opStr = "%"; break;
            }
            return "TypedBinaryOp(" + opStr + "): " + type->toString();
        }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Left:" << std::endl;
            left->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Right:" << std::endl;
            right->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> left;
        BinaryOpType op;
        std::shared_ptr<TypedExpressionNode> right;
    };

    class TypedAssignmentNode : public TypedExpressionNode {
    public:
        TypedAssignmentNode(std::string variableName, std::shared_ptr<TypedExpressionNode> rhs, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), variableName(std::move(variableName)), rhs(std::move(rhs)) {}

        const std::string &getVariableName() const { return variableName; }
        std::shared_ptr<TypedExpressionNode> getRHS() const { return rhs; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedAssign(" + variableName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "RHS:" << std::endl;
            rhs->dump(indent + 2);
        }

    private:
        std::string variableName;
        std::shared_ptr<TypedExpressionNode> rhs;
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
