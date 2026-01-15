
// Generated from ./antlr/Ryntra.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"


namespace Ryntra::antlr {


class  RyntraLexer : public antlr4::Lexer {
public:
  enum {
    INT = 1, RETURN = 2, STRING = 3, IF = 4, ELSE = 5, BOOL = 6, TRUE = 7, 
    FALSE = 8, WHILE = 9, FOR = 10, BREAK = 11, CONTINUE = 12, PLUS = 13, 
    MINUS = 14, INC = 15, DEC = 16, MULT = 17, DIV = 18, ASSIGN = 19, GREATER = 20, 
    LESS = 21, COND_EQUAL = 22, GREATER_EQ = 23, LESS_EQ = 24, LOGIC_AND = 25, 
    LOGIC_OR = 26, NOT = 27, SEMICOLON = 28, LPAREN = 29, RPAREN = 30, LBRACE = 31, 
    RBRACE = 32, COMMA = 33, STRING_LITERAL = 34, IDENTIFIER = 35, INTEGER_LITERAL = 36, 
    LINE_COMMENT = 37, WS = 38
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
