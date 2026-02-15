#include "SemanticAnalyzer.h"
#include <iostream>
#include <stdexcept>
#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {

    void SemanticAnalyzer::analyze(const std::shared_ptr<IASTNode>& root) {
        root->accept(*this);
    }

    void SemanticAnalyzer::visit(ProgramNode &node) {
        // First pass: Register all functions
        for (const auto &func : node.getFunctions()) {
            std::vector<std::string> paramTypes; 
            // Assuming no parameters for user defined functions as per current AST structure
            
            auto funcName = func->getName()->getName();
            auto returnType = func->getReturnType()->getName();
            
            symbolTable.define(std::make_shared<FunctionSymbol>(funcName, returnType, paramTypes), func->getLocation());
        }

        // Check for main function
        auto mainSym = symbolTable.resolve("main");
        if (!mainSym) {
            ErrorHandler::getInstance().makeError("Semantic Error: 'main' function is not defined.", node.getLocation());
            return;
        }
        
        auto mainFuncSym = std::dynamic_pointer_cast<FunctionSymbol>(mainSym);
        if (!mainFuncSym) {
             ErrorHandler::getInstance().makeError("Semantic Error: 'main' is not a function.", node.getLocation());
             return;
        }
        
        if (mainFuncSym->getReturnType() != "int") {
            ErrorHandler::getInstance().makeError("Semantic Error: 'main' function must return 'int'.", node.getLocation());
        }

        // Second pass: Analyze bodies
        for (const auto &func : node.getFunctions()) {
            func->accept(*this);
        }
    }

    void SemanticAnalyzer::visit(FunctionDefinitionNode &node) {
        // Enter function scope if we were handling local variables
        symbolTable.enterScope();
        node.getBody()->accept(*this);
        symbolTable.exitScope();
    }

    void SemanticAnalyzer::visit(FunctionCallNode &node) {
        auto funcName = node.getFunctionName()->getName();
        
        // Check if it is a built-in function
        if (funcName.rfind("__builtin_", 0) == 0) {
             // It starts with __builtin_
             auto sym = symbolTable.resolve(funcName);
             if (!sym) {
                 ErrorHandler::getInstance().makeError("Semantic Error: Built-in function '" + funcName + "' is not defined.", node.getLocation());
                 return;
             }
             
             auto funcSym = std::dynamic_pointer_cast<FunctionSymbol>(sym);
             if (!funcSym) {
                 ErrorHandler::getInstance().makeError("Semantic Error: '" + funcName + "' is not a function.", node.getLocation());
                 return;
             }
             
             const auto& expectedParams = funcSym->getParamTypes();
             const auto& args = node.getArguments();
             
             if (args.size() != expectedParams.size()) {
                 ErrorHandler::getInstance().makeError("Semantic Error: Function '" + funcName + "' expects " + std::to_string(expectedParams.size()) + " arguments, but got " + std::to_string(args.size()) + ".", node.getLocation());
                 // Continue checking args? Maybe, but arg count mismatch makes index access risky if we iterate expectedParams
                 // But the loop below uses args.size() and checks expectedParams[i]. If args > expected, index out of bounds.
                 return;
             }
             
             // Check argument types
             for (size_t i = 0; i < args.size(); ++i) {
                 if (expectedParams[i] == "string") {
                     // Check if arg[i] is a StringLiteralNode
                     if (!std::dynamic_pointer_cast<StringLiteralNode>(args[i])) {
                         ErrorHandler::getInstance().makeError("Semantic Error: Argument " + std::to_string(i+1) + " of function '" + funcName + "' must be a string literal.", args[i]->getLocation());
                     }
                 }
             }
        } else {
            // User function call check
             auto sym = symbolTable.resolve(funcName);
             if (!sym) {
                 ErrorHandler::getInstance().makeError("Semantic Error: Function '" + funcName + "' is not defined.", node.getLocation());
             }
        }
    }

    void SemanticAnalyzer::visit(BlockNode &node) {
        for (const auto &stmt : node.getStatements()) {
            stmt->accept(*this);
        }
    }

    void SemanticAnalyzer::visit(ExpressionStatementNode &node) {
        node.getExpression()->accept(*this);
    }

    void SemanticAnalyzer::visit(StringLiteralNode &node) {}
    void SemanticAnalyzer::visit(IdentifierNode &node) {}
    void SemanticAnalyzer::visit(TypeSpecifierNode &node) {}

}
