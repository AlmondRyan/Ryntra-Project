#include "../SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {
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

        if (varSTType->getKind() == STType::TypeKind::Reference) {
            auto &refSTType = dynamic_cast<const STType::ReferenceType &>(*varSTType);
            auto elemTyped = toTypedType(refSTType.getElementType());
            auto rhsType = typedRHS->getType();

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

        bool isAssignable = varType->equals(*rhsType) ||
                            (rhsType->toString() == "int" && varType->toString() == "long");
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

    void SemanticAnalyzer::visit(NewExpressionNode &node) {
        node.getElementType()->accept(*this);
        auto elemSTType = lastType;
        if (!elemSTType) {
            lastNode = nullptr;
            return;
        }

        auto elemType = toTypedType(elemSTType);

        std::shared_ptr<TypedExpressionNode> typedInit = nullptr;
        if (node.getInitializer()) {
            node.getInitializer()->accept(*this);
            typedInit = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
            if (!typedInit) {
                lastNode = nullptr;
                return;
            }
            if (!typedInit->getType()->equals(*elemType)) {
                ErrorHandler::getInstance().makeError(
                    "[RCE056]: Initializer type '" + typedInit->getType()->toString() +
                        "' does not match element type '" + elemType->toString() + "'.",
                    node.getLocation());
                lastNode = nullptr;
                return;
            }
        }

        auto ptrType = TypeFactory::getPointer(elemType);
        auto typedNew = std::make_shared<TypedNewNode>(elemType, typedInit, ptrType);
        typedNew->setLocation(node.getLocation());
        lastNode = typedNew;
    }

    void SemanticAnalyzer::visit(DeleteStatementNode &node) {
        if (unsafeDepth_ == 0) {
            ErrorHandler::getInstance().makeError(
                "[RCE057]: 'delete' is only allowed inside 'unsafe' blocks.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        node.getExpression()->accept(*this);
        auto typedExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedExpr) {
            lastNode = nullptr;
            return;
        }

        auto exprType = typedExpr->getType();
        if (exprType->getKind() != TypeKind::POINTER && exprType->toString() != "unknown") {
            ErrorHandler::getInstance().makeError(
                "[RCE058]: 'delete' requires a pointer expression, but got '" +
                    exprType->toString() + "'.",
                node.getLocation());
            lastNode = nullptr;
            return;
        }

        auto typedDelete = std::make_shared<TypedDeleteNode>(typedExpr);
        typedDelete->setLocation(node.getLocation());
        lastNode = typedDelete;
    }

    void SemanticAnalyzer::visit(ArrayIndexAccessNode &node) {
        node.getArrayExpr()->accept(*this);
        auto typedExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedExpr) {
            lastNode = nullptr;
            return;
        }

        auto exprType = typedExpr->getType();

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
                "[RCE038]: Index must be 'int' or 'long', but got '" +
                    typedIndex->getType()->toString() + "'.",
                node.getIndex()->getLocation());
        }

        if (exprType->getKind() == TypeKind::ARRAY) {
            std::string arrayName;
            if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(typedExpr)) {
                arrayName = varNode->getName();
            } else {
                ErrorHandler::getInstance().makeError(
                    "[RCE035]: Array expression is not a variable.",
                    node.getArrayExpr()->getLocation());
                lastNode = nullptr;
                return;
            }

            auto &arrType = static_cast<const ArrayType &>(*exprType);
            auto elemType = arrType.getElementType();

            auto typedAccess = std::make_shared<TypedArrayIndexAccessNode>(arrayName, typedIndex, elemType);
            typedAccess->setLocation(node.getLocation());
            lastNode = typedAccess;
            return;
        }

        if (exprType->getKind() == TypeKind::POINTER) {
            auto &ptrType = static_cast<const PointerType &>(*exprType);
            auto elemType = ptrType.getElementType();

            auto typedPtrAccess = std::make_shared<TypedPtrIndexAccessNode>(typedExpr, typedIndex, elemType);
            typedPtrAccess->setLocation(node.getLocation());
            lastNode = typedPtrAccess;
            return;
        }

        ErrorHandler::getInstance().makeError(
            "[RCE037]: Subscript operator '[]' requires an array or pointer expression, but got '" +
                exprType->toString() + "'.",
            node.getArrayExpr()->getLocation());
        lastNode = nullptr;
    }

    void SemanticAnalyzer::visit(ArrayIndexAssignmentNode &node) {
        node.getArrayExpr()->accept(*this);
        auto typedExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedExpr) {
            lastNode = nullptr;
            return;
        }

        auto exprType = typedExpr->getType();

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
                "[RCE042]: Index must be 'int' or 'long', but got '" +
                    typedIndex->getType()->toString() + "'.",
                node.getIndex()->getLocation());
        }

        node.getValue()->accept(*this);
        auto typedValue = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        if (!typedValue) {
            lastNode = nullptr;
            return;
        }

        if (exprType->getKind() == TypeKind::ARRAY) {
            std::string arrayName;
            if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(typedExpr)) {
                arrayName = varNode->getName();
            } else {
                ErrorHandler::getInstance().makeError(
                    "[RCE039]: Array expression is not a variable.",
                    node.getArrayExpr()->getLocation());
                lastNode = nullptr;
                return;
            }

            auto &arrType = static_cast<const ArrayType &>(*exprType);
            auto elemType = arrType.getElementType();

            bool isAssignable = elemType->equals(*typedValue->getType()) ||
                                (typedValue->getType()->toString() == "int" && elemType->toString() == "long");
            if (!isAssignable && typedValue->getType()->toString() != "unknown") {
                ErrorHandler::getInstance().makeError(
                    "[RCE043]: Cannot assign value of type '" + typedValue->getType()->toString() +
                        "' to array element of type '" + elemType->toString() + "'.",
                    node.getValue()->getLocation());
            }

            auto resultType = isAssignable ? elemType : TypeFactory::getPrimitive("unknown");
            auto typedAssign = std::make_shared<TypedArrayIndexAssignmentNode>(arrayName, typedIndex, typedValue, resultType);
            typedAssign->setLocation(node.getLocation());
            lastNode = typedAssign;
            return;
        }

        if (exprType->getKind() == TypeKind::POINTER) {
            auto &ptrType = static_cast<const PointerType &>(*exprType);
            auto elemType = ptrType.getElementType();

            bool isAssignable = elemType->equals(*typedValue->getType()) ||
                                (typedValue->getType()->toString() == "int" && elemType->toString() == "long");
            if (!isAssignable && typedValue->getType()->toString() != "unknown") {
                ErrorHandler::getInstance().makeError(
                    "[RCE060]: Cannot assign value of type '" + typedValue->getType()->toString() +
                        "' to pointer element of type '" + elemType->toString() + "'.",
                    node.getValue()->getLocation());
            }

            auto resultType = isAssignable ? elemType : TypeFactory::getPrimitive("unknown");
            auto typedAssign = std::make_shared<TypedPtrIndexAssignmentNode>(typedExpr, typedIndex, typedValue, resultType);
            typedAssign->setLocation(node.getLocation());
            lastNode = typedAssign;
            return;
        }

        ErrorHandler::getInstance().makeError(
            "[RCE041]: Subscript assignment '[]=' requires an array or pointer expression, but got '" +
                exprType->toString() + "'.",
            node.getArrayExpr()->getLocation());
        lastNode = nullptr;
    }
} // namespace Ryntra::Compiler::Semantic
