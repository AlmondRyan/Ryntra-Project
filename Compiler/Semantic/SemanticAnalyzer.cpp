#include "SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"
#include <iostream>

namespace Ryntra::Compiler {
    std::any SemanticAnalyzer::visitProgram(std::shared_ptr<ProgramNode> node) {
        if (node->getFunctions().empty()) {
            ErrorHandler::getInstance().makeError("You need at least one function.", SourceLocation(0, 0));
            return std::any();
        }

        bool hasMainFunction = false;
        for (auto i: node->getFunctions()) {
            visit(i);
            if (i->getFunctionName() == "main" && i->getReturnType() == "int") {
                hasMainFunction = true;
            }
        }

        if (!hasMainFunction) {
            ErrorHandler::getInstance().makeError("There's no main function (entry function) available.",
                                                  SourceLocation(0, 0));
        }

        return {};
    }

    std::any SemanticAnalyzer::visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) {
        for (auto &param : node->getParameters()) {
            visit(param);
        }

        visit(node->getBody());
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
        std::cout << "hello from visitFunctionCall!" << std::endl;
        if (node->getFunctionName() == "__builtin_print") {
            const auto& args = node->getArguments();
            
            // Check parameter counts
            if (args.size() != 1) {
                ErrorHandler::getInstance().makeError(
                    "Builtin Function: __builtin_print() requires exactly 1 argument, but got " + std::to_string(args.size()),
                    SourceLocation(0, 0)
                );
                return {};
            }

            // Check parameter type
            auto arg = args[0];
            std::any result = visit(arg);
            
            if (result.has_value()) {
                try {
                    std::string argType = std::any_cast<std::string>(result);
                    if (argType != "string") {
                        ErrorHandler::getInstance().makeError(
                            "__builtin_print() argument must be string, but got " + argType,
                            SourceLocation(0, 0)
                        );
                    }
                } catch (const std::bad_any_cast&) {
                    ErrorHandler::getInstance().makeError(
                        "__builtin_print() argument must be a string literal.",
                        SourceLocation(0, 0)
                    );
                }
            }
        }
        return {};
    }

    std::any SemanticAnalyzer::visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) {
        visit(node->getFunctionCall());
        return {};
    }

    std::any SemanticAnalyzer::visitIdentifier(std::shared_ptr<IdentifierNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) {
        return std::string("int");
    }

    std::any SemanticAnalyzer::visitParameter(std::shared_ptr<ParameterNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitStringLiteral(std::shared_ptr<StringLiteralNode> node) {
        return std::string("string");
    }

    std::any SemanticAnalyzer::visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) {
        return {};
    }
}
