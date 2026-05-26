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
} // namespace Ryntra::Compiler::Semantic
