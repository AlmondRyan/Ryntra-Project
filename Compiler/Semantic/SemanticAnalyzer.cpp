#include "SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"
#include <iostream>

namespace Ryntra::Compiler {
    std::any SemanticAnalyzer::visitProgram(std::shared_ptr<ProgramNode> node) {
        // Register all functions to symbol table
        for (const auto &i : node->getFunctions()) {
            FunctionSymbol functionSymbol;
            functionSymbol.name = i->getFunctionName();
            functionSymbol.returnType.kind = mapStringToType(i->getReturnType());
            for (const auto &paramNode : i->getParameters()) {
                TypeKind pk = mapStringToType(paramNode->getType());
                Symbol s({pk, ""}, paramNode->getName(), SymbolKind::Parameter);
                functionSymbol.parameters.push_back(s);
            }

            symbolTable.addFunction(functionSymbol);
        }

        // Iterate functions
        for (const auto &i : node->getFunctions()) {
            visit(i);
        }

        // Check is there any function called "main"
        auto mainFunc = symbolTable.lookupFunction("main");
        if (mainFunc == std::nullopt) {
            ErrorHandler::getInstance().makeError(
                "There's no main function.",
                SourceLocation(node->getLocation().line, node->getLocation().column)
            );
        } else {
            if (mainFunc->returnType.kind != TypeKind::Int) {
                ErrorHandler::getInstance().makeError(
                    "Function main() should return int.",
                    SourceLocation(node->getLocation().line, node->getLocation().column)
                );
            }
        }
        return {};
    }

    std::any SemanticAnalyzer::visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) {
        currentExpectedReturningType = mapStringToType(node->getReturnType());

        symbolTable.enterScope();
        for (auto &param : node->getParameters()) {
            Symbol s = {{mapStringToType(param->getType()), ""}, param->getName(), SymbolKind::Parameter};
            symbolTable.addSymbolToCurrentScope(s);
            visit(param);
        }

        visit(node->getBody());
        symbolTable.exitScope();
        currentExpectedReturningType = TypeKind::Void;
        return {};
    }

    std::any SemanticAnalyzer::visitBlock(std::shared_ptr<BlockNode> node) {
        for (auto &stmt : node->getStatements()) {
            visit(stmt);
        }
        return {};
    }

    std::any SemanticAnalyzer::visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitFunctionCall(std::shared_ptr<FunctionCallNode> node) {
        std::string funcName = node->getFunctionName();
        auto funcSymbol = symbolTable.lookupFunction(funcName);
        if (funcSymbol == std::nullopt) {
            ErrorHandler::getInstance().makeError("Undefined function: " + funcName,
                SourceLocation(node->getLocation().line, node->getLocation().column));
            return {};
        }

        const auto &args = node->getArguments();
        const auto &params = funcSymbol->parameters;

        if (args.size() != params.size()) {
            ErrorHandler::getInstance().makeError(
                "Function " + funcName + " requires " + std::to_string(params.size()) +
                " arguments, but got " + std::to_string(args.size()),
                SourceLocation(node->getLocation().line, node->getLocation().column)
            );
            return {};
        }

        for (auto i = 0; i < args.size(); i++) {
            auto result = visit(args[i]);
            if (result.has_value()) {
                // std::string argType = std::any_cast<std::string>(result);
                // std::string neededType = this->mapTypeToString(params[i].type.kind);
                TypeKind argType = std::any_cast<TypeKind>(result);

                if (argType != params[i].type.kind) {
                    ErrorHandler::getInstance().makeError(
                        "Function " + funcName + " requires " + mapTypeToString(params[i].type.kind) + " but got " +
                        mapTypeToString(argType),
                        SourceLocation(node->getLocation().line, node->getLocation().column)
                    );
                }
            }
        }

        // return {};
        // return this->mapTypeToString(funcSymbol->returnType.kind);
        return funcSymbol->returnType.kind;
    }

    std::any SemanticAnalyzer::visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) {
        visit(node->getFunctionCall());
        return {};
    }

    std::any SemanticAnalyzer::visitIdentifier(std::shared_ptr<IdentifierNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) {
        // return std::string("int");
        return TypeKind::Int;
    }

    std::any SemanticAnalyzer::visitParameter(std::shared_ptr<ParameterNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) {
        auto result = visit(node->getReturnValue());
        if (result.has_value()) {
            // std::string actualType = std::any_cast<std::string>(result);
            // TypeKind tk = mapStringToType(actualType);
            TypeKind tk = std::any_cast<TypeKind>(result);

            if (tk != currentExpectedReturningType) {
                ErrorHandler::getInstance().makeError(
                    "Mismatch returning type: expect " + mapTypeToString(currentExpectedReturningType) + " but got " + mapTypeToString(tk),
                    SourceLocation(node->getLocation())
                );
            }
        } else {
            if (currentExpectedReturningType != TypeKind::Void) {
                ErrorHandler::getInstance().makeError("Function expect " + mapTypeToString(currentExpectedReturningType) + " returning value but got empty.",
                    SourceLocation(node->getLocation()));
            }
        }
        return {};
    }

    std::any SemanticAnalyzer::visitStringLiteral(std::shared_ptr<StringLiteralNode> node) {
        // return std::string("string");
        return TypeKind::String;
    }

    std::any SemanticAnalyzer::visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) {
        return {};
    }
} // namespace Ryntra::Compiler
