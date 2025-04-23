#ifndef RYNTRA_TOKEN_HPP
#define RYNTRA_TOKEN_HPP

#include <string>
#include <string_view>

namespace Ryntra::Compiler {
    enum class TokenType {
        DECLARE,
        PACKAGE,
        IMPORT,
        PUBLIC,
        CLASS,
        STATIC,
        INT,
        RETURN,

        IDENTIFIER,
        STRING_LITERAL,

        ANNOTATION_AT,
        ANNOTATION_BODY,
        DOXYGEN_AT,
        DOXYGEN_KEYWORD,

        DOT,         // .
        SEMICOLON,   // ;
        LEFT_PAREN,  // (
        RIGHT_PAREN, // )
        LEFT_BRACE,  // {
        RIGHT_BRACE, // }

        SINGLE_LINE_COMMENT,
        BLOCK_COMMENT,

        END_OF_FILE
    };

    class Token {
    public:
        Token(TokenType type, std::string_view lexeme, size_t line);

        TokenType        getType() const;
        std::string_view getLexeme() const;
        size_t           getLine() const;

    private:
        TokenType        type_;
        std::string_view lexeme_;
        size_t           line_;
    };

} // namespace Ryntra::Compiler

#endif // RYNTRA_TOKEN_HPP