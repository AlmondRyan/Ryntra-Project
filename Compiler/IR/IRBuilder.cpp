#include "IRBuilder.h"
#include "ImmediateValue.h"

namespace Ryntra::IR {
    IRBuilder::IRBuilder() : unnamedCounter_(0) {}

    std::shared_ptr<Module> IRBuilder::createModule(const std::string &name) {
        currentModule_ = std::make_shared<Module>(name);
        return currentModule_;
    }

    std::shared_ptr<Function> IRBuilder::createFunction(const std::string &name,
                                                        std::shared_ptr<Type> returnType,
                                                        const std::vector<Function::Parameter> &parameters,
                                                        bool isExternal) {
        if (!currentModule_) {
            return nullptr;
        }

        auto function = std::make_shared<Function>(name, returnType, parameters, isExternal);
        currentModule_->addFunction(function);
        return function;
    }

    std::shared_ptr<BasicBlock> IRBuilder::createBasicBlock(const std::string &name) {
        return std::make_shared<BasicBlock>(name);
    }

    std::shared_ptr<Constant> IRBuilder::createGlobalConstant(const std::string &name,
                                                              std::shared_ptr<Type> type,
                                                              Constant::ValueType value) {
        if (!currentModule_) {
            return nullptr;
        }

        auto constant = std::make_shared<Constant>(type, value, name);
        currentModule_->addConstant(constant);
        return constant;
    }

    std::shared_ptr<Constant> IRBuilder::createGlobalConstant(std::shared_ptr<Type> type,
                                                              Constant::ValueType value) {
        if (!currentModule_) {
            return nullptr;
        }

        std::string name = "unnamed" + std::to_string(unnamedCounter_++);

        return createGlobalConstant(name, type, value);
    }

    std::shared_ptr<Instruction> IRBuilder::createLoadConstant(const std::string &name,
                                                               std::shared_ptr<Constant> constant) {
        if (!constant) {
            return nullptr;
        }

        std::vector<std::shared_ptr<Value>> operands;
        operands.push_back(constant);

        auto instruction = std::make_shared<Instruction>(
            Instruction::Opcode::LoadConstant,
            constant->getType(),
            operands,
            name);

        if (currentBlock_) {
            currentBlock_->addInstruction(instruction);
        }

        return instruction;
    }

    std::shared_ptr<Instruction> IRBuilder::createConstant(const std::string &name,
                                                           std::shared_ptr<Type> type,
                                                           std::shared_ptr<Value> value) {
        std::vector<std::shared_ptr<Value>> operands;
        if (value)
            operands.push_back(value);

        auto instruction = std::make_shared<Instruction>(
            Instruction::Opcode::Constant,
            type,
            operands,
            name);

        if (currentBlock_) {
            currentBlock_->addInstruction(instruction);
        }

        return instruction;
    }

    std::shared_ptr<Instruction> IRBuilder::createCall(const std::string &name,
                                                       std::shared_ptr<Function> function,
                                                       const std::vector<std::shared_ptr<Value>> &args) {
        if (!function) {
            return nullptr;
        }

        auto funcType = std::dynamic_pointer_cast<FunctionType>(function->getType());
        if (!funcType) {
            return nullptr;
        }

        std::vector<std::shared_ptr<Value>> operands;
        operands.push_back(function);
        operands.insert(operands.end(), args.begin(), args.end());

        auto instruction = std::make_shared<Instruction>(
            Instruction::Opcode::Call,
            funcType->getReturnType(),
            operands,
            name);

        if (currentBlock_) {
            currentBlock_->addInstruction(instruction);
        }

        return instruction;
    }

    std::shared_ptr<Instruction> IRBuilder::createReturn(const std::string &name,
                                                         std::shared_ptr<Value> value) {
        std::shared_ptr<Type> returnType;
        std::vector<std::shared_ptr<Value>> operands;

        if (value) {
            returnType = value->getType();
            operands.push_back(value);
        } else {
            returnType = Type::getVoidType();
        }

        auto instruction = std::make_shared<Instruction>(
            Instruction::Opcode::Return,
            returnType,
            operands,
            name);

        if (currentBlock_) {
            currentBlock_->addInstruction(instruction);
        }

        return instruction;
    }

