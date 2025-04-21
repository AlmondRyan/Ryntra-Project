#ifndef RYNTRA_LEXER_HPP
#define RYNTRA_LEXER_HPP

#include "Token.hpp"
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace Ryntra::Compiler {
    class Lexer {
    public:
        explicit Lexer(std::string_view source);
        std::vector<Token> scanTokens();

    private:
        void        initKeywords();
        void        initDoxygenKeywords();
        void        scanToken(std::vector<Token> &tokens);
        void        singleLineComment(std::vector<Token> &tokens);
        void        blockComment(std::vector<Token> &tokens);
        void        stringLiteral(std::vector<Token> &tokens);
        void        identifier(std::vector<Token> &tokens);
        void        doxygenKeyword(std::vector<Token> &tokens);
        void        annotationBody(std::vector<Token> &tokens);
        bool        isInComment() const;
        bool        isDoxygenKeyword();
        bool        isAtEnd() const;
        char        advance();
        bool        match(char expected);
        char        peek() const;
        char        peekNext() const;
        void        addToken(std::vector<Token> &tokens, TokenType type);
        static bool isAlpha(char c);
        static bool isDigit(char c);
        static bool isAlphaNumeric(char c);

    private:
        const std::string_view                     source_;
        size_t                                     start_;
        size_t                                     current_;
        size_t                                     line_;
        std::unordered_map<std::string, TokenType> keywords_;
        std::vector<std::string>                   doxygen_keywords_;
    };

} // namespace Ryntra::Compiler

#endif // RYNTRA_LEXER_HPP