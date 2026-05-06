#pragma once

#include "Compiler/Semantic/TypedAST.h"
#include "IRBuilder.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace Ryntra::IR {
    class IRGenerator : public Compiler::Semantic::ITypedVisitor {
    public:
        IRGenerator();

        std::shared_ptr<Module> generate(Compiler::Semantic::TypedProgramNode &program,
                                         const std::string &moduleName = "module");

        void visit(Compiler::Semantic::TypedProgramNode &node) override;
        void visit(Compiler::Semantic::TypedFunctionDefinitionNode &node) override;
        void visit(Compiler::Semantic::TypedBlockNode &node) override;
        void visit(Compiler::Semantic::TypedExpressionStatementNode &node) override;
        void visit(Compiler::Semantic::TypedReturnNode &node) override;
        void visit(Compiler::Semantic::TypedStringLiteralNode &node) override;
        void visit(Compiler::Semantic::TypedIntegerLiteralNode &node) override;
        void visit(Compiler::Semantic::TypedIdentifierNode &node) override;
        void visit(Compiler::Semantic::TypedFunctionCallNode &node) override;
        void visit(Compiler::Semantic::TypedVariableNode &node) override;
        void visit(Compiler::Semantic::TypedVariableDeclarationNode &node) override;
    private:
        IRBuilder builder_;

        // Last expression value produced by visiting an expression node
        std::shared_ptr<Value> lastValue_;

        // Map from function name -> IR Function (for call resolution)
        std::unordered_map<std::string, std::shared_ptr<Function>> functionMap_;

        // Map from variable name -> IR Value (for variable references)
        std::unordered_map<std::string, std::shared_ptr<Value>> variableMap_;

        // Convert a Semantic::Type to an IR::Type
        static std::shared_ptr<Type> toIRType(const std::shared_ptr<Compiler::Semantic::Type> &semType);
    };
} // namespace Ryntra::IR