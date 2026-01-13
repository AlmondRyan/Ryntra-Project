#include "ASTBuilder.h"

namespace Ryntra::Compiler {
    /**
     * @brief Construct the root node of the program
     */
    std::shared_ptr<ProgramNode> ASTBuilder::visitProgram(antlr::RyntraParser::ProgramContext *context) {
        std::vector<std::shared_ptr<FunctionDefinitionNode>> functions;
        for (auto *functionContext: context->functionDefinition()) {
            auto function = visitFunctionDefinition(functionContext);
            functions.push_back(std::move(function));
        }
        return createNode<ProgramNode>(context, std::move(functions));
    }

    std::shared_ptr<FunctionDefinitionNode> ASTBuilder::visitFunctionDefinition(antlr::RyntraParser::FunctionDefinitionContext *context) {
        // TODO: If function not returns int, change this
        std::string returnType = context->INT()->getText();
        std::string functionName = context->IDENTIFIER()->getText();
        std::vector<std::shared_ptr<ParameterNode>> parameters;
        if (context->parameterList()) {
            parameters = visitParameterList(context->parameterList());
        }

        auto body = visitBlock(context->block());
        return createNode<FunctionDefinitionNode>(context, returnType, functionName, std::move(parameters), std::move(body));
    }

    std::vector<std::shared_ptr<ParameterNode>> ASTBuilder::visitParameterList(antlr::RyntraParser::ParameterListContext *context) {
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

    std::shared_ptr<BlockNode> ASTBuilder::visitBlock(antlr::RyntraParser::BlockContext *context) {
        std::vector<std::shared_ptr<StatementNode>> statements;

        for (auto* stmtCtx : context->statement()) {
            auto stmt = visitStatement(stmtCtx);
            if (!stmt) continue;
            statements.push_back(std::move(stmt));
        }

        return createNode<BlockNode>(context, std::move(statements));
    }

    std::shared_ptr<StatementNode> ASTBuilder::visitStatement(antlr::RyntraParser::StatementContext *context) {
        if (context->functionCall()) {
            auto funcCall = visitFunctionCall(context->functionCall());
            return createNode<FunctionCallStatementNode>(context, std::move(funcCall));
        }
        else if (context->expression()) {
            auto expr = visitExpression(context->expression());
            return createNode<ExpressionStatementNode>(context, std::move(expr));
        }
        else if (context->variableDeclaration()) {
            return visitVariableDeclaration(context->variableDeclaration());
        }
        else if (context->returnStatement()) {
            return visitReturnStatement(context->returnStatement());
        }
        else if (context->assignment()) {
            auto assignExpr = visitAssignment(context->assignment());
            return createNode<ExpressionStatementNode>(context, std::move(assignExpr));
        }
        else {
            return createNode<EmptyStatementNode>(context);
        }
    }

    std::shared_ptr<VariableDeclarationNode> ASTBuilder::visitVariableDeclaration(antlr::RyntraParser::VariableDeclarationContext *context) {
        std::string varType = context->INT()->getText();
        std::string varName = context->IDENTIFIER()->getText();
        std::shared_ptr<IASTNode> initialValue = nullptr;

        if (context->expression()) {
            initialValue = visitExpression(context->expression());
        }

        return createNode<VariableDeclarationNode>(context, varType, varName, std::move(initialValue));
    }

    std::shared_ptr<ReturnStatementNode> ASTBuilder::visitReturnStatement(antlr::RyntraParser::ReturnStatementContext *context) {
        std::shared_ptr<IASTNode> returnValue = nullptr;
        if (context->expression()) {
            returnValue = visitExpression(context->expression());
        }
        return createNode<ReturnStatementNode>(context, std::move(returnValue));
    }

    std::shared_ptr<FunctionCallNode> ASTBuilder::visitFunctionCall(antlr::RyntraParser::FunctionCallContext *context) {
        std::string funcName = context->IDENTIFIER()->getText();
        std::vector<std::shared_ptr<IASTNode>> arguments;

        if (context->argumentList()) {
            arguments = visitArgumentList(context->argumentList());
        }

        return createNode<FunctionCallNode>(context, funcName, std::move(arguments));
    }

    std::vector<std::shared_ptr<IASTNode>> ASTBuilder::visitArgumentList(antlr::RyntraParser::ArgumentListContext *context) {
        std::vector<std::shared_ptr<IASTNode>> arguments;

        for (auto* exprCtx : context->expression()) {
            auto arg = visitExpression(exprCtx);
            if (arg) {
                arguments.push_back(std::move(arg));
            }
        }

        return arguments;
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitExpression(antlr::RyntraParser::ExpressionContext *context) {
        return visitAssignmentExpression(context->assignmentExpression());
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitLiteral(antlr::RyntraParser::LiteralContext *context) {
        if (context->STRING_LITERAL()) {
            std::string str = context->STRING_LITERAL()->getText();
            if (str.length() >= 2 && str.front() == '"' && str.back() == '"') {
                str = str.substr(1, str.length() - 2);
            }
            str = unescape(str);
            return createNode<StringLiteralNode>(context, str);
        }
        else if (context->INTEGER_LITERAL()) {
            int value = std::stoi(context->INTEGER_LITERAL()->getText());
            return createNode<IntegerLiteralNode>(context, value);
        }

        return nullptr;
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitAssignmentExpression(antlr::RyntraParser::AssignmentExpressionContext *context) {
        if (context->ASSIGN()) {
            std::string idName = context->IDENTIFIER()->getText();
            auto expr = visitExpression(context->expression());
            return createNode<AssignmentExpressionNode>(context, idName, std::move(expr));
        }
        return visitAdditiveExpression(context->additiveExpression());
    }

    std::shared_ptr<AssignmentExpressionNode> ASTBuilder::visitAssignment(antlr::RyntraParser::AssignmentContext *context) {
        std::string idName = context->IDENTIFIER()->getText();
        auto expr = visitExpression(context->expression());
        return createNode<AssignmentExpressionNode>(context, idName, std::move(expr));
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitAdditiveExpression(antlr::RyntraParser::AdditiveExpressionContext *context) {
        auto left = visitMultiplicativeExpression(context->multiplicativeExpression(0));
        
        for (size_t i = 1; i < context->multiplicativeExpression().size(); ++i) {
            std::string op = context->children[2 * i - 1]->getText();
            auto right = visitMultiplicativeExpression(context->multiplicativeExpression(i));
            left = createNode<BinaryExpressionNode>(context, left, right, op);
        }
        
        return left;
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitMultiplicativeExpression(antlr::RyntraParser::MultiplicativeExpressionContext *context) {
        auto left = visitPrimaryExpression(context->primaryExpression(0));
        
        for (size_t i = 1; i < context->primaryExpression().size(); ++i) {
            std::string op = context->children[2 * i - 1]->getText();
            auto right = visitPrimaryExpression(context->primaryExpression(i));
            left = createNode<BinaryExpressionNode>(context, left, right, op);
        }
        
        return left;
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitPrimaryExpression(antlr::RyntraParser::PrimaryExpressionContext *context) {
        if (context->literal()) {
            return visitLiteral(context->literal());
        }
        else if (context->functionCall()) {
            return visitFunctionCall(context->functionCall());
        }
        else if (context->IDENTIFIER()) {
            return createNode<IdentifierNode>(context, context->IDENTIFIER()->getText());
        }
        else if (context->LPAREN()) {
            return visitExpression(context->expression());
        }
        
        return nullptr;
    }
} // namespace Ryntra::Compiler