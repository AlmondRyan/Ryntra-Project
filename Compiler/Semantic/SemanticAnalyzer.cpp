#include "SemanticAnalyzer.h"

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
        return {};
    }

    std::any SemanticAnalyzer::visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitIdentifier(std::shared_ptr<IdentifierNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitParameter(std::shared_ptr<ParameterNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitStringLiteral(std::shared_ptr<StringLiteralNode> node) {
        return {};
    }

    std::any SemanticAnalyzer::visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) {
        return {};
    }
}
