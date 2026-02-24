#include "AST/ASTBuilder.h"
#include "Compiler/IR/HLIRBuilder.h"
// #include "Compiler/IR/LLIRBuilder.h"
#include "ErrorHandler/ErrorHandler.h"
#include "Semantic/SemanticAnalyzer.h"
#include <antlr/RyntraLexer.h>
#include <antlr/RyntraParser.h>
#include <antlr4-runtime.h>
#include <fstream>
#include <iostream>
#include <sstream>

// void manuallyCreateIR() {
//     using namespace Ryntra::Compiler;
//     auto module = std::make_unique<Module>("HelloWorld");
//     IRBuilder builder(module.get());
//
//     // Create `external func @__builtin_print(string) -> void`
//     std::vector<Type*> printArgs = { Type::getStringTy() }; // Argument
//     Function *printFunc = builder.CreateExternalFunction("__builtin_print", Type::getVoidTy(), printArgs);
//
//     // Create `@str0 = constant string "Hello World"
//     auto *str0 = builder.CreateConstant<ConstantObject>(Type::getStringTy(), "str0", "\"Hello World\"");
//     auto *str1 = builder.CreateConstant<ConstantObject>(Type::getStringTy(), "str1", "\"Hello World2\"");
//
//     // Create Function `func @main() -> i32`
//     Function *mainFunction = builder.CreateFunction("main", Type::getInt32Ty());
//
//     // Create `entry:` basic block
//     BasicBlock *entry = builder.CreateBasicBlock("entry", mainFunction);
//     builder.SetInsertPoint(entry);
//
//     // Create `%0 : load @str0`
//     auto *loadInst1 = builder.CreateLoad(str0);
//     auto *loadInst2 = builder.CreateLoad(str1);
//
//     // Create `call @__builtin_print(%0)`
//     std::vector<Value*> callArgs = { loadInst1 };
//     builder.CreateCall(printFunc, callArgs);
//
//     std::vector<Value*> callArgs2 = {loadInst2};
//     builder.CreateCall(printFunc, callArgs2);
//
//     // Create `ret i32 0`
//     auto *const0 = builder.CreateConstant<ConstantInt>(0);
//     builder.CreateRet(const0);
//
//     std::cout << module->print() << std::endl;
// }

int main() {
    try {
        std::string Source = R"(
public int main() {
    __builtin_print("hello world!");
    __builtin_print("hello world!2");
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
                std::cout << "====================================================" << std::endl;
                //
                // std::cout << "VM Execution:" << std::endl;
                // Ryntra::Compiler::VM::Assembler assembler;
                // auto vmProgram = assembler.assemble(module.get());
                //
                // Ryntra::Compiler::VM::Interpreter interpreter;
                // interpreter.execute(vmProgram);

                // manuallyCreateIR();
            }
        }

        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}