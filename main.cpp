#include <fstream>
#include <iostream>
#include <memory>

#include "Compiler/AST/ASTBuilder.h"
#include "Compiler/AST/ASTNodes.h"
#include "ErrorHandler/ErrorHandler.h"
#include "IRGenerator/IRGenerator.h"
#include "Semantic/SemanticAnalyzer.h"
#include "VM/Instructions/Instruction.h"
#include "VM/VM.h"
#include "antlr4-runtime.h"

#include <antlr/RyntraLexer.h>
#include <antlr/RyntraParser.h>

int main() {
    // // Read Source File
    // std::ifstream inFileStream("Test.rynt");
    // std::string src;
    // if (inFileStream) {
    //     std::ostringstream ss;
    //     ss << inFileStream.rdbuf();
    //     src = ss.str();
    // }
    //
    // try {
    //     // 1. Initialize ANTLR
    //     antlr4::ANTLRInputStream input(src);
    //     Ryntra::antlr::RyntraLexer lexer(&input);
    //     antlr4::CommonTokenStream tokens(&lexer);
    //
    //     tokens.fill();
    //     Ryntra::antlr::RyntraParser parser(&tokens);
    //
    //     auto* programContext = parser.program();
    //     if (parser.getNumberOfSyntaxErrors() > 0) {
    //         std::cout << "Syntax errors found in input" << std::endl;
    //         return 1;
    //     }
    //
    //     // 2. Build AST
    //     Ryntra::Compiler::ASTBuilder astBuilder;
    //     auto programNode = astBuilder.visitProgram(programContext);
    //
    //     std::cout << ">>> Generated AST:" << std::endl;
    //     std::cout << programNode->toString() << std::endl;
    //
    //     // 3. Semantic Analysis
    //     Ryntra::Compiler::SemanticAnalyzer semanticAnalyzer;
    //     semanticAnalyzer.visitProgram(programNode);
    //
    //     // 4. Get Semantic Errors
    //     Ryntra::Compiler::ErrorHandler::getInstance().print();
    //
    //     // If there's no errors but only warnings, continue IR Generating without terminate
    //     if (!Ryntra::Compiler::ErrorHandler::getInstance().getErrorObjects().empty()) {
    //         for (auto i : Ryntra::Compiler::ErrorHandler::getInstance().getErrorObjects()) {
    //             if (i.type == Ryntra::Compiler::ET_WARNING) {
    //                 continue;
    //             } else {
    //                 std::cout << "Semantic Analysis Failed." << std::endl;
    //                 return 0;
    //             }
    //         }
    //     }
    //
    //     // 5. IR Generating
    //     Ryntra::Compiler::IRGenerator irGenerator;
    //     irGenerator.visitProgram(programNode);
    //     auto ir = irGenerator.getIR();
    //     std::cout << ir << std::endl;
    //
    //     // 6. Write IR into .ll file
    //     std::ofstream out("output.ll");
    //     if (out.is_open()) {
    //         out << ir;
    //         out.close();
    //         std::cout << "IR Written Successfully." << std::endl;
    //     } else {
    //         std::cout << "Cannot open file." << std::endl;
    //     }
    // } catch (const std::exception& e) {
    //     std::cout << "Error occurred: " << e.what() << std::endl;
    //     return 1;
    // }
    //

    using namespace Ryntra::VM;

    std::vector<Value> constPool;
    Value promptValue;
    promptValue.data = std::string("请输入一行文本: ");
    constPool.push_back(promptValue);

    Value firstNumber;
    firstNumber.data = 5;
    constPool.push_back(firstNumber);

    Value secondNumber;
    secondNumber.data = 3;
    constPool.push_back(secondNumber);

    std::vector<Instruction> program;
    program.emplace_back(OpCodes::LD_CONST, 0);
    program.emplace_back(OpCodes::B_CALL, 0);
    program.emplace_back(OpCodes::B_CALL, 1);
    program.emplace_back(OpCodes::STORE_VAR, 0);
    program.emplace_back(OpCodes::LD_CONST, 1);
    program.emplace_back(OpCodes::LD_CONST, 2);
    program.emplace_back(OpCodes::ADD, 0);
    program.emplace_back(OpCodes::B_CALL, 0);
    program.emplace_back(OpCodes::HALT, 0);

    RVM vm(program, constPool);
    vm.operate();

    const auto& variables = vm.getVariables();
    if (!variables.empty()) {
        std::cout << "\n输入的是: ";
        std::visit([](auto&& v) {
            std::cout << v;
        }, variables[0].data);
        std::cout << std::endl;
    }

    return 0;
}
