#include "../SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"
#include <unordered_set>

namespace Ryntra::Compiler::Semantic {
    void SemanticAnalyzer::registerStructMembers(const std::shared_ptr<STType::StructType> &structType,
                                                 const std::shared_ptr<MemberListNode> &memberList) {
        if (!memberList) {
            return;
        }

        const auto &members = memberList->getMembers();
        const auto &structName = structType->getName();

        std::unordered_set<std::string> fieldNames;
        for (const auto &member : members) {
            if (auto field = std::dynamic_pointer_cast<FieldDeclarationNode>(member)) {
                auto fieldName = field->getName()->getName();
                if (!fieldNames.insert(fieldName).second) {
                    ErrorHandler::getInstance().makeError(
                        "[RCE097]: Field '" + fieldName + "' is already defined in struct '" +
                            structName + "'.",
                        field->getRange());
                    continue;
                }
                field->getType()->accept(*this);
                structType->addField(fieldName, lastType ? lastType : makeSTType("unknown"));
            }
        }

        std::unordered_set<std::string> memberSignatures;
        for (const auto &member : members) {
            if (auto method = std::dynamic_pointer_cast<FunctionDefinitionNode>(member)) {
                auto methodName = method->getName()->getName();

                method->getReturnType()->accept(*this);
                auto returnType = lastType ? lastType : makeSTType("unknown");

                std::vector<TypePtr> paramTypes;
                if (method->getParameterList()) {
                    for (const auto &param : method->getParameterList()->getParameters()) {
                        param->getType()->accept(*this);
                        paramTypes.push_back(lastType ? lastType : makeSTType("unknown"));
                    }
                }

                if (fieldNames.count(methodName)) {
                    ErrorHandler::getInstance().makeError(
                        "[RCE098]: Member '" + methodName + "' is already defined as a field in struct '" +
                            structName + "'.",
                        method->getRange());
                    continue;
                }

                std::string signature = methodName + "(";
                for (size_t i = 0; i < paramTypes.size(); ++i) {
                    if (i > 0)
                        signature += ",";
                    signature += std::to_string(static_cast<int>(paramTypes[i]->getKind()));
                }
                signature += ")";
                if (!memberSignatures.insert(signature).second) {
                    ErrorHandler::getInstance().makeError(
                        "[RCE098]: Method '" + methodName +
                            "' is already defined with the same signature in struct '" + structName + "'.",
                        method->getRange());
                    continue;
                }

                structType->defineMethod(std::make_shared<FunctionSymbol>(
                    methodName, returnType, std::move(paramTypes)));
            } else if (auto ctor = std::dynamic_pointer_cast<ConstructorDeclarationNode>(member)) {
                std::vector<TypePtr> paramTypes;
                if (ctor->getParameterList()) {
                    for (const auto &param : ctor->getParameterList()->getParameters()) {
                        param->getType()->accept(*this);
                        paramTypes.push_back(lastType ? lastType : makeSTType("unknown"));
                    }
                }

                std::string signature = ctor->getName()->getName() + "(";
                for (size_t i = 0; i < paramTypes.size(); ++i) {
                    if (i > 0)
                        signature += ",";
                    signature += std::to_string(static_cast<int>(paramTypes[i]->getKind()));
                }
                signature += ")";
                if (!memberSignatures.insert(signature).second) {
                    ErrorHandler::getInstance().makeError(
                        "[RCE098]: Constructor '" + ctor->getName()->getName() +
                            "' is already defined with the same signature in struct '" + structName + "'.",
                        ctor->getRange());
                    continue;
                }

                structType->defineMethod(std::make_shared<FunctionSymbol>(
                    ctor->getName()->getName(), structType, std::move(paramTypes)));
            }
        }
    }

