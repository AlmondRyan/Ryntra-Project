#pragma once

#include "../Semantic/TypedAST.h"
#include "IRBuilder.h"

namespace Ryntra::Compiler::IR {
    class HLIRBuilder : public Semantic::ITypedVisitor {
    public:
        HLIRBuilder();

        std::unique_ptr<Module> takeModule() { return std::move(module); }

        void visit(Semantic::TypedProgramNode &node) override;
        void visit(Semantic::TypedFunctionDefinitionNode &node) override;
        void visit(Semantic::TypedBlockNode &node) override;
        void visit(Semantic::TypedExpressionStatementNode &node) override;
        void visit(Semantic::TypedReturnNode &node) override;
        void visit(Semantic::TypedStringLiteralNode &node) override;
        void visit(Semantic::TypedIntegerLiteralNode &node) override;
        void visit(Semantic::TypedIdentifierNode &node) override;
        void visit(Semantic::TypedFunctionCallNode &node) override;

    private:
        Type *mapType(std::shared_ptr<Semantic::Type> type);

        std::unique_ptr<Module> module;
        std::unique_ptr<IRBuilder> builder;

        Value *lastValue = nullptr;
    };
} // namespace Ryntra::Compiler::IR
