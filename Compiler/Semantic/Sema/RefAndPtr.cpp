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
                        node.getLocation());
                } else {
                    ErrorHandler::getInstance().makeError(
                        "[RCE076]: Cannot take the address of '" + varName + "': it is not an addressable entity.",
                        node.getLocation());
                }
                lastNode = nullptr;
                return;
            }

            // Function symbols -> take the function address
            std::shared_ptr<FunctionSymbol> targetFn;
            if (auto fnSym = std::dynamic_pointer_cast<FunctionSymbol>(sym)) {
                targetFn = fnSym;
            } else if (auto ovSet = std::dynamic_pointer_cast<OverloadSet>(sym)) {
                targetFn = pickFunctionForAddress(ovSet, node.getLocation());
            }

            if (targetFn) {
                auto fnType = functionTypeOf(targetFn);
                auto ptrType = TypeFactory::getPointer(fnType);
                auto typedAddr = std::make_shared<TypedFunctionAddressNode>(targetFn->getName(), ptrType);
                typedAddr->setLocation(node.getLocation());
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
                    node.getLocation());
                lastNode = nullptr;
                return;
            }
            targetVarName = refLoadNode->getVariableName();
        } else if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(typedOperand)) {
            targetVarName = varNode->getName();
        } else {
            ErrorHandler::getInstance().makeError(
                "[RCE047]: 'ptr' requires a variable operand.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        if (operandType->getKind() == TypeKind::ARRAY) {
            auto &arrType = static_cast<const ArrayType &>(*operandType);
            auto elemType = arrType.getElementType();
            auto ptrType = TypeFactory::getPointer(elemType);
            auto typedPtr = std::make_shared<TypedPtrFromArrayNode>(targetVarName, ptrType);
            typedPtr->setLocation(node.getLocation());
            lastNode = typedPtr;
            return;
        }

        auto ptrType = TypeFactory::getPointer(operandType);
        auto typedPtr = std::make_shared<TypedPtrCreateNode>(targetVarName, ptrType);
        typedPtr->setLocation(node.getLocation());
        lastNode = typedPtr;
    }

    void SemanticAnalyzer::visit(FixedNode &node) {
        if (unsafeDepth_ == 0) {
            ErrorHandler::getInstance().makeError(
                "[RCE061]: 'fixed' is only allowed inside 'unsafe' blocks.",
                node.getLocation());
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
                node.getInit()->getLocation());
            lastNode = nullptr;
            return;
        }

        if (!elemType->equals(*std::dynamic_pointer_cast<PointerType>(initType)->getElementType())) {
            ErrorHandler::getInstance().makeError(
                "[RCE063]: Pointer type mismatch in 'fixed' initializer.",
                node.getInit()->getLocation());
            lastNode = nullptr;
            return;
        }

        auto varName = node.getName()->getName();
        auto ptrSTType = std::make_shared<STType::PointerType>(elemSTType);
        symbolTable.enterScope();
        symbolTable.define(std::make_shared<VariableSymbol>(varName, ptrSTType), node.getLocation());

        node.getBody()->accept(*this);

        symbolTable.exitScope();
        auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);
        if (!typedBody) {
            lastNode = nullptr;
            return;
        }

        auto typedFixed = std::make_shared<TypedFixedNode>(varName, ptrType, typedInit, typedBody);
        typedFixed->setLocation(node.getLocation());
        lastNode = typedFixed;
    }

    void SemanticAnalyzer::visit(MethodCallNode &node) {
        const auto &methodName = node.getMethodName();

        node.getObject()->accept(*this);
        auto typedObject = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedObject) {
            lastNode = nullptr;
            return;
        }

        auto objectType = typedObject->getType();

        // Only pointer method calls ('.load()' / '.store()') are supported for now.
        if (objectType->getKind() != TypeKind::POINTER && objectType->toString() != "unknown") {
            ErrorHandler::getInstance().makeError(
                "[RCE080]: Method call '." + methodName + "()' requires a pointer expression, but got '" +
                    objectType->toString() + "'.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        if (methodName == "load") {
            if (!node.getArguments().empty()) {
                ErrorHandler::getInstance().makeError(
                    "[RCE081]: '.load()' does not take any arguments.",
                    node.getLocation());
                lastNode = nullptr;
                return;
            }

            if (unsafeDepth_ == 0) {
                ErrorHandler::getInstance().makeError(
                    "[RCE048]: '.load()' is only allowed inside 'unsafe' blocks.",
                    node.getLocation());
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
                    node.getLocation());
                lastNode = nullptr;
                return;
            }

            auto elemType = std::dynamic_pointer_cast<PointerType>(objectType)->getElementType();
            auto typedPtrLoad = std::make_shared<TypedPtrLoadNode>(ptrVarName, elemType);
            typedPtrLoad->setLocation(node.getLocation());
            lastNode = typedPtrLoad;
            return;
        }

        if (methodName == "store") {
            if (node.getArguments().size() != 1) {
                ErrorHandler::getInstance().makeError(
                    "[RCE082]: '.store()' expects exactly one argument.",
                    node.getLocation());
                lastNode = nullptr;
                return;
            }

            if (unsafeDepth_ == 0) {
                ErrorHandler::getInstance().makeError(
                    "[RCE051]: '.store()' is only allowed inside 'unsafe' blocks.",
                    node.getLocation());
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
                    node.getLocation());
                lastNode = nullptr;
                return;
            }

            auto elemType = std::dynamic_pointer_cast<PointerType>(objectType)->getElementType();

            auto &argExpr = node.getArguments()[0];
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
                    argExpr->getLocation());
            }

            auto resultType = isAssignable ? elemType : TypeFactory::getPrimitive("unknown");
            auto typedPtrStore = std::make_shared<TypedPtrStoreNode>(ptrVarName, typedValue, resultType);
            typedPtrStore->setLocation(node.getLocation());
            lastNode = typedPtrStore;
            return;
        }

        ErrorHandler::getInstance().makeError(
            "[RCE078]: '." + methodName + "()' is not a pointer operation. " +
                "Only '.load()' (dereference) and '.store()' (store value) are allowed on pointers.",
            node.getLocation());
        lastNode = nullptr;
    }
} // namespace Ryntra::Compiler::Semantic
