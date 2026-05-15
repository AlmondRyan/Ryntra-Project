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
        if (ctx->variableDeclaration()) {
            return visitVariableDeclaration(ctx->variableDeclaration());
        }
        if (ctx->returnStatement()) {
            return visitReturnStatement(ctx->returnStatement());
        }
        if (ctx->ifStatement()) {
            return visitIfStatement(ctx->ifStatement());
        }
        if (ctx->expression()) {
            auto expr = visitExpression(ctx->expression());
            return createNode<ExpressionStatementNode>(ctx, std::move(expr));
        }
        return nullptr;
    }

    std::shared_ptr<ReturnNode> ASTBuilder::visitReturnStatement(antlr::RyntraParser::ReturnStatementContext *ctx) {
        auto expr = visitExpression(ctx->expression());
        return createNode<ReturnNode>(ctx, std::move(expr));
    }

    std::shared_ptr<IfNode> ASTBuilder::visitIfStatement(antlr::RyntraParser::IfStatementContext *ctx) {
        auto cond = visitExpression(ctx->expression());
        auto thenBlk = visitBlock(ctx->block());
        std::shared_ptr<StatementNode> elseBr = nullptr;
        if (ctx->elseBranch()) {
            elseBr = visitElseBranch(ctx->elseBranch());
        }
        return createNode<IfNode>(ctx, std::move(cond), std::move(thenBlk), std::move(elseBr));
    }

    std::shared_ptr<StatementNode> ASTBuilder::visitElseBranch(antlr::RyntraParser::ElseBranchContext *ctx) {
        if (ctx->ifStatement()) {
            return visitIfStatement(ctx->ifStatement());
        }
        return visitBlock(ctx->block());
    }

    std::shared_ptr<ExpressionNode> ASTBuilder::visitExpression(Ryntra::antlr::RyntraParser::ExpressionContext *ctx) {
        if (auto *assignCtx = dynamic_cast<Ryntra::antlr::RyntraParser::AssignmentExpressionContext *>(ctx)) {
            return visitAssignmentExpression(assignCtx);
        }
        if (auto *mulDivModCtx = dynamic_cast<Ryntra::antlr::RyntraParser::MulDivModExpressionContext *>(ctx)) {
            return visitMulDivModExpression(mulDivModCtx);
        }
        if (auto *plusMinusCtx = dynamic_cast<Ryntra::antlr::RyntraParser::PlusMinusExpressionContext *>(ctx)) {
            return visitPlusMinusExpression(plusMinusCtx);
        }
        if (auto *shiftCtx = dynamic_cast<Ryntra::antlr::RyntraParser::ShiftExpressionContext *>(ctx)) {
            return visitShiftExpression(shiftCtx);
        }
        if (auto *bitAndCtx = dynamic_cast<Ryntra::antlr::RyntraParser::BitAndExpressionContext *>(ctx)) {
            return visitBitAndExpression(bitAndCtx);
        }
        if (auto *bitXorCtx = dynamic_cast<Ryntra::antlr::RyntraParser::BitXorExpressionContext *>(ctx)) {
            return visitBitXorExpression(bitXorCtx);
        }
        if (auto *bitOrCtx = dynamic_cast<Ryntra::antlr::RyntraParser::BitOrExpressionContext *>(ctx)) {
            return visitBitOrExpression(bitOrCtx);
        }
        if (auto *castCtx = dynamic_cast<Ryntra::antlr::RyntraParser::CastExpressionContext *>(ctx)) {
            return visitCastExpression(castCtx);
        }
        if (auto *cmpCtx = dynamic_cast<Ryntra::antlr::RyntraParser::ComparisonExpressionContext *>(ctx)) {
            return visitComparisonExpression(cmpCtx);
        }
        if (auto *unaryCtx = dynamic_cast<Ryntra::antlr::RyntraParser::UnaryExpressionContext *>(ctx)) {
            return visitUnaryExpression(unaryCtx);
        }
        if (auto *parenCtx = dynamic_cast<Ryntra::antlr::RyntraParser::ParenthesizedExpressionContext *>(ctx)) {
            return visitExpression(parenCtx->expression());
        }
        if (auto *callCtx = dynamic_cast<Ryntra::antlr::RyntraParser::FunctionCallContext *>(ctx)) {
            return visitFunctionCall(callCtx);
        }
        if (auto *varCtx = dynamic_cast<Ryntra::antlr::RyntraParser::VariableReferenceContext *>(ctx)) {
            return visitVariableReference(varCtx);
        }
        if (auto *strCtx = dynamic_cast<Ryntra::antlr::RyntraParser::StringLiteralContext *>(ctx)) {
            return visitStringLiteral(strCtx);
        }
        if (auto *intCtx = dynamic_cast<Ryntra::antlr::RyntraParser::IntegerLiteralContext *>(ctx)) {
            std::string text = intCtx->INTEGER_LITERAL()->getText();
            // Check for 'L' or 'l' suffix → long literal
            if (!text.empty() && (text.back() == 'L' || text.back() == 'l')) {
                return visitLongLiteral(intCtx);
            }
            return visitIntegerLiteral(intCtx);
        }
        if (auto *trueCtx = dynamic_cast<Ryntra::antlr::RyntraParser::TrueLiteralContext *>(ctx)) {
            return visitTrueLiteral(trueCtx);
        }
        if (auto *falseCtx = dynamic_cast<Ryntra::antlr::RyntraParser::FalseLiteralContext *>(ctx)) {
            return visitFalseLiteral(falseCtx);
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
        // Remove surrounding quotes
        std::string inner = raw.substr(1, raw.length() - 2);
        // Process escape sequences
        std::string val;
        val.reserve(inner.size());
        for (size_t i = 0; i < inner.size(); ++i) {
            if (inner[i] == '\\' && i + 1 < inner.size()) {
                switch (inner[i + 1]) {
                case 'n':
                    val += '\n';
                    ++i;
                    break;
                case 't':
                    val += '\t';
                    ++i;
                    break;
                case 'r':
                    val += '\r';
                    ++i;
                    break;
                case '0':
                    val += '\0';
                    ++i;
                    break;
                case '\\':
                    val += '\\';
                    ++i;
                    break;
                case '"':
                    val += '"';
                    ++i;
                    break;
                default:
                    val += inner[i];
                    break;
                }
            } else {
                val += inner[i];
            }
        }
        return createNode<StringLiteralNode>(ctx, val);
    }

    std::shared_ptr<IntegerLiteralNode> ASTBuilder::visitIntegerLiteral(Ryntra::antlr::RyntraParser::IntegerLiteralContext *ctx) {
        int val = std::stoi(ctx->INTEGER_LITERAL()->getText());
        return createNode<IntegerLiteralNode>(ctx, val);
    }

    std::shared_ptr<LongLiteralNode> ASTBuilder::visitLongLiteral(Ryntra::antlr::RyntraParser::IntegerLiteralContext *ctx) {
        std::string text = ctx->INTEGER_LITERAL()->getText();
        // Strip the 'L' or 'l' suffix before parsing
        if (!text.empty() && (text.back() == 'L' || text.back() == 'l')) {
            text.pop_back();
        }
        int64_t val = std::stoll(text);
        return createNode<LongLiteralNode>(ctx, val);
    }

    std::shared_ptr<BoolLiteralNode> ASTBuilder::visitTrueLiteral(Ryntra::antlr::RyntraParser::TrueLiteralContext *ctx) {
        return createNode<BoolLiteralNode>(ctx, true);
    }

    std::shared_ptr<BoolLiteralNode> ASTBuilder::visitFalseLiteral(Ryntra::antlr::RyntraParser::FalseLiteralContext *ctx) {
        return createNode<BoolLiteralNode>(ctx, false);
    }

    std::vector<std::shared_ptr<ExpressionNode>> ASTBuilder::visitArgumentList(Ryntra::antlr::RyntraParser::ArgumentListContext *ctx) {
        std::vector<std::shared_ptr<ExpressionNode>> args;
        for (auto *exprCtx : ctx->expression()) {
            args.push_back(visitExpression(exprCtx));
        }
        return args;
    }

    std::shared_ptr<VariableDeclarationNode> ASTBuilder::visitVariableDeclaration(Ryntra::antlr::RyntraParser::VariableDeclarationContext *ctx) {
        auto type = visitTypeSpecifier(ctx->typeSpecifier());
        auto nameNode = createNode<IdentifierNode>(ctx->IDENTIFIER(), ctx->IDENTIFIER()->getText());
        std::shared_ptr<ExpressionNode> initializer = nullptr;
        if (ctx->ASSIGN() && ctx->expression()) {
            initializer = visitExpression(ctx->expression());
        }
        return createNode<VariableDeclarationNode>(ctx, std::move(type), std::move(nameNode), std::move(initializer));
    }

    std::shared_ptr<VariableNode> ASTBuilder::visitVariableReference(Ryntra::antlr::RyntraParser::VariableReferenceContext *ctx) {
        auto nameNode = createNode<IdentifierNode>(ctx->IDENTIFIER(), ctx->IDENTIFIER()->getText());
        return createNode<VariableNode>(ctx, std::move(nameNode));
    }

    std::shared_ptr<BinaryOpNode> ASTBuilder::visitMulDivModExpression(Ryntra::antlr::RyntraParser::MulDivModExpressionContext *ctx) {
        auto left = visitExpression(ctx->left);
        auto right = visitExpression(ctx->right);

        BinaryOpType op;
        if (ctx->MUL())
            op = BinaryOpType::Mul;
        else if (ctx->DIV())
            op = BinaryOpType::Div;
        else if (ctx->MOD())
            op = BinaryOpType::Mod;
        else
            op = BinaryOpType::Mul;

        return createNode<BinaryOpNode>(ctx, std::move(left), op, std::move(right));
    }

    std::shared_ptr<BinaryOpNode> ASTBuilder::visitPlusMinusExpression(Ryntra::antlr::RyntraParser::PlusMinusExpressionContext *ctx) {
        auto left = visitExpression(ctx->left);
        auto right = visitExpression(ctx->right);

        BinaryOpType op;
        if (ctx->PLUS())
            op = BinaryOpType::Add;
        else if (ctx->MINUS())
            op = BinaryOpType::Sub;
        else
            op = BinaryOpType::Add;

        return createNode<BinaryOpNode>(ctx, std::move(left), op, std::move(right));
    }

    std::shared_ptr<UnaryOpNode> ASTBuilder::visitUnaryExpression(Ryntra::antlr::RyntraParser::UnaryExpressionContext *ctx) {
        auto operand = visitExpression(ctx->expression());
        return createNode<UnaryOpNode>(ctx, UnaryOpType::BitNot, std::move(operand));
    }

    std::shared_ptr<BinaryOpNode> ASTBuilder::visitShiftExpression(Ryntra::antlr::RyntraParser::ShiftExpressionContext *ctx) {
        auto left = visitExpression(ctx->left);
        auto right = visitExpression(ctx->right);
        BinaryOpType op = ctx->SHL() ? BinaryOpType::Shl : BinaryOpType::Shr;
        return createNode<BinaryOpNode>(ctx, std::move(left), op, std::move(right));
    }

    std::shared_ptr<BinaryOpNode> ASTBuilder::visitBitAndExpression(Ryntra::antlr::RyntraParser::BitAndExpressionContext *ctx) {
        auto left = visitExpression(ctx->left);
        auto right = visitExpression(ctx->right);
        return createNode<BinaryOpNode>(ctx, std::move(left), BinaryOpType::BitAnd, std::move(right));
    }

    std::shared_ptr<BinaryOpNode> ASTBuilder::visitBitXorExpression(Ryntra::antlr::RyntraParser::BitXorExpressionContext *ctx) {
        auto left = visitExpression(ctx->left);
        auto right = visitExpression(ctx->right);
        return createNode<BinaryOpNode>(ctx, std::move(left), BinaryOpType::BitXor, std::move(right));
    }

    std::shared_ptr<BinaryOpNode> ASTBuilder::visitBitOrExpression(Ryntra::antlr::RyntraParser::BitOrExpressionContext *ctx) {
        auto left = visitExpression(ctx->left);
        auto right = visitExpression(ctx->right);
        return createNode<BinaryOpNode>(ctx, std::move(left), BinaryOpType::BitOr, std::move(right));
    }

    std::shared_ptr<CastNode> ASTBuilder::visitCastExpression(Ryntra::antlr::RyntraParser::CastExpressionContext *ctx) {
        auto targetType = visitTypeSpecifier(ctx->typeSpecifier());
        auto operand = visitExpression(ctx->expression());
        return createNode<CastNode>(ctx, std::move(targetType), std::move(operand));
    }

    std::shared_ptr<ComparisonNode> ASTBuilder::visitComparisonExpression(Ryntra::antlr::RyntraParser::ComparisonExpressionContext *ctx) {
        auto left = visitExpression(ctx->left);
        auto right = visitExpression(ctx->right);

        ComparisonOpType op;
        if (ctx->EQ()) op = ComparisonOpType::Eq;
        else if (ctx->NE()) op = ComparisonOpType::Ne;
        else if (ctx->LT()) op = ComparisonOpType::Lt;
        else if (ctx->GT()) op = ComparisonOpType::Gt;
        else if (ctx->LE()) op = ComparisonOpType::Le;
        else if (ctx->GE()) op = ComparisonOpType::Ge;
        else op = ComparisonOpType::Eq;

        return createNode<ComparisonNode>(ctx, std::move(left), op, std::move(right));
    }

    std::shared_ptr<AssignmentNode> ASTBuilder::visitAssignmentExpression(Ryntra::antlr::RyntraParser::AssignmentExpressionContext *ctx) {
        auto rhs = visitExpression(ctx->right);

        auto leftExprCtx = ctx->left;
        auto varRefCtx = dynamic_cast<Ryntra::antlr::RyntraParser::VariableReferenceContext *>(leftExprCtx);
        if (!varRefCtx) {
            return nullptr;
        }
        auto lhsName = createNode<IdentifierNode>(varRefCtx->IDENTIFIER(), varRefCtx->IDENTIFIER()->getText());

        if (ctx->ASSIGN()) {
            return createNode<AssignmentNode>(ctx, std::move(lhsName), std::move(rhs));
        }

        BinaryOpType binOp;
        if (ctx->ADD_ASSIGN())
            binOp = BinaryOpType::Add;
        else if (ctx->SUB_ASSIGN())
            binOp = BinaryOpType::Sub;
        else if (ctx->MUL_ASSIGN())
            binOp = BinaryOpType::Mul;
        else if (ctx->DIV_ASSIGN())
            binOp = BinaryOpType::Div;
        else if (ctx->MOD_ASSIGN())
            binOp = BinaryOpType::Mod;
        else if (ctx->AND_ASSIGN())
            binOp = BinaryOpType::BitAnd;
        else if (ctx->OR_ASSIGN())
            binOp = BinaryOpType::BitOr;
        else if (ctx->XOR_ASSIGN())
            binOp = BinaryOpType::BitXor;
        else if (ctx->SHL_ASSIGN())
            binOp = BinaryOpType::Shl;
        else if (ctx->SHR_ASSIGN())
            binOp = BinaryOpType::Shr;
        else
            return createNode<AssignmentNode>(ctx, std::move(lhsName), std::move(rhs));

        auto varRef = std::make_shared<VariableNode>(std::make_shared<IdentifierNode>(lhsName->getName()));
        varRef->setLocation(lhsName->getLocation());
        auto binExpr = std::make_shared<BinaryOpNode>(std::move(varRef), binOp, std::move(rhs));
        binExpr->setLocation(lhsName->getLocation());
        return createNode<AssignmentNode>(ctx, std::move(lhsName), std::move(binExpr));
    }

} // namespace Ryntra::Compiler
