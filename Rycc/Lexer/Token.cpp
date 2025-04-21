#include "Token.hpp"

namespace Ryntra::Compiler {

    Token::Token(TokenType type, std::string_view lexeme, size_t line)
        : type_(type), lexeme_(lexeme), line_(line) {}

    TokenType Token::getType() const { return type_; }

    std::string_view Token::getLexeme() const { return lexeme_; }

    size_t Token::getLine() const { return line_; }

} // namespace Ryntra::Compiler