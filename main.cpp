#include "AST/ASTBuilder.h"
#include "ErrorHandler/ErrorHandler.h"
#include "IR/BasicBlock.h"
#include "IR/IRBuilder.h"
#include "IR/IRGenerator.h"
#include "Semantic/SemanticAnalyzer.h"
#include "VM/BytecodeGenerator.h"
#include "VM/VirtualMachine.h"
#include <antlr/RyntraLexer.h>
#include <antlr/RyntraParser.h>
#include <antlr4-runtime.h>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char **argv) {
    try {
        std::string Source;

        std::ifstream sourceFile(argv[1]);
        if (sourceFile.is_open()) {
            Source = std::string((std::istreambuf_iterator<char>(sourceFile)),
                                 std::istreambuf_iterator<char>());
        }

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
                // std::cout << "Typed AST:" << std::endl;
                // typedAST->dump();
                // std::cout << std::endl;
                // std::cout << "====================================================" << std::endl;

                Ryntra::IR::IRGenerator irGen;
                auto module = irGen.generate(*typedAST, "HelloWorld");
                std::cout << module->toString() << std::endl;
                std::cout << "====================================================" << std::endl;

                // Generate bytecode and execute
                Ryntra::VM::BytecodeGenerator bcGen;
                auto bytecode = bcGen.generate(module);

                std::cout << "Executing VM..." << std::endl;
                Ryntra::VM::VirtualMachine vm;
                vm.load(bytecode, bcGen.getConstantPool());
                auto result = vm.execute("main");

                std::cout << "\nProgram exited with code: ";
                if (result.isInt32()) {
                    std::cout << result.asInt32() << std::endl;
                } else {
                    std::cout << "0" << std::endl;
                }
            }
        }

        std::cout << std::endl;
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}