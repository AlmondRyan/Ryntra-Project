grammar Ryntra;

// Keywords
PUBLIC: 'public';
INT: 'int';
VOID: 'void';
RETURN: 'return';

// Symbols & Operators
SEMICOLON: ';';
COMMA: ',';
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
ASSIGN: '=';
ADD_ASSIGN: '+=';
SUB_ASSIGN: '-=';
MUL_ASSIGN: '*=';
DIV_ASSIGN: '/=';
MOD_ASSIGN: '%=';
PLUS: '+';
MINUS: '-';
MUL: '*';
DIV: '/';
MOD: '%';

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
    | VOID
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
    : typeSpecifier IDENTIFIER (ASSIGN expression)?
    ;

returnStatement
    : RETURN expression SEMICOLON
    ;

expression
    : LPAREN expression RPAREN                              # ParenthesizedExpression
    | left=expression op=(MUL|DIV|MOD) right=expression     # BinaryExpression
    | left=expression op=(PLUS|MINUS) right=expression      # BinaryExpression
    | <assoc=right> left=expression op=(ASSIGN|ADD_ASSIGN|SUB_ASSIGN|MUL_ASSIGN|DIV_ASSIGN|MOD_ASSIGN) right=expression  # AssignmentExpression
    | IDENTIFIER LPAREN argumentList? RPAREN                # FunctionCall
    | IDENTIFIER                                            # VariableReference
    | STRING_LITERAL                                        # StringLiteral
    | INTEGER_LITERAL                                       # IntegerLiteral
    ;

argumentList
    : expression (COMMA expression)*
    ;