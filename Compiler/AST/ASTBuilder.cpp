#include "ASTBuilder.h"

namespace Ryntra::Compiler {
    std::shared_ptr<ProgramNode> ASTBuilder::visitProgram(antlr::RyntraParser::ProgramContext *ctx) {
        std::vector<std::shared_ptr<FunctionDefinitionNode>> functions;
        for (auto *funcCtx : ctx->functionDefinition()) {
            functions.push_back(visitFunctionDefinition(funcCtx));
        }
        return createNode<ProgramNode>(ctx, std::move(functions));
    }

    std::shared_ptr<FunctionDefinitionNode> ASTBuilder::visitFunctionDefinition(antlr::RyntraParser::FunctionDefinitionContext *ctx) {
        auto type = visitTypeSpecifier(ctx->typeSpecifier());
        auto nameNode = createNode<IdentifierNode>(ctx->IDENTIFIER(), ctx->IDENTIFIER()->getText());
        auto body = visitBlock(ctx->block());
        return createNode<FunctionDefinitionNode>(ctx, std::move(type), std::move(nameNode), std::move(body));
    }

    std::shared_ptr<TypeSpecifierNode> ASTBuilder::visitTypeSpecifier(antlr::RyntraParser::TypeSpecifierContext *ctx) {
        return createNode<TypeSpecifierNode>(ctx, ctx->getText());
    }

    std::shared_ptr<BlockNode> ASTBuilder::visitBlock(antlr::RyntraParser::BlockContext *ctx) {
        std::vector<std::shared_ptr<StatementNode>> statements;
        for (auto *stmtCtx : ctx->statement()) {
            statements.push_back(visitStatement(stmtCtx));
        }
        return createNode<BlockNode>(ctx, std::move(statements));
    }

    std::shared_ptr<StatementNode> ASTBuilder::visitStatement(Ryntra::antlr::RyntraParser::StatementContext *ctx) {
        // Currently only ExpressionStatement
        auto expr = visitExpression(ctx->expression());
        return createNode<ExpressionStatementNode>(ctx, std::move(expr));
    }

    std::shared_ptr<ExpressionNode> ASTBuilder::visitExpression(Ryntra::antlr::RyntraParser::ExpressionContext *ctx) {
        if (auto *callCtx = dynamic_cast<Ryntra::antlr::RyntraParser::FunctionCallContext *>(ctx)) {
            return visitFunctionCall(callCtx);
        }
        if (auto *strCtx = dynamic_cast<Ryntra::antlr::RyntraParser::StringLiteralContext *>(ctx)) {
            return visitStringLiteral(strCtx);
        }
        return nullptr; // Should not happen if grammar is covered
    }

    std::shared_ptr<FunctionCallNode> ASTBuilder::visitFunctionCall(Ryntra::antlr::RyntraParser::FunctionCallContext *ctx) {
        auto nameNode = createNode<IdentifierNode>(ctx->IDENTIFIER(), ctx->IDENTIFIER()->getText());
        std::vector<std::shared_ptr<ExpressionNode>> args;
        if (ctx->argumentList()) {
            args = visitArgumentList(ctx->argumentList());
        }
        return createNode<FunctionCallNode>(ctx, std::move(nameNode), std::move(args));
    }

    std::shared_ptr<StringLiteralNode> ASTBuilder::visitStringLiteral(Ryntra::antlr::RyntraParser::StringLiteralContext *ctx) {
        std::string raw = ctx->STRING_LITERAL()->getText();
        // Remove quotes
        std::string val = raw.substr(1, raw.length() - 2);
        // TODO: handle escape sequences if needed
        return createNode<StringLiteralNode>(ctx, val);
    }

    std::vector<std::shared_ptr<ExpressionNode>> ASTBuilder::visitArgumentList(Ryntra::antlr::RyntraParser::ArgumentListContext *ctx) {
        std::vector<std::shared_ptr<ExpressionNode>> args;
        for (auto *exprCtx : ctx->expression()) {
            args.push_back(visitExpression(exprCtx));
        }
        return args;
    }

} // namespace Ryntra::Compiler
