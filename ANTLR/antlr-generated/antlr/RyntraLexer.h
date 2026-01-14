
// Generated from ./antlr/Ryntra.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"


namespace Ryntra::antlr {


class  RyntraLexer : public antlr4::Lexer {
public:
  enum {
    INT = 1, RETURN = 2, STRING = 3, IF = 4, ELSE = 5, BOOL = 6, TRUE = 7, 
    FALSE = 8, WHILE = 9, PLUS = 10, MINUS = 11, MULT = 12, DIV = 13, ASSIGN = 14, 
    GREATER = 15, LESS = 16, COND_EQUAL = 17, GREATER_EQ = 18, LESS_EQ = 19, 
    LOGIC_AND = 20, LOGIC_OR = 21, NOT = 22, SEMICOLON = 23, LPAREN = 24, 
    RPAREN = 25, LBRACE = 26, RBRACE = 27, COMMA = 28, STRING_LITERAL = 29, 
    IDENTIFIER = 30, INTEGER_LITERAL = 31, LINE_COMMENT = 32, WS = 33
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
