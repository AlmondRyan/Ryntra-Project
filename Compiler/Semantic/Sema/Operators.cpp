#include "../SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {
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

        auto resultType = isLong ? longType : intType;
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

        auto leftType = typedLeft->getType();
        auto rightType = typedRight->getType();
        bool leftIsPtr = leftType->getKind() == TypeKind::POINTER;
        bool rightIsPtr = rightType->getKind() == TypeKind::POINTER;
        bool leftIsNull = leftType->toString() == "null";
        bool rightIsNull = rightType->toString() == "null";

        if (leftIsPtr || rightIsPtr || leftIsNull || rightIsNull) {
            if (leftIsNull && rightIsNull) {
                ErrorHandler::getInstance().makeError(
                    "[RCE055]: Cannot compare 'null' with 'null'.",
                    node.getLocation());
                lastNode = nullptr;
                return;
            }
            if (node.getOp() != ComparisonOpType::Eq && node.getOp() != ComparisonOpType::Ne) {
                ErrorHandler::getInstance().makeError(
                    "[RCE055]: Only '==' and '!=' are allowed for pointer comparison.",
                    node.getLocation());
                lastNode = nullptr;
                return;
            }
            auto boolType = TypeFactory::getPrimitive("bool");
            auto typedCmp = std::make_shared<TypedComparisonNode>(typedLeft, node.getOp(), typedRight, boolType);
            typedCmp->setLocation(node.getLocation());
            lastNode = typedCmp;
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

    void SemanticAnalyzer::visit(ConditionalAndNode &node) {
        node.getLeft()->accept(*this);
        auto typedLeft = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        node.getRight()->accept(*this);
        auto typedRight = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (!typedLeft || !typedRight) {
            lastNode = nullptr;
            return;
        }

        auto boolType = TypeFactory::getPrimitive("bool");

        if (!typedLeft->getType()->equals(*boolType)) {
            ErrorHandler::getInstance().makeError(
                "[RCE064]: Left operand of '&&' must be 'bool', but got '" +
                    typedLeft->getType()->toString() + "'.",
                node.getLeft()->getLocation());
        }

        if (!typedRight->getType()->equals(*boolType)) {
            ErrorHandler::getInstance().makeError(
                "[RCE065]: Right operand of '&&' must be 'bool', but got '" +
                    typedRight->getType()->toString() + "'.",
                node.getRight()->getLocation());
        }

        auto typedNode = std::make_shared<TypedConditionalAndNode>(typedLeft, typedRight, boolType);
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(ConditionalOrNode &node) {
        node.getLeft()->accept(*this);
        auto typedLeft = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        node.getRight()->accept(*this);
        auto typedRight = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (!typedLeft || !typedRight) {
            lastNode = nullptr;
            return;
        }

        auto boolType = TypeFactory::getPrimitive("bool");

        if (!typedLeft->getType()->equals(*boolType)) {
            ErrorHandler::getInstance().makeError(
                "[RCE066]: Left operand of '||' must be 'bool', but got '" +
                    typedLeft->getType()->toString() + "'.",
                node.getLeft()->getLocation());
        }

        if (!typedRight->getType()->equals(*boolType)) {
            ErrorHandler::getInstance().makeError(
                "[RCE067]: Right operand of '||' must be 'bool', but got '" +
                    typedRight->getType()->toString() + "'.",
                node.getRight()->getLocation());
        }

        auto typedNode = std::make_shared<TypedConditionalOrNode>(typedLeft, typedRight, boolType);
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }
} // namespace Ryntra::Compiler::Semantic
