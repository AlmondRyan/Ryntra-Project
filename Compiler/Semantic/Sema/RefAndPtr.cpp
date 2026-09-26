#include "../SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {
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
                node.getRange());
            lastNode = nullptr;
            return;
        }

        auto typedRef = std::make_shared<TypedRefCreateNode>(targetVarName, refType);
        typedRef->setRange(node.getRange());
        lastNode = typedRef;
    }

    void SemanticAnalyzer::visit(UnsafeBlockNode &node) {
        ++unsafeDepth_;
        node.getBody()->accept(*this);
        --unsafeDepth_;
        if (auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode)) {
            auto typedUnsafe = std::make_shared<TypedUnsafeBlockNode>(typedBody);
            typedUnsafe->setRange(node.getRange());
            lastNode = typedUnsafe;
        } else {
            lastNode = nullptr;
        }
    }

    void SemanticAnalyzer::visit(PtrExpressionNode &node) {
        // `ptr(...)` is a context-sensitive expression: it accepts any addressable
        // entity (a function or a variable), not just a variable.
        if (auto varNode = std::dynamic_pointer_cast<VariableNode>(node.getOperand())) {
            auto varName = varNode->getName()->getName();
            auto sym = symbolTable.resolve(varName);

            if (!sym || !SymbolTable::isAddressable(sym)) {
                if (!sym) {
                    ErrorHandler::getInstance().makeError(
                        "[RCE075]: Cannot take the address of '" + varName +
                            "': no function or variable named '" + varName + "' is defined.",
                        node.getRange());
                } else {
                    ErrorHandler::getInstance().makeError(
                        "[RCE076]: Cannot take the address of '" + varName + "': it is not an addressable entity.",
                        node.getRange());
                }
                lastNode = nullptr;
                return;
            }

            // Function symbols -> take the function address
            std::shared_ptr<FunctionSymbol> targetFn;
            if (auto fnSym = std::dynamic_pointer_cast<FunctionSymbol>(sym)) {
                targetFn = fnSym;
            } else if (auto ovSet = std::dynamic_pointer_cast<OverloadSet>(sym)) {
                targetFn = pickFunctionForAddress(ovSet, node.getRange());
            }

            if (targetFn) {
                auto fnType = functionTypeOf(targetFn);
                auto ptrType = TypeFactory::getPointer(fnType);
                auto typedAddr = std::make_shared<TypedFunctionAddressNode>(targetFn->getName(), ptrType);
                typedAddr->setRange(node.getRange());
                lastNode = typedAddr;
                return;
            }

            bool isFunctionSym = std::dynamic_pointer_cast<FunctionSymbol>(sym) ||
                                 std::dynamic_pointer_cast<OverloadSet>(sym);
            if (isFunctionSym) {
                // Overload resolution failed; the error was already reported.
                lastNode = nullptr;
                return;
            }

            // Variable symbol -> fall through to the regular pointer creation logic
        }

        node.getOperand()->accept(*this);
        auto typedOperand = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedOperand) {
            lastNode = nullptr;
            return;
        }

        auto operandType = typedOperand->getType();
        std::string targetVarName;

        if (auto refLoadNode = std::dynamic_pointer_cast<TypedRefLoadNode>(typedOperand)) {
            if (unsafeDepth_ == 0) {
                ErrorHandler::getInstance().makeError(
                    "[RCE046]: Converting 'ref' to 'ptr' is only allowed inside 'unsafe' blocks.",
                    node.getRange());
                lastNode = nullptr;
                return;
            }
            targetVarName = refLoadNode->getVariableName();
        } else if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(typedOperand)) {
            targetVarName = varNode->getName();
        } else {
            ErrorHandler::getInstance().makeError(
                "[RCE047]: 'ptr' requires a variable operand.",
                node.getRange());
            lastNode = nullptr;
            return;
        }

        if (operandType->getKind() == TypeKind::ARRAY) {
            auto &arrType = static_cast<const ArrayType &>(*operandType);
            auto elemType = arrType.getElementType();
            auto ptrType = TypeFactory::getPointer(elemType);
            auto typedPtr = std::make_shared<TypedPtrFromArrayNode>(targetVarName, ptrType);
            typedPtr->setRange(node.getRange());
            lastNode = typedPtr;
            return;
        }

        auto ptrType = TypeFactory::getPointer(operandType);
        auto typedPtr = std::make_shared<TypedPtrCreateNode>(targetVarName, ptrType);
        typedPtr->setRange(node.getRange());
        lastNode = typedPtr;
    }

    void SemanticAnalyzer::visit(FixedNode &node) {
        if (unsafeDepth_ == 0) {
            ErrorHandler::getInstance().makeError(
                "[RCE061]: 'fixed' is only allowed inside 'unsafe' blocks.",
                node.getRange());
            lastNode = nullptr;
            return;
        }

        node.getPtrType()->accept(*this);
        auto elemSTType = lastType;
        if (!elemSTType) {
            lastNode = nullptr;
            return;
        }
        auto elemType = toTypedType(elemSTType);
        auto ptrType = TypeFactory::getPointer(elemType);

        node.getInit()->accept(*this);
        auto typedInit = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedInit) {
            lastNode = nullptr;
            return;
        }

        auto initType = typedInit->getType();
        if (initType->getKind() != TypeKind::POINTER) {
            ErrorHandler::getInstance().makeError(
                "[RCE062]: 'fixed' initializer must be a pointer expression.",
                node.getInit()->getRange());
            lastNode = nullptr;
            return;
        }

        if (!elemType->equals(*std::dynamic_pointer_cast<PointerType>(initType)->getElementType())) {
            ErrorHandler::getInstance().makeError(
                "[RCE063]: Pointer type mismatch in 'fixed' initializer.",
                node.getInit()->getRange());
            lastNode = nullptr;
            return;
        }

        auto varName = node.getName()->getName();
        auto ptrSTType = std::make_shared<STType::PointerType>(elemSTType);
        symbolTable.enterScope();
        symbolTable.define(std::make_shared<VariableSymbol>(varName, ptrSTType), node.getRange());

        node.getBody()->accept(*this);

        symbolTable.exitScope();
        auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);
        if (!typedBody) {
            lastNode = nullptr;
            return;
        }

        auto typedFixed = std::make_shared<TypedFixedNode>(varName, ptrType, typedInit, typedBody);
        typedFixed->setRange(node.getRange());
        lastNode = typedFixed;
    }

    void SemanticAnalyzer::visit(MethodCallNode &node) {
        const auto &methodName = node.getMethodName();

        std::vector<std::shared_ptr<ExpressionNode>> args;
        if (node.getArgumentList()) {
            args = node.getArgumentList()->getArguments();
        }

        node.getObject()->accept(*this);
        auto typedObject = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedObject) {
            lastNode = nullptr;
            return;
        }

        auto objectType = typedObject->getType();

        if (objectType->toString() == "unknown") {
            lastNode = nullptr;
            return;
        }

        // Struct method call: `value.method(...)` / `self.method(...)`.
        if (objectType->getKind() == TypeKind::STRUCT) {
            auto &structType = static_cast<const StructType &>(*objectType);
            auto structIt = structTypes.find(structType.getName());
            if (structIt == structTypes.end()) {
                ErrorHandler::getInstance().makeError(
                    "[RCE100]: Struct '" + structType.getName() + "' has no method named '" + methodName + "'.",
                    node.getRange());
                lastNode = nullptr;
                return;
            }

            auto member = structIt->second->lookupMember(methodName);
            if (!member) {
                ErrorHandler::getInstance().makeError(
                    "[RCE100]: Struct '" + structType.getName() + "' has no method named '" + methodName + "'.",
                    node.getRange());
                lastNode = nullptr;
                return;
            }

            if (std::dynamic_pointer_cast<FieldSymbol>(member)) {
                ErrorHandler::getInstance().makeError(
                    "[RCE104]: '" + methodName + "' is a field of struct '" + structType.getName() +
                        "', not a method.",
                    node.getRange());
                lastNode = nullptr;
                return;
            }

            std::vector<std::shared_ptr<TypedExpressionNode>> typedArgs;
            for (const auto &arg : args) {
                arg->accept(*this);
                typedArgs.push_back(std::dynamic_pointer_cast<TypedExpressionNode>(lastNode));
            }

            std::shared_ptr<OverloadSet> overloadSet = std::dynamic_pointer_cast<OverloadSet>(member);
            if (!overloadSet) {
                ErrorHandler::getInstance().makeError(
                    "[RCE100]: Struct '" + structType.getName() + "' has no method named '" + methodName + "'.",
                    node.getRange());
                lastNode = nullptr;
                return;
            }

            auto paramMatches = [&](const std::shared_ptr<FunctionSymbol> &fn) {
                if (fn->getParamTypes().size() != typedArgs.size())
                    return false;
                for (size_t i = 0; i < typedArgs.size(); ++i) {
                    if (!typedArgs[i])
                        return false;
                    auto expected = toTypedType(fn->getParamTypes()[i]);
                    auto actual = typedArgs[i]->getType();
                    bool ok = expected->equals(*actual) ||
                              (actual->toString() == "int" && expected->toString() == "long");
                    if (!ok && actual->toString() != "unknown")
                        return false;
                }
                return true;
            };

            std::shared_ptr<FunctionSymbol> selected;
            std::shared_ptr<FunctionSymbol> sameArity;
            for (const auto &fn : overloadSet->getFunctions()) {
                if (fn->getParamTypes().size() == args.size() && !sameArity)
                    sameArity = fn;
                if (paramMatches(fn)) {
                    selected = fn;
                    break;
                }
            }

            if (!selected) {
                if (!sameArity) {
                    ErrorHandler::getInstance().makeError(
                        "[RCE101]: Method '" + structType.getName() + "." + methodName +
                            "' has no overload accepting " + std::to_string(args.size()) + " argument(s).",
                        node.getRange());
                } else {
                    for (size_t i = 0; i < typedArgs.size(); ++i) {
                        if (!typedArgs[i])
                            continue;
                        auto expected = toTypedType(sameArity->getParamTypes()[i]);
                        auto actual = typedArgs[i]->getType();
                        if (!expected->equals(*actual) && actual->toString() != "unknown" &&
                            !(actual->toString() == "int" && expected->toString() == "long")) {
                            ErrorHandler::getInstance().makeError(
                                "[RCE102]: Argument " + std::to_string(i + 1) + " of method '" +
                                    structType.getName() + "." + methodName + "' expects type '" +
                                    expected->toString() + "', but got '" + actual->toString() + "'.",
                                args[i]->getRange());
                        }
                    }
                }
            }

            auto resultType = selected ? toTypedType(selected->getReturnType())
                                       : TypeFactory::getPrimitive("unknown");
            auto typedCall = std::make_shared<TypedMethodCallNode>(
                typedObject, methodName, std::move(typedArgs), resultType);
            typedCall->setRange(node.getRange());
            lastNode = typedCall;
            return;
        }

        // Pointer method calls ('.load()' / '.store()') are the only other supported form.
        if (objectType->getKind() != TypeKind::POINTER) {
            ErrorHandler::getInstance().makeError(
                "[RCE099]: Method call '." + methodName + "()' requires a struct or pointer expression, but got '" +
                    objectType->toString() + "'.",
                node.getRange());
            lastNode = nullptr;
            return;
        }

        if (methodName == "load") {
            if (!args.empty()) {
                ErrorHandler::getInstance().makeError(
                    "[RCE081]: '.load()' does not take any arguments.",
                    node.getRange());
                lastNode = nullptr;
                return;
            }

            if (unsafeDepth_ == 0) {
                ErrorHandler::getInstance().makeError(
                    "[RCE048]: '.load()' is only allowed inside 'unsafe' blocks.",
                    node.getRange());
                lastNode = nullptr;
                return;
            }

            std::string ptrVarName;
            if (auto ptrCreateNode = std::dynamic_pointer_cast<TypedPtrCreateNode>(typedObject)) {
                ptrVarName = ptrCreateNode->getVariableName();
            } else if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(typedObject)) {
                ptrVarName = varNode->getName();
            } else {
                ErrorHandler::getInstance().makeError(
                    "[RCE050]: '.load()' requires a pointer variable.",
                    node.getRange());
                lastNode = nullptr;
                return;
            }

            auto elemType = std::dynamic_pointer_cast<PointerType>(objectType)->getElementType();
            auto typedPtrLoad = std::make_shared<TypedPtrLoadNode>(ptrVarName, elemType);
            typedPtrLoad->setRange(node.getRange());
            lastNode = typedPtrLoad;
            return;
        }

        if (methodName == "store") {
            if (args.size() != 1) {
                ErrorHandler::getInstance().makeError(
                    "[RCE082]: '.store()' expects exactly one argument.",
                    node.getRange());
                lastNode = nullptr;
                return;
            }

            if (unsafeDepth_ == 0) {
                ErrorHandler::getInstance().makeError(
                    "[RCE051]: '.store()' is only allowed inside 'unsafe' blocks.",
                    node.getRange());
                lastNode = nullptr;
                return;
            }

            std::string ptrVarName;
            if (auto ptrCreateNode = std::dynamic_pointer_cast<TypedPtrCreateNode>(typedObject)) {
                ptrVarName = ptrCreateNode->getVariableName();
            } else if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(typedObject)) {
                ptrVarName = varNode->getName();
            } else {
                ErrorHandler::getInstance().makeError(
                    "[RCE053]: '.store()' requires a pointer variable.",
                    node.getRange());
                lastNode = nullptr;
                return;
            }

            auto elemType = std::dynamic_pointer_cast<PointerType>(objectType)->getElementType();

            auto &argExpr = args[0];
            argExpr->accept(*this);
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
                    argExpr->getRange());
            }

            auto resultType = isAssignable ? elemType : TypeFactory::getPrimitive("unknown");
            auto typedPtrStore = std::make_shared<TypedPtrStoreNode>(ptrVarName, typedValue, resultType);
            typedPtrStore->setRange(node.getRange());
            lastNode = typedPtrStore;
            return;
        }

        ErrorHandler::getInstance().makeError(
            "[RCE078]: '." + methodName + "()' is not a pointer operation. " +
                "Only '.load()' (dereference) and '.store()' (store value) are allowed on pointers.",
            node.getRange());
        lastNode = nullptr;
    }
} // namespace Ryntra::Compiler::Semantic
