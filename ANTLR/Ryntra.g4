grammar Ryntra;

// LEXICAL RULES

INT: 'int' ;
RETURN: 'return';

PLUS: '+';
MINUS: '-';
MULT: '*';
DIV: '/';
ASSIGN: '=';

SEMICOLON : ';' ;
LPAREN: '(' ;
RPAREN: ')' ;
LBRACE: '{' ;
RBRACE: '}' ;
COMMA: ',';

STRING_LITERAL: '"' ( ~["\\\r\n] | '\\' ["\\bfnrt] )* '"';
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
INTEGER_LITERAL: '0' | [1-9] [0-9]*;

LINE_COMMENT: '//' ~[\r\n]* -> skip;
WS : [ \t\r\n]+ -> skip ;

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
    | assignment SEMICOLON
    | SEMICOLON
    ;

returnStatement
    : RETURN expression
    ;

functionCall: IDENTIFIER LPAREN (argumentList?) RPAREN;
argumentList: expression (COMMA expression)*;

assignment: IDENTIFIER ASSIGN expression;

expression
    : assignmentExpression
    ;

assignmentExpression
    : additiveExpression
    | IDENTIFIER ASSIGN expression
    ;

additiveExpression
    : multiplicativeExpression ((PLUS | MINUS) multiplicativeExpression)*
    ;

multiplicativeExpression
    : primaryExpression ((MULT | DIV) primaryExpression)*
    ;

primaryExpression
    : literal
    | functionCall
    | IDENTIFIER
    | LPAREN expression RPAREN
    ;

literal:
    STRING_LITERAL
    | INTEGER_LITERAL;