#include "../IRGenerator.h"
#include "../ImmediateValue.h"

namespace Ryntra::IR {
    namespace Sem = Compiler::Semantic;

    void IRGenerator::visit(Compiler::Semantic::TypedUnaryOpNode &node) {
        node.getOperand()->accept(*this);
        auto operand = lastValue_;
        if (!operand) {
            lastValue_ = nullptr;
            return;
        }

        Instruction::Opcode irOp;
        switch (node.getOp()) {
        case Compiler::UnaryOpType::BitNot:
            irOp = Instruction::Opcode::BitNot;
            break;
        case Compiler::UnaryOpType::LogicalNot:
            irOp = Instruction::Opcode::LogicalNot;
            break;
        case Compiler::UnaryOpType::Negate: {
            auto zeroImm = std::make_shared<ImmediateValue>(operand->getType(), "0");
            auto zeroConst = builder_.createConstant(
                builder_.generateUniqueName(""), operand->getType(), zeroImm);
            auto result = builder_.createBinaryOp(
                Instruction::Opcode::Sub, builder_.generateUniqueName(""), zeroConst, operand);
            lastValue_ = result;
            return;
        }
        default:
            lastValue_ = nullptr;
            return;
        }

        auto result = builder_.createUnaryOp(irOp, builder_.generateUniqueName(""), operand);
        lastValue_ = result;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedBinaryOpNode &node) {
        node.getLeft()->accept(*this);
        auto lhs = lastValue_;

        node.getRight()->accept(*this);
        auto rhs = lastValue_;

        if (!lhs || !rhs) {
            lastValue_ = nullptr;
            return;
        }

        if (!lhs->getType()->isEqual(rhs->getType().get())) {
            if (lhs->getType()->isInt64() && rhs->getType()->isInt32()) {
                if (auto rhsImm = std::dynamic_pointer_cast<ImmediateValue>(rhs)) {
                    rhs = std::make_shared<ImmediateValue>(
                        Type::getInt64Type(), rhsImm->getLiteralValue());
                } else {
                    rhs = builder_.createSExt(
                        builder_.generateUniqueName(""), rhs, Type::getInt64Type());
                }
            } else if (lhs->getType()->isInt32() && rhs->getType()->isInt64()) {
                if (auto lhsImm = std::dynamic_pointer_cast<ImmediateValue>(lhs)) {
                    lhs = std::make_shared<ImmediateValue>(
                        Type::getInt64Type(), lhsImm->getLiteralValue());
                } else {
                    lhs = builder_.createSExt(
                        builder_.generateUniqueName(""), lhs, Type::getInt64Type());
                }
            }
        }

        Instruction::Opcode irOp;
        switch (node.getOp()) {
        case Compiler::BinaryOpType::Add:
            irOp = Instruction::Opcode::Add;
            break;
        case Compiler::BinaryOpType::Sub:
            irOp = Instruction::Opcode::Sub;
            break;
        case Compiler::BinaryOpType::Mul:
            irOp = Instruction::Opcode::Mul;
            break;
        case Compiler::BinaryOpType::Div:
            irOp = Instruction::Opcode::Div;
            break;
        case Compiler::BinaryOpType::Mod:
            irOp = Instruction::Opcode::Mod;
            break;
        case Compiler::BinaryOpType::BitAnd:
            irOp = Instruction::Opcode::BitAnd;
            break;
        case Compiler::BinaryOpType::BitOr:
            irOp = Instruction::Opcode::BitOr;
            break;
        case Compiler::BinaryOpType::BitXor:
            irOp = Instruction::Opcode::BitXor;
            break;
        case Compiler::BinaryOpType::Shl:
            irOp = Instruction::Opcode::Shl;
            break;
        case Compiler::BinaryOpType::Shr:
            irOp = Instruction::Opcode::Shr;
            break;
        }

        auto result = builder_.createBinaryOp(irOp, builder_.generateUniqueName(""), lhs, rhs);
        lastValue_ = result;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedCastNode &node) {
        node.getOperand()->accept(*this);
        auto operand = lastValue_;
        if (!operand) {
            lastValue_ = nullptr;
            return;
        }

        auto targetIRType = toIRType(node.getType());
        auto operandIRType = operand->getType();

        std::shared_ptr<Value> castOperand = operand;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(operand)) {
            auto constInst = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
            castOperand = constInst;
        }

