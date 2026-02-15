#pragma once

#include "SymbolTable.h"
#include "../AST/ASTVisitor.h"
#include "../AST/ASTNodes.h"
#include "Compiler/GeneratedHeader/AllNodesVisitor.h"

namespace Ryntra::Compiler::Semantic {
    class SemanticAnalyzer : public AllNodesVisitor {
    public:
        SemanticAnalyzer() = default;
        
        void analyze(const std::shared_ptr<IASTNode>& root);

        // Visitor methods
        void visit(ProgramNode &node) override;
        void visit(FunctionDefinitionNode &node) override;
        void visit(FunctionCallNode &node) override;
        void visit(BlockNode &node) override;
        void visit(ExpressionStatementNode &node) override;
        void visit(StringLiteralNode &node) override;
        void visit(IdentifierNode &node) override;
        void visit(TypeSpecifierNode &node) override;

    private:
        SymbolTable symbolTable;
    };

}