    void SemanticAnalyzer::visit(ProgramNode &node) {
        // Pre-register struct types so function/method signatures can name them.
        // The bodies are analyzed later, once builtins are available.
        for (const auto &strct : node.getStructs()) {
            auto structName = strct->getName()->getName();
            if (std::dynamic_pointer_cast<TypeSymbol>(symbolTable.resolve(structName))) {
                continue;
            }

            auto structSTType = std::make_shared<STType::StructType>(structName);
            structTypes[structName] = structSTType;
            symbolTable.define(std::make_shared<TypeSymbol>(structName, structSTType), strct->getRange());
            registerStructMembers(structSTType, strct->getMemberList());
        }

        for (const auto &func : node.getFunctions()) {
            auto funcName = func->getName()->getName();

            func->getReturnType()->accept(*this);
            auto returnType = lastType ? lastType : makeSTType("unknown");

            std::vector<TypePtr> paramTypes;
            if (func->getParameterList()) {
                for (const auto &param : func->getParameterList()->getParameters()) {
                    param->getType()->accept(*this);
                    paramTypes.push_back(lastType ? lastType : makeSTType("unknown"));
                }
            }

            auto newFuncSym = std::make_shared<FunctionSymbol>(funcName, returnType, std::move(paramTypes));
            auto existingSym = symbolTable.resolve(funcName);

            if (!existingSym) {
                auto overloadSet = std::make_shared<OverloadSet>(funcName);
                overloadSet->addFunction(std::move(newFuncSym));
                symbolTable.define(overloadSet, func->getRange());
            } else if (auto overloadSet = std::dynamic_pointer_cast<OverloadSet>(existingSym)) {
                bool isDuplicate = false;
                for (const auto &existing : overloadSet->getFunctions()) {
                    if (existing->getParamTypes().size() != newFuncSym->getParamTypes().size())
                        continue;
                    bool match = true;
                    for (size_t i = 0; i < existing->getParamTypes().size(); ++i) {
                        if (existing->getParamTypes()[i]->getKind() != newFuncSym->getParamTypes()[i]->getKind()) {
                            match = false;
                            break;
                        }
                    }
                    if (match) {
                        ErrorHandler::getInstance().makeError(
                            "[RCE001]: Function '" + funcName + "' is already defined with the same signature.",
                            func->getRange());
                        isDuplicate = true;
                        break;
                    }
                }
                if (!isDuplicate) {
                    overloadSet->addFunction(std::move(newFuncSym));
                }
            }
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

            symbolTable.define(overloadSet, SourceRange(SourceLocation{0, 0, 0}));
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

            symbolTable.define(overloadSet, SourceRange(SourceLocation{0, 0, 0}));
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

            symbolTable.define(overloadSet, SourceRange(SourceLocation{0, 0, 0}));
        }

        auto mainSym = symbolTable.resolve("main");
        if (!mainSym) {
            ErrorHandler::getInstance().makeError(
                "[RCE002]: 'main' function is not defined.", node.getRange());
        } else if (auto overloadSet = std::dynamic_pointer_cast<OverloadSet>(mainSym)) {
            if (overloadSet->getFunctions().empty()) {
                ErrorHandler::getInstance().makeError(
                    "[RCE003]: 'main' is not a function.", node.getRange());
            } else {
                auto mainFuncSym = overloadSet->getFunctions()[0];
                if (!mainFuncSym->getReturnType()) {
                    ErrorHandler::getInstance().makeError(
                        "[RCE004]: 'main' function must have a return type.", node.getRange());
                } else if (mainFuncSym->getReturnType()->getKind() != STType::TypeKind::Void) {
                    ErrorHandler::getInstance().makeError(
                        "[RCE005]: 'main' function must return 'void'.", node.getRange());
                }
            }
        } else {
            ErrorHandler::getInstance().makeError(
                "[RCE003]: 'main' is not a function.", node.getRange());
        }

        std::vector<std::shared_ptr<TypedFunctionDefinitionNode>> typedFunctions;
        for (const auto &func : node.getFunctions()) {
            func->accept(*this);
            if (auto typedFunc = std::dynamic_pointer_cast<TypedFunctionDefinitionNode>(lastNode)) {
                typedFunctions.push_back(typedFunc);
            }
        }

        std::vector<std::shared_ptr<TypedStructDeclarationNode>> typedStructs;
        for (const auto &strct : node.getStructs()) {
            strct->accept(*this);
            if (auto typedStruct = std::dynamic_pointer_cast<TypedStructDeclarationNode>(lastNode)) {
                typedStructs.push_back(typedStruct);
            }
        }

        typedProgram = std::make_shared<TypedProgramNode>(std::move(typedFunctions), std::move(typedStructs));
        typedProgram->setRange(node.getRange());
        lastNode = typedProgram;
    }

