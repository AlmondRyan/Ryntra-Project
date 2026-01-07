grammar Ryntra;

// LEXICAL RULES

INT: 'int' ;
RETURN: 'return';
SEMICOLON : ';' ;
LPAREN: '(' ;
RPAREN: ')' ;
LBRACE: '{' ;
RBRACE: '}' ;
STRING_LITERAL: '"' ( ~["\\\r\n] | '\\' ["\\bfnrt] )* '"';
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
LINE_COMMENT: '//' ~[\r\n]* -> skip;
WS : [ \t\r\n]+ -> skip ;
COMMA: ',';
ASSIGN: '=';
INTEGER_LITERAL: '0' | [1-9] [0-9]*;

// PARSER RULES

program: functionDefinition+ EOF;

functionDefinition
    : INT IDENTIFIER LPAREN parameterList? RPAREN block
    ;

parameterList
    : INT IDENTIFIER (COMMA INT IDENTIFIER)*
    ;

block
    : LBRACE statement* RBRACE
    ;

variableDeclaration
    : INT IDENTIFIER (ASSIGN expression)?
    ;

statement:
    functionCall SEMICOLON
    | expression SEMICOLON
    | variableDeclaration SEMICOLON
    | returnStatement SEMICOLON
    | SEMICOLON
    ;

returnStatement
    : RETURN expression
    ;

functionCall: IDENTIFIER LPAREN (argumentList?) RPAREN;
argumentList: expression (COMMA expression)*;

expression:
    literal
    | functionCall
    | IDENTIFIER
    ;

literal:
    STRING_LITERAL
    | INTEGER_LITERAL;