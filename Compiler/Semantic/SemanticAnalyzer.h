#pragma once

#include "../AST/ASTNodes.h"
#include "../AST/ASTVisitor.h"
#include "Compiler/GeneratedHeader/AllNodesVisitor.h"
#include "SymbolTable.h"
#include "TypedAST.h"

namespace Ryntra::Compiler::Semantic {
    class SemanticAnalyzer : public AllNodesVisitor {
    public:
        SemanticAnalyzer() = default;

        void analyze(const std::shared_ptr<IASTNode> &root);
        std::shared_ptr<TypedProgramNode> getTypedAST() const { return typedProgram; }

        // Visitor methods
        void visit(ProgramNode &node) override;
        void visit(FunctionDefinitionNode &node) override;
        void visit(FunctionCallNode &node) override;
        void visit(BlockNode &node) override;
        void visit(ExpressionStatementNode &node) override;
        void visit(StringLiteralNode &node) override;
        void visit(BoolLiteralNode &node) override;
        void visit(IntegerLiteralNode &node) override;
        void visit(LongLiteralNode &node) override;
        void visit(IdentifierNode &node) override;
        void visit(TypeSpecifierNode &node) override;
        void visit(ReturnNode &node) override;
        void visit(VariableNode &node) override;
        void visit(VariableDeclarationNode &node) override;
        void visit(BinaryOpNode &node) override;
        void visit(UnaryOpNode &node) override;
        void visit(CastNode &node) override;
        void visit(ComparisonNode &node) override;
        void visit(AssignmentNode &node) override;

    private:
        SymbolTable symbolTable;
        std::shared_ptr<TypedProgramNode> typedProgram;

        // Intermediate state for building the Typed AST
        std::shared_ptr<ITypedASTNode> lastNode;
        TypePtr lastType;                         // STType::Type result from TypeSpecifierNode
        TypePtr currentFunctionReturnType;        // STType::Type of the current function
        std::shared_ptr<Type> expectedReturnType; // Expected return type from context (for __builtin_scan)

        // Convert STType::Type -> TypeSystem::Type (for TypedAST nodes)
        static std::shared_ptr<Type> toTypedType(const TypePtr &stType);

        // Build a TypePtr from a type-name string
        static TypePtr makeSTType(const std::string &name);
    };

} // namespace Ryntra::Compiler::Semantic
