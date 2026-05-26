#pragma once

#include "../TypeSystem.h"
#include "SourceLocation/SourceLocation.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Ryntra::Compiler::Semantic {

    class TypedExpressionNode;
    class TypedStatementNode;
    class TypedProgramNode;
    class TypedFunctionDefinitionNode;
    class TypedBlockNode;
    class TypedIfNode;
    class TypedWhileNode;
    class TypedForNode;
    class TypedBreakNode;
    class TypedContinueNode;
    class TypedPrefixOpNode;
    class TypedPostfixOpNode;
    class TypedStringLiteralNode;
    class TypedBoolLiteralNode;
    class TypedIntegerLiteralNode;
    class TypedLongLiteralNode;
    class TypedIdentifierNode;
    class TypedFunctionCallNode;
    class TypedExpressionStatementNode;
    class TypedReturnNode;
    class TypedVariableNode;
    class TypedVariableDeclarationNode;
    class TypedArrayDeclarationNode;
    class TypedArrayIndexAccessNode;
    class TypedArrayIndexAssignmentNode;
    class TypedBinaryOpNode;
    class TypedUnaryOpNode;
    class TypedCastNode;
    class TypedComparisonNode;
    class TypedConditionalAndNode;
    class TypedConditionalOrNode;
    class TypedAssignmentNode;
    class TypedRefCreateNode;
    class TypedRefLoadNode;
    class TypedRefAssignNode;
    class TypedUnsafeBlockNode;
    class TypedPtrCreateNode;
    class TypedPtrLoadNode;
    class TypedPtrStoreNode;
    class TypedNullLiteralNode;
    class TypedPtrOffsetNode;
    class TypedPtrDiffNode;
    class TypedNewNode;
    class TypedDeleteNode;
    class TypedFixedNode;
    class TypedPtrIndexAccessNode;
    class TypedPtrIndexAssignmentNode;
    class TypedPtrFromArrayNode;

    class ITypedVisitor {
    public:
        virtual ~ITypedVisitor() = default;
        virtual void visit(TypedProgramNode &node) = 0;
        virtual void visit(TypedFunctionDefinitionNode &node) = 0;
        virtual void visit(TypedBlockNode &node) = 0;
        virtual void visit(TypedIfNode &node) = 0;
        virtual void visit(TypedWhileNode &node) = 0;
        virtual void visit(TypedForNode &node) = 0;
        virtual void visit(TypedBreakNode &node) = 0;
        virtual void visit(TypedContinueNode &node) = 0;
        virtual void visit(TypedPrefixOpNode &node) = 0;
        virtual void visit(TypedPostfixOpNode &node) = 0;
        virtual void visit(TypedExpressionStatementNode &node) = 0;
        virtual void visit(TypedReturnNode &node) = 0;
        virtual void visit(TypedStringLiteralNode &node) = 0;
        virtual void visit(TypedBoolLiteralNode &node) = 0;
        virtual void visit(TypedIntegerLiteralNode &node) = 0;
        virtual void visit(TypedLongLiteralNode &node) = 0;
        virtual void visit(TypedIdentifierNode &node) = 0;
        virtual void visit(TypedFunctionCallNode &node) = 0;
        virtual void visit(TypedVariableNode &node) = 0;
        virtual void visit(TypedVariableDeclarationNode &node) = 0;
        virtual void visit(TypedArrayDeclarationNode &node) = 0;
        virtual void visit(TypedArrayIndexAccessNode &node) = 0;
        virtual void visit(TypedArrayIndexAssignmentNode &node) = 0;
        virtual void visit(TypedBinaryOpNode &node) = 0;
        virtual void visit(TypedUnaryOpNode &node) = 0;
        virtual void visit(TypedCastNode &node) = 0;
        virtual void visit(TypedComparisonNode &node) = 0;
        virtual void visit(TypedConditionalAndNode &node) = 0;
        virtual void visit(TypedConditionalOrNode &node) = 0;
        virtual void visit(TypedAssignmentNode &node) = 0;
        virtual void visit(TypedRefCreateNode &node) = 0;
        virtual void visit(TypedRefLoadNode &node) = 0;
        virtual void visit(TypedRefAssignNode &node) = 0;
        virtual void visit(TypedUnsafeBlockNode &node) = 0;
        virtual void visit(TypedPtrCreateNode &node) = 0;
        virtual void visit(TypedPtrLoadNode &node) = 0;
        virtual void visit(TypedPtrStoreNode &node) = 0;
        virtual void visit(TypedNullLiteralNode &node) = 0;
        virtual void visit(TypedPtrOffsetNode &node) = 0;
        virtual void visit(TypedPtrDiffNode &node) = 0;
        virtual void visit(TypedNewNode &node) = 0;
        virtual void visit(TypedDeleteNode &node) = 0;
        virtual void visit(TypedFixedNode &node) = 0;
        virtual void visit(TypedPtrIndexAccessNode &node) = 0;
        virtual void visit(TypedPtrIndexAssignmentNode &node) = 0;
        virtual void visit(TypedPtrFromArrayNode &node) = 0;
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
            for (int i = 0; i < indent; ++i)
                std::cout << "  ";
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

} // namespace Ryntra::Compiler::Semantic
