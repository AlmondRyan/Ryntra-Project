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
        std::string returnType = context->typeSpecifier()->getText();
        std::string functionName = context->IDENTIFIER()->getText();
        
        std::vector<std::shared_ptr<ParameterNode>> parameters;
        if (context->parameterList()) {
            parameters = visitParameterList(context->parameterList());
        }

        std::shared_ptr<BlockNode> body = visitBlock(context->block());

        return createNode<FunctionDefinitionNode>(context, returnType, functionName, std::move(parameters), std::move(body));
    }

    std::vector<std::shared_ptr<ParameterNode>> ASTBuilder::visitParameterList(antlr::RyntraParser::ParameterListContext *context) {
        std::vector<std::shared_ptr<ParameterNode>> parameters;
        auto types = context->typeSpecifier();
        auto names = context->IDENTIFIER();

        for (size_t i = 0; i < names.size(); ++i) {
            std::string paramType = types[i]->getText();
            std::string paramName = names[i]->getText();
            parameters.push_back(createNode<ParameterNode>(context, paramType, paramName));
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
        else if (context->ifStatement()) {
            return visitIfStatement(context->ifStatement());
        }
        else if (context->whileStatement()) {
            return visitWhileStatement(context->whileStatement());
        }
        else if (context->forStatement()) {
            return visitForStatement(context->forStatement());
        }
        else if (context->breakStatement()) {
            return visitBreakStatement(context->breakStatement());
        }
        else if (context->continueStatement()) {
            return visitContinueStatement(context->continueStatement());
        }
        else {
            return createNode<EmptyStatementNode>(context);
        }
    }

    std::shared_ptr<VariableDeclarationNode> ASTBuilder::visitVariableDeclaration(antlr::RyntraParser::VariableDeclarationContext *context) {
        std::string varType = context->typeSpecifier()->getText();
        
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

    std::shared_ptr<IfStatementNode> ASTBuilder::visitIfStatement(antlr::RyntraParser::IfStatementContext *context) {
        auto condition = visitExpression(context->expression());
        auto thenBody = visitBlock(context->block());
        std::shared_ptr<IASTNode> elseBody = nullptr;
        if (context->elseClause()) {
            elseBody = visitElseClause(context->elseClause());
        }
        return createNode<IfStatementNode>(context, std::move(condition), std::move(thenBody), std::move(elseBody));
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitElseClause(antlr::RyntraParser::ElseClauseContext *context) {
        if (context->ifStatement()) {
            return visitIfStatement(context->ifStatement());
        } else {
            return visitBlock(context->block());
        }
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
        return visitLogicalOrExpression(context->logicalOrExpression());
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitLogicalOrExpression(antlr::RyntraParser::LogicalOrExpressionContext *context) {
        auto left = visitLogicalAndExpression(context->logicalAndExpression(0));
        
        for (size_t i = 1; i < context->logicalAndExpression().size(); ++i) {
            std::string op = context->children[2 * i - 1]->getText();
            auto right = visitLogicalAndExpression(context->logicalAndExpression(i));
            left = createNode<BinaryExpressionNode>(context, left, right, op);
        }
        
        return left;
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitLogicalAndExpression(antlr::RyntraParser::LogicalAndExpressionContext *context) {
        auto left = visitEqualityExpression(context->equalityExpression(0));
        
        for (size_t i = 1; i < context->equalityExpression().size(); ++i) {
            std::string op = context->children[2 * i - 1]->getText();
            auto right = visitEqualityExpression(context->equalityExpression(i));
            left = createNode<BinaryExpressionNode>(context, left, right, op);
        }
        
        return left;
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitEqualityExpression(antlr::RyntraParser::EqualityExpressionContext *context) {
        auto left = visitRelationalExpression(context->relationalExpression(0));
        
        for (size_t i = 1; i < context->relationalExpression().size(); ++i) {
            std::string op = context->children[2 * i - 1]->getText();
            auto right = visitRelationalExpression(context->relationalExpression(i));
            left = createNode<BinaryExpressionNode>(context, left, right, op);
        }
        
        return left;
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
            std::string text = context->INTEGER_LITERAL()->getText();
            TypeKind kind = TypeKind::Int;
            long long value = 0;

            if (text.back() == 'L' || text.back() == 'l') {
                if (text.size() >= 2 && (text[text.size() - 2] == 'L' || text[text.size() - 2] == 'l')) {
                    kind = TypeKind::LongLong;
                    value = std::stoll(text.substr(0, text.size() - 2));
                } else {
                    kind = TypeKind::Long;
                    value = std::stoll(text.substr(0, text.size() - 1));
                }
            } else {
                value = std::stoll(text);
                // Even without suffix, if it's too large for int, we should promote it
                if (value > 2147483647LL || value < -2147483648LL) {
                    kind = TypeKind::Long; // Default to Long for large literals without suffix
                }
            }
            return createNode<IntegerLiteralNode>(context, value, kind);
        }
        else if (context->TRUE()) {
            return createNode<BooleanLiteralNode>(context, true);
        }
        else if (context->FALSE()) {
            return createNode<BooleanLiteralNode>(context, false);
        }

        return nullptr;
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitRelationalExpression(antlr::RyntraParser::RelationalExpressionContext *context) {
        auto left = visitAdditiveExpression(context->additiveExpression(0));
        
        for (size_t i = 1; i < context->additiveExpression().size(); ++i) {
            std::string op = context->children[2 * i - 1]->getText();
            auto right = visitAdditiveExpression(context->additiveExpression(i));
            left = createNode<BinaryExpressionNode>(context, left, right, op);
        }
        
        return left;
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
        auto left = visitUnaryExpression(context->unaryExpression(0));
        
        for (size_t i = 1; i < context->unaryExpression().size(); ++i) {
            std::string op = context->children[2 * i - 1]->getText();
            auto right = visitUnaryExpression(context->unaryExpression(i));
            left = createNode<BinaryExpressionNode>(context, left, right, op);
        }
        
        return left;
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitUnaryExpression(antlr::RyntraParser::UnaryExpressionContext *context) {
        if (context->postfixExpression()) {
            return visitPostfixExpression(context->postfixExpression());
        } else if (context->NOT()) {
            auto expr = visitUnaryExpression(context->unaryExpression());
            return createNode<UnaryExpressionNode>(context, "!", std::move(expr));
        } else if (context->MINUS()) {
            auto expr = visitUnaryExpression(context->unaryExpression());
            return createNode<UnaryExpressionNode>(context, "-", std::move(expr));
        }
        return nullptr;
    }

    std::shared_ptr<IASTNode> ASTBuilder::visitPostfixExpression(antlr::RyntraParser::PostfixExpressionContext *context) {
        if (context->primaryExpression()) {
            return visitPrimaryExpression(context->primaryExpression());
        } else if (context->INC()) {
            return createNode<PostfixExpressionNode>(context, context->IDENTIFIER()->getText(), "++");
        } else if (context->DEC()) {
            return createNode<PostfixExpressionNode>(context, context->IDENTIFIER()->getText(), "--");
        }
        return nullptr;
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

    std::shared_ptr<WhileStatementNode> ASTBuilder::visitWhileStatement(antlr::RyntraParser::WhileStatementContext *context) {
        auto condition = visitExpression(context->expression());
        auto body = visitBlock(context->block());
        return createNode<WhileStatementNode>(context, std::move(condition), std::move(body));
    }

    std::shared_ptr<ForStatementNode> ASTBuilder::visitForStatement(antlr::RyntraParser::ForStatementContext *context) {
        std::shared_ptr<IASTNode> init = nullptr;
        std::shared_ptr<IASTNode> cond = nullptr;
        std::shared_ptr<IASTNode> inc = nullptr;

        size_t semicolonCount = 0;
        for (auto child : context->children) {
            if (child->getText() == ";") {
                semicolonCount++;
                continue;
            }
            
            if (semicolonCount == 0) { // Init part
                if (auto varDecl = dynamic_cast<antlr::RyntraParser::VariableDeclarationContext*>(child)) {
                    init = visitVariableDeclaration(varDecl);
                } else if (auto assign = dynamic_cast<antlr::RyntraParser::AssignmentContext*>(child)) {
                    init = visitAssignment(assign);
                } else if (auto expr = dynamic_cast<antlr::RyntraParser::ExpressionContext*>(child)) {
                    init = visitExpression(expr);
                }
            } else if (semicolonCount == 1) { // Condition part
                if (auto expr = dynamic_cast<antlr::RyntraParser::ExpressionContext*>(child)) {
                    cond = visitExpression(expr);
                }
            } else if (semicolonCount == 2) { // Increment part
                if (auto assign = dynamic_cast<antlr::RyntraParser::AssignmentContext*>(child)) {
                    inc = visitAssignment(assign);
                } else if (auto expr = dynamic_cast<antlr::RyntraParser::ExpressionContext*>(child)) {
                    inc = visitExpression(expr);
                }
            }
        }

        auto body = visitBlock(context->block());
        return createNode<ForStatementNode>(context, std::move(init), std::move(cond), std::move(inc), std::move(body));
    }

    std::shared_ptr<BreakStatementNode> ASTBuilder::visitBreakStatement(antlr::RyntraParser::BreakStatementContext *context) {
        return createNode<BreakStatementNode>(context);
    }

    std::shared_ptr<ContinueStatementNode> ASTBuilder::visitContinueStatement(antlr::RyntraParser::ContinueStatementContext *context) {
        return createNode<ContinueStatementNode>(context);
    }
} // namespace Ryntra::Compiler