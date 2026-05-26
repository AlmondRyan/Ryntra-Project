#include "../IRGenerator.h"
#include "../ImmediateValue.h"

namespace Ryntra::IR {
    namespace Sem = Compiler::Semantic;

    void IRGenerator::visit(Compiler::Semantic::TypedVariableDeclarationNode &node) {
        auto varName = node.getName();
        auto varIRType = toIRType(node.getType());

        auto allocaInst = builder_.createAlloca(
            builder_.generateUniqueName(varName + "."), varIRType);
        allocaMap_[varName] = allocaInst;

        if (node.getInitializer()) {
            node.getInitializer()->accept(*this);
            if (lastValue_) {
                std::shared_ptr<Value> storeVal = lastValue_;
                if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(lastValue_)) {
                    storeVal = builder_.createConstant(
                        builder_.generateUniqueName(""),
                        imm->getType(), imm);
                }
                builder_.createStore(storeVal, allocaInst);
                lastValue_ = nullptr;
            }
        }
    }

    void IRGenerator::visit(Compiler::Semantic::TypedArrayDeclarationNode &node) {
        auto varName = node.getName();
        auto elementIRType = toIRType(node.getElementType());

        node.getSize()->accept(*this);
        auto sizeVal = lastValue_;
        if (!sizeVal) {
            lastValue_ = nullptr;
            return;
        }

        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(sizeVal)) {
            sizeVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        auto newArrayInst = builder_.createNewArray(
            builder_.generateUniqueName("arr." + varName + "."),
            elementIRType, sizeVal);

        auto arrIRType = std::make_shared<IR::ArrayType>(elementIRType);
        auto allocaInst = builder_.createAlloca(
            builder_.generateUniqueName(varName + "."), arrIRType);
        allocaMap_[varName] = allocaInst;

        builder_.createStore(newArrayInst, allocaInst);
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedVariableNode &node) {
        auto it = allocaMap_.find(node.getName());
        if (it != allocaMap_.end()) {
            auto loadType = toIRType(node.getType());
            lastValue_ = builder_.createLoad(
                builder_.generateUniqueName(""),
                it->second,
                loadType);
        } else {
            lastValue_ = nullptr;
        }
    }

    void IRGenerator::visit(Compiler::Semantic::TypedArrayIndexAccessNode &node) {
        auto it = allocaMap_.find(node.getArrayName());
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto elemIRType = toIRType(node.getType());

        auto allocaInst = it->second;
        auto arrIRType = std::make_shared<IR::ArrayType>(elemIRType);
        auto arrayVal = builder_.createLoad(
            builder_.generateUniqueName(""), allocaInst, arrIRType);

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

        auto refType = std::make_shared<IR::RefType>(elemIRType);
        auto arrRef = builder_.createArrRef(
            builder_.generateUniqueName(""), arrayVal, indexVal, refType);
        lastValue_ = builder_.createRefLoad(
            builder_.generateUniqueName(""), arrRef, elemIRType);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedArrayIndexAssignmentNode &node) {
        auto it = allocaMap_.find(node.getArrayName());
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto elemIRType = toIRType(node.getType());

        auto allocaInst = it->second;
        auto arrIRType = std::make_shared<IR::ArrayType>(elemIRType);
        auto arrayVal = builder_.createLoad(
            builder_.generateUniqueName(""), allocaInst, arrIRType);

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

        auto refType = std::make_shared<IR::RefType>(elemIRType);
        auto arrRef = builder_.createArrRef(
            builder_.generateUniqueName(""), arrayVal, indexVal, refType);

        builder_.createRefStore(arrRef, storeVal);
        lastValue_ = storeVal;
    }
} // namespace Ryntra::IR
