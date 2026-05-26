#include "../IRGenerator.h"

namespace Ryntra::IR {
    namespace Sem = Compiler::Semantic;

    void IRGenerator::visit(Sem::TypedProgramNode &node) {
        for (const auto &func : node.getFunctions()) {
            auto retType = toIRType(func->getReturnType());
            auto irFunc = builder_.createFunction(func->getName(), retType, {});
            functionMap_[func->getName()] = irFunc;
        }

        for (const auto &func : node.getFunctions()) {
            func->accept(*this);
        }
    }

    void IRGenerator::visit(Sem::TypedFunctionDefinitionNode &node) {
        auto irFunc = functionMap_[node.getName()];
        if (!irFunc)
            return;

        currentFunctionName_ = node.getName();
        ifCounter_ = 0;

        auto entry = builder_.createBasicBlock("entry");
        irFunc->addBasicBlock(entry);
        builder_.setInsertPoint(entry);

        node.getBody()->accept(*this);

        if (irFunc->getReturnType()->isVoid()) {
            auto &insts = entry->getInstructions();
            if (insts.empty() ||
                insts.back()->getOpcode() != Instruction::Opcode::Return) {
                builder_.createReturn("");
            }
        }
    }

    void IRGenerator::visit(Sem::TypedIfNode &node) {
        auto currentFunc = functionMap_[currentFunctionName_];
        if (!currentFunc)
            return;

        std::string suffix = std::to_string(ifCounter_++);

        node.getCondition()->accept(*this);
        auto condVal = lastValue_;
        if (!condVal) {
            lastValue_ = nullptr;
            return;
        }

        auto thenBlock = builder_.createBasicBlock("if.then." + suffix);
        auto elseBlock = builder_.createBasicBlock("if.else." + suffix);
        auto endBlock = builder_.createBasicBlock("if.end." + suffix);

        std::string trueTarget = thenBlock->getName();
        std::string falseTarget;

        if (node.getElseBranch()) {
            falseTarget = elseBlock->getName();
        } else {
            falseTarget = endBlock->getName();
        }

        builder_.createCondBr(condVal, trueTarget, falseTarget);
        currentFunc->addBasicBlock(thenBlock);
        builder_.setInsertPoint(thenBlock);

        node.getThenBlock()->accept(*this);

        auto curBlock = builder_.getInsertPoint();
        if (curBlock) {
            auto &insts = curBlock->getInstructions();
            if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                builder_.createBr(endBlock->getName());
            }
        }

