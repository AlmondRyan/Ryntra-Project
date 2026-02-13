grammar Ryntra;

// Keywords
PUBLIC: 'public';
INT: 'int';

// Symbols & Operators
SEMICOLON: ';';
COMMA: ',';
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';

// Lexical Objects
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
STRING_LITERAL: '"' (~["\\\r\n] | '\\' .)* '"';
WS: [ \t\r\n]+ -> skip;

// Parser Rules

program
    : functionDefinition+ EOF
    ;

functionDefinition
    : PUBLIC typeSpecifier IDENTIFIER LPAREN RPAREN block
    ;

typeSpecifier
    : INT
    ;

block
    : LBRACE statement* RBRACE
    ;

statement
    : expression SEMICOLON
    ;

expression
    : IDENTIFIER LPAREN argumentList? RPAREN # FunctionCall
    | STRING_LITERAL                         # StringLiteral
    ;

argumentList
    : expression (COMMA expression)*
    ;