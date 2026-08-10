#include "AST/ASTBuilder.h"
#include "ErrorHandler/ErrorHandler.h"
#include "ErrorHandler/LexParseErrorHandler.h"
#include "IR/IRGenerator.h"
#include "Semantic/SemanticAnalyzer.h"
#include "VM/BytecodeGenerator.h"
#include "VM/VirtualMachine.h"
#include <antlr/RyntraLexer.h>
#include <antlr/RyntraParser.h>
#include <antlr4-runtime.h>
#include <fstream>
#include <iostream>

// #define SHOW_LOG

int main(int argc, char **argv) {
    try {
        std::string Source;

        std::ifstream sourceFile(argv[1]);
        if (sourceFile.is_open()) {
            Source = std::string((std::istreambuf_iterator<char>(sourceFile)),
                                 std::istreambuf_iterator<char>());
        }

#ifdef SHOW_LOG
        std::cout << "Source: " << std::endl;
        std::cout << Source << std::endl;
        std::cout << "====================================================" << std::endl;
#endif // #ifdef SHOW_LOG

        antlr4::ANTLRInputStream input(Source);
        Ryntra::antlr::RyntraLexer lexer(&input);
        antlr4::CommonTokenStream tokens(&lexer);
        tokens.fill();
        Ryntra::antlr::RyntraParser parser(&tokens);

        parser.removeErrorListeners();
        parser.addErrorListener(new Ryntra::Compiler::LexParseErrorHandler());

        auto tree = parser.program();

#ifdef SHOW_LOG
        std::cout << tree->toStringTree(&parser) << std::endl;
        std::cout << std::endl;
#endif // #ifdef SHOW_LOG

        Ryntra::Compiler::ASTBuilder builder;
        auto ast = builder.visitProgram(tree);

#ifdef SHOW_LOG
        std::cout << std::endl;
        std::cout << ast->toString() << std::endl;
        std::cout << std::endl;
        std::cout << "====================================================" << std::endl;
        std::cout << std::endl;
#endif // #ifdef SHOW_LOG

        Ryntra::Compiler::Semantic::SemanticAnalyzer analyzer;
        analyzer.analyze(ast);

        Ryntra::Compiler::ErrorHandler::getInstance().print();
        bool hasError = false;
        for (const auto &error : Ryntra::Compiler::ErrorHandler::getInstance().getErrorObjects()) {
            if (error.type == Ryntra::Compiler::kError) {
                hasError = true;
                break;
            }
        }

        if (hasError) {
            std::cout << "Semantic Analysis Failed." << std::endl;
        } else {
            if (auto typedAST = analyzer.getTypedAST()) {
#ifdef SHOW_LOG
                std::cout << "Typed AST:" << std::endl;
                typedAST->dump();
                std::cout << std::endl;
                std::cout << "====================================================" << std::endl;
#endif // #ifdef SHOW_LOG

                Ryntra::IR::IRGenerator irGen;
                auto module = irGen.generate(*typedAST, "HelloWorld");

#ifdef SHOW_LOG
                std::cout << module->toString() << std::endl;
                std::cout << "====================================================" << std::endl;
#endif // #ifdef SHOW_LOG

                Ryntra::VM::BytecodeGenerator bcGen;
                auto bytecode = bcGen.generate(module);

                Ryntra::VM::VirtualMachine vm;
                vm.load(bytecode, bcGen.getConstantPool());
                auto result = vm.execute("main");

#ifdef SHOW_LOG
                vm.disassemble();
#endif // #ifdef SHOW_LOG

                // std::cout << "\nProgram exited with code: ";
                // if (result.isInt32()) {
                //     std::cout << result.asInt32() << std::endl;
                // } else {
                //     std::cout << "0" << std::endl;
                // }
            }
        }

        // std::cout << std::endl;
        return 0;
    } catch (const std::exception &e) {
        // std::cerr << "Error: " << e.what() << std::endl;
        std::print(std::cerr, "Error: {}\n", e.what());
        return 1;
    }
}