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
    // 1. Test __builtin_print()
    __builtin_print("Hello world! \n");

    // 2. Test variable declaration & assignment
    int a = 10;
    int b = a;
    a = 20;

    // 3. Test __builtin_intToString()
    __builtin_print(__builtin_intToString(a));
    __builtin_print(__builtin_intToString(b));

    // 4. Test Binary Operator
    int c = a + b;
    __builtin_print(" ");
    __builtin_print(__builtin_intToString(c));

    int d = a - b;
    __builtin_print(" ");
    __builtin_print(__builtin_intToString(d));

    int e = a * b;
    __builtin_print(" ");
    __builtin_print(__builtin_intToString(e));

    int f = a / b;
    __builtin_print(" ");
    __builtin_print(__builtin_intToString(f));

    // 5. Test Result Discarding (should do a warning)
    f + 10;

    // 6. Test boolean declaration
    bool g1 = true;
    bool g2 = false;

    // 6. Test return statement
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
            for (auto i : Ryntra::Compiler::ErrorHandler::getInstance().getErrorObjects()) {
                if (i.type == Ryntra::Compiler::ET_WARNING) {
                    continue;
                } else {
                    std::cout << "Semantic Analysis Failed." << std::endl;
                    return 0;
                }
            }
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
