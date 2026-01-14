
// Generated from ./antlr/Ryntra.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "RyntraListener.h"


namespace Ryntra::antlr {

/**
 * This class provides an empty implementation of RyntraListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  RyntraBaseListener : public RyntraListener {
public:

  virtual void enterProgram(RyntraParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(RyntraParser::ProgramContext * /*ctx*/) override { }

  virtual void enterFunctionDefinition(RyntraParser::FunctionDefinitionContext * /*ctx*/) override { }
  virtual void exitFunctionDefinition(RyntraParser::FunctionDefinitionContext * /*ctx*/) override { }

  virtual void enterParameterList(RyntraParser::ParameterListContext * /*ctx*/) override { }
  virtual void exitParameterList(RyntraParser::ParameterListContext * /*ctx*/) override { }

  virtual void enterBlock(RyntraParser::BlockContext * /*ctx*/) override { }
  virtual void exitBlock(RyntraParser::BlockContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(RyntraParser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(RyntraParser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterStatement(RyntraParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(RyntraParser::StatementContext * /*ctx*/) override { }

  virtual void enterReturnStatement(RyntraParser::ReturnStatementContext * /*ctx*/) override { }
  virtual void exitReturnStatement(RyntraParser::ReturnStatementContext * /*ctx*/) override { }

  virtual void enterIfStatement(RyntraParser::IfStatementContext * /*ctx*/) override { }
  virtual void exitIfStatement(RyntraParser::IfStatementContext * /*ctx*/) override { }

  virtual void enterWhileStatement(RyntraParser::WhileStatementContext * /*ctx*/) override { }
  virtual void exitWhileStatement(RyntraParser::WhileStatementContext * /*ctx*/) override { }

  virtual void enterElseClause(RyntraParser::ElseClauseContext * /*ctx*/) override { }
  virtual void exitElseClause(RyntraParser::ElseClauseContext * /*ctx*/) override { }

  virtual void enterFunctionCall(RyntraParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(RyntraParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterArgumentList(RyntraParser::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(RyntraParser::ArgumentListContext * /*ctx*/) override { }

  virtual void enterAssignment(RyntraParser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(RyntraParser::AssignmentContext * /*ctx*/) override { }

  virtual void enterExpression(RyntraParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(RyntraParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalOrExpression(RyntraParser::LogicalOrExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalOrExpression(RyntraParser::LogicalOrExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalAndExpression(RyntraParser::LogicalAndExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalAndExpression(RyntraParser::LogicalAndExpressionContext * /*ctx*/) override { }

  virtual void enterEqualityExpression(RyntraParser::EqualityExpressionContext * /*ctx*/) override { }
  virtual void exitEqualityExpression(RyntraParser::EqualityExpressionContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(RyntraParser::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(RyntraParser::RelationalExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(RyntraParser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(RyntraParser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(RyntraParser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(RyntraParser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(RyntraParser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(RyntraParser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterPrimaryExpression(RyntraParser::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(RyntraParser::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterLiteral(RyntraParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(RyntraParser::LiteralContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace Ryntra::antlr
