#include "ASTBuilder.h"
#include <any>

namespace Ryntra::Compiler {
    std::any ASTBuilder::visitProgram(antlr::RyntraParser::ProgramContext *context) {
        std::vector<std::shared_ptr<FunctionDefinitionNode>> functions;
        for (auto *functionContext: context->functionDefinition()) {
            auto function = std::any_cast<std::shared_ptr<FunctionDefinitionNode>>(visit(functionContext));
            functions.push_back(std::move(function));
        }
        return std::make_shared<ProgramNode>(std::move(functions));
    }

    std::any ASTBuilder::visitFunctionDefinition(antlr::RyntraParser::FunctionDefinitionContext *context) {
        // TODO: If function not returns int, change this
        std::string returnType = context->INT()->getText();
        std::string functionName = context->IDENTIFIER()->getText();
        std::vector<std::shared_ptr<ParameterNode>> parameters;
        if (context->parameterList()) {
            auto params = std::any_cast<std::vector<std::shared_ptr<ParameterNode>>>(
                visit(context->parameterList())
            );
            parameters = std::move(params);
        }

        auto body = std::any_cast<std::shared_ptr<BlockNode>>(visit(context->block()));
        return std::make_shared<FunctionDefinitionNode>(returnType, functionName, std::move(parameters), std::move(body));
    }

    std::any ASTBuilder::visitParameterList(antlr::RyntraParser::ParameterListContext *context) {
        std::vector<std::shared_ptr<ParameterNode>> parameters;

        // TODO: If function parameters not only int, change this
        auto intTokens = context->INT();
        auto idTokens = context->IDENTIFIER();

        for (size_t i = 0; i < intTokens.size(); ++i) {
            std::string type = intTokens[i]->getText();
            std::string name = idTokens[i]->getText();
            parameters.push_back(
                std::make_shared<ParameterNode>(type, name)
            );
        }

        return parameters;
    }

    std::any ASTBuilder::visitBlock(antlr::RyntraParser::BlockContext *context) {
        std::vector<std::shared_ptr<StatementNode>> statements;

        for (auto* stmtCtx : context->statement()) {
            auto stmt = visit(stmtCtx);
            if (!stmt.has_value()) continue;

            try {
                auto varDecl = std::any_cast<std::shared_ptr<VariableDeclarationNode>>(stmt);
                statements.push_back(std::move(varDecl));
                continue;
            } catch (const std::bad_any_cast&) {}

            try {
                auto returnStmt = std::any_cast<std::shared_ptr<ReturnStatementNode>>(stmt);
                statements.push_back(std::move(returnStmt));
                continue;
            } catch (const std::bad_any_cast&) {}

            try {
                auto funcCallStmt = std::any_cast<std::shared_ptr<FunctionCallStatementNode>>(stmt);
                statements.push_back(std::move(funcCallStmt));
                continue;
            } catch (const std::bad_any_cast&) {}

            try {
                auto exprStmt = std::any_cast<std::shared_ptr<ExpressionStatementNode>>(stmt);
                statements.push_back(std::move(exprStmt));
                continue;
            } catch (const std::bad_any_cast&) {}
        }

        return std::make_shared<BlockNode>(std::move(statements));
    }

    std::any ASTBuilder::visitStatement(antlr::RyntraParser::StatementContext *context) {
        if (context->functionCall()) {
            auto funcCall = std::any_cast<std::shared_ptr<FunctionCallNode>>(
                visit(context->functionCall())
            );
            return std::make_shared<FunctionCallStatementNode>(std::move(funcCall));
        }
        else if (context->expression()) {
            auto expr = std::any_cast<std::shared_ptr<IASTNode>>(
                visit(context->expression())
            );
            return std::make_shared<ExpressionStatementNode>(std::move(expr));
        }
        else if (context->variableDeclaration()) {
            return visit(context->variableDeclaration());
        }
        else if (context->returnStatement()) {
            return visit(context->returnStatement());
        }
        else {
            return std::make_shared<EmptyStatementNode>();
        }
    }

    std::any ASTBuilder::visitVariableDeclaration(antlr::RyntraParser::VariableDeclarationContext *context) {
        std::string varName = context->IDENTIFIER()->getText();
        std::shared_ptr<IASTNode> initialValue = nullptr;

        if (context->expression()) {
            auto result = visit(context->expression());
            if (result.has_value()) {
                initialValue = std::any_cast<std::shared_ptr<IASTNode>>(result);
            }
        }

        return std::make_shared<VariableDeclarationNode>(varName, std::move(initialValue));
    }

    std::any ASTBuilder::visitReturnStatement(antlr::RyntraParser::ReturnStatementContext *context) {
        auto result = visit(context->expression());
        std::shared_ptr<IASTNode> returnValue = nullptr;
        if (result.has_value()) {
            returnValue = std::any_cast<std::shared_ptr<IASTNode>>(result);
        }
        return std::make_shared<ReturnStatementNode>(std::move(returnValue));
    }

    std::any ASTBuilder::visitFunctionCall(antlr::RyntraParser::FunctionCallContext *context) {
        std::string funcName = context->IDENTIFIER()->getText();
        std::vector<std::shared_ptr<IASTNode>> arguments;

        if (context->argumentList()) {
            auto args = std::any_cast<std::vector<std::shared_ptr<IASTNode>>>(
                visit(context->argumentList())
            );
            arguments = std::move(args);
        }

        return std::make_shared<FunctionCallNode>(funcName, std::move(arguments));
    }

    std::any ASTBuilder::visitArgumentList(antlr::RyntraParser::ArgumentListContext *context) {
        std::vector<std::shared_ptr<IASTNode>> arguments;

        for (auto* exprCtx : context->expression()) {
            auto result = visit(exprCtx);
            if (result.has_value()) {
                auto arg = std::any_cast<std::shared_ptr<IASTNode>>(result);
                arguments.push_back(std::move(arg));
            }
        }

        return arguments;
    }

    std::any ASTBuilder::visitExpression(antlr::RyntraParser::ExpressionContext *context) {
        if (context->literal()) {
            return visit(context->literal());
        }
        else if (context->functionCall()) {
            // FunctionCallNode inherits from IASTNode, but we must cast to shared_ptr<IASTNode>
            // for any_cast to work in the caller.
            auto funcCall = std::any_cast<std::shared_ptr<FunctionCallNode>>(visit(context->functionCall()));
            return std::static_pointer_cast<IASTNode>(funcCall);
        }
        else if (context->IDENTIFIER()) {
            std::string varName = context->IDENTIFIER()->getText();
            return std::static_pointer_cast<IASTNode>(std::make_shared<IdentifierNode>(varName));
        }

        // Return empty any instead of nullptr to avoid type mismatch
        return std::any();
    }

    std::any ASTBuilder::visitLiteral(antlr::RyntraParser::LiteralContext *context) {
        if (context->STRING_LITERAL()) {
            std::string str = context->STRING_LITERAL()->getText();
            if (str.length() >= 2 && str.front() == '"' && str.back() == '"') {
                str = str.substr(1, str.length() - 2);
            }
            return std::static_pointer_cast<IASTNode>(std::make_shared<StringLiteralNode>(str));
        }
        else if (context->INTEGER_LITERAL()) {
            int value = std::stoi(context->INTEGER_LITERAL()->getText());
            return std::static_pointer_cast<IASTNode>(std::make_shared<IntegerLiteralNode>(value));
        }

        return std::any();
    }
}