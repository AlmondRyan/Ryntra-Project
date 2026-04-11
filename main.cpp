#include "AST/ASTBuilder.h"
#include "ErrorHandler/ErrorHandler.h"
#include "IR/BasicBlock.h"
#include "IR/IRBuilder.h"
#include "Semantic/SemanticAnalyzer.h"
#include <antlr/RyntraLexer.h>
#include <antlr/RyntraParser.h>
#include <antlr4-runtime.h>
#include <fstream>
#include <iostream>
#include <sstream>

void manuallyGenIR() {
    using namespace Ryntra::IR;
    IRBuilder builder;

    auto module = builder.createModule("Hello World");
    auto printFunc = builder.createFunction(
        "__builtin_print",
        Type::getVoidType(),
        {Function::Parameter("string", Type::getStringType())},
        true);

    auto stringConst = builder.createGlobalConstant(
        Type::getStringType(),
        "Hello World\0"
    );

    auto mainFunc = builder.createFunction("main", Type::getInt32Type());
    auto entryBlock = builder.createBasicBlock("entry");
    builder.setInsertPoint(entryBlock);

    auto loadInst = builder.createLoadConstant("0", stringConst);
    auto callInst = builder.createCall("", printFunc, { loadInst });
    auto retInst = builder.createReturnInt32("", 0);
    mainFunc->addBasicBlock(entryBlock);
    std::cout << module->toString() << std::endl;
}

int main() {
    try {
        std::string Source = R"(
public int main() {
     __builtin_print("Hello World");
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

                manuallyGenIR();
            }
        }

        std::cout << std::endl;
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}