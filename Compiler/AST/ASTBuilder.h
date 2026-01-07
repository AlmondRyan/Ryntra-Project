#pragma once
#include "ASTNodes.h"
#include "antlr/RyntraBaseVisitor.h"

namespace Ryntra::Compiler {
    class ASTBuilder : public antlr::RyntraBaseVisitor {
    public:
        std::any visitProgram(antlr::RyntraParser::ProgramContext *context) override;
        std::any visitFunctionDefinition(antlr::RyntraParser::FunctionDefinitionContext *context) override;
        std::any visitParameterList(antlr::RyntraParser::ParameterListContext *context) override;
        std::any visitBlock(antlr::RyntraParser::BlockContext *context) override;
        std::any visitStatement(antlr::RyntraParser::StatementContext *context) override;
        std::any visitVariableDeclaration(antlr::RyntraParser::VariableDeclarationContext *context) override;
        std::any visitReturnStatement(antlr::RyntraParser::ReturnStatementContext *context) override;
        std::any visitLiteral(antlr::RyntraParser::LiteralContext *context) override;
        std::any visitArgumentList(antlr::RyntraParser::ArgumentListContext *context) override;
        std::any visitExpression(antlr::RyntraParser::ExpressionContext *context) override;
        std::any visitFunctionCall(antlr::RyntraParser::FunctionCallContext *context) override;
    };
}