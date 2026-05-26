#include "../IRGenerator.h"
#include "../ImmediateValue.h"

namespace Ryntra::IR {
    namespace Sem = Compiler::Semantic;

    void IRGenerator::visit(Compiler::Semantic::TypedConditionalAndNode &node) {
        auto currentFunc = functionMap_[currentFunctionName_];
        if (!currentFunc)
            return;

        std::string suffix = std::to_string(ifCounter_++);

        auto resultAlloca = builder_.createAlloca(
            builder_.generateUniqueName("condand.result."), Type::getBoolType());

        node.getLeft()->accept(*this);
        auto leftVal = lastValue_;
        if (!leftVal) {
            lastValue_ = nullptr;
            return;
        }

        auto materialize = [&](std::shared_ptr<Value> v) -> std::shared_ptr<Value> {
            if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(v)) {
                return builder_.createConstant(
                    builder_.generateUniqueName(""), imm->getType(), imm);
            }
            return v;
        };

        auto leftMaterialized = materialize(leftVal);

        auto evalRightBlock = builder_.createBasicBlock("condand.right." + suffix);
        auto trueBlock = builder_.createBasicBlock("condand.true." + suffix);
        auto falseBlock = builder_.createBasicBlock("condand.false." + suffix);
        auto endBlock = builder_.createBasicBlock("condand.end." + suffix);

        builder_.createCondBr(leftMaterialized, evalRightBlock->getName(), falseBlock->getName());
        currentFunc->addBasicBlock(evalRightBlock);
        builder_.setInsertPoint(evalRightBlock);

        node.getRight()->accept(*this);
        auto rightVal = lastValue_;
        if (!rightVal) {
            lastValue_ = nullptr;
            return;
        }
        auto rightMaterialized = materialize(rightVal);

        builder_.createCondBr(rightMaterialized, trueBlock->getName(), falseBlock->getName());

        currentFunc->addBasicBlock(trueBlock);
        builder_.setInsertPoint(trueBlock);
        auto trueImm = std::make_shared<ImmediateValue>(Type::getBoolType(), "1");
        auto trueConst = builder_.createConstant(
            builder_.generateUniqueName(""), Type::getBoolType(), trueImm);
        builder_.createStore(trueConst, resultAlloca);
        builder_.createBr(endBlock->getName());

        currentFunc->addBasicBlock(falseBlock);
        builder_.setInsertPoint(falseBlock);
        auto falseImm = std::make_shared<ImmediateValue>(Type::getBoolType(), "0");
        auto falseConst = builder_.createConstant(
            builder_.generateUniqueName(""), Type::getBoolType(), falseImm);
        builder_.createStore(falseConst, resultAlloca);
        builder_.createBr(endBlock->getName());

        currentFunc->addBasicBlock(endBlock);
        builder_.setInsertPoint(endBlock);
        lastValue_ = builder_.createLoad(
            builder_.generateUniqueName(""), resultAlloca, Type::getBoolType());
    }

    void IRGenerator::visit(Compiler::Semantic::TypedConditionalOrNode &node) {
        auto currentFunc = functionMap_[currentFunctionName_];
        if (!currentFunc)
            return;

        std::string suffix = std::to_string(ifCounter_++);

        auto resultAlloca = builder_.createAlloca(
            builder_.generateUniqueName("condor.result."), Type::getBoolType());

        node.getLeft()->accept(*this);
        auto leftVal = lastValue_;
        if (!leftVal) {
            lastValue_ = nullptr;
            return;
        }

        auto materialize = [&](std::shared_ptr<Value> v) -> std::shared_ptr<Value> {
            if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(v)) {
                return builder_.createConstant(
                    builder_.generateUniqueName(""), imm->getType(), imm);
            }
            return v;
        };

        auto leftMaterialized = materialize(leftVal);

        auto evalRightBlock = builder_.createBasicBlock("condor.right." + suffix);
        auto trueBlock = builder_.createBasicBlock("condor.true." + suffix);
        auto falseBlock = builder_.createBasicBlock("condor.false." + suffix);
        auto endBlock = builder_.createBasicBlock("condor.end." + suffix);

        builder_.createCondBr(leftMaterialized, trueBlock->getName(), evalRightBlock->getName());
        currentFunc->addBasicBlock(evalRightBlock);
        builder_.setInsertPoint(evalRightBlock);

        node.getRight()->accept(*this);
        auto rightVal = lastValue_;
        if (!rightVal) {
            lastValue_ = nullptr;
            return;
        }
        auto rightMaterialized = materialize(rightVal);

        builder_.createCondBr(rightMaterialized, trueBlock->getName(), falseBlock->getName());

        currentFunc->addBasicBlock(trueBlock);
        builder_.setInsertPoint(trueBlock);
        auto trueImm = std::make_shared<ImmediateValue>(Type::getBoolType(), "1");
        auto trueConst = builder_.createConstant(
            builder_.generateUniqueName(""), Type::getBoolType(), trueImm);
        builder_.createStore(trueConst, resultAlloca);
        builder_.createBr(endBlock->getName());

        currentFunc->addBasicBlock(falseBlock);
        builder_.setInsertPoint(falseBlock);
        auto falseImm = std::make_shared<ImmediateValue>(Type::getBoolType(), "0");
        auto falseConst = builder_.createConstant(
            builder_.generateUniqueName(""), Type::getBoolType(), falseImm);
        builder_.createStore(falseConst, resultAlloca);
        builder_.createBr(endBlock->getName());

        currentFunc->addBasicBlock(endBlock);
        builder_.setInsertPoint(endBlock);
        lastValue_ = builder_.createLoad(
            builder_.generateUniqueName(""), resultAlloca, Type::getBoolType());
    }
} // namespace Ryntra::IR
