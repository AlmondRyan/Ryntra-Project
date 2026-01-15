
// Generated from ./antlr/Ryntra.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"


namespace Ryntra::antlr {


class  RyntraLexer : public antlr4::Lexer {
public:
  enum {
    INT = 1, RETURN = 2, STRING = 3, IF = 4, ELSE = 5, BOOL = 6, TRUE = 7, 
    FALSE = 8, WHILE = 9, FOR = 10, BREAK = 11, CONTINUE = 12, LONG = 13, 
    PLUS = 14, MINUS = 15, INC = 16, DEC = 17, MULT = 18, DIV = 19, MOD = 20, 
    ASSIGN = 21, ADD_ASSIGN = 22, SUB_ASSIGN = 23, MUL_ASSIGN = 24, DIV_ASSIGN = 25, 
    MOD_ASSIGN = 26, AND_ASSIGN = 27, OR_ASSIGN = 28, XOR_ASSIGN = 29, LSHIFT_ASSIGN = 30, 
    RSHIFT_ASSIGN = 31, GREATER = 32, LESS = 33, COND_EQUAL = 34, GREATER_EQ = 35, 
    LESS_EQ = 36, LOGIC_AND = 37, LOGIC_OR = 38, NOT = 39, SEMICOLON = 40, 
    LPAREN = 41, RPAREN = 42, LBRACE = 43, RBRACE = 44, COMMA = 45, STRING_LITERAL = 46, 
    IDENTIFIER = 47, INTEGER_LITERAL = 48, LINE_COMMENT = 49, WS = 50, BIT_AND = 51, 
    BIT_OR = 52, BIT_XOR = 53, BIT_NOT = 54, LSHIFT = 55, RSHIFT = 56
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
