#pragma once

#include "ASTNodes.h"
#include "SourceLocation/SourceLocation.h"
#include "antlr/RyntraParser.h"
#include <memory>
#include <vector>

namespace Ryntra::Compiler {
    class ASTBuilder {
    public:
        std::shared_ptr<ProgramNode> visitProgram(antlr::RyntraParser::ProgramContext *ctx);
        std::shared_ptr<FunctionDefinitionNode> visitFunctionDefinition(antlr::RyntraParser::FunctionDefinitionContext *ctx);
        std::shared_ptr<TypeSpecifierNode> visitTypeSpecifier(antlr::RyntraParser::TypeSpecifierContext *ctx);
        std::shared_ptr<BlockNode> visitBlock(antlr::RyntraParser::BlockContext *ctx);
        std::shared_ptr<StatementNode> visitStatement(antlr::RyntraParser::StatementContext *ctx);
        std::shared_ptr<ExpressionNode> visitExpression(antlr::RyntraParser::ExpressionContext *ctx);
        std::shared_ptr<FunctionCallNode> visitFunctionCall(antlr::RyntraParser::FunctionCallContext *ctx);
        std::shared_ptr<StringLiteralNode> visitStringLiteral(antlr::RyntraParser::StringLiteralContext *ctx);
        std::vector<std::shared_ptr<ExpressionNode>> visitArgumentList(antlr::RyntraParser::ArgumentListContext *ctx);

    private:
        SourceLocation getLoc(antlr4::ParserRuleContext *context) {
            return SourceLocation(context->getStart()->getLine(), context->getStart()->getCharPositionInLine());
        }

        SourceLocation getLoc(antlr4::tree::TerminalNode *node) {
            return SourceLocation(node->getSymbol()->getLine(), node->getSymbol()->getCharPositionInLine());
        }

        template <typename Tp, typename... Args>
        std::shared_ptr<Tp> createNode(antlr4::ParserRuleContext *ctx, Args &&...args) {
            auto node = std::make_shared<Tp>(std::forward<Args>(args)...);
            node->setLocation(getLoc(ctx));
            return node;
        }

        template <typename Tp, typename... Args>
        std::shared_ptr<Tp> createNode(antlr4::tree::TerminalNode *node, Args &&...args) {
            auto astNode = std::make_shared<Tp>(std::forward<Args>(args)...);
            astNode->setLocation(getLoc(node));
            return astNode;
        }
    };
} // namespace Ryntra::Compiler
