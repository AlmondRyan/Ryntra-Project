#include "../IRGenerator.h"

namespace Ryntra::IR {
    namespace Sem = Compiler::Semantic;

    void IRGenerator::visit(Sem::TypedProgramNode &node) {
        // Pre-create canonical IR struct types (fields filled below) so signature
        // types can reference any struct by name regardless of declaration order.
        for (const auto &strct : node.getStructs()) {
            if (structTypeMap_.find(strct->getName()) == structTypeMap_.end()) {
                auto irStruct = std::make_shared<IR::StructType>(strct->getName());
                structTypeMap_[strct->getName()] = irStruct;
                if (auto module = builder_.getModule())
                    module->addType(irStruct);
            }
        }
        for (const auto &strct : node.getStructs()) {
            auto irStruct = structTypeMap_[strct->getName()];
            for (const auto &field : strct->getFields()) {
                irStruct->addField(field->getName(), toIRType(field->getType()));
            }
        }

        for (const auto &func : node.getFunctions()) {
            auto retType = toIRType(func->getReturnType());

            std::vector<Function::Parameter> irParams;
            if (func->getParameterList()) {
                for (const auto &param : func->getParameterList()->getParameters()) {
                    auto paramIRType = toIRType(param->getType());
                    irParams.emplace_back(param->getName(), paramIRType);
                }
            }

            auto irFunc = builder_.createFunction(func->getName(), retType, irParams);
            functionMap_[func->getName()] = irFunc;
        }

        registerStructFunctions(node.getStructs());

        for (const auto &func : node.getFunctions()) {
            func->accept(*this);
        }

        for (const auto &strct : node.getStructs()) {
            strct->accept(*this);
        }
    }

    void IRGenerator::visit(Sem::TypedFunctionDefinitionNode &node) {
        auto irFunc = functionMap_[node.getName()];
        if (!irFunc)
            return;

        generateCallableBody(irFunc, node.getParameterList(), *node.getBody(), /*hasSelf=*/false);
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
        std::shared_ptr<Value> retVal;
        if (node.getValue()) {
            node.getValue()->accept(*this);
            retVal = lastValue_;
        }
        builder_.createReturn("", retVal);
        lastValue_ = nullptr;
    }
} // namespace Ryntra::IR
