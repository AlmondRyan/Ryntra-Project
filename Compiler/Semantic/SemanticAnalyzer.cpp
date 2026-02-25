#include "SemanticAnalyzer.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {

    void SemanticAnalyzer::analyze(const std::shared_ptr<IASTNode>& root) {
        if (!root) return;
        root->accept(*this);
        // The result for ProgramNode will be stored in typedProgram
    }

    void SemanticAnalyzer::visit(ProgramNode &node) {
        // First pass: Register all functions
        for (const auto &func : node.getFunctions()) {
            std::vector<std::string> paramTypes; 
            // Assuming no parameters for user defined functions as per current AST structure
            // In a real scenario, we would parse parameters here.
            
            auto funcName = func->getName()->getName();
            auto returnTypeName = func->getReturnType()->getName();
            
            // Basic conflict check
            if (symbolTable.resolve(funcName)) {
                 ErrorHandler::getInstance().makeError("Semantic Error: Function '" + funcName + "' is already defined.", func->getLocation());
                 continue;
            }

            symbolTable.define(std::make_shared<FunctionSymbol>(funcName, returnTypeName, paramTypes), func->getLocation());
        }

        // Register built-in functions if not present (simple hack for now if they are not in AST)
        // For example: print(string)
        if (!symbolTable.resolve("print")) {
             symbolTable.define(std::make_shared<FunctionSymbol>("print", "void", std::vector<std::string>{"string"}), SourceLocation{0,0});
        }
        if (!symbolTable.resolve("__builtin_print")) {
             symbolTable.define(std::make_shared<FunctionSymbol>("__builtin_print", "void", std::vector<std::string>{"string"}), SourceLocation{0,0});
        }

        // Check for main function
        auto mainSym = symbolTable.resolve("main");
        if (!mainSym) {
            ErrorHandler::getInstance().makeError("Semantic Error: 'main' function is not defined.", node.getLocation());
        } else {
            auto mainFuncSym = std::dynamic_pointer_cast<FunctionSymbol>(mainSym);
            if (!mainFuncSym) {
                 ErrorHandler::getInstance().makeError("Semantic Error: 'main' is not a function.", node.getLocation());
            } else if (mainFuncSym->getReturnType() != "int") {
                ErrorHandler::getInstance().makeError("Semantic Error: 'main' function must return 'int'.", node.getLocation());
            }
        }

        // Second pass: Analyze bodies and build Typed AST
        std::vector<std::shared_ptr<TypedFunctionDefinitionNode>> typedFunctions;
        for (const auto &func : node.getFunctions()) {
            func->accept(*this);
            if (auto typedFunc = std::dynamic_pointer_cast<TypedFunctionDefinitionNode>(lastNode)) {
                typedFunctions.push_back(typedFunc);
            }
        }
        
        typedProgram = std::make_shared<TypedProgramNode>(std::move(typedFunctions));
        typedProgram->setLocation(node.getLocation());
        lastNode = typedProgram;
    }

    void SemanticAnalyzer::visit(FunctionDefinitionNode &node) {
        // Resolve return type
        node.getReturnType()->accept(*this);
        auto returnType = lastType;
        if (!returnType) {
            returnType = TypeFactory::getPrimitive("void"); // Default/Error fallback
        }
        currentFunctionReturnType = returnType;

        auto funcName = node.getName()->getName();

        // Enter function scope
        symbolTable.enterScope();
        
        // Visit body
        node.getBody()->accept(*this);
        auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);
        
        symbolTable.exitScope();
        
        if (typedBody) {
            auto typedFunc = std::make_shared<TypedFunctionDefinitionNode>(funcName, returnType, typedBody);
            typedFunc->setLocation(node.getLocation());
            lastNode = typedFunc;

            // Check for main function return
            if (funcName == "main") {
                bool hasReturn = false;
                for (const auto& stmt : typedBody->getStatements()) {
                    if (std::dynamic_pointer_cast<TypedReturnNode>(stmt)) {
                        hasReturn = true;
                        break;
                    }
                }
                if (!hasReturn) {
                    ErrorHandler::getInstance().makeError("Semantic Error: 'main' function must explicitly return a value.", node.getLocation());
                }
            }
        } else {
            lastNode = nullptr; // Error case
        }
        currentFunctionReturnType = nullptr;
    }

    void SemanticAnalyzer::visit(ReturnNode &node) {
        node.getValue()->accept(*this);
        auto typedExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        
        if (typedExpr) {
            if (currentFunctionReturnType) {
                std::string expectedType = currentFunctionReturnType->toString();
                std::string actualType = typedExpr->getType()->toString();
                
                if (expectedType != actualType && actualType != "unknown") {
                     ErrorHandler::getInstance().makeError("Semantic Error: Return type mismatch. Expected '" + expectedType + "', but got '" + actualType + "'.", node.getLocation());
                }
            }
            
            auto typedReturn = std::make_shared<TypedReturnNode>(typedExpr);
            typedReturn->setLocation(node.getLocation());
            lastNode = typedReturn;
        } else {
            lastNode = nullptr;
        }
    }

    void SemanticAnalyzer::visit(BlockNode &node) {
        std::vector<std::shared_ptr<TypedStatementNode>> typedStatements;
        for (const auto &stmt : node.getStatements()) {
            stmt->accept(*this);
            if (auto typedStmt = std::dynamic_pointer_cast<TypedStatementNode>(lastNode)) {
                typedStatements.push_back(typedStmt);
            }
        }
        auto typedBlock = std::make_shared<TypedBlockNode>(std::move(typedStatements));
        typedBlock->setLocation(node.getLocation());
        lastNode = typedBlock;
    }

    void SemanticAnalyzer::visit(ExpressionStatementNode &node) {
        node.getExpression()->accept(*this);
        if (auto typedExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode)) {
            auto typedStmt = std::make_shared<TypedExpressionStatementNode>(typedExpr);
            typedStmt->setLocation(node.getLocation());
            lastNode = typedStmt;
        } else {
            lastNode = nullptr;
        }
    }

    void SemanticAnalyzer::visit(StringLiteralNode &node) {
        auto type = TypeFactory::getPrimitive("string");
        auto typedNode = std::make_shared<TypedStringLiteralNode>(node.getValue(), type);
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(IntegerLiteralNode &node) {
        auto type = TypeFactory::getPrimitive("int");
        auto typedNode = std::make_shared<TypedIntegerLiteralNode>(node.getValue(), type);
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(IdentifierNode &node) {
        auto name = node.getName();
        auto sym = symbolTable.resolve(name);
        
        std::shared_ptr<Type> type;
        if (!sym) {
            ErrorHandler::getInstance().makeError("Semantic Error: Identifier '" + name + "' is not defined.", node.getLocation());
            type = TypeFactory::getPrimitive("unknown");
        } else {
            if (auto funcSym = std::dynamic_pointer_cast<FunctionSymbol>(sym)) {
                 auto retType = TypeFactory::getPrimitive(funcSym->getReturnType());
                 std::vector<std::shared_ptr<Type>> paramTypes;
                 for(const auto& p : funcSym->getParamTypes()) {
                     paramTypes.push_back(TypeFactory::getPrimitive(p));
                 }
                 type = TypeFactory::getFunction(retType, paramTypes);
            } else {
                type = TypeFactory::getPrimitive("int"); 
            }
        }
        
        auto typedNode = std::make_shared<TypedIdentifierNode>(name, type);
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(FunctionCallNode &node) {
        auto funcNameNode = node.getFunctionName();
        std::string funcName = funcNameNode->getName();

        // Resolve function
        auto sym = symbolTable.resolve(funcName);
        std::shared_ptr<Type> returnType = TypeFactory::getPrimitive("void"); // Default
        std::vector<std::string> expectedParamTypes;

        if (!sym) {
            ErrorHandler::getInstance().makeError("Semantic Error: Function '" + funcName + "' is not defined.", node.getLocation());
            returnType = TypeFactory::getPrimitive("unknown");
        } else {
            auto funcSym = std::dynamic_pointer_cast<FunctionSymbol>(sym);
            if (!funcSym) {
                 ErrorHandler::getInstance().makeError("Semantic Error: '" + funcName + "' is not a function.", node.getLocation());
                 returnType = TypeFactory::getPrimitive("unknown");
            } else {
                returnType = TypeFactory::getPrimitive(funcSym->getReturnType());
                expectedParamTypes = funcSym->getParamTypes();
            }
        }

        // Process arguments
        std::vector<std::shared_ptr<TypedExpressionNode>> typedArgs;
        const auto& args = node.getArguments();
        
        if (sym && args.size() != expectedParamTypes.size()) {
             ErrorHandler::getInstance().makeError("Semantic Error: Function '" + funcName + "' expects " + std::to_string(expectedParamTypes.size()) + " arguments, but got " + std::to_string(args.size()) + ".", node.getLocation());
        }

        for (size_t i = 0; i < args.size(); ++i) {
            args[i]->accept(*this);
            auto typedArg = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
            if (typedArg) {
                typedArgs.push_back(typedArg);
                
                // Type check
                if (i < expectedParamTypes.size()) {
                    std::string expectedTypeStr = expectedParamTypes[i];
                    std::string actualTypeStr = typedArg->getType()->toString();
                    
                    if (expectedTypeStr != actualTypeStr && expectedTypeStr != "any" && actualTypeStr != "unknown") {
                         ErrorHandler::getInstance().makeError("Semantic Error: Argument " + std::to_string(i+1) + " expects type '" + expectedTypeStr + "', but got '" + actualTypeStr + "'.", args[i]->getLocation());
                    }
                }
            }
        }

        std::vector<std::shared_ptr<Type>> paramTypeObjs;
        for(const auto& pt : expectedParamTypes) paramTypeObjs.push_back(TypeFactory::getPrimitive(pt));
        auto funcType = TypeFactory::getFunction(returnType, paramTypeObjs);
        
        auto typedFuncName = std::make_shared<TypedIdentifierNode>(funcName, funcType);
        typedFuncName->setLocation(funcNameNode->getLocation());

        auto typedCall = std::make_shared<TypedFunctionCallNode>(typedFuncName, typedArgs, returnType);
        typedCall->setLocation(node.getLocation());
        lastNode = typedCall;
    }

    void SemanticAnalyzer::visit(TypeSpecifierNode &node) {
        lastType = TypeFactory::getPrimitive(node.getName());
    }
}
