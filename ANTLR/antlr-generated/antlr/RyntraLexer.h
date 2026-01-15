
// Generated from ./antlr/Ryntra.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"


namespace Ryntra::antlr {


class  RyntraLexer : public antlr4::Lexer {
public:
  enum {
    INT = 1, RETURN = 2, STRING = 3, IF = 4, ELSE = 5, BOOL = 6, TRUE = 7, 
    FALSE = 8, WHILE = 9, FOR = 10, PLUS = 11, MINUS = 12, INC = 13, DEC = 14, 
    MULT = 15, DIV = 16, ASSIGN = 17, GREATER = 18, LESS = 19, COND_EQUAL = 20, 
    GREATER_EQ = 21, LESS_EQ = 22, LOGIC_AND = 23, LOGIC_OR = 24, NOT = 25, 
    SEMICOLON = 26, LPAREN = 27, RPAREN = 28, LBRACE = 29, RBRACE = 30, 
    COMMA = 31, STRING_LITERAL = 32, IDENTIFIER = 33, INTEGER_LITERAL = 34, 
    LINE_COMMENT = 35, WS = 36
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
