
// Generated from ./antlr/Ryntra.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"


namespace Ryntra::antlr {


class  RyntraLexer : public antlr4::Lexer {
public:
  enum {
    INT = 1, RETURN = 2, STRING = 3, IF = 4, ELSE = 5, BOOL = 6, TRUE = 7, 
    FALSE = 8, PLUS = 9, MINUS = 10, MULT = 11, DIV = 12, ASSIGN = 13, GREATER = 14, 
    LESS = 15, COND_EQUAL = 16, GREATER_EQ = 17, LESS_EQ = 18, LOGIC_AND = 19, 
    LOGIC_OR = 20, NOT = 21, SEMICOLON = 22, LPAREN = 23, RPAREN = 24, LBRACE = 25, 
    RBRACE = 26, COMMA = 27, STRING_LITERAL = 28, IDENTIFIER = 29, INTEGER_LITERAL = 30, 
    LINE_COMMENT = 31, WS = 32
  };

  explicit RyntraLexer(antlr4::CharStream *input);

  ~RyntraLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

}  // namespace Ryntra::antlr
