grammar Ryntra;

// Keywords
PUBLIC: 'public';
INT: 'int';
RETURN: 'return';

// Symbols & Operators
SEMICOLON: ';';
COMMA: ',';
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
EQUAL: '=';

// Lexical Objects
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
STRING_LITERAL: '"' (~["\\\r\n] | '\\' .)* '"';
INTEGER_LITERAL: [0-9]+;
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
    : variableDeclaration SEMICOLON
    | expression SEMICOLON
    | returnStatement
    ;

variableDeclaration
    : typeSpecifier IDENTIFIER (EQUAL expression)?
    ;

returnStatement
    : RETURN expression SEMICOLON
    ;

expression
    : IDENTIFIER LPAREN argumentList? RPAREN # FunctionCall
    | IDENTIFIER                             # VariableReference
    | STRING_LITERAL                         # StringLiteral
    | INTEGER_LITERAL                        # IntegerLiteral
    ;

argumentList
    : expression (COMMA expression)*
    ;