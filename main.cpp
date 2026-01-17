#include <fstream>
#include <iostream>
#include <memory>
#include <variant>

#include "Compiler/AST/ASTBuilder.h"
#include "Compiler/AST/ASTNodes.h"
#include "ErrorHandler/ErrorHandler.h"
#include "Semantic/SemanticAnalyzer.h"
#include "VM/Instructions/Instruction.h"
#include "VM/VM.h"
#include "VM/VMCodeGenerator.h"
#include "antlr4-runtime.h"

#include <antlr/RyntraLexer.h>
#include <antlr/RyntraParser.h>

int main() {
    std::ifstream inFileStream("Test.rynt");
    std::string src;
    if (inFileStream) {
        std::ostringstream ss;
        ss << inFileStream.rdbuf();
        src = ss.str();
    }

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

    Ryntra::Compiler::VMCodeGenerator vmCodeGen;
    vmCodeGen.visitProgram(programNode);

    auto program = vmCodeGen.getProgram();
    auto constPool = vmCodeGen.getConstantPool();

    Ryntra::VM::RVM vm(program, constPool);
    vm.operate();

    if (vm.hasReturnValue()) {
        const auto& ret = vm.getReturnValue();
        if (std::holds_alternative<int>(ret.data)) {
            return std::get<int>(ret.data);
        }
    }

    return 0;
}
