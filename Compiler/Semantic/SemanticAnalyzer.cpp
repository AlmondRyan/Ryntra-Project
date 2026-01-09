#include "SemanticAnalyzer.h"

#include <iostream>

#include "Symbol.h"
#include "ErrorHandler/ErrorHandler.h"

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
        return {};
    }

    std::any SemanticAnalyzer::visitBlock(std::shared_ptr<BlockNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitFunctionCall(std::shared_ptr<FunctionCallNode> node) {
        if (node->getFunctionName() == "__builtin_print") {
            const auto& args = node->getArguments();
            
            // 1. 检查参数数量
            if (args.size() != 1) {
                ErrorHandler::getInstance().makeError(
                    "Builtin Function: __builtin_print() requires exactly 1 argument, but got " + std::to_string(args.size()),
                    SourceLocation(0, 0)
                );
                return {};
            }

            // 2. 检查参数类型
            auto arg = args[0];
            std::any result = visit(arg);
            
            if (result.has_value()) {
                try {
                    Type argType = std::any_cast<Type>(result);
                    if (argType.kind != TypeKind::String) {
                        ErrorHandler::getInstance().makeError(
                            "__builtin_print() argument must be string, but got " + 
                            (argType.kind == TypeKind::Int ? "int" : "custom"),
                            SourceLocation(0, 0)
                        );
                    }
                } catch (const std::bad_any_cast&) {
                    ErrorHandler::getInstance().makeError(
                        "Internal Error: Failed to determine argument type for __builtin_print",
                        SourceLocation(0, 0)
                    );
                }
            }
        }
        return {};
    }

    std::any SemanticAnalyzer::visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitIdentifier(std::shared_ptr<IdentifierNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) {
        return Type{TypeKind::Int, ""};
    }

    std::any SemanticAnalyzer::visitParameter(std::shared_ptr<ParameterNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitStringLiteral(std::shared_ptr<StringLiteralNode> node) {
        return Type{TypeKind::String, ""};
    }

    std::any SemanticAnalyzer::visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) {
        Type type{TypeKind::Int, ""}; // 默认类型
        
        // 如果有初始化表达式，推导类型
        if (node->getInitializer()) {
            std::any initResult = visit(node->getInitializer());
            if (initResult.has_value()) {
                try {
                    type = std::any_cast<Type>(initResult);
                } catch (const std::bad_any_cast&) {
                    // 如果无法识别类型，保留默认值或报错
                }
            }
        }
        
        Symbol symbol(type, node->getVariableName(), SymbolKind::Variable);
        
        if (!symbolTable.addSymbolToCurrentScope(symbol)) {
            ErrorHandler::getInstance().makeError(
                "Redefinition of variable: " + node->getVariableName(),
                SourceLocation(0, 0)
            );
        }
        
        return type;
    }
}
