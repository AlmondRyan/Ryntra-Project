grammar Ryntra;

// LEXICAL RULES

// Keywords
INT: 'int' ;
RETURN: 'return';
STRING: 'string';
IF: 'if';
ELSE: 'else';
BOOL: 'bool';
TRUE: 'true';
FALSE: 'false';
WHILE: 'while';
FOR: 'for';
BREAK: 'break';
CONTINUE: 'continue';
LONG: 'long';
FLOAT: 'float';
DOUBLE: 'double';

// Operators
PLUS: '+';
MINUS: '-';
INC: '++';
DEC: '--';
MULT: '*';
DIV: '/';
MOD: '%';
ASSIGN: '=';
ADD_ASSIGN: '+=';
SUB_ASSIGN: '-=';
MUL_ASSIGN: '*=';
DIV_ASSIGN: '/=';
MOD_ASSIGN: '%=';
AND_ASSIGN: '&=';
OR_ASSIGN: '|=';
XOR_ASSIGN: '^=';
LSHIFT_ASSIGN: '<<=';
RSHIFT_ASSIGN: '>>=';
GREATER: '>';
LESS: '<';
COND_EQUAL: '==';
NOT_EQUAL: '!=';
GREATER_EQ: '>=';
LESS_EQ: '<=';
LOGIC_AND: '&&';
LOGIC_OR: '||';
NOT: '!';
BIT_AND: '&';
BIT_OR: '|';
BIT_XOR: '^';
BIT_NOT: '~';
LSHIFT: '<<';
RSHIFT: '>>';

// Symbols
SEMICOLON : ';' ;
LPAREN: '(' ;
RPAREN: ')' ;
LBRACE: '{' ;
RBRACE: '}' ;
COMMA: ',';

// Literals
STRING_LITERAL: '"' ( ~["\\\r\n] | '\\' ["\\bfnrt] )* '"';
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
INTEGER_LITERAL: ('0' | [1-9] [0-9]*) ([lL] | [lL][lL])?;
FLOAT_LITERAL: [0-9]+ '.' [0-9]* ([eE] [+-]? [0-9]+)? [fF]?
             | '.' [0-9]+ ([eE] [+-]? [0-9]+)? [fF]?
             | [0-9]+ [eE] [+-]? [0-9]+ [fF]?
             ;

// Comments and Whitespaces
LINE_COMMENT: '//' ~[\r\n]* -> skip;
WS : [ \t\r\n]+ -> skip ;

// PARSER RULES

program: functionDefinition+ EOF;

functionDefinition
    : typeSpecifier IDENTIFIER LPAREN parameterList? RPAREN block
    ;

parameterList
    : typeSpecifier IDENTIFIER (COMMA typeSpecifier IDENTIFIER)*
    ;

block
    : LBRACE statement* RBRACE
    ;

typeSpecifier
    : INT
    | STRING
    | BOOL
    | LONG
    | LONG LONG
    | FLOAT
    | DOUBLE
    ;

variableDeclaration
    : typeSpecifier IDENTIFIER (ASSIGN expression)?
//    | STRING IDENTIFIER (ASSIGN expression)?
//    | BOOL IDENTIFIER (ASSIGN expression)?
//    | LONG IDENTIFIER (ASSIGN expression)?
//    | LONG LONG IDENTIFIER (ASSIGN expression)?
    ;

statement:
    functionCall SEMICOLON
    | expression SEMICOLON
    | variableDeclaration SEMICOLON
    | returnStatement SEMICOLON
    | assignment SEMICOLON
    | ifStatement
    | whileStatement
    | forStatement
    | breakStatement SEMICOLON
    | continueStatement SEMICOLON
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

whileStatement
    : WHILE LPAREN expression RPAREN block
    ;

forStatement
    : FOR LPAREN (variableDeclaration | assignment | expression)? SEMICOLON
      expression? SEMICOLON
      (assignment | expression)? RPAREN block
    ;

breakStatement
    : BREAK
    ;

continueStatement
    : CONTINUE
    ;

functionCall: IDENTIFIER LPAREN (argumentList?) RPAREN;
argumentList: expression (COMMA expression)*;

assignment: IDENTIFIER (ASSIGN | ADD_ASSIGN | SUB_ASSIGN | MUL_ASSIGN | DIV_ASSIGN | MOD_ASSIGN | AND_ASSIGN | OR_ASSIGN | XOR_ASSIGN | LSHIFT_ASSIGN | RSHIFT_ASSIGN) expression;

expression
    : logicalOrExpression
    ;

logicalOrExpression
    : logicalAndExpression (LOGIC_OR logicalAndExpression)*
    ;

logicalAndExpression
    : inclusiveOrExpression (LOGIC_AND inclusiveOrExpression)*
    ;

inclusiveOrExpression
    : exclusiveOrExpression (BIT_OR exclusiveOrExpression)*
    ;

exclusiveOrExpression
    : andExpression (BIT_XOR andExpression)*
    ;

andExpression
    : equalityExpression (BIT_AND equalityExpression)*
    ;

equalityExpression
    : relationalExpression ((COND_EQUAL | NOT_EQUAL) relationalExpression)*
    ;

relationalExpression
    : shiftExpression ((GREATER | LESS | GREATER_EQ | LESS_EQ) shiftExpression)*
    ;

shiftExpression
    : additiveExpression ((LSHIFT | RSHIFT) additiveExpression)*
    ;

additiveExpression
    : multiplicativeExpression ((PLUS | MINUS) multiplicativeExpression)*
    ;

multiplicativeExpression
    : unaryExpression ((MULT | DIV | MOD) unaryExpression)*
    ;

unaryExpression
    : postfixExpression
    | NOT unaryExpression
    | BIT_NOT unaryExpression
    | MINUS unaryExpression
    ;

postfixExpression
    : primaryExpression
    | IDENTIFIER INC
    | IDENTIFIER DEC
    ;

primaryExpression
    : literal
    | functionCall
    | IDENTIFIER
    | LPAREN expression RPAREN
    ;

literal:
    STRING_LITERAL
    | INTEGER_LITERAL
    | FLOAT_LITERAL
    | TRUE
    | FALSE;