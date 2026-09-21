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
        bool emitIR = false;
        bool emitBytecode = false;
        bool emitAST = false;
        std::string sourcePath;

        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--emit-ir") {
                emitIR = true;
            } else if (arg == "--emit-bytecode") {
                emitBytecode = true;
            } else if (arg == "--emit-ast") {
                emitAST = true;
            } else if (arg.empty() || arg[0] == '-') {
                // Ignore unknown options.
            } else {
                sourcePath = arg;
            }
        }

        if (sourcePath.empty()) {
            std::print(std::cerr, "Usage: {} <source-file> [--emit-ast] [--emit-ir] [--emit-bytecode]\n",
                       argv[0]);
            return 1;
        }

        std::string Source;

        std::ifstream sourceFile(sourcePath);
        if (sourceFile.is_open()) {
            Source = std::string((std::istreambuf_iterator<char>(sourceFile)),
                                 std::istreambuf_iterator<char>());
        } else {
            std::print(std::cerr, "Error: cannot open source file '{}'\n", sourcePath);
            return 1;
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
        std::cout << std::endl;

#ifdef SHOW_LOG
        std::cout << tree->toStringTree(&parser) << std::endl;
#endif // #ifdef SHOW_LOG

        bool hasParseError = false;
        for (const auto &error : Ryntra::Compiler::ErrorHandler::getInstance().getErrorObjects()) {
            if (error.type == Ryntra::Compiler::kError) {
                hasParseError = true;
                break;
            }
        }

        if (hasParseError) {
            Ryntra::Compiler::ErrorHandler::getInstance().print();
            // std::cout << "Semantic Analysis Failed." << std::endl;
            return 0;
        }

        Ryntra::Compiler::ASTBuilder builder;
        auto ast = builder.visitProgram(tree);

#ifdef SHOW_LOG
        std::cout << std::endl;
        std::cout << ast->toString() << std::endl;
        std::cout << std::endl;
        std::cout << "====================================================" << std::endl;
        std::cout << std::endl;
#endif // #ifdef SHOW_LOG

        if (emitAST) {
            std::cout << ast->toString() << std::endl;
            return 0;
        }

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
            // std::cout << "Semantic Analysis Failed." << std::endl;
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

                if (emitIR) {
                    std::cout << module->toString() << std::endl;
                    return 0;
                }

                Ryntra::VM::BytecodeGenerator bcGen;
                auto bytecode = bcGen.generate(module);

                if (emitBytecode) {
                    Ryntra::VM::VirtualMachine dumpVM;
                    dumpVM.load(bytecode, bcGen.getConstantPool());
                    dumpVM.disassemble();
                    return 0;
                }

                Ryntra::VM::VirtualMachine vm;
                vm.load(bytecode, bcGen.getConstantPool());
                auto result = vm.execute("main");

#ifdef SHOW_LOG
                vm.disassemble();
#endif // #ifdef SHOW_LOG
            }
        }

        return 0;
    } catch (const std::exception &e) {
        std::print(std::cerr, "Error: {}\n", e.what());
        return 1;
    }
}