    std::shared_ptr<Instruction> IRBuilder::createReturnInt32(const std::string &name,
                                                              int32_t value) {
        auto immediate = std::make_shared<ImmediateValue>(
            Type::getInt32Type(),
            std::to_string(value));

        return createReturn(name, immediate);
    }

    std::shared_ptr<Instruction> IRBuilder::createUnaryOp(Instruction::Opcode opcode,
                                                          const std::string &name,
                                                          std::shared_ptr<Value> operand) {
        if (!operand) {
            return nullptr;
        }

        std::vector<std::shared_ptr<Value>> operands = {operand};

        auto instruction = std::make_shared<Instruction>(
            opcode,
            operand->getType(),
            operands,
            name);

        if (currentBlock_) {
            currentBlock_->addInstruction(instruction);
        }

        return instruction;
    }

    std::shared_ptr<Instruction> IRBuilder::createBinaryOp(Instruction::Opcode opcode,
                                                           const std::string &name,
                                                           std::shared_ptr<Value> lhs,
                                                           std::shared_ptr<Value> rhs) {
        if (!lhs || !rhs) {
            return nullptr;
        }

        if (!lhs->getType()->isEqual(rhs->getType().get())) {
            return nullptr;
        }

        std::vector<std::shared_ptr<Value>> operands = {lhs, rhs};

        auto instruction = std::make_shared<Instruction>(
            opcode,
            lhs->getType(),
            operands,
            name);

        if (currentBlock_) {
            currentBlock_->addInstruction(instruction);
        }

        return instruction;
    }

    std::shared_ptr<Instruction> IRBuilder::createSExt(const std::string &name,
                                                       std::shared_ptr<Value> operand,
                                                       std::shared_ptr<Type> targetType) {
        if (!operand || !targetType)
            return nullptr;

        std::vector<std::shared_ptr<Value>> operands = {operand};
        auto instruction = std::make_shared<Instruction>(
            Instruction::Opcode::SExt,
            targetType,
            operands,
            name);

        if (currentBlock_) {
            currentBlock_->addInstruction(instruction);
        }

        return instruction;
    }

    std::shared_ptr<Instruction> IRBuilder::createTrunc(const std::string &name,
                                                        std::shared_ptr<Value> operand,
                                                        std::shared_ptr<Type> targetType) {
        if (!operand || !targetType)
            return nullptr;

        std::vector<std::shared_ptr<Value>> operands = {operand};
        auto instruction = std::make_shared<Instruction>(
            Instruction::Opcode::Trunc,
            targetType,
            operands,
            name);

        if (currentBlock_) {
            currentBlock_->addInstruction(instruction);
        }

        return instruction;
    }

    std::shared_ptr<Instruction> IRBuilder::createCompare(Instruction::Opcode opcode,
                                                           const std::string &name,
                                                           std::shared_ptr<Value> lhs,
                                                           std::shared_ptr<Value> rhs) {
        if (!lhs || !rhs)
            return nullptr;

        std::vector<std::shared_ptr<Value>> operands = {lhs, rhs};

        auto instruction = std::make_shared<Instruction>(
            opcode,
            Type::getBoolType(),
            operands,
            name);

        if (currentBlock_)
            currentBlock_->addInstruction(instruction);

        return instruction;
    }

    void IRBuilder::setInsertPoint(std::shared_ptr<BasicBlock> block) {
        currentBlock_ = block;
    }

    std::shared_ptr<BasicBlock> IRBuilder::getInsertPoint() const {
        return currentBlock_;
    }

    void IRBuilder::addInstruction(std::shared_ptr<Instruction> instruction) {
        if (currentBlock_ && instruction) {
            currentBlock_->addInstruction(instruction);
        }
    }

    std::string IRBuilder::generateUniqueName(const std::string &base) {
        return base + std::to_string(unnamedCounter_++);
    }
} // namespace Ryntra::IR
