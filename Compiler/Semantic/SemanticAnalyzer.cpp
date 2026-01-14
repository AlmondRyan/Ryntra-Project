#include "SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"
#include <iostream>

namespace Ryntra::Compiler {
    void SemanticAnalyzer::visitProgram(std::shared_ptr<ProgramNode> node) {
        // Register all functions to symbol table
        for (const auto &i : node->getFunctions()) {
            FunctionSymbol functionSymbol;
            functionSymbol.name = i->getFunctionName();
            functionSymbol.returnType = {mapStringToType(i->getReturnType()), ""};
            for (const auto &paramNode : i->getParameters()) {
                TypeKind pk = mapStringToType(paramNode->getType());
                Symbol   s({pk, ""}, paramNode->getName(), SymbolKind::Parameter);
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
                SourceLocation(node->getLocation().line, node->getLocation().column));
        } else {
            if (mainFunc->returnType.kind != TypeKind::Int) {
                ErrorHandler::getInstance().makeError(
                    "Function main() should return int.",
                    SourceLocation(node->getLocation().line, node->getLocation().column));
            }
        }
    }

    void SemanticAnalyzer::visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) {
        // Get current expecting type, which is The function return type
        currentExpectedReturningType = mapStringToType(node->getReturnType());

        // A Function is wrapped by braces, the block in braces will be a single scope
        symbolTable.enterScope();

        // Iterate parameters
        for (auto &param : node->getParameters()) {
            // Add parameter into symbol table
            Symbol s = {{mapStringToType(param->getType()), ""}, param->getName(), SymbolKind::Parameter};
            symbolTable.addSymbolToCurrentScope(s);
            // Process parameter (visitParameter());
            visit(param);
        }

        // Visit Block
        visit(node->getBody());

        // The function is completely processed, exit current scope
        symbolTable.exitScope();
        // Reset the currentExpectedReturningType
        currentExpectedReturningType = TypeKind::Void;
    }

    void SemanticAnalyzer::visitBlock(std::shared_ptr<BlockNode> node) {
        // Visit current block, a block will be a single scope
        symbolTable.enterScope();
        for (auto &stmt : node->getStatements()) {
            visit(stmt);
        }
        symbolTable.exitScope();
    }

    void SemanticAnalyzer::visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) {
    }

    void SemanticAnalyzer::visitIfStatement(std::shared_ptr<IfStatementNode> node) {
        Type condType = evaluate(node->getCondition());
        if (condType.kind != TypeKind::Boolean) {
            ErrorHandler::getInstance().makeError(
                "If condition must be a boolean expression, but got " + mapTypeToString(condType.kind) + ".",
                SourceLocation(node->getLocation())
            );
        }

        visit(node->getThenBody());
        if (node->getElseBody()) {
            visit(node->getElseBody());
        }
    }

    void SemanticAnalyzer::visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) {
        if (node->getExpression()) {
            auto expr = node->getExpression();
            if (std::dynamic_pointer_cast<BinaryExpressionNode>(expr)) {
                ErrorHandler::getInstance().makeWarning(
                    "Expression result discarded.",
                    SourceLocation(node->getLocation()));
            }

            visit(node->getExpression());
        }
    }

    Type SemanticAnalyzer::visitFunctionCall(std::shared_ptr<FunctionCallNode> node) {
        std::string funcName = node->getFunctionName();
        auto        funcSymbol = symbolTable.lookupFunction(funcName);
        if (funcSymbol == std::nullopt) {
            ErrorHandler::getInstance().makeError("Undefined function: " + funcName,
                                                  SourceLocation(node->getLocation().line, node->getLocation().column));
            lastTypeResult = {TypeKind::Void, ""};
            return lastTypeResult;
        }

        const auto &args = node->getArguments();
        const auto &params = funcSymbol->parameters;

        if (args.size() != params.size()) {
            ErrorHandler::getInstance().makeError(
                "Function " + funcName + " requires " + std::to_string(params.size()) +
                    " arguments, but got " + std::to_string(args.size()),
                SourceLocation(node->getLocation().line, node->getLocation().column));
        }

        for (auto i = 0; i < args.size(); i++) {
            Type argType = evaluate(args[i]);
            if (i < params.size()) {
                if (argType.kind != params[i].type.kind) {
                    ErrorHandler::getInstance().makeError(
                        "Function " + funcName + " requires " + mapTypeToString(params[i].type.kind) + " but got " +
                            mapTypeToString(argType.kind),
                        SourceLocation(node->getLocation().line, node->getLocation().column));
                }
            }
        }

        lastTypeResult = funcSymbol->returnType;
        return lastTypeResult;
    }

    void SemanticAnalyzer::visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) {
        visit(node->getFunctionCall());
    }

    Type SemanticAnalyzer::visitIdentifier(std::shared_ptr<IdentifierNode> node) {
        std::string name = node->getName();
        auto        symbol = symbolTable.lookupSymbolInScopes(name);
        if (symbol == std::nullopt) {
            ErrorHandler::getInstance().makeError(
                "Undefined identifier: " + name,
                SourceLocation(node->getLocation()));
            lastTypeResult = {TypeKind::Void, ""};
            return lastTypeResult;
        }
        lastTypeResult = symbol->type;
        return lastTypeResult;
    }

    Type SemanticAnalyzer::visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) {
        lastTypeResult = {TypeKind::Int, ""};
        return lastTypeResult;
    }

    void SemanticAnalyzer::visitParameter(std::shared_ptr<ParameterNode> node) {
    }

    void SemanticAnalyzer::visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) {
        Type tk = evaluate(node->getReturnValue());
        if (tk.kind != TypeKind::Void || node->getReturnValue()) {
            if (tk.kind != currentExpectedReturningType) {
                ErrorHandler::getInstance().makeError(
                    "Mismatch returning type: expect " + mapTypeToString(currentExpectedReturningType) + " but got " + mapTypeToString(tk.kind),
                    SourceLocation(node->getLocation()));
            }
        } else {
            if (currentExpectedReturningType != TypeKind::Void) {
                ErrorHandler::getInstance().makeError("Function expect " + mapTypeToString(currentExpectedReturningType) + " returning value but got empty.",
                                                      SourceLocation(node->getLocation()));
            }
        }
    }

    Type SemanticAnalyzer::visitStringLiteral(std::shared_ptr<StringLiteralNode> node) {
        lastTypeResult = {TypeKind::String, ""};
        return lastTypeResult;
    }

    void SemanticAnalyzer::visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) {
        std::string varName = node->getVarName();
        // std::cout << "VarType: " << node->getVarType() << std::endl;

        TypeKind declaredType = mapStringToType(node->getVarType());

        auto initialValue = node->getInitialValue();
        if (initialValue) {
            Type initValueType = evaluate(initialValue);

            if (declaredType != initValueType.kind) {
                ErrorHandler::getInstance().makeError(
                    "Mismatched value type. Expect " + mapTypeToString(declaredType) + " but got " + mapTypeToString(initValueType.kind) + ".",
                    SourceLocation(node->getLocation()));
            }
        }

        Symbol variableSymbol = {
            {declaredType, ""},
            varName,
            SymbolKind::Variable};

        if (!symbolTable.addSymbolToCurrentScope(variableSymbol)) {
            ErrorHandler::getInstance().makeError(
                "Variable '" + varName + "' is already defined in this scope.",
                SourceLocation(node->getLocation()));
        }
    }

    Type SemanticAnalyzer::visitBinaryExpression(std::shared_ptr<BinaryExpressionNode> node) {
        Type        lhs = evaluate(node->getLeft());
        Type        rhs = evaluate(node->getRight());
        std::string op = node->getOp();

        if (op == "+" || op == "-" || op == "*" || op == "/") {
            if (!(lhs.kind == TypeKind::Int && rhs.kind == TypeKind::Int)) {
                ErrorHandler::getInstance().makeError(
                    "Binary Arithmical Operator only use between arithmetic type.",
                    SourceLocation(node->getLocation()));
            }
            lastTypeResult = {TypeKind::Int, ""};
        } else if (op == "&&" || op == "||") {
            if (!(lhs.kind == TypeKind::Boolean && rhs.kind == TypeKind::Boolean)) {
                ErrorHandler::getInstance().makeError(
                    "Logical Operator only use in boolean type.",
                    SourceLocation(node->getLocation()));
            }
            lastTypeResult = {TypeKind::Boolean, ""};
        } else if (op == "==" || op == "!=" || op == ">" || op == "<" || op == ">=" || op == "<=") {
            if (lhs.kind != rhs.kind) {
                ErrorHandler::getInstance().makeError(
                    "Cannot compare between different types.",
                    SourceLocation(node->getLocation()));
            }
            lastTypeResult = {TypeKind::Boolean, ""};
        } else {
            lastTypeResult = {TypeKind::Void, ""};
        }

        return lastTypeResult;
    }

    Type SemanticAnalyzer::visitAssignmentExpression(std::shared_ptr<AssignmentExpressionNode> node) {
        auto idName = node->getIdentifier();
        auto symbol = symbolTable.lookupSymbolInScopes(idName);

        if (symbol == std::nullopt) {
            ErrorHandler::getInstance().makeError(
                "Undefined variable '" + idName + "' in current scope.",
                SourceLocation(node->getLocation()));
            lastTypeResult = {TypeKind::Void, ""};
            return lastTypeResult;
        }

        Type rhsType = evaluate(node->getExpression());
        Type lhsType = symbol->type;

        if (lhsType.kind != rhsType.kind) {
            ErrorHandler::getInstance().makeError(
                "Cannot assign " + mapTypeToString(rhsType.kind) +
                    " rvalue to variable '" + idName + "' of type " + mapTypeToString(lhsType.kind),
                SourceLocation(node->getLocation()));
        }

        lastTypeResult = lhsType;
        return lastTypeResult;
    }

    Type SemanticAnalyzer::visitBooleanLiteral(std::shared_ptr<BooleanLiteralNode> node) {
        lastTypeResult = {TypeKind::Boolean, ""};
        return lastTypeResult;
    }

    Type SemanticAnalyzer::visitUnaryExpression(std::shared_ptr<UnaryExpressionNode> node) {
        Type        exprType = evaluate(node->getExpression());
        std::string op = node->getOp();

        if (op == "!") {
            if (exprType.kind == TypeKind::Boolean) {
                lastTypeResult = {TypeKind::Boolean, ""};
            } else {
                ErrorHandler::getInstance().makeError(
                    "Operator ! only use in boolean type.",
                    SourceLocation(node->getLocation()));
                lastTypeResult = {TypeKind::Boolean, ""};
            }
        } else if (op == "-") {
            if (exprType.kind == TypeKind::Int) {
                lastTypeResult = {TypeKind::Int, ""};
            } else {
                ErrorHandler::getInstance().makeError("Operator - only use in int type.",
                    SourceLocation(node->getLocation()));
                lastTypeResult = {TypeKind::Int, ""};
            }
        }

        return lastTypeResult;
    }
} // namespace Ryntra::Compiler
