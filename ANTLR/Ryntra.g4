grammar Ryntra;

// Keywords
PUBLIC: 'public';
INT: 'int';
LONG: 'long';
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

// Bitwise Operators
BIT_AND: '&';
BIT_OR: '|';
BIT_XOR: '^';
BIT_NOT: '~';
SHL: '<<';
SHR: '>>';

// Bitwise Compound Assignment
AND_ASSIGN: '&=';
OR_ASSIGN: '|=';
XOR_ASSIGN: '^=';
SHL_ASSIGN: '<<=';
SHR_ASSIGN: '>>=';

// Lexical Objects
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
STRING_LITERAL: '"' (~["\\\r\n] | '\\' .)* '"';
INTEGER_LITERAL: [0-9]+ [Ll]?;
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
    | LONG
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
    : LPAREN expression RPAREN                                      # ParenthesizedExpression
    | BIT_NOT expression                                            # UnaryExpression
    | left=expression op=(MUL|DIV|MOD) right=expression              # MulDivModExpression
    | left=expression op=(PLUS|MINUS) right=expression               # PlusMinusExpression
    | left=expression op=(SHL|SHR) right=expression                  # ShiftExpression
    | left=expression op=BIT_AND right=expression                    # BitAndExpression
    | left=expression op=BIT_XOR right=expression                    # BitXorExpression
    | left=expression op=BIT_OR right=expression                     # BitOrExpression
    | <assoc=right> left=expression op=(ASSIGN|ADD_ASSIGN|SUB_ASSIGN|MUL_ASSIGN|DIV_ASSIGN|MOD_ASSIGN|AND_ASSIGN|OR_ASSIGN|XOR_ASSIGN|SHL_ASSIGN|SHR_ASSIGN) right=expression  # AssignmentExpression
    | IDENTIFIER LPAREN argumentList? RPAREN                        # FunctionCall
    | IDENTIFIER                                                    # VariableReference
    | STRING_LITERAL                                                # StringLiteral
    | INTEGER_LITERAL                                               # IntegerLiteral
    ;

argumentList
    : expression (COMMA expression)*
    ;
