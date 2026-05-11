#include "SemanticAnalyzer.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {
    TypePtr SemanticAnalyzer::makeSTType(const std::string& name) {
        if (name == "void")   return std::make_shared<STType::VoidType>();
        if (name == "string") return std::make_shared<STType::StringType>();
        if (name == "long")   return std::make_shared<STType::Int64Type>();
        // int / int32 both map to Int32
        return std::make_shared<STType::Int32Type>();
    }

    std::shared_ptr<Type> SemanticAnalyzer::toTypedType(const TypePtr& stType) {
        if (!stType) return TypeFactory::getPrimitive("unknown");
        switch (stType->getKind()) {
            case STType::TypeKind::Void:   return TypeFactory::getVoid();
            case STType::TypeKind::String: return TypeFactory::getPrimitive("string");
            case STType::TypeKind::Int32:  return TypeFactory::getPrimitive("int");
            case STType::TypeKind::Int64:  return TypeFactory::getPrimitive("long");
            default:                       return TypeFactory::getPrimitive("unknown");
        }
    }

    void SemanticAnalyzer::analyze(const std::shared_ptr<IASTNode>& root) {
        if (!root) return;
        root->accept(*this);
    }

    void SemanticAnalyzer::visit(ProgramNode &node) {
        // First pass: register all user-defined functions
        for (const auto &func : node.getFunctions()) {
            auto funcName      = func->getName()->getName();
            auto returnTypeName = func->getReturnType()->getName();
            auto returnType    = makeSTType(returnTypeName);

            if (symbolTable.resolve(funcName)) {
                ErrorHandler::getInstance().makeError(
                    "[RCE001]: Function '" + funcName + "' is already defined.",
                    func->getLocation());
                continue;
            }

            symbolTable.define(
                std::make_shared<FunctionSymbol>(funcName, returnType, std::vector<TypePtr>{}),
                func->getLocation());
        }

        // Register __builtin_print with overloads for string, int, and long
        if (!symbolTable.resolve("__builtin_print")) {
            auto overloadSet = std::make_shared<OverloadSet>("__builtin_print");

            // Overload 1: __builtin_print(string)
            {
                std::vector<TypePtr> params{ std::make_shared<STType::StringType>() };
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_print",
                    std::make_shared<STType::VoidType>(), std::move(params)));
            }

            // Overload 2: __builtin_print(int) — already supported via builtin_print_i32
            {
                std::vector<TypePtr> params{ std::make_shared<STType::Int32Type>() };
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_print",
                    std::make_shared<STType::VoidType>(), std::move(params)));
            }

            // Overload 3: __builtin_print(long)
            {
                std::vector<TypePtr> params{ std::make_shared<STType::Int64Type>() };
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_print",
                    std::make_shared<STType::VoidType>(), std::move(params)));
            }

            symbolTable.define(overloadSet, SourceLocation{0, 0});
        }

        // Register __builtin_scan with overloads for int and long
        if (!symbolTable.resolve("__builtin_scan")) {
            auto overloadSet = std::make_shared<OverloadSet>("__builtin_scan");

            // Overload 1: __builtin_scan() → int
            {
                std::vector<TypePtr> params{};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_scan",
                    std::make_shared<STType::Int32Type>(), std::move(params)));
            }

            // Overload 2: __builtin_scan() → long
            {
                std::vector<TypePtr> params{};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_scan",
                    std::make_shared<STType::Int64Type>(), std::move(params)));
            }

            symbolTable.define(overloadSet, SourceLocation{0, 0});
        }

        // Also register plain "print" for backward compatibility
        if (!symbolTable.resolve("print")) {
            auto overloadSet = std::make_shared<OverloadSet>("print");

            // Overload 1: print(string)
            {
                std::vector<TypePtr> params{ std::make_shared<STType::StringType>() };
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("print",
                    std::make_shared<STType::VoidType>(), std::move(params)));
            }

            // Overload 2: print(int) — already supported via builtin_print_i32
            {
                std::vector<TypePtr> params{ std::make_shared<STType::Int32Type>() };
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("print",
                    std::make_shared<STType::VoidType>(), std::move(params)));
            }

            // Overload 3: print(long)
            {
                std::vector<TypePtr> params{ std::make_shared<STType::Int64Type>() };
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("print",
                    std::make_shared<STType::VoidType>(), std::move(params)));
            }

            symbolTable.define(overloadSet, SourceLocation{0, 0});
        }

        auto mainSym = symbolTable.resolve("main");
        if (!mainSym) {
            ErrorHandler::getInstance().makeError(
                "[RCE002]: 'main' function is not defined.", node.getLocation());
        } else {
            auto mainFuncSym = std::dynamic_pointer_cast<FunctionSymbol>(mainSym);
            if (!mainFuncSym) {
                ErrorHandler::getInstance().makeError(
                    "[RCE003]: 'main' is not a function.", node.getLocation());
            } else if (!mainFuncSym->getReturnType()) {
                ErrorHandler::getInstance().makeError(
                    "[RCE004]: 'main' function must have a return type.", node.getLocation());
            } else if (mainFuncSym->getReturnType()->getKind() != STType::TypeKind::Void) {
                ErrorHandler::getInstance().makeError(
                    "[RCE004]: 'main' function must return 'void'.", node.getLocation());
            }
        }

        // Second pass: analyze bodies
        std::vector<std::shared_ptr<TypedFunctionDefinitionNode>> typedFunctions;
        for (const auto &func : node.getFunctions()) {
            func->accept(*this);
            if (auto typedFunc = std::dynamic_pointer_cast<TypedFunctionDefinitionNode>(lastNode)) {
                typedFunctions.push_back(typedFunc);
            }
        }

        typedProgram = std::make_shared<TypedProgramNode>(std::move(typedFunctions));
        typedProgram->setLocation(node.getLocation());
        lastNode = typedProgram;
    }

    void SemanticAnalyzer::visit(FunctionDefinitionNode &node) {
        node.getReturnType()->accept(*this);
        auto returnType = lastType ? lastType : makeSTType("void");
        currentFunctionReturnType = returnType;

        auto funcName = node.getName()->getName();

        symbolTable.enterScope();
        node.getBody()->accept(*this);
        auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);
        symbolTable.exitScope();

        if (typedBody) {
            auto typedFunc = std::make_shared<TypedFunctionDefinitionNode>(
                funcName, toTypedType(returnType), typedBody);
            typedFunc->setLocation(node.getLocation());
            lastNode = typedFunc;
        } else {
            lastNode = nullptr;
        }
        currentFunctionReturnType = nullptr;
    }

    void SemanticAnalyzer::visit(ReturnNode &node) {
        node.getValue()->accept(*this);
        auto typedExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (typedExpr) {
            if (currentFunctionReturnType) {
                auto expectedTyped = toTypedType(currentFunctionReturnType);
                auto actualType    = typedExpr->getType();

                if (!expectedTyped->equals(*actualType) && actualType->toString() != "unknown") {
                    ErrorHandler::getInstance().makeError(
                        "[RCE006]: Return type mismatch. Expected '" +
                        expectedTyped->toString() + "', but got '" +
                        actualType->toString() + "'.",
                        node.getLocation());
                }
            }
            auto typedReturn = std::make_shared<TypedReturnNode>(typedExpr);
            typedReturn->setLocation(node.getLocation());
            lastNode = typedReturn;
        } else {
            lastNode = nullptr;
        }
    }

    void SemanticAnalyzer::visit(BlockNode &node) {
        std::vector<std::shared_ptr<TypedStatementNode>> typedStatements;
        for (const auto &stmt : node.getStatements()) {
            stmt->accept(*this);
            if (auto typedStmt = std::dynamic_pointer_cast<TypedStatementNode>(lastNode)) {
                typedStatements.push_back(typedStmt);
            }
        }
        auto typedBlock = std::make_shared<TypedBlockNode>(std::move(typedStatements));
        typedBlock->setLocation(node.getLocation());
        lastNode = typedBlock;
    }

    void SemanticAnalyzer::visit(ExpressionStatementNode &node) {
        node.getExpression()->accept(*this);
        if (auto typedExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode)) {
            // RCW001: Warn if the result of a non-void expression is discarded (skip assignments)
            auto exprType = typedExpr->getType();
            if (exprType && exprType->getKind() != TypeKind::VOID && exprType->toString() != "unknown") {
                auto rawExpr = node.getExpression();
                if (!std::dynamic_pointer_cast<AssignmentNode>(rawExpr)) {
                    ErrorHandler::getInstance().makeWarning(
                        "[RCW001]: Result will be discarded.",
                        node.getLocation());
                }
            }

            auto typedStmt = std::make_shared<TypedExpressionStatementNode>(typedExpr);
            typedStmt->setLocation(node.getLocation());
            lastNode = typedStmt;
        } else {
            lastNode = nullptr;
        }
    }

    void SemanticAnalyzer::visit(StringLiteralNode &node) {
        auto stType    = std::make_shared<STType::StringType>();
        auto typedNode = std::make_shared<TypedStringLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(IntegerLiteralNode &node) {
        auto stType    = std::make_shared<STType::Int32Type>();
        auto typedNode = std::make_shared<TypedIntegerLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(LongLiteralNode &node) {
        auto stType    = std::make_shared<STType::Int64Type>();
        auto typedNode = std::make_shared<TypedLongLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(IdentifierNode &node) {
        auto name = node.getName();
        auto sym  = symbolTable.resolve(name);

        std::shared_ptr<Type> type;
        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "[RCE007]: Identifier '" + name + "' is not defined.",
                node.getLocation());
            type = TypeFactory::getPrimitive("unknown");
        } else if (auto funcSym = std::dynamic_pointer_cast<FunctionSymbol>(sym)) {
            std::vector<std::shared_ptr<Type>> paramTypes;
            for (const auto& p : funcSym->getParamTypes())
                paramTypes.push_back(toTypedType(p));
            type = TypeFactory::getFunction(toTypedType(funcSym->getReturnType()), paramTypes);
        } else if (auto overloadSet = std::dynamic_pointer_cast<OverloadSet>(sym)) {
            auto firstOverload = overloadSet->getFunctions().front();
            std::vector<std::shared_ptr<Type>> paramTypes;
            for (const auto& p : firstOverload->getParamTypes())
                paramTypes.push_back(toTypedType(p));
            type = TypeFactory::getFunction(toTypedType(firstOverload->getReturnType()), paramTypes);
        } else if (auto varSym = std::dynamic_pointer_cast<VariableSymbol>(sym)) {
            type = toTypedType(varSym->getType());
        } else {
            type = TypeFactory::getPrimitive("unknown");
        }

        auto typedNode = std::make_shared<TypedIdentifierNode>(name, type);
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(FunctionCallNode &node) {
        auto funcNameNode = node.getFunctionName();
        std::string funcName = funcNameNode->getName();

        auto sym = symbolTable.resolve(funcName);

        // Process arguments first to get their typed AST nodes
        const auto& args = node.getArguments();
        std::vector<std::shared_ptr<TypedExpressionNode>> typedArgs;
        for (size_t i = 0; i < args.size(); ++i) {
            args[i]->accept(*this);
            auto typedArg = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
            typedArgs.push_back(typedArg);
        }

        TypePtr stReturnType;
        std::vector<TypePtr> expectedParamTypes;

        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "[RCE008]: Function '" + funcName + "' is not defined.",
                node.getLocation());
            stReturnType = makeSTType("unknown");
        } else if (auto overloadSet = std::dynamic_pointer_cast<OverloadSet>(sym)) {
            bool found = false;

            // For __builtin_scan, use expectedReturnType from context if available
            if (funcName == "__builtin_scan" && expectedReturnType) {
                for (const auto& overload : overloadSet->getFunctions()) {
                    auto overloadRetTyped = toTypedType(overload->getReturnType());
                    if (overloadRetTyped->equals(*expectedReturnType)) {
                        stReturnType = overload->getReturnType();
                        expectedParamTypes = overload->getParamTypes();
                        found = true;
                        break;
                    }
                }
            }

            if (!found) for (const auto& overload : overloadSet->getFunctions()) {
                if (overload->getParamTypes().size() != args.size()) continue;

                bool match = true;
                for (size_t i = 0; i < args.size(); ++i) {
                    if (!typedArgs[i]) { match = false; break; }
                    auto expectedTyped = toTypedType(overload->getParamTypes()[i]);
                    if (!expectedTyped->equals(*typedArgs[i]->getType()) &&
                        typedArgs[i]->getType()->toString() != "unknown") {
                        match = false;
                        break;
                    }
                }

                if (match) {
                    stReturnType = overload->getReturnType();
                    expectedParamTypes = overload->getParamTypes();
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::string expectedTypes;
                for (const auto& overload : overloadSet->getFunctions()) {
                    if (!expectedTypes.empty()) expectedTypes += " or ";
                    expectedTypes += "'" + toTypedType(overload->getParamTypes()[0])->toString() + "'";
                }
                ErrorHandler::getInstance().makeError(
                    "[RCE009]: No matching overload for function '" + funcName +
                    "'. Expected " + expectedTypes + " argument, but got '" +
                    (typedArgs.empty() || !typedArgs[0] ? "unknown" : typedArgs[0]->getType()->toString()) + "'.",
                    node.getLocation());
                stReturnType = makeSTType("unknown");
                if (!overloadSet->getFunctions().empty()) {
                    expectedParamTypes = overloadSet->getFunctions()[0]->getParamTypes();
                }
            }
        } else if (auto funcSym = std::dynamic_pointer_cast<FunctionSymbol>(sym)) {
            stReturnType       = funcSym->getReturnType();
            expectedParamTypes = funcSym->getParamTypes();
        } else {
            ErrorHandler::getInstance().makeError(
                "[RCE010]: '" + funcName + "' is not a function.",
                node.getLocation());
            stReturnType = makeSTType("unknown");
        }

        auto returnType = toTypedType(stReturnType);

        // Check argument count
        if (sym && args.size() != expectedParamTypes.size() &&
            !std::dynamic_pointer_cast<OverloadSet>(sym)) {
            ErrorHandler::getInstance().makeError(
                "[RCE011]: Function '" + funcName + "' expects " +
                std::to_string(expectedParamTypes.size()) + " arguments, but got " +
                std::to_string(args.size()) + ".",
                node.getLocation());
        }

        // Type checking for each argument
        for (size_t i = 0; i < typedArgs.size(); ++i) {
            auto typedArg = typedArgs[i];
            if (!typedArg) continue;

            if (i < expectedParamTypes.size()) {
                auto expectedTyped = toTypedType(expectedParamTypes[i]);
                auto actualType    = typedArg->getType();
                if (!expectedTyped->equals(*actualType) &&
                    actualType->toString() != "unknown") {
                    ErrorHandler::getInstance().makeError(
                        "[RCE012]: Argument " + std::to_string(i + 1) +
                        " expects type '" + expectedTyped->toString() +
                        "', but got '" + actualType->toString() + "'.",
                        args[i]->getLocation());
                }
            }
        }

        std::vector<std::shared_ptr<Type>> paramTypeObjs;
        for (const auto& pt : expectedParamTypes)
            paramTypeObjs.push_back(toTypedType(pt));
        auto funcType = TypeFactory::getFunction(returnType, paramTypeObjs);

        auto typedFuncName = std::make_shared<TypedIdentifierNode>(funcName, funcType);
        typedFuncName->setLocation(funcNameNode->getLocation());

        auto typedCall = std::make_shared<TypedFunctionCallNode>(typedFuncName, typedArgs, returnType);
        typedCall->setLocation(node.getLocation());
        lastNode = typedCall;
    }

    void SemanticAnalyzer::visit(TypeSpecifierNode &node) {
        lastType = makeSTType(node.getName());
    }

    void SemanticAnalyzer::visit(VariableDeclarationNode &node) {
        auto varName = node.getName()->getName();

        node.getType()->accept(*this);
        auto varType = lastType ? lastType : makeSTType("unknown");

        std::shared_ptr<TypedExpressionNode> typedInit = nullptr;
        if (node.getInitializer()) {
            // Set expected return type for context-sensitive functions like __builtin_scan
            expectedReturnType = toTypedType(varType);
            node.getInitializer()->accept(*this);
            expectedReturnType = nullptr;
            typedInit = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

            if (typedInit) {
                auto expectedTyped = toTypedType(varType);
                auto actualType = typedInit->getType();
                // Allow implicit int → long widening promotion
                bool isAssignable = expectedTyped->equals(*actualType) ||
                    (actualType->toString() == "int" && expectedTyped->toString() == "long");
                if (!isAssignable && actualType->toString() != "unknown") {
                    ErrorHandler::getInstance().makeError(
                        "[RCE013]: Variable '" + varName + "' expects type '" +
                        expectedTyped->toString() + "', but initializer has type '" +
                        actualType->toString() + "'.",
                        node.getLocation());
                }
            }
        }

        auto varSym = std::make_shared<VariableSymbol>(varName, varType);
        symbolTable.define(varSym, node.getLocation());

        auto typedDecl = std::make_shared<TypedVariableDeclarationNode>(varName, toTypedType(varType), typedInit);
        typedDecl->setLocation(node.getLocation());
        lastNode = typedDecl;
    }

    void SemanticAnalyzer::visit(VariableNode &node) {
        auto varName = node.getName()->getName();
        auto sym = symbolTable.resolve(varName);

        std::shared_ptr<Type> type;
        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "[RCE014]: Variable '" + varName + "' is not defined.",
                node.getLocation());
            type = TypeFactory::getPrimitive("unknown");
        } else if (auto varSym = std::dynamic_pointer_cast<VariableSymbol>(sym)) {
            type = toTypedType(varSym->getType());
        } else {
            ErrorHandler::getInstance().makeError(
                "[RCE015]: '" + varName + "' is not a variable.",
                node.getLocation());
            type = TypeFactory::getPrimitive("unknown");
        }

        auto typedVar = std::make_shared<TypedVariableNode>(varName, type);
        typedVar->setLocation(node.getLocation());
        lastNode = typedVar;
    }

    void SemanticAnalyzer::visit(UnaryOpNode &node) {
        node.getOperand()->accept(*this);
        auto typedOperand = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedOperand) {
            lastNode = nullptr;
            return;
        }

        auto intType = TypeFactory::getPrimitive("int");
        auto longType = TypeFactory::getPrimitive("long");
        bool isInt = typedOperand->getType()->equals(*intType);
        bool isLong = typedOperand->getType()->equals(*longType);
        if (!isInt && !isLong) {
            ErrorHandler::getInstance().makeError(
                "[RCE019]: Unary operator '~' requires 'int' or 'long' operand, but got '" +
                typedOperand->getType()->toString() + "'.",
                node.getOperand()->getLocation());
        }

        auto resultType = isLong ? longType : intType;  // ~int -> int, ~long -> long
        auto typedUnary = std::make_shared<TypedUnaryOpNode>(
            node.getOp(), typedOperand, resultType);
        typedUnary->setLocation(node.getLocation());
        lastNode = typedUnary;
    }

    void SemanticAnalyzer::visit(BinaryOpNode &node) {
        node.getLeft()->accept(*this);
        auto typedLeft = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        node.getRight()->accept(*this);
        auto typedRight = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (!typedLeft || !typedRight) {
            lastNode = nullptr;
            return;
        }

        auto intType = TypeFactory::getPrimitive("int");
        auto longType = TypeFactory::getPrimitive("long");
        bool leftIsInt = typedLeft->getType()->equals(*intType);
        bool rightIsInt = typedRight->getType()->equals(*intType);
        bool leftIsLong = typedLeft->getType()->equals(*longType);
        bool rightIsLong = typedRight->getType()->equals(*longType);

        if (!leftIsInt && !leftIsLong) {
            ErrorHandler::getInstance().makeError(
                "[RCE016]: Left operand of binary expression must be 'int' or 'long', but got '" +
                typedLeft->getType()->toString() + "'.",
                node.getLeft()->getLocation());
        }
        if (!rightIsInt && !rightIsLong) {
            ErrorHandler::getInstance().makeError(
                "[RCE017]: Right operand of binary expression must be 'int' or 'long', but got '" +
                typedRight->getType()->toString() + "'.",
                node.getRight()->getLocation());
        }

        // Result type: long if either operand is long, otherwise int
        std::shared_ptr<Type> resultType;
        if ((leftIsLong || rightIsLong) && (leftIsInt || leftIsLong) && (rightIsInt || rightIsLong)) {
            resultType = longType;
        } else if (leftIsInt && rightIsInt) {
            resultType = intType;
        } else {
            resultType = TypeFactory::getPrimitive("unknown");
        }

        auto typedBinOp = std::make_shared<TypedBinaryOpNode>(typedLeft, node.getOp(), typedRight, resultType);
        typedBinOp->setLocation(node.getLocation());
        lastNode = typedBinOp;
    }

    void SemanticAnalyzer::visit(CastNode &node) {
        node.getOperand()->accept(*this);
        auto typedOperand = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedOperand) {
            lastNode = nullptr;
            return;
        }

        node.getTargetType()->accept(*this);
        auto targetSTType = lastType;
        if (!targetSTType) {
            lastNode = nullptr;
            return;
        }

        auto targetTyped = toTypedType(targetSTType);
        auto operandType = typedOperand->getType();

        auto intType = TypeFactory::getPrimitive("int");
        auto longType = TypeFactory::getPrimitive("long");

        bool castValid = false;
        if (operandType->equals(*intType) && targetTyped->equals(*longType))
            castValid = true;
        else if (operandType->equals(*longType) && targetTyped->equals(*intType))
            castValid = true;
        else if (operandType->equals(*targetTyped))
            castValid = true;

        if (!castValid && operandType->toString() != "unknown") {
            ErrorHandler::getInstance().makeError(
                "[RCE020]: Cannot cast from '" + operandType->toString() +
                "' to '" + targetTyped->toString() + "'.",
                node.getLocation());
        }

        // RCW002: Warn when casting from a larger type to a smaller type (truncation)
        if (operandType->equals(*longType) && targetTyped->equals(*intType)) {
            ErrorHandler::getInstance().makeWarning(
                "[RCW002]: Result of this casting operation will be truncated.",
                node.getLocation());
        }

        auto typedCast = std::make_shared<TypedCastNode>(typedOperand, targetTyped);
        typedCast->setLocation(node.getLocation());
        lastNode = typedCast;
    }

    void SemanticAnalyzer::visit(AssignmentNode &node) {
        auto varName = node.getLHS()->getName();
        auto sym = symbolTable.resolve(varName);

        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "[RCE014]: Variable '" + varName + "' is not defined.",
                node.getLHS()->getLocation());
            lastNode = nullptr;
            return;
        }

        auto varSym = std::dynamic_pointer_cast<VariableSymbol>(sym);
        if (!varSym) {
            ErrorHandler::getInstance().makeError(
                "[RCE015]: '" + varName + "' is not a variable.",
                node.getLHS()->getLocation());
            lastNode = nullptr;
            return;
        }

        node.getRHS()->accept(*this);
        auto typedRHS = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (!typedRHS) {
            lastNode = nullptr;
            return;
        }

        auto varType = toTypedType(varSym->getType());
        auto rhsType = typedRHS->getType();

        // Allow implicit int → long widening promotion
        bool isAssignable = varType->equals(*rhsType) ||
            (rhsType->toString() == "int" && varType->toString() == "long");
        if (!isAssignable && rhsType->toString() != "unknown") {
            ErrorHandler::getInstance().makeError(
                "[RCE018]: Cannot assign value of type '" + rhsType->toString() +
                "' to variable '" + varName + "' of type '" + varType->toString() + "'.",
                node.getRHS()->getLocation());
        }

        auto resultType = isAssignable ? varType : TypeFactory::getPrimitive("unknown");
        auto typedAssign = std::make_shared<TypedAssignmentNode>(varName, typedRHS, resultType);
        typedAssign->setLocation(node.getLocation());
        lastNode = typedAssign;
    }

} // namespace Ryntra::Compiler::Semantic
