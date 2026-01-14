#pragma once
#include "ASTNodes.h"
#include <antlr4-runtime.h>
#include <antlr/RyntraParser.h>

namespace Ryntra::Compiler {
    class ASTBuilder {
    public:
        std::shared_ptr<ProgramNode> visitProgram(antlr::RyntraParser::ProgramContext *context);
        std::shared_ptr<FunctionDefinitionNode> visitFunctionDefinition(antlr::RyntraParser::FunctionDefinitionContext *context);
        std::vector<std::shared_ptr<ParameterNode>> visitParameterList(antlr::RyntraParser::ParameterListContext *context);
        std::shared_ptr<BlockNode> visitBlock(antlr::RyntraParser::BlockContext *context);
        std::shared_ptr<StatementNode> visitStatement(antlr::RyntraParser::StatementContext *context);
        std::shared_ptr<VariableDeclarationNode> visitVariableDeclaration(antlr::RyntraParser::VariableDeclarationContext *context);
        std::shared_ptr<ReturnStatementNode> visitReturnStatement(antlr::RyntraParser::ReturnStatementContext *context);
        std::shared_ptr<IASTNode> visitLiteral(antlr::RyntraParser::LiteralContext *context);
        std::shared_ptr<IfStatementNode> visitIfStatement(antlr::RyntraParser::IfStatementContext *context);
        std::shared_ptr<IASTNode> visitElseClause(antlr::RyntraParser::ElseClauseContext *context);
        std::vector<std::shared_ptr<IASTNode>> visitArgumentList(antlr::RyntraParser::ArgumentListContext *context);
        std::shared_ptr<IASTNode> visitExpression(antlr::RyntraParser::ExpressionContext *context);
        std::shared_ptr<IASTNode> visitLogicalOrExpression(antlr::RyntraParser::LogicalOrExpressionContext *context);
        std::shared_ptr<IASTNode> visitLogicalAndExpression(antlr::RyntraParser::LogicalAndExpressionContext *context);
        std::shared_ptr<IASTNode> visitEqualityExpression(antlr::RyntraParser::EqualityExpressionContext *context);
        std::shared_ptr<FunctionCallNode> visitFunctionCall(antlr::RyntraParser::FunctionCallContext *context);
        std::shared_ptr<AssignmentExpressionNode> visitAssignment(antlr::RyntraParser::AssignmentContext *context);
        std::shared_ptr<IASTNode> visitRelationalExpression(antlr::RyntraParser::RelationalExpressionContext *context);
        std::shared_ptr<IASTNode> visitAdditiveExpression(antlr::RyntraParser::AdditiveExpressionContext *context);
        std::shared_ptr<IASTNode> visitMultiplicativeExpression(antlr::RyntraParser::MultiplicativeExpressionContext *context);
        std::shared_ptr<IASTNode> visitUnaryExpression(antlr::RyntraParser::UnaryExpressionContext *context);
        std::shared_ptr<IASTNode> visitPrimaryExpression(antlr::RyntraParser::PrimaryExpressionContext *context);
        std::shared_ptr<WhileStatementNode> visitWhileStatement(antlr::RyntraParser::WhileStatementContext *context);
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

        std::string unescape(std::string input) {
            std::string result;
            for (size_t i = 0; i < input.length(); ++i) {
                if (input[i] == '\\' && i + 1 < input.length()) {
                    char next = input[++i];
                    if (next == 'n') result += '\n';
                    else if (next == 't') result += '\t';
                    else if (next == '\\') result += '\\';
                    else if (next == '"') result += '"';
                    else result += next;
                } else {
                    result += input[i];
                }
            }
            return result; // 必须返回结果！
        }
    };
} // namespace Ryntra::Compiler