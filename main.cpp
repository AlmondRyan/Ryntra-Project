#include <iostream>
#include <fstream>
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
    // Read Source File
    std::ifstream inFileStream("Test.rynt");
    std::string src;
    if (inFileStream) {
        std::ostringstream ss;
        ss << inFileStream.rdbuf();
        src = ss.str();
    }

    try {
        // 1. Initialize ANTLR
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

        // 2. Build AST
        Ryntra::Compiler::ASTBuilder astBuilder;
        auto programNode = astBuilder.visitProgram(programContext);
        
        std::cout << ">>> Generated AST:" << std::endl;
        std::cout << programNode->toString() << std::endl;

        // 3. Semantic Analysis
        Ryntra::Compiler::SemanticAnalyzer semanticAnalyzer;
        semanticAnalyzer.visitProgram(programNode);

        // 4. Get Semantic Errors
        Ryntra::Compiler::ErrorHandler::getInstance().print();

        // If there's no errors but only warnings, continue IR Generating without terminate
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

        // 5. IR Generating
        Ryntra::Compiler::IRGenerator irGenerator;
        irGenerator.visitProgram(programNode);
        auto ir = irGenerator.getIR();
        std::cout << ir << std::endl;

        // 6. Write IR into .ll file
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
