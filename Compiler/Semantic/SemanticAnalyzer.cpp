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

    bool SemanticAnalyzer::isInteger(TypeKind kind) {
        return kind == TypeKind::Int || kind == TypeKind::Long || kind == TypeKind::LongLong;
    }

    bool SemanticAnalyzer::isFloatingPoint(TypeKind kind) {
        return kind == TypeKind::Float || kind == TypeKind::Double;
    }

    bool SemanticAnalyzer::isNumeric(TypeKind kind) {
        return isInteger(kind) || isFloatingPoint(kind);
    }

    bool SemanticAnalyzer::isCompatible(TypeKind expected, TypeKind actual) {
        if (expected == actual)
            return true;
        if (isInteger(expected) && isInteger(actual)) {
            // Allow promotion: actual <= expected
            // We can define an order: Int < Long < LongLong
            auto rank = [](TypeKind k) {
                if (k == TypeKind::Int)
                    return 1;
                if (k == TypeKind::Long)
                    return 2;
                if (k == TypeKind::LongLong)
                    return 3;
                return 0;
            };
            return rank(actual) <= rank(expected);
        }

        // Float < Double
        if (isFloatingPoint(expected) && isFloatingPoint(actual)) {
            auto rank = [](TypeKind k) {
                if (k == TypeKind::Float)
                    return 1;
                if (k == TypeKind::Double)
                    return 2;
                return 0;
            };
            return rank(actual) <= rank(expected);
        }

        // Integer can be promoted to FloatingPoint
        if (isFloatingPoint(expected) && isInteger(actual)) {
            return true;
        }

        return false;
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
                SourceLocation(node->getLocation()));
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

    void SemanticAnalyzer::visitFunctionCall(std::shared_ptr<FunctionCallNode> node) {
        std::string funcName = node->getFunctionName();
        auto        funcSymbol = symbolTable.lookupFunction(funcName);
        if (funcSymbol == std::nullopt) {
            ErrorHandler::getInstance().makeError("Undefined function: " + funcName,
                                                  SourceLocation(node->getLocation().line, node->getLocation().column));
            lastTypeResult = {TypeKind::Void, ""};
            nodeTypes[node] = lastTypeResult;
            return;
        }

        const auto &args = node->getArguments();
        const auto &params = funcSymbol->parameters;

        if (funcName == "__builtin_scan") {
            ErrorHandler::getInstance().makeError(
                "__builtin_scan can only be used as a variable initializer like '[type] name = __builtin_scan()'.",
                SourceLocation(node->getLocation().line, node->getLocation().column));
            lastTypeResult = {TypeKind::ErrorType, ""};
            nodeTypes[node] = lastTypeResult;
            return;
        }

        if (args.size() != params.size()) {
            ErrorHandler::getInstance().makeError(
                "Function " + funcName + " requires " + std::to_string(params.size()) +
                    " arguments, but got " + std::to_string(args.size()),
                SourceLocation(node->getLocation().line, node->getLocation().column));
        }

        for (auto i = 0; i < (int)args.size(); i++) {
            Type argType = evaluate(args[i]);
            if (i < (int)params.size()) {
                if (!isCompatible(params[i].type.kind, argType.kind)) {
                    ErrorHandler::getInstance().makeError(
                        "Function " + funcName + " requires " + mapTypeToString(params[i].type.kind) + " but got " +
                            mapTypeToString(argType.kind),
                        SourceLocation(node->getLocation().line, node->getLocation().column));
                }
            }
        }

        lastTypeResult = funcSymbol->returnType;
        nodeTypes[node] = lastTypeResult;
    }

    void SemanticAnalyzer::visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) {
        visit(node->getFunctionCall());
    }

    void SemanticAnalyzer::visitIdentifier(std::shared_ptr<IdentifierNode> node) {
        std::string name = node->getName();
        auto        symbol = symbolTable.lookupSymbolInScopes(name);
        if (symbol == std::nullopt) {
            ErrorHandler::getInstance().makeError(
                "Undefined identifier: " + name,
                SourceLocation(node->getLocation()));
            lastTypeResult = {TypeKind::Void, ""};
            nodeTypes[node] = lastTypeResult;
            return;
        }
        lastTypeResult = symbol->type;
        nodeTypes[node] = lastTypeResult;
    }

    void SemanticAnalyzer::visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) {
        lastTypeResult = {node->getTypeKind(), ""};
        nodeTypes[node] = lastTypeResult;
    }

    void SemanticAnalyzer::visitFloatingLiteral(std::shared_ptr<FloatingLiteralNode> node) {
        lastTypeResult = {node->getTypeKind(), ""};
        nodeTypes[node] = lastTypeResult;
    }

    void SemanticAnalyzer::visitParameter(std::shared_ptr<ParameterNode> node) {
    }

    void SemanticAnalyzer::visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) {
        Type tk = evaluate(node->getReturnValue());
        if (!isCompatible(currentExpectedReturningType, tk.kind)) {
            ErrorHandler::getInstance().makeError(
                "Mismatched return type. Expect " + mapTypeToString(currentExpectedReturningType) + " but got " + mapTypeToString(tk.kind) + ".",
                SourceLocation(node->getLocation()));
        }
    }

    void SemanticAnalyzer::visitStringLiteral(std::shared_ptr<StringLiteralNode> node) {
        lastTypeResult = {TypeKind::String, ""};
        nodeTypes[node] = lastTypeResult;
    }

    void SemanticAnalyzer::visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) {
        std::string varName = node->getVarName();
        TypeKind    declaredType = mapStringToType(node->getVarType());

        auto initialValue = node->getInitialValue();
        if (initialValue) {
            bool handledBuiltinScan = false;

            if (auto callNode = std::dynamic_pointer_cast<FunctionCallNode>(initialValue)) {
                std::string funcName = callNode->getFunctionName();
                if (funcName == "__builtin_scan") {
                    handledBuiltinScan = true;

                    const auto &args = callNode->getArguments();
                    if (!args.empty()) {
                        ErrorHandler::getInstance().makeError(
                            "__builtin_scan does not accept any arguments.",
                            SourceLocation(callNode->getLocation()));
                    }

                    bool supportedType =
                        isInteger(declaredType) ||
                        isFloatingPoint(declaredType) ||
                        declaredType == TypeKind::Boolean;

                    if (!supportedType) {
                        ErrorHandler::getInstance().makeError(
                            "Type " + mapTypeToString(declaredType) + " cannot be initialized by __builtin_scan.",
                            SourceLocation(node->getLocation()));
                    }

                    lastTypeResult = {declaredType, ""};
                    nodeTypes[callNode] = lastTypeResult;
                }
            }

            if (!handledBuiltinScan) {
                Type initValueType = evaluate(initialValue);

                if (!isCompatible(declaredType, initValueType.kind)) {
                    ErrorHandler::getInstance().makeError(
                        "Mismatched value type. Expect " + mapTypeToString(declaredType) + " but got " + mapTypeToString(initValueType.kind) + ".",
                        SourceLocation(node->getLocation()));
                }
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

    void SemanticAnalyzer::visitBinaryExpression(std::shared_ptr<BinaryExpressionNode> node) {
        Type        lhs = evaluate(node->getLeft());
        Type        rhs = evaluate(node->getRight());
        std::string op = node->getOp();

        if (op == "+" || op == "-" || op == "*" || op == "/") {
            if (!(isNumeric(lhs.kind) && isNumeric(rhs.kind))) {
                ErrorHandler::getInstance().makeError(
                    "Binary Arithmical Operator " + op + " only use between numeric types.",
                    SourceLocation(node->getLocation()));
            }

            // Type promotion: Double > Float > LongLong > Long > Int
            if (lhs.kind == TypeKind::Double || rhs.kind == TypeKind::Double) {
                lastTypeResult = {TypeKind::Double, ""};
            } else if (lhs.kind == TypeKind::Float || rhs.kind == TypeKind::Float) {
                lastTypeResult = {TypeKind::Float, ""};
            } else if (lhs.kind == TypeKind::LongLong || rhs.kind == TypeKind::LongLong) {
                lastTypeResult = {TypeKind::LongLong, ""};
            } else if (lhs.kind == TypeKind::Long || rhs.kind == TypeKind::Long) {
                lastTypeResult = {TypeKind::Long, ""};
            } else {
                lastTypeResult = {TypeKind::Int, ""};
            }
        } else if (op == "%" || op == "&" || op == "|" || op == "^" || op == "<<" || op == ">>") {
            if (!(isInteger(lhs.kind) && isInteger(rhs.kind))) {
                ErrorHandler::getInstance().makeError(
                    "Operator " + op + " only use between integer types.",
                    SourceLocation(node->getLocation()));
            }

            // Type promotion for integers
            if (lhs.kind == TypeKind::LongLong || rhs.kind == TypeKind::LongLong) {
                lastTypeResult = {TypeKind::LongLong, ""};
            } else if (lhs.kind == TypeKind::Long || rhs.kind == TypeKind::Long) {
                lastTypeResult = {TypeKind::Long, ""};
            } else {
                lastTypeResult = {TypeKind::Int, ""};
            }
        } else if (op == "&&" || op == "||") {
            if (!(lhs.kind == TypeKind::Boolean && rhs.kind == TypeKind::Boolean)) {
                ErrorHandler::getInstance().makeError(
                    "Logical Operator only use in boolean type.",
                    SourceLocation(node->getLocation()));
            }
            lastTypeResult = {TypeKind::Boolean, ""};
        } else if (op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=") {
            if (!(isNumeric(lhs.kind) && isNumeric(rhs.kind)) && lhs.kind != rhs.kind) {
                ErrorHandler::getInstance().makeError(
                    "Cannot compare between different types.",
                    SourceLocation(node->getLocation()));
            }
            lastTypeResult = {TypeKind::Boolean, ""};
        } else {
            lastTypeResult = {TypeKind::Void, ""};
        }

        nodeTypes[node] = lastTypeResult;
    }

    void SemanticAnalyzer::visitAssignmentExpression(std::shared_ptr<AssignmentExpressionNode> node) {
        std::string idName = node->getIdentifier();
        std::string op = node->getOp();
        auto        symbol = symbolTable.lookupSymbolInScopes(idName);

        if (symbol == std::nullopt) {
            ErrorHandler::getInstance().makeError(
                "Undefined variable '" + idName + "' in current scope.",
                SourceLocation(node->getLocation()));
            lastTypeResult = {TypeKind::Void, ""};
            nodeTypes[node] = lastTypeResult;
            return;
        }

        Type lhsType = symbol->type;
        Type rhsType = evaluate(node->getExpression());

        if (op == "=") {
            if (!isCompatible(lhsType.kind, rhsType.kind)) {
                ErrorHandler::getInstance().makeError(
                    "Cannot assign value of type " + mapTypeToString(rhsType.kind) +
                        " to variable '" + idName + "' of type " + mapTypeToString(lhsType.kind),
                    SourceLocation(node->getLocation()));
            }
            lastTypeResult = lhsType;
            nodeTypes[node] = lastTypeResult;
            return;
        }

        bool isArithmeticCompound =
            op == "+=" || op == "-=" || op == "*=" || op == "/=" ||
            op == "%=";
        bool isBitwiseCompound =
            op == "&=" || op == "|=" || op == "^=" ||
            op == "<<=" || op == ">>=";

        if (isArithmeticCompound) {
            if (!isNumeric(lhsType.kind) || !isNumeric(rhsType.kind)) {
                ErrorHandler::getInstance().makeError(
                    "Operator " + op + " can only be applied between numeric types.",
                    SourceLocation(node->getLocation()));
            }
        } else if (isBitwiseCompound) {
            if (!isInteger(lhsType.kind) || !isInteger(rhsType.kind)) {
                ErrorHandler::getInstance().makeError(
                    "Operator " + op + " can only be applied between integer types.",
                    SourceLocation(node->getLocation()));
            }
        } else {
            ErrorHandler::getInstance().makeError(
                "Unsupported assignment operator '" + op + "'.",
                SourceLocation(node->getLocation()));
        }

        lastTypeResult = lhsType;
        nodeTypes[node] = lastTypeResult;
    }

    void SemanticAnalyzer::visitUnaryExpression(std::shared_ptr<UnaryExpressionNode> node) {
        Type        exprType = evaluate(node->getExpression());
        std::string op = node->getOp();

        if (op == "!") {
            if (exprType.kind != TypeKind::Boolean) {
                ErrorHandler::getInstance().makeError(
                    "Operator ! only use in boolean type.",
                    SourceLocation(node->getLocation()));
            }
            lastTypeResult = {TypeKind::Boolean, ""};
        } else if (op == "-") {
            if (isNumeric(exprType.kind)) {
                lastTypeResult = exprType;
            } else {
                ErrorHandler::getInstance().makeError(
                    "Operator - only use in numeric type.",
                    SourceLocation(node->getLocation()));
                lastTypeResult = {TypeKind::Int, ""};
            }
        } else if (op == "~") {
            if (isInteger(exprType.kind)) {
                lastTypeResult = exprType;
            } else {
                ErrorHandler::getInstance().makeError(
                    "Operator ~ only use in integer type.",
                    SourceLocation(node->getLocation()));
                lastTypeResult = {TypeKind::Int, ""};
            }
        } else {
            lastTypeResult = exprType;
        }

        nodeTypes[node] = lastTypeResult;
    }

    void SemanticAnalyzer::visitWhileStatement(std::shared_ptr<WhileStatementNode> node) {
    symbolTable.enterScope();
    loopDepth++;
    Type condType = evaluate(node->getCondition());
    if (condType.kind != TypeKind::Boolean) {
        ErrorHandler::getInstance().makeError(
            "While condition must be a boolean expression, but got " + mapTypeToString(condType.kind) + ".",
            SourceLocation(node->getLocation()));
    }
    visit(node->getBody());
    loopDepth--;
    symbolTable.exitScope();
}

void SemanticAnalyzer::visitForStatement(std::shared_ptr<ForStatementNode> node) {
    // For loop creates a new scope for its initializer
    symbolTable.enterScope();
    loopDepth++;

    if (node->getInit()) {
        visit(node->getInit());
    }

    if (node->getCondition()) {
        Type condType = evaluate(node->getCondition());
        if (condType.kind != TypeKind::Boolean) {
            ErrorHandler::getInstance().makeError(
                "For condition must be a boolean expression, but got " + mapTypeToString(condType.kind) + ".",
                SourceLocation(node->getLocation()));
        }
    }

    if (node->getIncrement()) {
        visit(node->getIncrement());
    }

    // Body will enter its own scope via visitBlock, which is fine
    visit(node->getBody());

    loopDepth--;
    symbolTable.exitScope();
}

void SemanticAnalyzer::visitPostfixExpression(std::shared_ptr<PostfixExpressionNode> node) {
    auto symbol = symbolTable.lookupSymbolInScopes(node->getVarName());
    if (symbol == std::nullopt) {
        ErrorHandler::getInstance().makeError(
            "Undefined identifier: " + node->getVarName(),
            SourceLocation(node->getLocation()));
        lastTypeResult = {TypeKind::ErrorType, ""};
        nodeTypes[node] = lastTypeResult;
        return;
    }

    if (!isNumeric(symbol->type.kind)) {
        ErrorHandler::getInstance().makeError(
            "Increment/Decrement operator can only be applied to numeric types, but got " + mapTypeToString(symbol->type.kind) + ".",
            SourceLocation(node->getLocation()));
        lastTypeResult = {TypeKind::ErrorType, ""};
        nodeTypes[node] = lastTypeResult;
        return;
    }

    lastTypeResult = symbol->type;
    nodeTypes[node] = lastTypeResult;
}

void SemanticAnalyzer::visitContinueStatement(std::shared_ptr<ContinueStatementNode> node) {
    if (!(loopDepth > 0)) {
        ErrorHandler::getInstance().makeError("Continue must use in a loop statement.",
                                              SourceLocation(node->getLocation()));
    }
}

void SemanticAnalyzer::visitBreakStatement(std::shared_ptr<BreakStatementNode> node) {
    if (!(loopDepth > 0)) {
        ErrorHandler::getInstance().makeError("Break must use in a loop statement.",
                                              SourceLocation(node->getLocation()));
    }
}

void SemanticAnalyzer::visitBooleanLiteral(std::shared_ptr<BooleanLiteralNode> node) {

}
} // namespace Ryntra::Compiler
