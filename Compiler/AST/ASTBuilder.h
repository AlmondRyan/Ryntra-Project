#pragma once
#include "ASTNodes.h"
#include "antlr/RyntraBaseVisitor.h"

namespace Ryntra::Compiler {
    class ASTBuilder : public antlr::RyntraBaseVisitor {
    public:
        // Override from the base class
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

    private:
        /**
         * @brief Get the source location from ANTLR4 Parser Context.
         * @param ctx The pointer of ANTLR4 Parser Rule Context
         * @return SourceLocation, contains the Row and Column Information
         */
        SourceLocation getLoc(antlr4::ParserRuleContext *ctx) {
            return SourceLocation(ctx->getStart()->getLine(), ctx->getStart()->getCharPositionInLine());
        }

        /**
         * @brief Create AST Node Object and set SourceLocation automatically.
         * @tparam Tp The type of the node you want to create.
         * @tparam Args The constructor arguments of the node.
         * @param ctx The pointer of ANTLR4 Parser Rule Context
         * @param args The parameters will be forwarding to the constructor
         * @return The pointer that point to the created node.
         */
        template <typename Tp, typename... Args>
        std::shared_ptr<Tp> createNode(antlr4::ParserRuleContext *ctx, Args &&...args) {
            auto node = std::make_shared<Tp>(std::forward<Args>(args)...);
            node->setLocation(getLoc(ctx));
            return node;
        }
    };
} // namespace Ryntra::Compiler