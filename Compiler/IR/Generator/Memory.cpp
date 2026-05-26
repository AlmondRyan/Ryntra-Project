#include "../IRGenerator.h"
#include "../ImmediateValue.h"

namespace Ryntra::IR {
    namespace Sem = Compiler::Semantic;

    void IRGenerator::visit(Compiler::Semantic::TypedRefCreateNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto refIRType = toIRType(node.getType());
        lastValue_ = builder_.createRefCreate(
            builder_.generateUniqueName(""), refIRType, it->second);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedRefLoadNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto refIRType = std::make_shared<IR::RefType>(toIRType(node.getType()));
        auto refVal = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, refIRType);

        auto elemIRType = toIRType(node.getType());
        lastValue_ = builder_.createRefLoad(
            builder_.generateUniqueName(""), refVal, elemIRType);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedRefAssignNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto refIRType = std::make_shared<IR::RefType>(toIRType(node.getType()));
        auto refVal = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, refIRType);

        node.getRHS()->accept(*this);
        if (!lastValue_) {
            lastValue_ = nullptr;
            return;
        }

        std::shared_ptr<Value> storeVal = lastValue_;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(lastValue_)) {
            storeVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        builder_.createRefStore(refVal, storeVal);
        lastValue_ = storeVal;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPtrCreateNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto ptrIRType = toIRType(node.getType());
        lastValue_ = builder_.createPtrCreate(
            builder_.generateUniqueName(""), ptrIRType, it->second);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPtrLoadNode &node) {
        auto ptrVarName = node.getPtrVarName();
        auto it = allocaMap_.find(ptrVarName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto ptrIRType = std::make_shared<IR::PtrType>(toIRType(node.getType()));
        auto ptrVal = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, ptrIRType);

        auto elemIRType = toIRType(node.getType());
        lastValue_ = builder_.createPtrLoad(
            builder_.generateUniqueName(""), ptrVal, elemIRType);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPtrStoreNode &node) {
        auto ptrVarName = node.getPtrVarName();
        auto it = allocaMap_.find(ptrVarName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto ptrIRType = std::make_shared<IR::PtrType>(toIRType(node.getType()));
        auto ptrVal = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, ptrIRType);

        node.getRHS()->accept(*this);
        if (!lastValue_) {
            lastValue_ = nullptr;
            return;
        }

        std::shared_ptr<Value> storeVal = lastValue_;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(lastValue_)) {
            storeVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        builder_.createPtrStore(ptrVal, storeVal);
        lastValue_ = storeVal;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPtrOffsetNode &node) {
        auto ptrVarName = node.getPtrVarName();
        auto it = allocaMap_.find(ptrVarName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto ptrIRType = std::make_shared<IR::PtrType>(Type::getInt32Type());
        auto ptrVal = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, ptrIRType);

        std::shared_ptr<Value> ptrForArith = ptrVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(ptrVal)) {
            ptrForArith = builder_.createConstant(
                builder_.generateUniqueName(""), Type::getInt32Type(), imm);
        }

        node.getOffset()->accept(*this);
        auto offsetVal = lastValue_;
        if (!offsetVal) {
            lastValue_ = nullptr;
            return;
        }
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(offsetVal)) {
            offsetVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        auto arithOp = node.getIsAdd() ? Instruction::Opcode::Add : Instruction::Opcode::Sub;
        std::vector<std::shared_ptr<Value>> arithOperands = {ptrForArith, offsetVal};
        auto newSlotInst = std::make_shared<Instruction>(
            arithOp, Type::getInt32Type(), arithOperands,
            builder_.generateUniqueName(""));
        builder_.addInstruction(newSlotInst);

        auto ptrResultType = toIRType(node.getType());
        std::vector<std::shared_ptr<Value>> createOperands = {newSlotInst};
        auto ptrResult = std::make_shared<Instruction>(
            Instruction::Opcode::PtrCreate, ptrResultType, createOperands,
            builder_.generateUniqueName(""));
        builder_.addInstruction(ptrResult);
        lastValue_ = ptrResult;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPtrDiffNode &node) {
        auto leftIt = allocaMap_.find(node.getLeftPtrName());
        auto rightIt = allocaMap_.find(node.getRightPtrName());
        if (leftIt == allocaMap_.end() || rightIt == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto ptrIRType = std::make_shared<IR::PtrType>(Type::getInt32Type());
        auto leftPtrVal = builder_.createLoad(
            builder_.generateUniqueName(""), leftIt->second, ptrIRType);
        auto rightPtrVal = builder_.createLoad(
            builder_.generateUniqueName(""), rightIt->second, ptrIRType);

        std::shared_ptr<Value> leftForArith = leftPtrVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(leftPtrVal)) {
            leftForArith = builder_.createConstant(
                builder_.generateUniqueName(""), Type::getInt32Type(), imm);
        }
        std::shared_ptr<Value> rightForArith = rightPtrVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(rightPtrVal)) {
            rightForArith = builder_.createConstant(
                builder_.generateUniqueName(""), Type::getInt32Type(), imm);
        }

        std::vector<std::shared_ptr<Value>> operands = {leftForArith, rightForArith};
        auto result = std::make_shared<Instruction>(
            Instruction::Opcode::Sub, Type::getInt32Type(), operands,
            builder_.generateUniqueName(""));
        builder_.addInstruction(result);
        lastValue_ = result;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPtrFromArrayNode &node) {
        auto varName = node.getArrayName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto &semPtrType = static_cast<const Sem::PointerType &>(*node.getType());
        auto elemIRType = toIRType(semPtrType.getElementType());

        auto arrAlloca = it->second;
        auto arrIRType = std::make_shared<IR::ArrayType>(elemIRType);
        auto arrayVal = builder_.createLoad(
            builder_.generateUniqueName(""), arrAlloca, arrIRType);

        auto ptrIRType = toIRType(node.getType());
        lastValue_ = builder_.createPtrFromArray(
            builder_.generateUniqueName(""), ptrIRType, arrayVal);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedUnsafeBlockNode &node) {
        node.getBody()->accept(*this);
    }

    void IRGenerator::visit(Sem::TypedNewNode &node) {
        std::shared_ptr<Value> initVal;
        if (node.getInitializer()) {
            node.getInitializer()->accept(*this);
            initVal = lastValue_;
            if (!initVal) {
                lastValue_ = nullptr;
                return;
            }
        } else {
            auto elemIRType = toIRType(node.getElementType());
            if (elemIRType->isInt32()) {
                initVal = std::make_shared<ImmediateValue>(Type::getInt32Type(), "0");
            } else if (elemIRType->isInt64()) {
                initVal = std::make_shared<ImmediateValue>(Type::getInt64Type(), "0");
            } else if (elemIRType->isBool()) {
                initVal = std::make_shared<ImmediateValue>(Type::getBoolType(), "0");
            } else {
                lastValue_ = nullptr;
                return;
            }
        }

        std::shared_ptr<Value> materialized = initVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(initVal)) {
            materialized = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        auto ptrType = toIRType(node.getType());
        lastValue_ = builder_.createNewHeap(
            builder_.generateUniqueName(""), ptrType, materialized);
    }

    void IRGenerator::visit(Sem::TypedDeleteNode &node) {
        node.getPtrExpr()->accept(*this);
        auto ptrVal = lastValue_;
        if (!ptrVal) {
            lastValue_ = nullptr;
            return;
        }

        std::shared_ptr<Value> materialized = ptrVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(ptrVal)) {
            materialized = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        builder_.createDeleteHeap(materialized);
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedFixedNode &node) {
        node.getInitExpr()->accept(*this);
        auto initVal = lastValue_;
        if (!initVal) {
            lastValue_ = nullptr;
            return;
        }

        std::shared_ptr<Value> materialized = initVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(initVal)) {
            materialized = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        builder_.createPinArray(materialized);

        auto ptrIRType = toIRType(node.getPtrType());
        auto allocaInst = builder_.createAlloca(node.getVarName(), ptrIRType);
        allocaMap_[node.getVarName()] = allocaInst;
        builder_.createStore(materialized, allocaInst);

        node.getBody()->accept(*this);

        auto loadedPtr = builder_.createLoad(
            builder_.generateUniqueName(""), allocaInst, ptrIRType);
        builder_.createUnpinArray(loadedPtr);

        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedPtrIndexAccessNode &node) {
        node.getPtrExpr()->accept(*this);
        auto ptrVal = lastValue_;
        if (!ptrVal) {
            lastValue_ = nullptr;
            return;
        }

        std::shared_ptr<Value> ptrMaterialized = ptrVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(ptrVal)) {
            ptrMaterialized = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        node.getIndex()->accept(*this);
        auto indexVal = lastValue_;
        if (!indexVal) {
            lastValue_ = nullptr;
            return;
        }
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(indexVal)) {
            indexVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        auto elemIRType = toIRType(node.getType());
        auto refType = std::make_shared<IR::RefType>(elemIRType);

        auto ptrIndexRef = builder_.createPtrIndexRef(
            builder_.generateUniqueName(""), ptrMaterialized, indexVal, refType);

        lastValue_ = builder_.createRefLoad(
            builder_.generateUniqueName(""), ptrIndexRef, elemIRType);
    }

    void IRGenerator::visit(Sem::TypedPtrIndexAssignmentNode &node) {
        node.getPtrExpr()->accept(*this);
        auto ptrVal = lastValue_;
        if (!ptrVal) {
            lastValue_ = nullptr;
            return;
        }

        std::shared_ptr<Value> ptrMaterialized = ptrVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(ptrVal)) {
            ptrMaterialized = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        node.getIndex()->accept(*this);
        auto indexVal = lastValue_;
        if (!indexVal) {
            lastValue_ = nullptr;
            return;
        }
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(indexVal)) {
            indexVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        node.getValue()->accept(*this);
        auto valueVal = lastValue_;
        if (!valueVal) {
            lastValue_ = nullptr;
            return;
        }
        std::shared_ptr<Value> storeVal = valueVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(valueVal)) {
            storeVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        auto refType = std::make_shared<IR::RefType>(Type::getInt32Type());
        auto ptrIndexRef = builder_.createPtrIndexRef(
            builder_.generateUniqueName(""), ptrMaterialized, indexVal, refType);

        builder_.createRefStore(ptrIndexRef, storeVal);
        lastValue_ = storeVal;
    }
} // namespace Ryntra::IR
