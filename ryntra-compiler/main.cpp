#include "Lexer/Lexer.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// 将TokenType转换为字符串的辅助函数
std::string tokenTypeToString(Ryntra::Compiler::TokenType type) {
    switch (type) {
        case Ryntra::Compiler::TokenType::DECLARE: return "DECLARE";
        case Ryntra::Compiler::TokenType::PACKAGE: return "PACKAGE";
        case Ryntra::Compiler::TokenType::IMPORT: return "IMPORT";
        case Ryntra::Compiler::TokenType::PUBLIC: return "PUBLIC";
        case Ryntra::Compiler::TokenType::CLASS: return "CLASS";
        case Ryntra::Compiler::TokenType::STATIC: return "STATIC";
        case Ryntra::Compiler::TokenType::INT: return "INT";
        case Ryntra::Compiler::TokenType::RETURN: return "RETURN";
        case Ryntra::Compiler::TokenType::IDENTIFIER: return "IDENTIFIER";
        case Ryntra::Compiler::TokenType::STRING_LITERAL: return "STRING_LITERAL";
        case Ryntra::Compiler::TokenType::ANNOTATION_AT: return "ANNOTATION_AT";
        case Ryntra::Compiler::TokenType::ANNOTATION_BODY: return "ANNOTATION_BODY";
        case Ryntra::Compiler::TokenType::DOXYGEN_AT: return "DOXYGEN_AT";
        case Ryntra::Compiler::TokenType::DOXYGEN_KEYWORD: return "DOXYGEN_KEYWORD";
        case Ryntra::Compiler::TokenType::DOT: return "DOT";
        case Ryntra::Compiler::TokenType::SEMICOLON: return "SEMICOLON";
        case Ryntra::Compiler::TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case Ryntra::Compiler::TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case Ryntra::Compiler::TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case Ryntra::Compiler::TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case Ryntra::Compiler::TokenType::SINGLE_LINE_COMMENT: return "SINGLE_LINE_COMMENT";
        case Ryntra::Compiler::TokenType::BLOCK_COMMENT: return "BLOCK_COMMENT";
        case Ryntra::Compiler::TokenType::END_OF_FILE: return "END_OF_FILE";
        default: return "UNKNOWN";
    }
}

int main() {
    // 从文件读取源代码
    std::string filename;
    std::cout << "Please enter the path you want to analyze: ";
    std::getline(std::cin, filename);
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    
    try {
        Ryntra::Compiler::Lexer lexer(source);
        auto tokens = lexer.scanTokens();
        
        std::cout << "\nResult:\n";
        std::cout << "==============================\n";
        std::cout << "Row\tType\t\tContent\n";
        std::cout << "==============================\n";
        
        for (const auto& token : tokens) {
            std::string typeStr = tokenTypeToString(token.getType());
            std::cout << token.getLine() << "\t" 
                      << typeStr << "\t\t" 
                      << "\"" << token.getLexeme() << "\"\n";
        }
        
        std::cout << "==============================\n";
        std::cout << "Total Find " << tokens.size() << " Lexical Unit(s).\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}