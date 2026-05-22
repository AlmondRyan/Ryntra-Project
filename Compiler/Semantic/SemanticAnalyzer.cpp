#include "SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace Ryntra::Compiler::Semantic {
    TypePtr SemanticAnalyzer::makeSTType(const std::string &name) {
        if (name == "void")
            return std::make_shared<STType::VoidType>();
        if (name == "string")
            return std::make_shared<STType::StringType>();
        if (name == "long")
            return std::make_shared<STType::Int64Type>();
        if (name == "bool")
            return std::make_shared<STType::BoolType>();
        if (name.rfind("ref<", 0) == 0 && name.size() > 5 && name.back() == '>') {
            auto innerName = name.substr(4, name.size() - 5);
            auto innerType = makeSTType(innerName);
            return std::make_shared<STType::ReferenceType>(innerType);
        }
        if (name.rfind("ptr<", 0) == 0 && name.size() > 5 && name.back() == '>') {
            auto innerName = name.substr(4, name.size() - 5);
            auto innerType = makeSTType(innerName);
            return std::make_shared<STType::PointerType>(innerType);
        }
        // int / int32 both map to Int32
        return std::make_shared<STType::Int32Type>();
    }

    std::string SemanticAnalyzer::getPtrVarName(const std::shared_ptr<TypedExpressionNode> &expr,
                                                  const SourceLocation &loc) {
        if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(expr)) {
            return varNode->getName();
        }
        if (auto ptrCreateNode = std::dynamic_pointer_cast<TypedPtrCreateNode>(expr)) {
            return ptrCreateNode->getVariableName();
        }
        if (auto ptrOffsetNode = std::dynamic_pointer_cast<TypedPtrOffsetNode>(expr)) {
            return ptrOffsetNode->getPtrVarName();
        }
        ErrorHandler::getInstance().makeError(
            "[RCE059]: Expected a pointer variable or pointer expression.",
            loc);
        return "";
    }

    std::shared_ptr<Type> SemanticAnalyzer::toTypedType(const TypePtr &stType) {
        if (!stType)
            return TypeFactory::getPrimitive("unknown");
        switch (stType->getKind()) {
        case STType::TypeKind::Void:
            return TypeFactory::getVoid();
        case STType::TypeKind::String:
            return TypeFactory::getPrimitive("string");
        case STType::TypeKind::Int32:
            return TypeFactory::getPrimitive("int");
        case STType::TypeKind::Int64:
            return TypeFactory::getPrimitive("long");
        case STType::TypeKind::Bool:
            return TypeFactory::getPrimitive("bool");
        case STType::TypeKind::Array: {
            auto &arrSTType = static_cast<const STType::ArrayType &>(*stType);
            return TypeFactory::getArray(toTypedType(arrSTType.getElementType()));
        }
        case STType::TypeKind::Reference: {
            auto &refSTType = static_cast<const STType::ReferenceType &>(*stType);
            return TypeFactory::getReference(toTypedType(refSTType.getElementType()));
        }
        case STType::TypeKind::Pointer: {
            auto &ptrSTType = static_cast<const STType::PointerType &>(*stType);
            return TypeFactory::getPointer(toTypedType(ptrSTType.getElementType()));
        }
        default:
            return TypeFactory::getPrimitive("unknown");
        }
    }

    void SemanticAnalyzer::analyze(const std::shared_ptr<IASTNode> &root) {
        if (!root)
            return;
        root->accept(*this);
    }

    void SemanticAnalyzer::visit(ProgramNode &node) {
        // First pass: register all user-defined functions
        for (const auto &func : node.getFunctions()) {
            auto funcName = func->getName()->getName();
            auto returnTypeName = func->getReturnType()->getName();
            auto returnType = makeSTType(returnTypeName);

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
                std::vector<TypePtr> params{std::make_shared<STType::StringType>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_print",
                                                                          std::make_shared<STType::VoidType>(), std::move(params)));
            }

            // Overload 2: __builtin_print(int) — already supported via builtin_print_i32
            {
                std::vector<TypePtr> params{std::make_shared<STType::Int32Type>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_print",
                                                                          std::make_shared<STType::VoidType>(), std::move(params)));
            }

            // Overload 3: __builtin_print(long)
            {
                std::vector<TypePtr> params{std::make_shared<STType::Int64Type>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_print",
                                                                          std::make_shared<STType::VoidType>(), std::move(params)));
            }

            // Overload 4: __builtin_print(bool)
            {
                std::vector<TypePtr> params{std::make_shared<STType::BoolType>()};
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

            // Overload 3: __builtin_scan() → bool
            {
                std::vector<TypePtr> params{};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_scan",
                                                                          std::make_shared<STType::BoolType>(), std::move(params)));
            }

            symbolTable.define(overloadSet, SourceLocation{0, 0});
        }

        // Also register plain "print" for backward compatibility
        if (!symbolTable.resolve("print")) {
            auto overloadSet = std::make_shared<OverloadSet>("print");

            // Overload 1: print(string)
            {
                std::vector<TypePtr> params{std::make_shared<STType::StringType>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("print",
                                                                          std::make_shared<STType::VoidType>(), std::move(params)));
            }

            // Overload 2: print(int) — already supported via builtin_print_i32
            {
                std::vector<TypePtr> params{std::make_shared<STType::Int32Type>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("print",
                                                                          std::make_shared<STType::VoidType>(), std::move(params)));
            }

            // Overload 3: print(long)
            {
                std::vector<TypePtr> params{std::make_shared<STType::Int64Type>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("print",
                                                                          std::make_shared<STType::VoidType>(), std::move(params)));
            }

            // Overload 4: print(bool)
            {
                std::vector<TypePtr> params{std::make_shared<STType::BoolType>()};
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
                    "[RCE005]: 'main' function must return 'void'.", node.getLocation());
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
                auto actualType = typedExpr->getType();

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

    void SemanticAnalyzer::visit(IfNode &node) {
        node.getCondition()->accept(*this);
        auto typedCond = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (typedCond) {
            auto boolType = TypeFactory::getPrimitive("bool");
            if (!typedCond->getType()->equals(*boolType) && typedCond->getType()->toString() != "unknown") {
                ErrorHandler::getInstance().makeError(
                    "[RCE023]: If condition must be 'bool', but got '" +
                        typedCond->getType()->toString() + "'.",
                    node.getCondition()->getLocation());
            }
        }

        node.getThenBlock()->accept(*this);
        auto typedThen = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);

        std::shared_ptr<TypedStatementNode> typedElse = nullptr;
        if (node.getElseBranch()) {
            node.getElseBranch()->accept(*this);
            typedElse = std::dynamic_pointer_cast<TypedStatementNode>(lastNode);
        }

        auto typedIf = std::make_shared<TypedIfNode>(typedCond, typedThen, typedElse);
        typedIf->setLocation(node.getLocation());
        lastNode = typedIf;
    }

    void SemanticAnalyzer::visit(WhileNode &node) {
        node.getCondition()->accept(*this);
        auto typedCond = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (typedCond) {
            auto boolType = TypeFactory::getPrimitive("bool");
            if (!typedCond->getType()->equals(*boolType) && typedCond->getType()->toString() != "unknown") {
                ErrorHandler::getInstance().makeError(
                    "[RCE024]: While condition must be 'bool', but got '" +
                        typedCond->getType()->toString() + "'.",
                    node.getCondition()->getLocation());
            }
        }

        ++loopDepth_;
        node.getBody()->accept(*this);
        --loopDepth_;
        auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);

        auto typedWhile = std::make_shared<TypedWhileNode>(typedCond, typedBody);
        typedWhile->setLocation(node.getLocation());
        lastNode = typedWhile;
    }

    void SemanticAnalyzer::visit(ForNode &node) {
        symbolTable.enterScope();

        std::shared_ptr<TypedStatementNode> typedInit = nullptr;
        if (node.getInit()) {
            node.getInit()->accept(*this);
            typedInit = std::dynamic_pointer_cast<TypedStatementNode>(lastNode);
        }

        std::shared_ptr<TypedExpressionNode> typedCond = nullptr;
        if (node.getCondition()) {
            node.getCondition()->accept(*this);
            typedCond = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

            if (typedCond) {
                auto boolType = TypeFactory::getPrimitive("bool");
                if (!typedCond->getType()->equals(*boolType) && typedCond->getType()->toString() != "unknown") {
                    ErrorHandler::getInstance().makeError(
                        "[RCE031]: For-loop condition must be 'bool', but got '" +
                            typedCond->getType()->toString() + "'.",
                        node.getCondition()->getLocation());
                }
            }
        }

        std::shared_ptr<TypedExpressionNode> typedOp = nullptr;
        if (node.getOperation()) {
            node.getOperation()->accept(*this);
            typedOp = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        }

        ++loopDepth_;
        node.getBody()->accept(*this);
        --loopDepth_;
        auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);

        symbolTable.exitScope();

        auto typedFor = std::make_shared<TypedForNode>(typedInit, typedCond, typedOp, typedBody);
        typedFor->setLocation(node.getLocation());
        lastNode = typedFor;
    }

    void SemanticAnalyzer::visit(BreakNode &node) {
        if (loopDepth_ == 0) {
            ErrorHandler::getInstance().makeError(
                "[RCE025]: 'break' outside of loop.", node.getLocation());
            lastNode = nullptr;
            return;
        }
        auto typedBreak = std::make_shared<TypedBreakNode>();
        typedBreak->setLocation(node.getLocation());
        lastNode = typedBreak;
    }

    void SemanticAnalyzer::visit(ContinueNode &node) {
        if (loopDepth_ == 0) {
            ErrorHandler::getInstance().makeError(
                "[RCE026]: 'continue' outside of loop.", node.getLocation());
            lastNode = nullptr;
            return;
        }
        auto typedContinue = std::make_shared<TypedContinueNode>();
        typedContinue->setLocation(node.getLocation());
        lastNode = typedContinue;
    }

    void SemanticAnalyzer::visit(ExpressionStatementNode &node) {
        node.getExpression()->accept(*this);
        if (auto typedExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode)) {
            // RCW001: Warn if the result of a non-void expression is discarded (skip assignments)
            auto exprType = typedExpr->getType();
            if (exprType && exprType->getKind() != TypeKind::VOID && exprType->toString() != "unknown") {
                auto rawExpr = node.getExpression();
            if (!std::dynamic_pointer_cast<AssignmentNode>(rawExpr) &&
                !std::dynamic_pointer_cast<ArrayIndexAssignmentNode>(rawExpr) &&
                !std::dynamic_pointer_cast<PrefixOpNode>(rawExpr) &&
                !std::dynamic_pointer_cast<PostfixOpNode>(rawExpr)) {
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
        auto stType = std::make_shared<STType::StringType>();
        auto typedNode = std::make_shared<TypedStringLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(NullLiteralNode &node) {
        // null gets a special "null" type — it will be checked against ptr<T>
        // when used in assignments or comparisons
        auto typedNode = std::make_shared<TypedNullLiteralNode>(
            TypeFactory::getPrimitive("null"));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(BoolLiteralNode &node) {
        auto stType = std::make_shared<STType::BoolType>();
        auto typedNode = std::make_shared<TypedBoolLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(IntegerLiteralNode &node) {
        auto stType = std::make_shared<STType::Int32Type>();
        auto typedNode = std::make_shared<TypedIntegerLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(LongLiteralNode &node) {
        auto stType = std::make_shared<STType::Int64Type>();
        auto typedNode = std::make_shared<TypedLongLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(IdentifierNode &node) {
        auto name = node.getName();
        auto sym = symbolTable.resolve(name);

        std::shared_ptr<Type> type;
        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "[RCE007]: Identifier '" + name + "' is not defined.",
                node.getLocation());
            type = TypeFactory::getPrimitive("unknown");
        } else if (auto funcSym = std::dynamic_pointer_cast<FunctionSymbol>(sym)) {
            std::vector<std::shared_ptr<Type>> paramTypes;
            for (const auto &p : funcSym->getParamTypes())
                paramTypes.push_back(toTypedType(p));
            type = TypeFactory::getFunction(toTypedType(funcSym->getReturnType()), paramTypes);
        } else if (auto overloadSet = std::dynamic_pointer_cast<OverloadSet>(sym)) {
            auto firstOverload = overloadSet->getFunctions().front();
            std::vector<std::shared_ptr<Type>> paramTypes;
            for (const auto &p : firstOverload->getParamTypes())
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
        const auto &args = node.getArguments();
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
                for (const auto &overload : overloadSet->getFunctions()) {
                    auto overloadRetTyped = toTypedType(overload->getReturnType());
                    if (overloadRetTyped->equals(*expectedReturnType)) {
                        stReturnType = overload->getReturnType();
                        expectedParamTypes = overload->getParamTypes();
                        found = true;
                        break;
                    }
                }
            }

            if (!found)
                for (const auto &overload : overloadSet->getFunctions()) {
                    if (overload->getParamTypes().size() != args.size())
                        continue;

                    bool match = true;
                    for (size_t i = 0; i < args.size(); ++i) {
                        if (!typedArgs[i]) {
                            match = false;
                            break;
                        }
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
                for (const auto &overload : overloadSet->getFunctions()) {
                    if (!expectedTypes.empty())
                        expectedTypes += " or ";
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
            stReturnType = funcSym->getReturnType();
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
            if (!typedArg)
                continue;

            if (i < expectedParamTypes.size()) {
                auto expectedTyped = toTypedType(expectedParamTypes[i]);
                auto actualType = typedArg->getType();
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
        for (const auto &pt : expectedParamTypes)
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

    void SemanticAnalyzer::visit(RefExpressionNode &node) {
        node.getOperand()->accept(*this);
        auto typedOperand = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedOperand) {
            lastNode = nullptr;
            return;
        }

        auto operandType = typedOperand->getType();
        auto refType = TypeFactory::getReference(operandType);

        std::string targetVarName;
        if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(typedOperand)) {
            targetVarName = varNode->getName();
        } else if (auto refLoadNode = std::dynamic_pointer_cast<TypedRefLoadNode>(typedOperand)) {
            targetVarName = refLoadNode->getVariableName();
        } else {
            ErrorHandler::getInstance().makeError(
                "[RCE044]: 'ref' requires a variable operand.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        auto typedRef = std::make_shared<TypedRefCreateNode>(targetVarName, refType);
        typedRef->setLocation(node.getLocation());
        lastNode = typedRef;
    }

    void SemanticAnalyzer::visit(UnsafeBlockNode &node) {
        ++unsafeDepth_;
        node.getBody()->accept(*this);
        --unsafeDepth_;
        if (auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode)) {
            auto typedUnsafe = std::make_shared<TypedUnsafeBlockNode>(typedBody);
            typedUnsafe->setLocation(node.getLocation());
            lastNode = typedUnsafe;
        } else {
            lastNode = nullptr;
        }
    }

    void SemanticAnalyzer::visit(PtrExpressionNode &node) {
        if (unsafeDepth_ == 0) {
            ErrorHandler::getInstance().makeError(
                "[RCE046]: 'ptr' expression is only allowed inside 'unsafe' blocks.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        node.getOperand()->accept(*this);
        auto typedOperand = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedOperand) {
            lastNode = nullptr;
            return;
        }

        auto operandType = typedOperand->getType();
        auto ptrType = TypeFactory::getPointer(operandType);

        std::string targetVarName;
        if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(typedOperand)) {
            targetVarName = varNode->getName();
        } else if (auto refLoadNode = std::dynamic_pointer_cast<TypedRefLoadNode>(typedOperand)) {
            targetVarName = refLoadNode->getVariableName();
        } else {
            ErrorHandler::getInstance().makeError(
                "[RCE047]: 'ptr' requires a variable operand.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        auto typedPtr = std::make_shared<TypedPtrCreateNode>(targetVarName, ptrType);
        typedPtr->setLocation(node.getLocation());
        lastNode = typedPtr;
    }

    void SemanticAnalyzer::visit(PtrLoadNode &node) {
        if (unsafeDepth_ == 0) {
            ErrorHandler::getInstance().makeError(
                "[RCE048]: '.load()' is only allowed inside 'unsafe' blocks.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        node.getPtrExpression()->accept(*this);
        auto typedPtrExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedPtrExpr) {
            lastNode = nullptr;
            return;
        }

        auto ptrExprType = typedPtrExpr->getType();
        if (ptrExprType->getKind() != TypeKind::POINTER && ptrExprType->toString() != "unknown") {
            ErrorHandler::getInstance().makeError(
                "[RCE049]: '.load()' requires a pointer expression, but got '" +
                    ptrExprType->toString() + "'.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        std::string ptrVarName;
        if (auto ptrCreateNode = std::dynamic_pointer_cast<TypedPtrCreateNode>(typedPtrExpr)) {
            ptrVarName = ptrCreateNode->getVariableName();
        } else if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(typedPtrExpr)) {
            ptrVarName = varNode->getName();
        } else {
            ErrorHandler::getInstance().makeError(
                "[RCE050]: '.load()' requires a pointer variable.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        auto elemType = std::dynamic_pointer_cast<PointerType>(ptrExprType)->getElementType();
        auto typedPtrLoad = std::make_shared<TypedPtrLoadNode>(ptrVarName, elemType);
        typedPtrLoad->setLocation(node.getLocation());
        lastNode = typedPtrLoad;
    }

    void SemanticAnalyzer::visit(PtrStoreNode &node) {
        if (unsafeDepth_ == 0) {
            ErrorHandler::getInstance().makeError(
                "[RCE051]: '.store()' is only allowed inside 'unsafe' blocks.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        node.getPtrExpression()->accept(*this);
        auto typedPtrExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedPtrExpr) {
            lastNode = nullptr;
            return;
        }

        auto ptrExprType = typedPtrExpr->getType();
        if (ptrExprType->getKind() != TypeKind::POINTER && ptrExprType->toString() != "unknown") {
            ErrorHandler::getInstance().makeError(
                "[RCE052]: '.store()' requires a pointer expression, but got '" +
                    ptrExprType->toString() + "'.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        std::string ptrVarName;
        if (auto ptrCreateNode = std::dynamic_pointer_cast<TypedPtrCreateNode>(typedPtrExpr)) {
            ptrVarName = ptrCreateNode->getVariableName();
        } else if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(typedPtrExpr)) {
            ptrVarName = varNode->getName();
        } else {
            ErrorHandler::getInstance().makeError(
                "[RCE053]: '.store()' requires a pointer variable.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        auto elemType = std::dynamic_pointer_cast<PointerType>(ptrExprType)->getElementType();

        node.getValue()->accept(*this);
        auto typedValue = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedValue) {
            lastNode = nullptr;
            return;
        }

        bool isAssignable = elemType->equals(*typedValue->getType()) ||
                            (typedValue->getType()->toString() == "int" && elemType->toString() == "long");
        if (!isAssignable && typedValue->getType()->toString() != "unknown") {
            ErrorHandler::getInstance().makeError(
                "[RCE054]: Cannot store value of type '" + typedValue->getType()->toString() +
                    "' to pointer of type '" + elemType->toString() + "'.",
                node.getValue()->getLocation());
        }

        auto resultType = isAssignable ? elemType : TypeFactory::getPrimitive("unknown");
        auto typedPtrStore = std::make_shared<TypedPtrStoreNode>(ptrVarName, typedValue, resultType);
        typedPtrStore->setLocation(node.getLocation());
        lastNode = typedPtrStore;
    }

    void SemanticAnalyzer::visit(ArrayTypeNode &node) {
        node.getElementType()->accept(*this);
        auto elemType = lastType;
        if (elemType) {
            lastType = std::make_shared<STType::ArrayType>(elemType);
        } else {
            lastType = nullptr;
        }
    }

    void SemanticAnalyzer::visit(ReferenceTypeNode &node) {
        node.getElementType()->accept(*this);
        auto elemType = lastType;
        if (elemType) {
            lastType = std::make_shared<STType::ReferenceType>(elemType);
        } else {
            lastType = nullptr;
        }
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
                // Allow null initializer for ptr<T> variables
                if (!isAssignable && actualType->toString() == "null" && expectedTyped->getKind() == TypeKind::POINTER) {
                    isAssignable = true;
                }
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

    void SemanticAnalyzer::visit(ArrayDeclarationNode &node) {
        auto varName = node.getName()->getName();

        node.getArrayType()->accept(*this);
        auto arrayType = lastType;
        if (!arrayType) {
            lastNode = nullptr;
            return;
        }

        // Check element type from "new type[size]" matches declaration type
        node.getElementType()->accept(*this);
        auto newElemType = lastType;
        if (!newElemType) {
            lastNode = nullptr;
            return;
        }

        auto declElemType = std::dynamic_pointer_cast<STType::ArrayType>(arrayType)->getElementType();
        if (declElemType->getKind() != newElemType->getKind()) {
            ErrorHandler::getInstance().makeError(
                "[RCE033]: Array element type mismatch. Declaration has '" +
                    toTypedType(declElemType)->toString() + "', but 'new' has '" +
                    toTypedType(newElemType)->toString() + "'.",
                node.getLocation());
        }

        // Visit size expression
        expectedReturnType = TypeFactory::getPrimitive("int");
        node.getSize()->accept(*this);
        expectedReturnType = nullptr;
        auto typedSize = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (typedSize) {
            auto intType = TypeFactory::getPrimitive("int");
            auto longType = TypeFactory::getPrimitive("long");
            auto sizeType = typedSize->getType();
            if (!sizeType->equals(*intType) && !sizeType->equals(*longType) && sizeType->toString() != "unknown") {
                ErrorHandler::getInstance().makeError(
                    "[RCE034]: Array size must be 'int' or 'long', but got '" +
                        sizeType->toString() + "'.",
                    node.getSize()->getLocation());
            }
        }

        // Define array variable in symbol table
        auto varSym = std::make_shared<VariableSymbol>(varName, arrayType);
        symbolTable.define(varSym, node.getLocation());

        auto typedDecl = std::make_shared<TypedArrayDeclarationNode>(varName, toTypedType(declElemType), typedSize);
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
            auto varSTType = varSym->getType();
            // Auto-dereference ref<T> to T when used as an rvalue expression
            if (varSTType->getKind() == STType::TypeKind::Reference) {
                auto &refSTType = static_cast<const STType::ReferenceType &>(*varSTType);
                auto derefType = toTypedType(refSTType.getElementType());
                auto typedRefLoad = std::make_shared<TypedRefLoadNode>(varName, derefType);
                typedRefLoad->setLocation(node.getLocation());
                lastNode = typedRefLoad;
                return;
            }
            type = toTypedType(varSTType);
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

    void SemanticAnalyzer::visit(ArrayIndexAccessNode &node) {
        auto arrayName = node.getArrayName()->getName();
        auto sym = symbolTable.resolve(arrayName);

        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "[RCE035]: Array '" + arrayName + "' is not defined.",
                node.getArrayName()->getLocation());
            lastNode = nullptr;
            return;
        }

        auto varSym = std::dynamic_pointer_cast<VariableSymbol>(sym);
        if (!varSym) {
            ErrorHandler::getInstance().makeError(
                "[RCE036]: '" + arrayName + "' is not a variable.",
                node.getArrayName()->getLocation());
            lastNode = nullptr;
            return;
        }

        auto varSTType = varSym->getType();
        if (varSTType->getKind() != STType::TypeKind::Array) {
            ErrorHandler::getInstance().makeError(
                "[RCE037]: '" + arrayName + "' is not an array.",
                node.getArrayName()->getLocation());
            lastNode = nullptr;
            return;
        }

        auto arrSTType = std::dynamic_pointer_cast<STType::ArrayType>(varSTType);
        auto elemType = toTypedType(arrSTType->getElementType());

        // Visit index expression
        node.getIndex()->accept(*this);
        auto typedIndex = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (typedIndex) {
            auto intType = TypeFactory::getPrimitive("int");
            auto longType = TypeFactory::getPrimitive("long");
            if (!typedIndex->getType()->equals(*intType) && !typedIndex->getType()->equals(*longType) && typedIndex->getType()->toString() != "unknown") {
                ErrorHandler::getInstance().makeError(
                    "[RCE038]: Array index must be 'int' or 'long', but got '" +
                        typedIndex->getType()->toString() + "'.",
                    node.getIndex()->getLocation());
            }
        }

        auto typedAccess = std::make_shared<TypedArrayIndexAccessNode>(arrayName, typedIndex, elemType);
        typedAccess->setLocation(node.getLocation());
        lastNode = typedAccess;
    }

    void SemanticAnalyzer::visit(ArrayIndexAssignmentNode &node) {
        auto arrayName = node.getArrayName()->getName();
        auto sym = symbolTable.resolve(arrayName);

        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "[RCE039]: Array '" + arrayName + "' is not defined.",
                node.getArrayName()->getLocation());
            lastNode = nullptr;
            return;
        }

        auto varSym = std::dynamic_pointer_cast<VariableSymbol>(sym);
        if (!varSym) {
            ErrorHandler::getInstance().makeError(
                "[RCE040]: '" + arrayName + "' is not a variable.",
                node.getArrayName()->getLocation());
            lastNode = nullptr;
            return;
        }

        auto varSTType = varSym->getType();
        if (varSTType->getKind() != STType::TypeKind::Array) {
            ErrorHandler::getInstance().makeError(
                "[RCE041]: '" + arrayName + "' is not an array.",
                node.getArrayName()->getLocation());
            lastNode = nullptr;
            return;
        }

        auto arrSTType = std::dynamic_pointer_cast<STType::ArrayType>(varSTType);
        auto elemSTType = arrSTType->getElementType();
        auto elemTyped = toTypedType(elemSTType);

        // Visit index expression
        node.getIndex()->accept(*this);
        auto typedIndex = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedIndex) {
            lastNode = nullptr;
            return;
        }

        auto intType = TypeFactory::getPrimitive("int");
        auto longType = TypeFactory::getPrimitive("long");
        if (!typedIndex->getType()->equals(*intType) && !typedIndex->getType()->equals(*longType) && typedIndex->getType()->toString() != "unknown") {
            ErrorHandler::getInstance().makeError(
                "[RCE042]: Array index must be 'int' or 'long', but got '" +
                    typedIndex->getType()->toString() + "'.",
                node.getIndex()->getLocation());
        }

        // Visit value expression
        node.getValue()->accept(*this);
        auto typedValue = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedValue) {
            lastNode = nullptr;
            return;
        }

        // Type check
        bool isAssignable = elemTyped->equals(*typedValue->getType()) ||
                            (typedValue->getType()->toString() == "int" && elemTyped->toString() == "long");
        if (!isAssignable && typedValue->getType()->toString() != "unknown") {
            ErrorHandler::getInstance().makeError(
                "[RCE043]: Cannot assign value of type '" + typedValue->getType()->toString() +
                    "' to array element of type '" + elemTyped->toString() + "'.",
                node.getValue()->getLocation());
        }

        auto resultType = isAssignable ? elemTyped : TypeFactory::getPrimitive("unknown");
        auto typedAssign = std::make_shared<TypedArrayIndexAssignmentNode>(arrayName, typedIndex, typedValue, resultType);
        typedAssign->setLocation(node.getLocation());
        lastNode = typedAssign;
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
        auto boolType = TypeFactory::getPrimitive("bool");

        if (node.getOp() == UnaryOpType::LogicalNot) {
            if (!typedOperand->getType()->equals(*boolType)) {
                ErrorHandler::getInstance().makeError(
                    "[RCE020]: Unary operator '!' requires 'bool' operand, but got '" +
                        typedOperand->getType()->toString() + "'.",
                    node.getOperand()->getLocation());
            }
            auto typedUnary = std::make_shared<TypedUnaryOpNode>(
                node.getOp(), typedOperand, boolType);
            typedUnary->setLocation(node.getLocation());
            lastNode = typedUnary;
            return;
        }

        bool isInt = typedOperand->getType()->equals(*intType);
        bool isLong = typedOperand->getType()->equals(*longType);

        if (node.getOp() == UnaryOpType::Negate) {
            if (!isInt && !isLong) {
                ErrorHandler::getInstance().makeError(
                    "[RCE032]: Unary operator '-' requires 'int' or 'long' operand, but got '" +
                        typedOperand->getType()->toString() + "'.",
                    node.getOperand()->getLocation());
            }
            auto resultType = isLong ? longType : intType;
            auto typedUnary = std::make_shared<TypedUnaryOpNode>(
                node.getOp(), typedOperand, resultType);
            typedUnary->setLocation(node.getLocation());
            lastNode = typedUnary;
            return;
        }

        if (!isInt && !isLong) {
            ErrorHandler::getInstance().makeError(
                "[RCE019]: Unary operator '~' requires 'int' or 'long' operand, but got '" +
                    typedOperand->getType()->toString() + "'.",
                node.getOperand()->getLocation());
        }

        auto resultType = isLong ? longType : intType; // ~int -> int, ~long -> long
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

        auto leftType = typedLeft->getType();
        auto rightType = typedRight->getType();
        bool leftIsPtr = leftType->getKind() == TypeKind::POINTER;
        bool rightIsPtr = rightType->getKind() == TypeKind::POINTER;

        // Detect pointer arithmetic: ptr + int, ptr - int, ptr - ptr
        if ((leftIsPtr || rightIsPtr) && (node.getOp() == BinaryOpType::Add || node.getOp() == BinaryOpType::Sub)) {
            if (unsafeDepth_ == 0) {
                ErrorHandler::getInstance().makeError(
                    "[RCE057]: Pointer arithmetic is only allowed inside 'unsafe' blocks.",
                    node.getLocation());
                lastNode = nullptr;
                return;
            }

            auto intType = TypeFactory::getPrimitive("int");
            auto longType = TypeFactory::getPrimitive("long");
            bool offsetIsInt = false;
            bool offsetIsLong = false;

            // ptr + int / int + ptr
            if (node.getOp() == BinaryOpType::Add) {
                if (leftIsPtr && (typedRight->getType()->equals(*intType) || typedRight->getType()->equals(*longType))) {
                    offsetIsInt = typedRight->getType()->equals(*intType);
                    offsetIsLong = typedRight->getType()->equals(*longType);
                    std::string ptrVarName = getPtrVarName(typedLeft, node.getLeft()->getLocation());
                    if (ptrVarName.empty()) { lastNode = nullptr; return; }
                    auto typedOffset = std::make_shared<TypedPtrOffsetNode>(ptrVarName, typedRight, true, leftType);
                    typedOffset->setLocation(node.getLocation());
                    lastNode = typedOffset;
                    return;
                } else if (rightIsPtr && (typedLeft->getType()->equals(*intType) || typedLeft->getType()->equals(*longType))) {
                    offsetIsInt = typedLeft->getType()->equals(*intType);
                    offsetIsLong = typedLeft->getType()->equals(*longType);
                    std::string ptrVarName = getPtrVarName(typedRight, node.getRight()->getLocation());
                    if (ptrVarName.empty()) { lastNode = nullptr; return; }
                    auto typedOffset = std::make_shared<TypedPtrOffsetNode>(ptrVarName, typedLeft, true, rightType);
                    typedOffset->setLocation(node.getLocation());
                    lastNode = typedOffset;
                    return;
                }
            }

            // ptr - int
            if (node.getOp() == BinaryOpType::Sub && leftIsPtr && !rightIsPtr) {
                if (typedRight->getType()->equals(*intType) || typedRight->getType()->equals(*longType)) {
                    std::string ptrVarName = getPtrVarName(typedLeft, node.getLeft()->getLocation());
                    if (ptrVarName.empty()) { lastNode = nullptr; return; }
                    auto typedOffset = std::make_shared<TypedPtrOffsetNode>(ptrVarName, typedRight, false, leftType);
                    typedOffset->setLocation(node.getLocation());
                    lastNode = typedOffset;
                    return;
                }
            }

            // ptr - ptr
            if (node.getOp() == BinaryOpType::Sub && leftIsPtr && rightIsPtr) {
                if (leftType->equals(*rightType)) {
                    std::string leftPtrName = getPtrVarName(typedLeft, node.getLeft()->getLocation());
                    std::string rightPtrName = getPtrVarName(typedRight, node.getRight()->getLocation());
                    if (leftPtrName.empty() || rightPtrName.empty()) { lastNode = nullptr; return; }
                    auto typedDiff = std::make_shared<TypedPtrDiffNode>(leftPtrName, rightPtrName, intType);
                    typedDiff->setLocation(node.getLocation());
                    lastNode = typedDiff;
                    return;
                } else {
                    ErrorHandler::getInstance().makeError(
                        "[RCE058]: Cannot subtract pointers of different types '" +
                            leftType->toString() + "' and '" + rightType->toString() + "'.",
                        node.getLocation());
                    lastNode = nullptr;
                    return;
                }
            }
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

    void SemanticAnalyzer::visit(ComparisonNode &node) {
        node.getLeft()->accept(*this);
        auto typedLeft = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        node.getRight()->accept(*this);
        auto typedRight = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (!typedLeft || !typedRight) {
            lastNode = nullptr;
            return;
        }

        // Detect ptr == null / ptr != null patterns
        auto leftType = typedLeft->getType();
        auto rightType = typedRight->getType();
        bool leftIsPtr = leftType->getKind() == TypeKind::POINTER;
        bool rightIsPtr = rightType->getKind() == TypeKind::POINTER;
        bool leftIsNull = leftType->toString() == "null";
        bool rightIsNull = rightType->toString() == "null";

        if ((leftIsPtr && rightIsNull) || (leftIsNull && rightIsPtr)) {
            if (node.getOp() != ComparisonOpType::Eq && node.getOp() != ComparisonOpType::Ne) {
                ErrorHandler::getInstance().makeError(
                    "[RCE055]: Only '==' and '!=' are allowed for pointer-null comparison.",
                    node.getLocation());
                lastNode = nullptr;
                return;
            }

            // Extract the pointer variable name
            std::string ptrVarName;
            auto ptrExpr = leftIsPtr ? typedLeft : typedRight;
            if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(ptrExpr)) {
                ptrVarName = varNode->getName();
            } else if (auto ptrCreate = std::dynamic_pointer_cast<TypedPtrCreateNode>(ptrExpr)) {
                ptrVarName = ptrCreate->getVariableName();
            } else {
                ErrorHandler::getInstance().makeError(
                    "[RCE056]: Pointer-null comparison requires a pointer variable.",
                    node.getLocation());
                lastNode = nullptr;
                return;
            }

            auto boolType = TypeFactory::getPrimitive("bool");
            bool isEq = (node.getOp() == ComparisonOpType::Eq);
            auto typedIsNull = std::make_shared<TypedPtrIsNullNode>(ptrVarName, isEq, boolType);
            typedIsNull->setLocation(node.getLocation());
            lastNode = typedIsNull;
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
                "[RCE021]: Left operand of comparison must be 'int' or 'long', but got '" +
                    typedLeft->getType()->toString() + "'.",
                node.getLeft()->getLocation());
        }
        if (!rightIsInt && !rightIsLong) {
            ErrorHandler::getInstance().makeError(
                "[RCE022]: Right operand of comparison must be 'int' or 'long', but got '" +
                    typedRight->getType()->toString() + "'.",
                node.getRight()->getLocation());
        }

        auto boolType = TypeFactory::getPrimitive("bool");
        auto typedCmp = std::make_shared<TypedComparisonNode>(typedLeft, node.getOp(), typedRight, boolType);
        typedCmp->setLocation(node.getLocation());
        lastNode = typedCmp;
    }

    void SemanticAnalyzer::visit(PrefixOpNode &node) {
        auto operand = node.getOperand();
        auto varNode = std::dynamic_pointer_cast<VariableNode>(operand);
        if (!varNode) {
            ErrorHandler::getInstance().makeError(
                "[RCE027]: Prefix '++'/'--' requires a variable operand.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        auto varName = varNode->getName()->getName();
        auto sym = symbolTable.resolve(varName);

        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "[RCE014]: Variable '" + varName + "' is not defined.",
                varNode->getLocation());
            lastNode = nullptr;
            return;
        }

        auto varSym = std::dynamic_pointer_cast<VariableSymbol>(sym);
        if (!varSym) {
            ErrorHandler::getInstance().makeError(
                "[RCE015]: '" + varName + "' is not a variable.",
                varNode->getLocation());
            lastNode = nullptr;
            return;
        }

        auto varType = toTypedType(varSym->getType());
        auto intType = TypeFactory::getPrimitive("int");
        auto longType = TypeFactory::getPrimitive("long");

        if (!varType->equals(*intType) && !varType->equals(*longType)) {
            ErrorHandler::getInstance().makeError(
                "[RCE028]: Prefix '++'/'--' requires 'int' or 'long' variable, but got '" +
                    varType->toString() + "'.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        auto typedPrefix = std::make_shared<TypedPrefixOpNode>(varName, node.getOp(), varType);
        typedPrefix->setLocation(node.getLocation());
        lastNode = typedPrefix;
    }

    void SemanticAnalyzer::visit(PostfixOpNode &node) {
        auto operand = node.getOperand();
        auto varNode = std::dynamic_pointer_cast<VariableNode>(operand);
        if (!varNode) {
            ErrorHandler::getInstance().makeError(
                "[RCE029]: Postfix '++'/'--' requires a variable operand.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        auto varName = varNode->getName()->getName();
        auto sym = symbolTable.resolve(varName);

        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "[RCE014]: Variable '" + varName + "' is not defined.",
                varNode->getLocation());
            lastNode = nullptr;
            return;
        }

        auto varSym = std::dynamic_pointer_cast<VariableSymbol>(sym);
        if (!varSym) {
            ErrorHandler::getInstance().makeError(
                "[RCE015]: '" + varName + "' is not a variable.",
                varNode->getLocation());
            lastNode = nullptr;
            return;
        }

        auto varType = toTypedType(varSym->getType());
        auto intType = TypeFactory::getPrimitive("int");
        auto longType = TypeFactory::getPrimitive("long");

        if (!varType->equals(*intType) && !varType->equals(*longType)) {
            ErrorHandler::getInstance().makeError(
                "[RCE030]: Postfix '++'/'--' requires 'int' or 'long' variable, but got '" +
                    varType->toString() + "'.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        auto typedPostfix = std::make_shared<TypedPostfixOpNode>(varName, node.getOp(), varType);
        typedPostfix->setLocation(node.getLocation());
        lastNode = typedPostfix;
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

        auto varSTType = varSym->getType();

        // Handle assignment to ref<T> variable
        if (varSTType->getKind() == STType::TypeKind::Reference) {
            auto &refSTType = dynamic_cast<const STType::ReferenceType &>(*varSTType);
            auto elemTyped = toTypedType(refSTType.getElementType());
            auto rhsType = typedRHS->getType();

            // If RHS type matches the element type, store through the ref
            bool isAssignable = elemTyped->equals(*rhsType) ||
                                (rhsType->toString() == "int" && elemTyped->toString() == "long");
            if (!isAssignable && rhsType->toString() != "unknown") {
                ErrorHandler::getInstance().makeError(
                    "[RCE045]: Cannot assign value of type '" + rhsType->toString() +
                        "' to ref<" + elemTyped->toString() + "> variable '" + varName + "'.",
                    node.getRHS()->getLocation());
            }

            auto resultType = isAssignable ? elemTyped : TypeFactory::getPrimitive("unknown");
            auto typedRefAssign = std::make_shared<TypedRefAssignNode>(varName, typedRHS, resultType);
            typedRefAssign->setLocation(node.getLocation());
            lastNode = typedRefAssign;
            return;
        }

        auto varType = toTypedType(varSTType);
        auto rhsType = typedRHS->getType();

        // Allow implicit int → long widening promotion
        bool isAssignable = varType->equals(*rhsType) ||
                            (rhsType->toString() == "int" && varType->toString() == "long");
        // Allow null assignment to ptr<T> variables
        if (!isAssignable && rhsType->toString() == "null" && varType->getKind() == TypeKind::POINTER) {
            isAssignable = true;
        }
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
