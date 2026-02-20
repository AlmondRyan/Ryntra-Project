#pragma once

#include "SymbolTable.h"
#include "../AST/ASTVisitor.h"
#include "../AST/ASTNodes.h"
#include "Compiler/GeneratedHeader/AllNodesVisitor.h"
#include "TypedAST.h"

namespace Ryntra::Compiler::Semantic {
    class SemanticAnalyzer : public AllNodesVisitor {
    public:
        SemanticAnalyzer() = default;
        
        void analyze(const std::shared_ptr<IASTNode>& root);
        std::shared_ptr<TypedProgramNode> getTypedAST() const { return typedProgram; }

        // Visitor methods
        void visit(ProgramNode &node) override;
        void visit(FunctionDefinitionNode &node) override;
        void visit(FunctionCallNode &node) override;
        void visit(BlockNode &node) override;
        void visit(ExpressionStatementNode &node) override;
        void visit(StringLiteralNode &node) override;
        void visit(IntegerLiteralNode &node) override;
        void visit(IdentifierNode &node) override;
        void visit(TypeSpecifierNode &node) override;
        void visit(ReturnNode &node) override;

    private:
        SymbolTable symbolTable;
        std::shared_ptr<TypedProgramNode> typedProgram;

        // Intermediate state for building the Typed AST
        std::shared_ptr<ITypedASTNode> lastNode;
        std::shared_ptr<Type> lastType; // For TypeSpecifierNode result
        std::shared_ptr<Type> currentFunctionReturnType;
    };

}