    void SemanticAnalyzer::visit(FunctionDefinitionNode &node) {
        node.getReturnType()->accept(*this);
        auto returnType = lastType ? lastType : makeSTType("void");
        currentFunctionReturnType = returnType;

        auto funcName = node.getName()->getName();

        symbolTable.enterScope(Scope::Kind::Function);

        std::vector<std::shared_ptr<TypedParameterNode>> typedParams;
        if (node.getParameterList()) {
            for (const auto &param : node.getParameterList()->getParameters()) {
                param->getType()->accept(*this);
                auto paramType = lastType;
                auto paramName = param->getName()->getName();
                if (paramType) {
                    symbolTable.define(
                        std::make_shared<VariableSymbol>(paramName, paramType),
                        param->getRange());
                    typedParams.push_back(
                        std::make_shared<TypedParameterNode>(paramName, toTypedType(paramType)));
                }
            }
        }

        node.getBody()->accept(*this);
        auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);
        symbolTable.exitScope();

        auto typedParamList = std::make_shared<TypedParameterListNode>(std::move(typedParams));
        typedParamList->setRange(node.getParameterList() ? node.getParameterList()->getRange() : node.getRange());

        if (typedBody) {
            auto typedFunc = std::make_shared<TypedFunctionDefinitionNode>(
                funcName, toTypedType(returnType), typedParamList, typedBody);
            typedFunc->setRange(node.getRange());
            lastNode = typedFunc;
        } else {
            lastNode = nullptr;
        }
        currentFunctionReturnType = nullptr;
    }

    void SemanticAnalyzer::visit(ReturnNode &node) {
        std::shared_ptr<TypedExpressionNode> typedExpr = nullptr;
        if (node.getValue()) {
            node.getValue()->accept(*this);
            typedExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        }

        if (typedExpr) {
            if (currentFunctionReturnType) {
                auto expectedTyped = toTypedType(currentFunctionReturnType);
                auto actualType = typedExpr->getType();

                if (!expectedTyped->equals(*actualType) && actualType->toString() != "unknown") {
                    ErrorHandler::getInstance().makeError(
                        "[RCE006]: Return type mismatch. Expected '" +
                            expectedTyped->toString() + "', but got '" +
                            actualType->toString() + "'.",
                        node.getRange());
                }
            }
            auto typedReturn = std::make_shared<TypedReturnNode>(typedExpr);
            typedReturn->setRange(node.getRange());
            lastNode = typedReturn;
            return;
        }

        // Bare `return;`: only valid in a void-returning function/constructor.
        if (currentFunctionReturnType &&
            currentFunctionReturnType->getKind() != STType::TypeKind::Void) {
            ErrorHandler::getInstance().makeError(
                "[RCE006]: Return type mismatch. Expected '" +
                    toTypedType(currentFunctionReturnType)->toString() +
                    "', but no value was returned.",
                node.getRange());
        }

        auto typedReturn = std::make_shared<TypedReturnNode>(nullptr);
        typedReturn->setRange(node.getRange());
        lastNode = typedReturn;
    }

    void SemanticAnalyzer::visit(TypeSpecifierNode &node) {
        if (node.getFunctionType()) {
            node.getFunctionType()->accept(*this);
            return;
        }

        if (!node.getWrappedBareFunctionType().empty()) {
            ErrorHandler::getInstance().makeError(
                "[RCE072]: '" + node.getWrappedBareFunctionType() +
                    "' is not a valid type that can be placed in 'ptr<T>'. Use 'Fn<...>' to declare a function type.",
                node.getRange());
        }

        checkKnownTypeNames(node.getName(), node.getRange());

        // Prefer the symbol table so struct (and other named aggregate) types keep
        // their full definition instead of being reduced to a default primitive.
        if (auto typeSym = std::dynamic_pointer_cast<TypeSymbol>(symbolTable.resolve(node.getName()))) {
            lastType = typeSym->getType();
            return;
        }

        lastType = makeSTType(node.getName());
    }

    void SemanticAnalyzer::visit(FunctionTypeNode &node) {
        if (node.isBare()) {
            ErrorHandler::getInstance().makeError(
                "[RCE073]: Function type '" + node.getText() +
                    "' must be written as 'Fn<" + node.getText() + ">'.",
                node.getRange());
        }

        node.getReturnType()->accept(*this);
        auto returnType = lastType;
        if (!returnType) {
            lastType = nullptr;
            return;
        }

        std::vector<TypePtr> paramTypes;
        for (const auto &param : node.getParamTypes()) {
            param->accept(*this);
            if (!lastType) {
                lastType = nullptr;
                return;
            }
            paramTypes.push_back(lastType);
        }

        lastType = std::make_shared<STType::FunctionType>(returnType, std::move(paramTypes));
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
                        node.getRange());
                }
            }
        }

        auto varSym = std::make_shared<VariableSymbol>(varName, varType);
        symbolTable.define(varSym, node.getRange());

        auto typedDecl = std::make_shared<TypedVariableDeclarationNode>(varName, toTypedType(varType), typedInit);
        typedDecl->setRange(node.getRange());
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
                node.getRange());
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
                    node.getSize()->getRange());
            }
        }

        auto varSym = std::make_shared<VariableSymbol>(varName, arrayType);
        symbolTable.define(varSym, node.getRange());

        auto typedDecl = std::make_shared<TypedArrayDeclarationNode>(varName, toTypedType(declElemType), typedSize);
        typedDecl->setRange(node.getRange());
        lastNode = typedDecl;
    }

    void SemanticAnalyzer::visit(VariableNode &node) {
        auto varName = node.getName()->getName();
        auto sym = symbolTable.resolve(varName);

        std::shared_ptr<Type> type;
        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "[RCE014]: Variable '" + varName + "' is not defined.",
                node.getRange());
            type = TypeFactory::getPrimitive("unknown");
        } else if (auto varSym = std::dynamic_pointer_cast<VariableSymbol>(sym)) {
            auto varSTType = varSym->getType();
            if (varSTType->getKind() == STType::TypeKind::Reference) {
                auto &refSTType = static_cast<const STType::ReferenceType &>(*varSTType);
                auto derefType = toTypedType(refSTType.getElementType());
                auto typedRefLoad = std::make_shared<TypedRefLoadNode>(varName, derefType);
                typedRefLoad->setRange(node.getRange());
                lastNode = typedRefLoad;
                return;
            }
            type = toTypedType(varSTType);
        } else {
            ErrorHandler::getInstance().makeError(
                "[RCE015]: '" + varName + "' is not a variable.",
                node.getRange());
            type = TypeFactory::getPrimitive("unknown");
        }

        auto typedVar = std::make_shared<TypedVariableNode>(varName, type);
        typedVar->setRange(node.getRange());
        lastNode = typedVar;
    }

    void SemanticAnalyzer::visit(IdentifierNode &node) {
        auto name = node.getName();
        auto sym = symbolTable.resolve(name);

        std::shared_ptr<Type> type;
        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "[RCE007]: Identifier '" + name + "' is not defined.",
                node.getRange());
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
        typedNode->setRange(node.getRange());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(StructDeclarationNode &node) {
        auto structName = node.getName()->getName();

        std::shared_ptr<STType::StructType> structSTType;
        if (auto existing = std::dynamic_pointer_cast<TypeSymbol>(symbolTable.resolve(structName))) {
            structSTType = std::dynamic_pointer_cast<STType::StructType>(existing->getType());
        }
        if (!structSTType) {
            structSTType = std::make_shared<STType::StructType>(structName);
        }

        // Member symbols (fields/methods/constructors) were already registered
        // during pre-registration; here we only analyze the member bodies.
        auto memberList = node.getMemberList();

        structTypes[structName] = structSTType;

        if (!std::dynamic_pointer_cast<TypeSymbol>(symbolTable.resolve(structName))) {
            symbolTable.define(std::make_shared<TypeSymbol>(structName, structSTType), node.getRange());
        }

        auto savedStruct = currentStruct;
        currentStruct = structSTType;

        std::vector<std::shared_ptr<TypedFieldDeclarationNode>> typedFields;
        std::vector<std::shared_ptr<TypedConstructorDeclarationNode>> typedConstructors;
        std::vector<std::shared_ptr<TypedFunctionDefinitionNode>> typedMethods;

        if (memberList) {
            for (const auto &member : memberList->getMembers()) {
                if (auto field = std::dynamic_pointer_cast<FieldDeclarationNode>(member)) {
                    field->accept(*this);
                    if (auto typedField = std::dynamic_pointer_cast<TypedFieldDeclarationNode>(lastNode)) {
                        typedFields.push_back(typedField);
                    }
                } else if (auto ctor = std::dynamic_pointer_cast<ConstructorDeclarationNode>(member)) {
                    ctor->accept(*this);
                    if (auto typedCtor = std::dynamic_pointer_cast<TypedConstructorDeclarationNode>(lastNode)) {
                        typedConstructors.push_back(typedCtor);
                    }
                } else if (auto method = std::dynamic_pointer_cast<FunctionDefinitionNode>(member)) {
                    method->accept(*this);
                    if (auto typedMethod = std::dynamic_pointer_cast<TypedFunctionDefinitionNode>(lastNode)) {
                        typedMethods.push_back(typedMethod);
                    }
                }
            }
        }

        currentStruct = savedStruct;

        auto typedStruct = std::make_shared<TypedStructDeclarationNode>(
            structName, std::move(typedFields), std::move(typedConstructors), std::move(typedMethods));
        typedStruct->setRange(node.getRange());
        lastNode = typedStruct;
    }

    void SemanticAnalyzer::visit(FieldDeclarationNode &node) {
        auto fieldName = node.getName()->getName();
        node.getType()->accept(*this);
        auto fieldType = lastType ? lastType : makeSTType("unknown");

        auto typedField = std::make_shared<TypedFieldDeclarationNode>(fieldName, toTypedType(fieldType));
        typedField->setRange(node.getRange());
        lastNode = typedField;
    }

    void SemanticAnalyzer::visit(ConstructorDeclarationNode &node) {
        auto ctorName = node.getName()->getName();

        symbolTable.enterScope(Scope::Kind::Function);

        std::vector<std::shared_ptr<TypedParameterNode>> typedParams;
        if (node.getParameterList()) {
            for (const auto &param : node.getParameterList()->getParameters()) {
                param->getType()->accept(*this);
                auto paramType = lastType;
                auto paramName = param->getName()->getName();
                if (paramType) {
                    symbolTable.define(
                        std::make_shared<VariableSymbol>(paramName, paramType),
                        param->getRange());
                    typedParams.push_back(
                        std::make_shared<TypedParameterNode>(paramName, toTypedType(paramType)));
                }
            }
        }

        auto savedReturnType = currentFunctionReturnType;
        currentFunctionReturnType = makeSTType("void");
        node.getBody()->accept(*this);
        auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);
        currentFunctionReturnType = savedReturnType;
        symbolTable.exitScope();

        auto typedParamList = std::make_shared<TypedParameterListNode>(std::move(typedParams));
        typedParamList->setRange(node.getParameterList() ? node.getParameterList()->getRange() : node.getRange());

        auto typedCtor = std::make_shared<TypedConstructorDeclarationNode>(
            ctorName, typedParamList, typedBody);
        typedCtor->setRange(node.getRange());
        lastNode = typedCtor;
    }

    void SemanticAnalyzer::visit(SelfExpressionNode &node) {
        if (!currentStruct) {
            // TODO: This should be replaced by something in the future, because not only struct can hold self
            ErrorHandler::getInstance().makeError(
                "[RCE093]: 'self' can only be used inside a struct member.",
                node.getRange());
            lastNode = nullptr;
            return;
        }

        auto typedSelf = std::make_shared<TypedSelfExpressionNode>(toTypedType(currentStruct));
        typedSelf->setRange(node.getRange());
        lastNode = typedSelf;
    }

    void SemanticAnalyzer::visit(MemberAccessNode &node) {
        node.getObject()->accept(*this);
        auto typedObject = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedObject) {
            lastNode = nullptr;
            return;
        }

        auto memberName = node.getMember()->getName();
        auto objectType = typedObject->getType();

        if (objectType->getKind() != TypeKind::STRUCT) {
            ErrorHandler::getInstance().makeError(
                "[RCE094]: Member access '." + memberName + "' requires a struct value, but got '" +
                    objectType->toString() + "'.",
                node.getRange());
            lastNode = nullptr;
            return;
        }

        auto &structType = static_cast<const StructType &>(*objectType);
        auto fieldType = structType.getField(memberName);
        if (!fieldType) {
            // The name may refer to a method: accessing a method without calling it
            // is not a value expression.
            auto structIt = structTypes.find(structType.getName());
            if (structIt != structTypes.end()) {
                auto member = structIt->second->lookupMember(memberName);
                if (member && std::dynamic_pointer_cast<OverloadSet>(member)) {
                    ErrorHandler::getInstance().makeError(
                        "[RCE103]: '" + memberName + "' is a method of struct '" + structType.getName() +
                            "' and must be called, e.g. '." + memberName + "(...)'.",
                        node.getMember()->getRange());
                    lastNode = nullptr;
                    return;
                }
            }

            ErrorHandler::getInstance().makeError(
                "[RCE095]: Struct '" + structType.getName() + "' has no member named '" + memberName + "'.",
                node.getMember()->getRange());
            lastNode = nullptr;
            return;
        }

        auto typedAccess = std::make_shared<TypedMemberAccessNode>(typedObject, memberName, fieldType);
        typedAccess->setRange(node.getRange());
        lastNode = typedAccess;
    }

    void SemanticAnalyzer::visit(MemberAssignmentNode &node) {
        node.getTarget()->accept(*this);
        auto typedTarget = std::dynamic_pointer_cast<TypedMemberAccessNode>(lastNode);
        if (!typedTarget) {
            lastNode = nullptr;
            return;
        }

        node.getValue()->accept(*this);
        auto typedValue = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedValue) {
            lastNode = nullptr;
            return;
        }

        auto fieldType = typedTarget->getType();
        auto valueType = typedValue->getType();

        bool isAssignable = fieldType->equals(*valueType) ||
                            (valueType->toString() == "int" && fieldType->toString() == "long");
        if (!isAssignable && valueType->toString() == "null" && fieldType->getKind() == TypeKind::POINTER) {
            isAssignable = true;
        }
        if (!isAssignable && valueType->toString() != "unknown") {
            ErrorHandler::getInstance().makeError(
                "[RCE096]: Cannot assign value of type '" + valueType->toString() +
                    "' to member '" + typedTarget->getMemberName() + "' of type '" +
                    fieldType->toString() + "'.",
                node.getValue()->getRange());
        }

        auto resultType = isAssignable ? fieldType : TypeFactory::getPrimitive("unknown");
        auto typedAssign = std::make_shared<TypedMemberAssignmentNode>(
            typedTarget->getObject(), typedTarget->getMemberName(), typedValue, resultType);
        typedAssign->setRange(node.getRange());
        lastNode = typedAssign;
    }
} // namespace Ryntra::Compiler::Semantic
