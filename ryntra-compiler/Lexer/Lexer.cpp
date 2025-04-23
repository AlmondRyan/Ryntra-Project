#include "Lexer.hpp"
#include <vector>

namespace Ryntra::Compiler {
    Lexer::Lexer(std::string_view source)
        : source_(source), start_(0), current_(0), line_(1) {
        initKeywords();
        initDoxygenKeywords();
    }

    std::vector<Token> Lexer::scanTokens() {
        std::vector<Token> tokens;

        while (!isAtEnd()) {
            start_ = current_;
            scanToken(tokens);
        }

        tokens.emplace_back(TokenType::END_OF_FILE, "", line_);
        return tokens;
    }

    void Lexer::initKeywords() {
        keywords_["declare"] = TokenType::DECLARE;
        keywords_["package"] = TokenType::PACKAGE;
        keywords_["import"] = TokenType::IMPORT;
        keywords_["public"] = TokenType::PUBLIC;
        keywords_["class"] = TokenType::CLASS;
        keywords_["static"] = TokenType::STATIC;
        keywords_["int"] = TokenType::INT;
        keywords_["return"] = TokenType::RETURN;
    }

    void Lexer::initDoxygenKeywords() {
        doxygen_keywords_.push_back("brief");
        doxygen_keywords_.push_back("param");
        doxygen_keywords_.push_back("return");
        doxygen_keywords_.push_back("sa");
        doxygen_keywords_.push_back("see");
        doxygen_keywords_.push_back("author");
        doxygen_keywords_.push_back("date");
        doxygen_keywords_.push_back("version");
    }

    void Lexer::scanToken(std::vector<Token> &tokens) {
        char c = advance();
        switch (c) {
        case '@':
            if (isInComment()) {
                addToken(tokens, TokenType::DOXYGEN_AT);
                if (isDoxygenKeyword()) {
                    doxygenKeyword(tokens);
                } else {
                    identifier(tokens);
                }
            } else {
                addToken(tokens, TokenType::ANNOTATION_AT);
                if (isAlpha(peek())) {
                    annotationBody(tokens);
                }
            }
            break;
        case '.':
            addToken(tokens, TokenType::DOT);
            break;
        case ';':
            addToken(tokens, TokenType::SEMICOLON);
            break;
        case '(':
            addToken(tokens, TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(tokens, TokenType::RIGHT_PAREN);
            break;
        case '{':
            addToken(tokens, TokenType::LEFT_BRACE);
            break;
        case '}':
            addToken(tokens, TokenType::RIGHT_BRACE);
            break;

        case '/':
            if (match('/')) {
                singleLineComment(tokens);
            } else if (match('*')) {
                blockComment(tokens);
            }
            break;

        case '"':
            stringLiteral(tokens);
            break;

        case ' ':
        case '\r':
        case '\t':
            break;

        case '\n':
            line_++;
            break;

        default:
            if (isAlpha(c)) {
                identifier(tokens);
            } else {
                throw std::runtime_error("Unexpected character at line " + std::to_string(line_));
            }
            break;
        }
    }

    bool Lexer::isInComment() const {
        return false;
    }

    bool Lexer::isDoxygenKeyword() {
        size_t saved_current = current_;

        std::string potential_keyword;
        while (isAlpha(peek()) && !isAtEnd()) {
            potential_keyword += advance();
        }

        current_ = saved_current;

        for (const auto &keyword : doxygen_keywords_) {
            if (potential_keyword == keyword) {
                return true;
            }
        }

        return false;
    }

    void Lexer::doxygenKeyword(std::vector<Token> &tokens) {
        while (isAlphaNumeric(peek())) {
            advance();
        }

        std::string_view text = source_.substr(start_ + 1, current_ - start_ - 1);
        tokens.emplace_back(TokenType::DOXYGEN_KEYWORD, text, line_);
    }

    void Lexer::annotationBody(std::vector<Token> &tokens) {
        while (isAlphaNumeric(peek())) {
            advance();
        }

        std::string_view text = source_.substr(start_ + 1, current_ - start_ - 1);
        tokens.emplace_back(TokenType::ANNOTATION_BODY, text, line_);
    }

    void Lexer::singleLineComment(std::vector<Token> &tokens) {
        while (peek() != '\n' && !isAtEnd()) {
            advance();
        }
        std::string_view text = source_.substr(start_, current_ - start_);
        tokens.emplace_back(TokenType::SINGLE_LINE_COMMENT, text, line_);
    }

    void Lexer::blockComment(std::vector<Token> &tokens) {
        bool isDoxygen = peek() == '*';
        if (isDoxygen)
            advance();

        while (!isAtEnd()) {
            if (peek() == '*' && peekNext() == '/') {
                advance(); // *
                advance(); // /
                break;
            }

            if (peek() == '\n')
                line_++;
            advance();
        }

        if (isAtEnd()) {
            throw std::runtime_error("Unterminated block comment at line " + std::to_string(line_));
        }

        std::string_view text = source_.substr(start_, current_ - start_);
        tokens.emplace_back(TokenType::BLOCK_COMMENT, text, line_);
    }

    void Lexer::stringLiteral(std::vector<Token> &tokens) {
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n')
                line_++;
            advance();
        }

        if (isAtEnd()) {
            throw std::runtime_error("Unterminated string at line " + std::to_string(line_));
        }

        advance(); // closing "

        std::string_view text = source_.substr(start_ + 1, current_ - start_ - 2);
        tokens.emplace_back(TokenType::STRING_LITERAL, text, line_);
    }

    void Lexer::identifier(std::vector<Token> &tokens) {
        while (isAlphaNumeric(peek())) {
            advance();
        }

        std::string_view text = source_.substr(start_, current_ - start_);
        auto             it = keywords_.find(std::string(text));
        TokenType        type = (it != keywords_.end()) ? it->second : TokenType::IDENTIFIER;

        tokens.emplace_back(type, text, line_);
    }

    char Lexer::advance() {
        return source_[current_++];
    }

    bool Lexer::match(char expected) {
        if (isAtEnd() || source_[current_] != expected) {
            return false;
        }
        current_++;
        return true;
    }

    char Lexer::peek() const {
        return isAtEnd() ? '\0' : source_[current_];
    }

    char Lexer::peekNext() const {
        return (current_ + 1 >= source_.length()) ? '\0' : source_[current_ + 1];
    }

    bool Lexer::isAtEnd() const {
        return current_ >= source_.length();
    }

    bool Lexer::isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    }

    bool Lexer::isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    bool Lexer::isAlphaNumeric(char c) {
        return isAlpha(c) || isDigit(c);
    }

    void Lexer::addToken(std::vector<Token> &tokens, TokenType type) {
        std::string_view text = source_.substr(start_, current_ - start_);
        tokens.emplace_back(type, text, line_);
    }

} // namespace Ryntra::Compiler