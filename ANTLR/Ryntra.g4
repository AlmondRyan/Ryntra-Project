grammar Ryntra;

// Keywords
PUBLIC: 'public';
INT: 'int';
LONG: 'long';
VOID: 'void';
RETURN: 'return';
IF: 'if';
ELSE: 'else';
WHILE: 'while';
FOR: 'for';
BREAK: 'break';
CONTINUE: 'continue';
BOOL: 'bool';
TRUE: 'true';
FALSE: 'false';
NEW: 'new';
REF: 'ref';
PTR: 'ptr';
UNSAFE: 'unsafe';
LOAD: 'load';
STORE: 'store';

// Symbols & Operators
SEMICOLON: ';';
COMMA: ',';
DOT: '.';
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
LBRACK: '[';
RBRACK: ']';
INC: '++';
DEC: '--';
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
NOT: '!';
SHL: '<<';
SHR: '>>';

// Comparison Operators
EQ: '==';
NE: '!=';
GE: '>=';
LE: '<=';
GT: '>';
LT: '<';

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

LINE_COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;
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
    | BOOL
    | REF LT typeSpecifier GT
    | PTR LT typeSpecifier GT
    ;

block
    : LBRACE statement* RBRACE
    ;

statement
    : variableDeclaration SEMICOLON
    | arrayDeclaration
    | expression SEMICOLON
    | returnStatement
    | ifStatement
    | whileStatement
    | forStatement
    | breakStatement
    | continueStatement
    | unsafeBlock
    ;

unsafeBlock
    : UNSAFE block
    ;

whileStatement
    : WHILE LPAREN expression RPAREN block
    ;

forStatement
    : FOR LPAREN forInitClause? SEMICOLON forCondClause? SEMICOLON forOperClause? RPAREN block
    ;

forInitClause
    : variableDeclaration
    | expression
    ;

forCondClause
    : expression
    ;

forOperClause
    : expression
    ;

breakStatement
    : BREAK SEMICOLON
    ;

continueStatement
    : CONTINUE SEMICOLON
    ;

ifStatement
    : IF LPAREN expression RPAREN block elseBranch?
    ;

elseBranch
    : ELSE block
    | ELSE ifStatement
    ;

variableDeclaration
    : typeSpecifier IDENTIFIER (ASSIGN expression)?
    ;

arrayDeclaration
    : typeSpecifier LBRACK RBRACK IDENTIFIER ASSIGN NEW typeSpecifier LBRACK expression RBRACK SEMICOLON
    ;

returnStatement
    : RETURN expression SEMICOLON
    ;

expression
    : REF LPAREN expression RPAREN                                  # RefExpression
    | PTR LPAREN expression RPAREN                                  # PtrExpression
    | LPAREN typeSpecifier RPAREN expression                        # CastExpression
    | LPAREN expression RPAREN                                      # ParenthesizedExpression
    | expression INC                                                # PostfixIncExpression
    | expression DEC                                                # PostfixDecExpression
    | IDENTIFIER LPAREN argumentList? RPAREN                        # FunctionCall
    | ptr=expression DOT LOAD LPAREN RPAREN                         # PtrLoadExpression
    | ptr=expression DOT STORE LPAREN value=expression RPAREN       # PtrStoreExpression
    | array=expression LBRACK index=expression RBRACK               # ArrayIndexAccess
    | INC expression                                                # PrefixIncExpression
    | DEC expression                                                # PrefixDecExpression
    | MINUS expression                                              # UnaryMinusExpression
    | BIT_NOT expression                                            # UnaryExpression
    | NOT expression                                                # NotExpression
    | left=expression op=(MUL|DIV|MOD) right=expression              # MulDivModExpression
    | left=expression op=(PLUS|MINUS) right=expression               # PlusMinusExpression
    | left=expression op=(SHL|SHR) right=expression                  # ShiftExpression
    | left=expression op=BIT_AND right=expression                    # BitAndExpression
    | left=expression op=BIT_XOR right=expression                    # BitXorExpression
    | left=expression op=BIT_OR right=expression                     # BitOrExpression
    | left=expression op=(EQ|NE|GE|LE|GT|LT) right=expression         # ComparisonExpression
    | <assoc=right> left=expression op=(ASSIGN|ADD_ASSIGN|SUB_ASSIGN|MUL_ASSIGN|DIV_ASSIGN|MOD_ASSIGN|AND_ASSIGN|OR_ASSIGN|XOR_ASSIGN|SHL_ASSIGN|SHR_ASSIGN) right=expression  # AssignmentExpression
    | IDENTIFIER                                                    # VariableReference
    | STRING_LITERAL                                                # StringLiteral
    | INTEGER_LITERAL                                               # IntegerLiteral
    | TRUE                                                          # TrueLiteral
    | FALSE                                                         # FalseLiteral
    ;

argumentList
    : expression (COMMA expression)*
    ;
