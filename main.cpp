#include "AST/ASTBuilder.h"
#include "Compiler/IR/HLIRBuilder.h"
#include "Compiler/IR/LLIRBuilder.h"
#include "ErrorHandler/ErrorHandler.h"
#include "IR/IRBuilder.h"
#include "Semantic/SemanticAnalyzer.h"
#include <antlr/RyntraLexer.h>
#include <antlr/RyntraParser.h>
#include <antlr4-runtime.h>
#include <fstream>
#include <iostream>
#include <sstream>

int main() {
    try {
        std::string Source = R"(
public int main() {
    __builtin_print("hello");
    return 0;
})";

        std::cout << "Source: ";
        std::cout << Source << std::endl;
        std::cout << "====================================================" << std::endl;

        antlr4::ANTLRInputStream input(Source);
        Ryntra::antlr::RyntraLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        tokens.fill();
        Ryntra::antlr::RyntraParser parser(&tokens);
        auto tree = parser.program();

        // std::cout << tree->toStringTree(&parser) << std::endl;
        // std::cout << std::endl;

        Ryntra::Compiler::ASTBuilder builder;
        auto ast = builder.visitProgram(tree);
        std::cout << std::endl;
        std::cout << ast->toString() << std::endl;
        std::cout << std::endl;
        std::cout << "====================================================" << std::endl;
        std::cout << std::endl;

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
            std::cout << "Semantic Analysis Failed." << std::endl;
        } else {
            std::cout << "Semantic Analysis Passed." << std::endl;
            if (auto typedAST = analyzer.getTypedAST()) {
                std::cout << "Typed AST:" << std::endl;
                typedAST->dump();
                std::cout << std::endl;
                std::cout << "====================================================" << std::endl;

                // Generate IR
                std::cout << "\nGenerating High-Level IR (SSA IR)..." << std::endl << std::endl;
                Ryntra::Compiler::IR::HLIRBuilder irBuilder;
                typedAST->accept(irBuilder);

                auto module = irBuilder.takeModule();
                std::cout << "HLIR Output:" << std::endl;
                std::cout << module->print() << std::endl;

                std::cout << "LLIR Output:" << std::endl;
                Ryntra::Compiler::IR::LLIRBuilder llirBuilder;
                std::cout << llirBuilder.emit(module.get()) << std::endl;
                std::cout << "====================================================" << std::endl;
            }
        }

        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}