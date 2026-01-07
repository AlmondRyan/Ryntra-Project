
// Generated from ./antlr/Ryntra.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "RyntraVisitor.h"


namespace Ryntra::antlr {

/**
 * This class provides an empty implementation of RyntraVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  RyntraBaseVisitor : public RyntraVisitor {
public:

  virtual std::any visitProgram(RyntraParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDefinition(RyntraParser::FunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterList(RyntraParser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(RyntraParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(RyntraParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(RyntraParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(RyntraParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(RyntraParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(RyntraParser::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(RyntraParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(RyntraParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace Ryntra::antlr
