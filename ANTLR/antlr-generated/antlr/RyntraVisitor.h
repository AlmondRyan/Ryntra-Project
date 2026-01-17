
// Generated from ./antlr/Ryntra.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "RyntraParser.h"


namespace Ryntra::antlr {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by RyntraParser.
 */
class  RyntraVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by RyntraParser.
   */
    virtual std::any visitProgram(RyntraParser::ProgramContext *context) = 0;

    virtual std::any visitFunctionDefinition(RyntraParser::FunctionDefinitionContext *context) = 0;

    virtual std::any visitParameterList(RyntraParser::ParameterListContext *context) = 0;

    virtual std::any visitBlock(RyntraParser::BlockContext *context) = 0;

    virtual std::any visitTypeSpecifier(RyntraParser::TypeSpecifierContext *context) = 0;

    virtual std::any visitVariableDeclaration(RyntraParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitStatement(RyntraParser::StatementContext *context) = 0;

    virtual std::any visitReturnStatement(RyntraParser::ReturnStatementContext *context) = 0;

    virtual std::any visitIfStatement(RyntraParser::IfStatementContext *context) = 0;

    virtual std::any visitElseClause(RyntraParser::ElseClauseContext *context) = 0;

    virtual std::any visitWhileStatement(RyntraParser::WhileStatementContext *context) = 0;

    virtual std::any visitForStatement(RyntraParser::ForStatementContext *context) = 0;

    virtual std::any visitBreakStatement(RyntraParser::BreakStatementContext *context) = 0;

    virtual std::any visitContinueStatement(RyntraParser::ContinueStatementContext *context) = 0;

    virtual std::any visitFunctionCall(RyntraParser::FunctionCallContext *context) = 0;

    virtual std::any visitArgumentList(RyntraParser::ArgumentListContext *context) = 0;

    virtual std::any visitAssignment(RyntraParser::AssignmentContext *context) = 0;

    virtual std::any visitExpression(RyntraParser::ExpressionContext *context) = 0;

    virtual std::any visitLogicalOrExpression(RyntraParser::LogicalOrExpressionContext *context) = 0;

    virtual std::any visitLogicalAndExpression(RyntraParser::LogicalAndExpressionContext *context) = 0;

    virtual std::any visitInclusiveOrExpression(RyntraParser::InclusiveOrExpressionContext *context) = 0;

    virtual std::any visitExclusiveOrExpression(RyntraParser::ExclusiveOrExpressionContext *context) = 0;

    virtual std::any visitAndExpression(RyntraParser::AndExpressionContext *context) = 0;

    virtual std::any visitEqualityExpression(RyntraParser::EqualityExpressionContext *context) = 0;

    virtual std::any visitRelationalExpression(RyntraParser::RelationalExpressionContext *context) = 0;

    virtual std::any visitShiftExpression(RyntraParser::ShiftExpressionContext *context) = 0;

    virtual std::any visitAdditiveExpression(RyntraParser::AdditiveExpressionContext *context) = 0;

    virtual std::any visitMultiplicativeExpression(RyntraParser::MultiplicativeExpressionContext *context) = 0;

    virtual std::any visitUnaryExpression(RyntraParser::UnaryExpressionContext *context) = 0;

    virtual std::any visitPostfixExpression(RyntraParser::PostfixExpressionContext *context) = 0;

    virtual std::any visitPrimaryExpression(RyntraParser::PrimaryExpressionContext *context) = 0;

    virtual std::any visitLiteral(RyntraParser::LiteralContext *context) = 0;


};

}  // namespace Ryntra::antlr
