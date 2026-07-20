#pragma once

#include "TypedASTBase.h"

namespace Ryntra::Compiler::Semantic {

    class TypedRefCreateNode : public TypedExpressionNode {
    public:
        TypedRefCreateNode(std::string variableName, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), variableName(std::move(variableName)) {}

        const std::string &getVariableName() const { return variableName; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedRefCreate(" + variableName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string variableName;
    };

    class TypedRefLoadNode : public TypedExpressionNode {
    public:
        TypedRefLoadNode(std::string variableName, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), variableName(std::move(variableName)) {}

        const std::string &getVariableName() const { return variableName; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedRefLoad(" + variableName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string variableName;
    };

    class TypedRefAssignNode : public TypedExpressionNode {
    public:
        TypedRefAssignNode(std::string variableName, std::shared_ptr<TypedExpressionNode> rhs, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), variableName(std::move(variableName)), rhs(std::move(rhs)) {}

        const std::string &getVariableName() const { return variableName; }
        std::shared_ptr<TypedExpressionNode> getRHS() const { return rhs; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedRefAssign(" + variableName + "): " + type->toString(); }
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

    class TypedUnsafeBlockNode : public TypedStatementNode {
    public:
        explicit TypedUnsafeBlockNode(std::shared_ptr<TypedBlockNode> body)
            : body(std::move(body)) {}

        std::shared_ptr<TypedBlockNode> getBody() const { return body; }
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedUnsafeBlock"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            body->dump(indent + 1);
        }

    private:
        std::shared_ptr<TypedBlockNode> body;
    };

    class TypedPtrCreateNode : public TypedExpressionNode {
    public:
        TypedPtrCreateNode(std::string variableName, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), variableName(std::move(variableName)) {}

        const std::string &getVariableName() const { return variableName; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrCreate(" + variableName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string variableName;
    };

    class TypedPtrLoadNode : public TypedExpressionNode {
    public:
        TypedPtrLoadNode(std::string ptrVarName, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), ptrVarName(std::move(ptrVarName)) {}

        const std::string &getPtrVarName() const { return ptrVarName; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrLoad(" + ptrVarName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string ptrVarName;
    };

    class TypedPtrStoreNode : public TypedExpressionNode {
    public:
        TypedPtrStoreNode(std::string ptrVarName, std::shared_ptr<TypedExpressionNode> rhs, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), ptrVarName(std::move(ptrVarName)), rhs(std::move(rhs)) {}

        const std::string &getPtrVarName() const { return ptrVarName; }
        std::shared_ptr<TypedExpressionNode> getRHS() const { return rhs; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrStore(" + ptrVarName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "RHS:" << std::endl;
            rhs->dump(indent + 2);
        }

    private:
        std::string ptrVarName;
        std::shared_ptr<TypedExpressionNode> rhs;
    };

    class TypedNullLiteralNode : public TypedExpressionNode {
    public:
        explicit TypedNullLiteralNode(std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)) {}

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedNullLiteral: " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }
    };

    class TypedNewNode : public TypedExpressionNode {
    public:
        TypedNewNode(std::shared_ptr<Type> elementType,
                      std::shared_ptr<TypedExpressionNode> initializer,
                      std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)),
              elementType(std::move(elementType)),
              initializer(std::move(initializer)) {}

        std::shared_ptr<Type> getElementType() const { return elementType; }
        std::shared_ptr<TypedExpressionNode> getInitializer() const { return initializer; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override {
            return "TypedNew(" + elementType->toString() + "): " + type->toString();
        }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            if (initializer) {
                printIndent(indent + 1);
                std::cout << "Initializer:" << std::endl;
                initializer->dump(indent + 2);
            }
        }

    private:
        std::shared_ptr<Type> elementType;
        std::shared_ptr<TypedExpressionNode> initializer;
    };

    class TypedDeleteNode : public TypedStatementNode {
    public:
        explicit TypedDeleteNode(std::shared_ptr<TypedExpressionNode> ptrExpr)
            : ptrExpr(std::move(ptrExpr)) {}

        std::shared_ptr<TypedExpressionNode> getPtrExpr() const { return ptrExpr; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedDelete"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Ptr:" << std::endl;
            ptrExpr->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> ptrExpr;
    };

    class TypedFixedNode : public TypedStatementNode {
    public:
        TypedFixedNode(std::string varName,
                        std::shared_ptr<Type> ptrType,
                        std::shared_ptr<TypedExpressionNode> initExpr,
                        std::shared_ptr<TypedBlockNode> body)
            : varName(std::move(varName)), ptrType(std::move(ptrType)),
              initExpr(std::move(initExpr)), body(std::move(body)) {}

        const std::string &getVarName() const { return varName; }
        std::shared_ptr<Type> getPtrType() const { return ptrType; }
        std::shared_ptr<TypedExpressionNode> getInitExpr() const { return initExpr; }
        std::shared_ptr<TypedBlockNode> getBody() const { return body; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedFixed(" + varName + "): " + ptrType->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Init:" << std::endl;
            initExpr->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Body:" << std::endl;
            body->dump(indent + 2);
        }

    private:
        std::string varName;
        std::shared_ptr<Type> ptrType;
        std::shared_ptr<TypedExpressionNode> initExpr;
        std::shared_ptr<TypedBlockNode> body;
    };

    class TypedPtrIndexAccessNode : public TypedExpressionNode {
    public:
        TypedPtrIndexAccessNode(std::shared_ptr<TypedExpressionNode> ptrExpr,
                                 std::shared_ptr<TypedExpressionNode> index,
                                 std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), ptrExpr(std::move(ptrExpr)), index(std::move(index)) {}

        std::shared_ptr<TypedExpressionNode> getPtrExpr() const { return ptrExpr; }
        std::shared_ptr<TypedExpressionNode> getIndex() const { return index; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrIndexAccess: " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Ptr:" << std::endl;
            ptrExpr->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Index:" << std::endl;
            index->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> ptrExpr;
        std::shared_ptr<TypedExpressionNode> index;
    };

    class TypedPtrIndexAssignmentNode : public TypedExpressionNode {
    public:
        TypedPtrIndexAssignmentNode(std::shared_ptr<TypedExpressionNode> ptrExpr,
                                     std::shared_ptr<TypedExpressionNode> index,
                                     std::shared_ptr<TypedExpressionNode> value,
                                     std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), ptrExpr(std::move(ptrExpr)), index(std::move(index)), value(std::move(value)) {}

        std::shared_ptr<TypedExpressionNode> getPtrExpr() const { return ptrExpr; }
        std::shared_ptr<TypedExpressionNode> getIndex() const { return index; }
        std::shared_ptr<TypedExpressionNode> getValue() const { return value; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrIndexAssign: ptr[index]: " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Ptr:" << std::endl;
            ptrExpr->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Index:" << std::endl;
            index->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Value:" << std::endl;
            value->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> ptrExpr;
        std::shared_ptr<TypedExpressionNode> index;
        std::shared_ptr<TypedExpressionNode> value;
    };

    class TypedPtrFromArrayNode : public TypedExpressionNode {
    public:
        TypedPtrFromArrayNode(std::string arrayName, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), arrayName(std::move(arrayName)) {}

        const std::string &getArrayName() const { return arrayName; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrFromArray(" + arrayName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string arrayName;
    };

    class TypedPtrOffsetNode : public TypedExpressionNode {
    public:
        TypedPtrOffsetNode(std::string ptrVarName, std::shared_ptr<TypedExpressionNode> offset, bool isAdd, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), ptrVarName(std::move(ptrVarName)), offset(std::move(offset)), isAdd(isAdd) {}

        const std::string &getPtrVarName() const { return ptrVarName; }
        std::shared_ptr<TypedExpressionNode> getOffset() const { return offset; }
        bool getIsAdd() const { return isAdd; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrOffset(" + ptrVarName + ", " + (isAdd ? "+" : "-") + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Offset:" << std::endl;
            offset->dump(indent + 2);
        }

    private:
        std::string ptrVarName;
        std::shared_ptr<TypedExpressionNode> offset;
        bool isAdd;
    };

    class TypedPtrDiffNode : public TypedExpressionNode {
    public:
        TypedPtrDiffNode(std::string leftPtrName, std::string rightPtrName, std::shared_ptr<Type> type)
            : TypedExpressionNode(std::move(type)), leftPtrName(std::move(leftPtrName)), rightPtrName(std::move(rightPtrName)) {}

        const std::string &getLeftPtrName() const { return leftPtrName; }
        const std::string &getRightPtrName() const { return rightPtrName; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedPtrDiff(" + leftPtrName + " - " + rightPtrName + "): " + type->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }

    private:
        std::string leftPtrName;
        std::string rightPtrName;
    };

    class TypedIfNode : public TypedStatementNode {
    public:
        TypedIfNode(std::shared_ptr<TypedExpressionNode> condition,
                     std::shared_ptr<TypedBlockNode> thenBlock,
                     std::shared_ptr<TypedStatementNode> elseBranch)
            : condition(std::move(condition)), thenBlock(std::move(thenBlock)), elseBranch(std::move(elseBranch)) {}

        std::shared_ptr<TypedExpressionNode> getCondition() const { return condition; }
        std::shared_ptr<TypedBlockNode> getThenBlock() const { return thenBlock; }
        std::shared_ptr<TypedStatementNode> getElseBranch() const { return elseBranch; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedIf"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Condition:" << std::endl;
            condition->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Then:" << std::endl;
            thenBlock->dump(indent + 2);
            if (elseBranch) {
                printIndent(indent + 1);
                std::cout << "Else:" << std::endl;
                elseBranch->dump(indent + 2);
            }
        }

    private:
        std::shared_ptr<TypedExpressionNode> condition;
        std::shared_ptr<TypedBlockNode> thenBlock;
        std::shared_ptr<TypedStatementNode> elseBranch;
    };

    class TypedWhileNode : public TypedStatementNode {
    public:
        TypedWhileNode(std::shared_ptr<TypedExpressionNode> condition,
                        std::shared_ptr<TypedBlockNode> body)
            : condition(std::move(condition)), body(std::move(body)) {}

        std::shared_ptr<TypedExpressionNode> getCondition() const { return condition; }
        std::shared_ptr<TypedBlockNode> getBody() const { return body; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedWhile"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            printIndent(indent + 1);
            std::cout << "Condition:" << std::endl;
            condition->dump(indent + 2);
            printIndent(indent + 1);
            std::cout << "Body:" << std::endl;
            body->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedExpressionNode> condition;
        std::shared_ptr<TypedBlockNode> body;
    };

    class TypedForNode : public TypedStatementNode {
    public:
        TypedForNode(std::shared_ptr<TypedStatementNode> init,
                      std::shared_ptr<TypedExpressionNode> condition,
                      std::shared_ptr<TypedExpressionNode> operation,
                      std::shared_ptr<TypedBlockNode> body)
            : init(std::move(init)), condition(std::move(condition)), operation(std::move(operation)), body(std::move(body)) {}

        std::shared_ptr<TypedStatementNode> getInit() const { return init; }
        std::shared_ptr<TypedExpressionNode> getCondition() const { return condition; }
        std::shared_ptr<TypedExpressionNode> getOperation() const { return operation; }
        std::shared_ptr<TypedBlockNode> getBody() const { return body; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedFor"; }
        void dump(const int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            if (init) {
                printIndent(indent + 1);
                std::cout << "Init:" << std::endl;
                init->dump(indent + 2);
            }
            if (condition) {
                printIndent(indent + 1);
                std::cout << "Condition:" << std::endl;
                condition->dump(indent + 2);
            }
            if (operation) {
                printIndent(indent + 1);
                std::cout << "Operation:" << std::endl;
                operation->dump(indent + 2);
            }
            printIndent(indent + 1);
            std::cout << "Body:" << std::endl;
            body->dump(indent + 2);
        }

    private:
        std::shared_ptr<TypedStatementNode> init;
        std::shared_ptr<TypedExpressionNode> condition;
        std::shared_ptr<TypedExpressionNode> operation;
        std::shared_ptr<TypedBlockNode> body;
    };

    class TypedBreakNode : public TypedStatementNode {
    public:
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedBreak"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }
    };

    class TypedContinueNode : public TypedStatementNode {
    public:
        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedContinue"; }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
        }
    };

    class TypedParameterNode {
    public:
        TypedParameterNode(std::string name, std::shared_ptr<Type> type)
            : name(std::move(name)), type(std::move(type)) {}

        const std::string &getName() const { return name; }
        std::shared_ptr<Type> getType() const { return type; }

        std::string toString() const {
            return "TypedParameter(" + name + "): " + type->toString();
        }

    private:
        std::string name;
        std::shared_ptr<Type> type;
    };

    class TypedFunctionDefinitionNode : public ITypedASTNode {
    public:
        TypedFunctionDefinitionNode(std::string name,
                                     std::shared_ptr<Type> returnType,
                                     std::vector<std::shared_ptr<TypedParameterNode>> parameters,
                                     std::shared_ptr<TypedBlockNode> body)
            : name(std::move(name)), returnType(std::move(returnType)), parameters(std::move(parameters)), body(std::move(body)) {}

        const std::string &getName() const { return name; }
        std::shared_ptr<Type> getReturnType() const { return returnType; }
        const std::vector<std::shared_ptr<TypedParameterNode>> &getParameters() const { return parameters; }
        std::shared_ptr<TypedBlockNode> getBody() const { return body; }

        void accept(ITypedVisitor &visitor) override { visitor.visit(*this); }
        std::string toString() const override { return "TypedFunctionDefinition(" + name + "): " + returnType->toString(); }
        void dump(int indent = 0) const override {
            printIndent(indent);
            std::cout << toString() << std::endl;
            for (const auto &param : parameters) {
                printIndent(indent + 1);
                std::cout << param->toString() << std::endl;
            }
            body->dump(indent + 1);
        }

    private:
        std::string name;
        std::shared_ptr<Type> returnType;
        std::vector<std::shared_ptr<TypedParameterNode>> parameters;
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
