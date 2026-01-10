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
        for (const auto &i : node->getFunctions()) {
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
        std::string funcName = node->getFunctionName();
        auto funcSymbol = symbolTable.lookupFunction(funcName);
        if (funcSymbol == std::nullopt) {
            ErrorHandler::getInstance().makeError("Undefined function: " + funcName, SourceLocation(0, 0));
            return {};
        }

        const auto &args = node->getArguments();
        const auto &params = funcSymbol->parameters;

        if (args.size() != params.size()) {
            ErrorHandler::getInstance().makeError(
                "Function " + funcName + " requires " + std::to_string(params.size()) +
                " arguments, but got " + std::to_string(args.size()),
                SourceLocation(0, 0)
            );
            return {};
        }

        for (auto i = 0; i < args.size(); i++) {
            auto result = visit(args[i]);
            if (result.has_value()) {
                std::string argType = std::any_cast<std::string>(result);
                std::string neededType = this->mapTypeToString(params[i].type.kind);

                if (argType != neededType) {
                    ErrorHandler::getInstance().makeError(
                        "Function " + funcName + " requires " + neededType + " but got " + argType,
                        SourceLocation(0, 0)
                    );
                }
            }
        }

        // return {};
        return this->mapTypeToString(funcSymbol->returnType.kind);
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
} // namespace Ryntra::Compiler
