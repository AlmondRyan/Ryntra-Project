
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

    virtual std::any visitVariableDeclaration(RyntraParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitStatement(RyntraParser::StatementContext *context) = 0;

    virtual std::any visitReturnStatement(RyntraParser::ReturnStatementContext *context) = 0;

    virtual std::any visitFunctionCall(RyntraParser::FunctionCallContext *context) = 0;

    virtual std::any visitArgumentList(RyntraParser::ArgumentListContext *context) = 0;

    virtual std::any visitAssignment(RyntraParser::AssignmentContext *context) = 0;

    virtual std::any visitExpression(RyntraParser::ExpressionContext *context) = 0;

    virtual std::any visitAssignmentExpression(RyntraParser::AssignmentExpressionContext *context) = 0;

    virtual std::any visitAdditiveExpression(RyntraParser::AdditiveExpressionContext *context) = 0;

    virtual std::any visitMultiplicativeExpression(RyntraParser::MultiplicativeExpressionContext *context) = 0;

    virtual std::any visitPrimaryExpression(RyntraParser::PrimaryExpressionContext *context) = 0;

    virtual std::any visitLiteral(RyntraParser::LiteralContext *context) = 0;


};

}  // namespace Ryntra::antlr
