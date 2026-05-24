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
        std::shared_ptr<ReferenceTypeNode> visitReferenceType(antlr::RyntraParser::TypeSpecifierContext *ctx);
        std::shared_ptr<BlockNode> visitBlock(antlr::RyntraParser::BlockContext *ctx);
        std::shared_ptr<StatementNode> visitStatement(antlr::RyntraParser::StatementContext *ctx);
        std::shared_ptr<UnsafeBlockNode> visitUnsafeBlock(antlr::RyntraParser::UnsafeBlockContext *ctx);
        std::shared_ptr<ReturnNode> visitReturnStatement(antlr::RyntraParser::ReturnStatementContext *ctx);
        std::shared_ptr<IfNode> visitIfStatement(antlr::RyntraParser::IfStatementContext *ctx);
        std::shared_ptr<WhileNode> visitWhileStatement(antlr::RyntraParser::WhileStatementContext *ctx);
        std::shared_ptr<ForNode> visitForStatement(antlr::RyntraParser::ForStatementContext *ctx);
        std::shared_ptr<BreakNode> visitBreakStatement(antlr::RyntraParser::BreakStatementContext *ctx);
        std::shared_ptr<ContinueNode> visitContinueStatement(antlr::RyntraParser::ContinueStatementContext *ctx);
        std::shared_ptr<StatementNode> visitElseBranch(antlr::RyntraParser::ElseBranchContext *ctx);
        std::shared_ptr<ExpressionNode> visitExpression(antlr::RyntraParser::ExpressionContext *ctx);
        std::shared_ptr<FunctionCallNode> visitFunctionCall(antlr::RyntraParser::FunctionCallContext *ctx);
        std::shared_ptr<StringLiteralNode> visitStringLiteral(antlr::RyntraParser::StringLiteralContext *ctx);
        std::shared_ptr<IntegerLiteralNode> visitIntegerLiteral(antlr::RyntraParser::IntegerLiteralContext *ctx);
        std::shared_ptr<LongLiteralNode> visitLongLiteral(antlr::RyntraParser::IntegerLiteralContext *ctx);
        std::shared_ptr<BoolLiteralNode> visitTrueLiteral(antlr::RyntraParser::TrueLiteralContext *ctx);
        std::shared_ptr<BoolLiteralNode> visitFalseLiteral(antlr::RyntraParser::FalseLiteralContext *ctx);
        std::shared_ptr<NullLiteralNode> visitNullLiteral(antlr::RyntraParser::NullLiteralContext *ctx);
        std::shared_ptr<ArrayDeclarationNode> visitArrayDeclaration(antlr::RyntraParser::ArrayDeclarationContext *ctx);
        std::shared_ptr<FixedNode> visitFixedStatement(antlr::RyntraParser::FixedStatementContext *ctx);
        std::shared_ptr<ArrayIndexAccessNode> visitArrayIndexAccess(antlr::RyntraParser::ArrayIndexAccessContext *ctx);
        std::shared_ptr<VariableDeclarationNode> visitVariableDeclaration(antlr::RyntraParser::VariableDeclarationContext *ctx);
        std::shared_ptr<VariableNode> visitVariableReference(antlr::RyntraParser::VariableReferenceContext *ctx);
        std::shared_ptr<BinaryOpNode> visitMulDivModExpression(antlr::RyntraParser::MulDivModExpressionContext *ctx);
        std::shared_ptr<BinaryOpNode> visitPlusMinusExpression(antlr::RyntraParser::PlusMinusExpressionContext *ctx);
        std::shared_ptr<PrefixOpNode> visitPrefixIncExpression(antlr::RyntraParser::PrefixIncExpressionContext *ctx);
        std::shared_ptr<PrefixOpNode> visitPrefixDecExpression(antlr::RyntraParser::PrefixDecExpressionContext *ctx);
        std::shared_ptr<PostfixOpNode> visitPostfixIncExpression(antlr::RyntraParser::PostfixIncExpressionContext *ctx);
        std::shared_ptr<PostfixOpNode> visitPostfixDecExpression(antlr::RyntraParser::PostfixDecExpressionContext *ctx);
        std::shared_ptr<UnaryOpNode> visitUnaryMinusExpression(antlr::RyntraParser::UnaryMinusExpressionContext *ctx);
        std::shared_ptr<UnaryOpNode> visitUnaryExpression(antlr::RyntraParser::UnaryExpressionContext *ctx);
        std::shared_ptr<UnaryOpNode> visitNotExpression(antlr::RyntraParser::NotExpressionContext *ctx);
        std::shared_ptr<BinaryOpNode> visitShiftExpression(antlr::RyntraParser::ShiftExpressionContext *ctx);
        std::shared_ptr<BinaryOpNode> visitBitAndExpression(antlr::RyntraParser::BitAndExpressionContext *ctx);
        std::shared_ptr<BinaryOpNode> visitBitXorExpression(antlr::RyntraParser::BitXorExpressionContext *ctx);
        std::shared_ptr<BinaryOpNode> visitBitOrExpression(antlr::RyntraParser::BitOrExpressionContext *ctx);
        std::shared_ptr<CastNode> visitCastExpression(antlr::RyntraParser::CastExpressionContext *ctx);
        std::shared_ptr<PtrExpressionNode> visitPtrExpression(antlr::RyntraParser::PtrExpressionContext *ctx);
        std::shared_ptr<PtrLoadNode> visitPtrLoadExpression(antlr::RyntraParser::PtrLoadExpressionContext *ctx);
        std::shared_ptr<PtrStoreNode> visitPtrStoreExpression(antlr::RyntraParser::PtrStoreExpressionContext *ctx);
        std::shared_ptr<RefExpressionNode> visitRefExpression(antlr::RyntraParser::RefExpressionContext *ctx);
        std::shared_ptr<NewExpressionNode> visitNewExpression(antlr::RyntraParser::NewExpressionContext *ctx);
        std::shared_ptr<NewExpressionNode> visitNewWithInitExpression(antlr::RyntraParser::NewWithInitExpressionContext *ctx);
        std::shared_ptr<ExpressionNode> visitConditionalAndExpression(antlr::RyntraParser::ConditionalAndExpressionContext *ctx);
        std::shared_ptr<ExpressionNode> visitConditionalOrExpression(antlr::RyntraParser::ConditionalOrExpressionContext *ctx);
        std::shared_ptr<ComparisonNode> visitComparisonExpression(antlr::RyntraParser::ComparisonExpressionContext *ctx);
        std::shared_ptr<ExpressionNode> visitAssignmentExpression(antlr::RyntraParser::AssignmentExpressionContext *ctx);
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
