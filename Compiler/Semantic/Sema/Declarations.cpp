#include "../SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {
    void SemanticAnalyzer::visit(ProgramNode &node) {
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

        if (!symbolTable.resolve("__builtin_print")) {
            auto overloadSet = std::make_shared<OverloadSet>("__builtin_print");

            {
                std::vector<TypePtr> params{std::make_shared<STType::StringType>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_print",
                                                                           std::make_shared<STType::VoidType>(), std::move(params)));
            }
            {
                std::vector<TypePtr> params{std::make_shared<STType::Int32Type>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_print",
                                                                           std::make_shared<STType::VoidType>(), std::move(params)));
            }
            {
                std::vector<TypePtr> params{std::make_shared<STType::Int64Type>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_print",
                                                                           std::make_shared<STType::VoidType>(), std::move(params)));
            }
            {
                std::vector<TypePtr> params{std::make_shared<STType::BoolType>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_print",
                                                                           std::make_shared<STType::VoidType>(), std::move(params)));
            }

            symbolTable.define(overloadSet, SourceLocation{0, 0});
        }

        if (!symbolTable.resolve("__builtin_scan")) {
            auto overloadSet = std::make_shared<OverloadSet>("__builtin_scan");

            {
                std::vector<TypePtr> params{};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_scan",
                                                                           std::make_shared<STType::Int32Type>(), std::move(params)));
            }
            {
                std::vector<TypePtr> params{};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_scan",
                                                                           std::make_shared<STType::Int64Type>(), std::move(params)));
            }
            {
                std::vector<TypePtr> params{};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("__builtin_scan",
                                                                           std::make_shared<STType::BoolType>(), std::move(params)));
            }

            symbolTable.define(overloadSet, SourceLocation{0, 0});
        }

        if (!symbolTable.resolve("print")) {
            auto overloadSet = std::make_shared<OverloadSet>("print");

            {
                std::vector<TypePtr> params{std::make_shared<STType::StringType>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("print",
                                                                           std::make_shared<STType::VoidType>(), std::move(params)));
            }
            {
                std::vector<TypePtr> params{std::make_shared<STType::Int32Type>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("print",
                                                                           std::make_shared<STType::VoidType>(), std::move(params)));
            }
            {
                std::vector<TypePtr> params{std::make_shared<STType::Int64Type>()};
                overloadSet->addFunction(std::make_shared<FunctionSymbol>("print",
                                                                           std::make_shared<STType::VoidType>(), std::move(params)));
            }
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

    void SemanticAnalyzer::visit(TypeSpecifierNode &node) {
        lastType = makeSTType(node.getName());
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
            expectedReturnType = toTypedType(varType);
            node.getInitializer()->accept(*this);
            expectedReturnType = nullptr;
            typedInit = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

            if (typedInit) {
                auto expectedTyped = toTypedType(varType);
                auto actualType = typedInit->getType();
                bool isAssignable = expectedTyped->equals(*actualType) ||
                                    (actualType->toString() == "int" && expectedTyped->toString() == "long");
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
} // namespace Ryntra::Compiler::Semantic
