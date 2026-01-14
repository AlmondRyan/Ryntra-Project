grammar Ryntra;

// LEXICAL RULES

INT: 'int' ;
RETURN: 'return';
STRING: 'string';
IF: 'if';
ELSE: 'else';

PLUS: '+';
MINUS: '-';
MULT: '*';
DIV: '/';
ASSIGN: '=';
GREATER: '>';
LESS: '<';
COND_EQUAL: '==';
GREATER_EQ: '>=';
LESS_EQ: '<=';

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
    | STRING IDENTIFIER (ASSIGN expression)?
    ;

statement:
    functionCall SEMICOLON
    | expression SEMICOLON
    | variableDeclaration SEMICOLON
    | returnStatement SEMICOLON
    | assignment SEMICOLON
    | ifStatement
    | SEMICOLON
    ;

returnStatement
    : RETURN expression
    ;

ifStatement
    : IF LPAREN expression RPAREN block elseClause?
    ;

elseClause
    : ELSE (ifStatement | block)
    ;

functionCall: IDENTIFIER LPAREN (argumentList?) RPAREN;
argumentList: expression (COMMA expression)*;

assignment: IDENTIFIER ASSIGN expression;

expression
    : assignmentExpression
    ;

assignmentExpression
    : relationalExpression
    | IDENTIFIER ASSIGN expression
    ;

relationalExpression
    : additiveExpression ((GREATER | LESS | GREATER_EQ | LESS_EQ | COND_EQUAL) additiveExpression)*
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