        if (node.getElseBranch()) {
            currentFunc->addBasicBlock(elseBlock);
            builder_.setInsertPoint(elseBlock);

            if (auto typedElseBlock = std::dynamic_pointer_cast<Sem::TypedBlockNode>(node.getElseBranch())) {
                typedElseBlock->accept(*this);
            } else if (auto typedElseIf = std::dynamic_pointer_cast<Sem::TypedIfNode>(node.getElseBranch())) {
                typedElseIf->accept(*this);
            }

            curBlock = builder_.getInsertPoint();
            if (curBlock) {
                auto &insts = curBlock->getInstructions();
                if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                    builder_.createBr(endBlock->getName());
                }
            }
        }

        currentFunc->addBasicBlock(endBlock);
        builder_.setInsertPoint(endBlock);
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedWhileNode &node) {
        auto currentFunc = functionMap_[currentFunctionName_];
        if (!currentFunc)
            return;

        std::string suffix = std::to_string(ifCounter_++);

        auto condBlock = builder_.createBasicBlock("while.cond." + suffix);
        auto bodyBlock = builder_.createBasicBlock("while.body." + suffix);
        auto endBlock = builder_.createBasicBlock("while.end." + suffix);

        builder_.createBr(condBlock->getName());
        currentFunc->addBasicBlock(condBlock);
        builder_.setInsertPoint(condBlock);

        node.getCondition()->accept(*this);
        auto condVal = lastValue_;
        if (!condVal) {
            lastValue_ = nullptr;
            return;
        }

        builder_.createCondBr(condVal, bodyBlock->getName(), endBlock->getName());
        currentFunc->addBasicBlock(bodyBlock);
        builder_.setInsertPoint(bodyBlock);

        loopStack_.push_back({condBlock->getName(), endBlock->getName()});
        node.getBody()->accept(*this);
        loopStack_.pop_back();

        auto curBlock = builder_.getInsertPoint();
        if (curBlock) {
            auto &insts = curBlock->getInstructions();
            if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                builder_.createBr(condBlock->getName());
            }
        }

        currentFunc->addBasicBlock(endBlock);
        builder_.setInsertPoint(endBlock);
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedForNode &node) {
        auto currentFunc = functionMap_[currentFunctionName_];
        if (!currentFunc)
            return;

        std::string suffix = std::to_string(ifCounter_++);

        if (node.getInit()) {
            node.getInit()->accept(*this);
        }

        auto condBlock = builder_.createBasicBlock("for.cond." + suffix);
        auto bodyBlock = builder_.createBasicBlock("for.body." + suffix);
        auto iterBlock = builder_.createBasicBlock("for.iter." + suffix);
        auto endBlock = builder_.createBasicBlock("for.end." + suffix);

        builder_.createBr(condBlock->getName());
        currentFunc->addBasicBlock(condBlock);
        builder_.setInsertPoint(condBlock);

        std::shared_ptr<Value> condVal;
        if (node.getCondition()) {
            node.getCondition()->accept(*this);
            condVal = lastValue_;
        } else {
            condVal = std::make_shared<ImmediateValue>(Type::getBoolType(), "1");
        }

        if (!condVal) {
            lastValue_ = nullptr;
            return;
        }

        builder_.createCondBr(condVal, bodyBlock->getName(), endBlock->getName());
        currentFunc->addBasicBlock(bodyBlock);
        builder_.setInsertPoint(bodyBlock);

        loopStack_.push_back({iterBlock->getName(), endBlock->getName()});
        node.getBody()->accept(*this);
        loopStack_.pop_back();

        auto curBlock = builder_.getInsertPoint();
        if (curBlock) {
            auto &insts = curBlock->getInstructions();
            if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                builder_.createBr(iterBlock->getName());
            }
        }

        currentFunc->addBasicBlock(iterBlock);
        builder_.setInsertPoint(iterBlock);

        if (node.getOperation()) {
            node.getOperation()->accept(*this);
        }

        curBlock = builder_.getInsertPoint();
        if (curBlock) {
            auto &insts = curBlock->getInstructions();
            if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                builder_.createBr(condBlock->getName());
            }
        }

        currentFunc->addBasicBlock(endBlock);
        builder_.setInsertPoint(endBlock);
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedBreakNode &node) {
        if (loopStack_.empty())
            return;
        auto curBlock = builder_.getInsertPoint();
        if (curBlock) {
            auto &insts = curBlock->getInstructions();
            if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                builder_.createBr(loopStack_.back().endBlockName);
            }
        }
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedContinueNode &node) {
        if (loopStack_.empty())
            return;
        auto curBlock = builder_.getInsertPoint();
        if (curBlock) {
            auto &insts = curBlock->getInstructions();
            if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                builder_.createBr(loopStack_.back().condBlockName);
            }
        }
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedBlockNode &node) {
        for (const auto &stmt : node.getStatements()) {
            stmt->accept(*this);
        }
    }

    void IRGenerator::visit(Sem::TypedExpressionStatementNode &node) {
        node.getExpression()->accept(*this);
    }

    void IRGenerator::visit(Sem::TypedReturnNode &node) {
        node.getValue()->accept(*this);
        auto retVal = lastValue_;
        builder_.createReturn("", retVal);
        lastValue_ = nullptr;
    }
} // namespace Ryntra::IR