        if (operandIRType->isInt32() && targetIRType->isInt64()) {
            lastValue_ = builder_.createSExt(
                builder_.generateUniqueName(""), castOperand, targetIRType);
        } else if (operandIRType->isInt64() && targetIRType->isInt32()) {
            lastValue_ = builder_.createTrunc(
                builder_.generateUniqueName(""), castOperand, targetIRType);
        } else {
            lastValue_ = castOperand;
        }
    }

    void IRGenerator::visit(Compiler::Semantic::TypedComparisonNode &node) {
        node.getLeft()->accept(*this);
        auto lhs = lastValue_;

        node.getRight()->accept(*this);
        auto rhs = lastValue_;

        if (!lhs || !rhs) {
            lastValue_ = nullptr;
            return;
        }

        if (!lhs->getType()->isEqual(rhs->getType().get())) {
            if (lhs->getType()->isInt64() && rhs->getType()->isInt32()) {
                if (auto rhsImm = std::dynamic_pointer_cast<ImmediateValue>(rhs))
                    rhs = std::make_shared<ImmediateValue>(Type::getInt64Type(), rhsImm->getLiteralValue());
                else
                    rhs = builder_.createSExt(builder_.generateUniqueName(""), rhs, Type::getInt64Type());
            } else if (lhs->getType()->isInt32() && rhs->getType()->isInt64()) {
                if (auto lhsImm = std::dynamic_pointer_cast<ImmediateValue>(lhs))
                    lhs = std::make_shared<ImmediateValue>(Type::getInt64Type(), lhsImm->getLiteralValue());
                else
                    lhs = builder_.createSExt(builder_.generateUniqueName(""), lhs, Type::getInt64Type());
            }
        }

        Instruction::Opcode irOp;
        switch (node.getOp()) {
        case Compiler::ComparisonOpType::Eq: irOp = Instruction::Opcode::Eq; break;
        case Compiler::ComparisonOpType::Ne: irOp = Instruction::Opcode::Ne; break;
        case Compiler::ComparisonOpType::Lt: irOp = Instruction::Opcode::Lt; break;
        case Compiler::ComparisonOpType::Gt: irOp = Instruction::Opcode::Gt; break;
        case Compiler::ComparisonOpType::Le: irOp = Instruction::Opcode::Le; break;
        case Compiler::ComparisonOpType::Ge: irOp = Instruction::Opcode::Ge; break;
        }

        lastValue_ = builder_.createCompare(irOp, builder_.generateUniqueName(""), lhs, rhs);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPrefixOpNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto varIRType = toIRType(node.getType());

        auto loadInst = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, varIRType);

        auto oneImm = std::make_shared<ImmediateValue>(varIRType, "1");
        auto oneConst = builder_.createConstant(
            builder_.generateUniqueName(""), varIRType, oneImm);

        Instruction::Opcode arithOp = (node.getOp() == Compiler::IncDecOpType::Increment)
                                          ? Instruction::Opcode::Add
                                          : Instruction::Opcode::Sub;
        auto result = builder_.createBinaryOp(
            arithOp, builder_.generateUniqueName(""), loadInst, oneConst);

        builder_.createStore(result, it->second);

        lastValue_ = result;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPostfixOpNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto varIRType = toIRType(node.getType());

        auto loadInst = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, varIRType);

        auto oneImm = std::make_shared<ImmediateValue>(varIRType, "1");
        auto oneConst = builder_.createConstant(
            builder_.generateUniqueName(""), varIRType, oneImm);

        Instruction::Opcode arithOp = (node.getOp() == Compiler::IncDecOpType::Increment)
                                          ? Instruction::Opcode::Add
                                          : Instruction::Opcode::Sub;
        auto newVal = builder_.createBinaryOp(
            arithOp, builder_.generateUniqueName(""), loadInst, oneConst);

        builder_.createStore(newVal, it->second);

        lastValue_ = loadInst;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedAssignmentNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        node.getRHS()->accept(*this);
        if (lastValue_) {
            std::shared_ptr<Value> storeVal = lastValue_;
            if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(lastValue_)) {
                storeVal = builder_.createConstant(
                    builder_.generateUniqueName(""),
                    imm->getType(), imm);
            }
            builder_.createStore(storeVal, it->second);
            lastValue_ = storeVal;
        }
    }
} // namespace Ryntra::IR
