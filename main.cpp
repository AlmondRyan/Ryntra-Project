#include <iostream>
#include <memory>
#include "antlr4-runtime.h"
#include <antlr/RyntraLexer.h>
#include <antlr/RyntraParser.h>
#include "Compiler/AST/ASTBuilder.h"
#include "Compiler/AST/ASTNodes.h"
#include "ErrorHandler/ErrorHandler.h"
#include "IRGenerator/IRGenerator.h"
#include "Semantic/SemanticAnalyzer.h"

int main() {
    std::string src = R"(int main() {
    __builtin_print("Fuck you world!");
    int a = 10;
    int b = a;
    a = 20;
    __builtin_print(__builtin_intToString(a));
    __builtin_print(__builtin_intToString(b));
    return 0;
})";
    try {
        antlr4::ANTLRInputStream input(src);
        Ryntra::antlr::RyntraLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        
        tokens.fill();
        Ryntra::antlr::RyntraParser parser(&tokens);

        auto* programContext = parser.program();
        if (parser.getNumberOfSyntaxErrors() > 0) {
            std::cout << "Syntax errors found in input" << std::endl;
            return 1;
        }
        
        Ryntra::Compiler::ASTBuilder astBuilder;
        auto programNode = astBuilder.visitProgram(programContext);
        
        std::cout << ">>> Generated AST:" << std::endl;
        std::cout << programNode->toString() << std::endl;

        Ryntra::Compiler::SemanticAnalyzer semanticAnalyzer;
        semanticAnalyzer.visitProgram(programNode);

        Ryntra::Compiler::ErrorHandler::getInstance().print();

        if (!Ryntra::Compiler::ErrorHandler::getInstance().getErrorObjects().empty()) {
            std::cout << "Semantic Analysis failed." << std::endl;
            return 0;
        }

        Ryntra::Compiler::IRGenerator irGenerator;
        irGenerator.visitProgram(programNode);
        auto ir = irGenerator.getIR();
        std::cout << ir << std::endl;

        std::ofstream out("output.ll");
        if (out.is_open()) {
            out << ir;
            out.close();
            std::cout << "IR Written Successfully." << std::endl;
        } else {
            std::cout << "Cannot open file." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Error occurred: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
