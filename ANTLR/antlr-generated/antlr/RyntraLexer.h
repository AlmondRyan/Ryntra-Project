
// Generated from ./antlr/Ryntra.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"


namespace Ryntra::antlr {


class  RyntraLexer : public antlr4::Lexer {
public:
  enum {
    INT = 1, RETURN = 2, STRING = 3, IF = 4, ELSE = 5, BOOL = 6, TRUE = 7, 
    FALSE = 8, WHILE = 9, FOR = 10, BREAK = 11, CONTINUE = 12, LONG = 13, 
    FLOAT = 14, DOUBLE = 15, PLUS = 16, MINUS = 17, INC = 18, DEC = 19, 
    MULT = 20, DIV = 21, MOD = 22, ASSIGN = 23, ADD_ASSIGN = 24, SUB_ASSIGN = 25, 
    MUL_ASSIGN = 26, DIV_ASSIGN = 27, MOD_ASSIGN = 28, AND_ASSIGN = 29, 
    OR_ASSIGN = 30, XOR_ASSIGN = 31, LSHIFT_ASSIGN = 32, RSHIFT_ASSIGN = 33, 
    GREATER = 34, LESS = 35, COND_EQUAL = 36, NOT_EQUAL = 37, GREATER_EQ = 38, 
    LESS_EQ = 39, LOGIC_AND = 40, LOGIC_OR = 41, NOT = 42, SEMICOLON = 43, 
    LPAREN = 44, RPAREN = 45, LBRACE = 46, RBRACE = 47, LBRACKET = 48, RBRACKET = 49, 
    COMMA = 50, STRING_LITERAL = 51, IDENTIFIER = 52, INTEGER_LITERAL = 53, 
    FLOAT_LITERAL = 54, LINE_COMMENT = 55, WS = 56, BIT_AND = 57, BIT_OR = 58, 
    BIT_XOR = 59, BIT_NOT = 60, LSHIFT = 61, RSHIFT = 62
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
