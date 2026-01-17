
// Generated from ./antlr/Ryntra.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "RyntraParser.h"


namespace Ryntra::antlr {

/**
 * This interface defines an abstract listener for a parse tree produced by RyntraParser.
 */
class  RyntraListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(RyntraParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(RyntraParser::ProgramContext *ctx) = 0;

  virtual void enterFunctionDefinition(RyntraParser::FunctionDefinitionContext *ctx) = 0;
  virtual void exitFunctionDefinition(RyntraParser::FunctionDefinitionContext *ctx) = 0;

  virtual void enterParameterList(RyntraParser::ParameterListContext *ctx) = 0;
  virtual void exitParameterList(RyntraParser::ParameterListContext *ctx) = 0;

  virtual void enterBlock(RyntraParser::BlockContext *ctx) = 0;
  virtual void exitBlock(RyntraParser::BlockContext *ctx) = 0;

  virtual void enterTypeSpecifier(RyntraParser::TypeSpecifierContext *ctx) = 0;
  virtual void exitTypeSpecifier(RyntraParser::TypeSpecifierContext *ctx) = 0;

  virtual void enterVariableDeclaration(RyntraParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(RyntraParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterStatement(RyntraParser::StatementContext *ctx) = 0;
  virtual void exitStatement(RyntraParser::StatementContext *ctx) = 0;

  virtual void enterReturnStatement(RyntraParser::ReturnStatementContext *ctx) = 0;
  virtual void exitReturnStatement(RyntraParser::ReturnStatementContext *ctx) = 0;

  virtual void enterIfStatement(RyntraParser::IfStatementContext *ctx) = 0;
  virtual void exitIfStatement(RyntraParser::IfStatementContext *ctx) = 0;

  virtual void enterElseClause(RyntraParser::ElseClauseContext *ctx) = 0;
  virtual void exitElseClause(RyntraParser::ElseClauseContext *ctx) = 0;

  virtual void enterWhileStatement(RyntraParser::WhileStatementContext *ctx) = 0;
  virtual void exitWhileStatement(RyntraParser::WhileStatementContext *ctx) = 0;

  virtual void enterForStatement(RyntraParser::ForStatementContext *ctx) = 0;
  virtual void exitForStatement(RyntraParser::ForStatementContext *ctx) = 0;

  virtual void enterBreakStatement(RyntraParser::BreakStatementContext *ctx) = 0;
  virtual void exitBreakStatement(RyntraParser::BreakStatementContext *ctx) = 0;

  virtual void enterContinueStatement(RyntraParser::ContinueStatementContext *ctx) = 0;
  virtual void exitContinueStatement(RyntraParser::ContinueStatementContext *ctx) = 0;

  virtual void enterFunctionCall(RyntraParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(RyntraParser::FunctionCallContext *ctx) = 0;

  virtual void enterArgumentList(RyntraParser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(RyntraParser::ArgumentListContext *ctx) = 0;

  virtual void enterAssignment(RyntraParser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(RyntraParser::AssignmentContext *ctx) = 0;

  virtual void enterExpression(RyntraParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(RyntraParser::ExpressionContext *ctx) = 0;

  virtual void enterLogicalOrExpression(RyntraParser::LogicalOrExpressionContext *ctx) = 0;
  virtual void exitLogicalOrExpression(RyntraParser::LogicalOrExpressionContext *ctx) = 0;

  virtual void enterLogicalAndExpression(RyntraParser::LogicalAndExpressionContext *ctx) = 0;
  virtual void exitLogicalAndExpression(RyntraParser::LogicalAndExpressionContext *ctx) = 0;

  virtual void enterInclusiveOrExpression(RyntraParser::InclusiveOrExpressionContext *ctx) = 0;
  virtual void exitInclusiveOrExpression(RyntraParser::InclusiveOrExpressionContext *ctx) = 0;

  virtual void enterExclusiveOrExpression(RyntraParser::ExclusiveOrExpressionContext *ctx) = 0;
  virtual void exitExclusiveOrExpression(RyntraParser::ExclusiveOrExpressionContext *ctx) = 0;

  virtual void enterAndExpression(RyntraParser::AndExpressionContext *ctx) = 0;
  virtual void exitAndExpression(RyntraParser::AndExpressionContext *ctx) = 0;

  virtual void enterEqualityExpression(RyntraParser::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(RyntraParser::EqualityExpressionContext *ctx) = 0;

  virtual void enterRelationalExpression(RyntraParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(RyntraParser::RelationalExpressionContext *ctx) = 0;

  virtual void enterShiftExpression(RyntraParser::ShiftExpressionContext *ctx) = 0;
  virtual void exitShiftExpression(RyntraParser::ShiftExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(RyntraParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(RyntraParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(RyntraParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(RyntraParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterUnaryExpression(RyntraParser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(RyntraParser::UnaryExpressionContext *ctx) = 0;

  virtual void enterPostfixExpression(RyntraParser::PostfixExpressionContext *ctx) = 0;
  virtual void exitPostfixExpression(RyntraParser::PostfixExpressionContext *ctx) = 0;

  virtual void enterPrimaryExpression(RyntraParser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(RyntraParser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterLiteral(RyntraParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(RyntraParser::LiteralContext *ctx) = 0;


};

}  // namespace Ryntra::antlr
