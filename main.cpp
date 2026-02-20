#include <iostream>
#include <fstream>
#include <sstream>
#include <antlr4-runtime.h>
#include <antlr/RyntraLexer.h>
#include <antlr/RyntraParser.h>
#include "AST/ASTBuilder.h"
#include "Semantic/SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"
#include "IR/IRBuilder.h"
#include "Compiler/IR/HLIRBuilder.h"

int main() {
    try {
        std::string Source = R"(
public int main() {
    __builtin_print("hello");
    return 0;
})";

        antlr4::ANTLRInputStream input(Source);
        Ryntra::antlr::RyntraLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        tokens.fill();
        Ryntra::antlr::RyntraParser parser(&tokens);
        auto tree = parser.program();

        // std::cout << tree->toStringTree(&parser) << std::endl;
        std::cout << std::endl;

        Ryntra::Compiler::ASTBuilder builder;
        auto ast = builder.visitProgram(tree);
        // std::cout << ast->toString() << std::endl;

        Ryntra::Compiler::Semantic::SemanticAnalyzer analyzer;
        analyzer.analyze(ast);

        Ryntra::Compiler::ErrorHandler::getInstance().print();
        bool hasError = false;
        for (const auto &error : Ryntra::Compiler::ErrorHandler::getInstance().getErrorObjects()) {
            if (error.type == Ryntra::Compiler::ET_ERROR) {
                hasError = true;
                break;
            }
        }

        if (hasError) {
            std::cout << "Semantic Analysis Failed" << std::endl;
        } else {
            std::cout << "Semantic Analysis Passed" << std::endl;
            if (auto typedAST = analyzer.getTypedAST()) {
                std::cout << "Typed AST:" << std::endl;
                typedAST->dump();

                // Generate IR
                std::cout << "\nGenerating IR..." << std::endl;
                Ryntra::Compiler::IR::HLIRBuilder irBuilder;
                typedAST->accept(irBuilder);
                
                auto module = irBuilder.takeModule();
                std::cout << "IR Output:" << std::endl;
                std::cout << module->print() << std::endl;
            }
        }

        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}