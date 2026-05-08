#include "BytecodeGenerator.h"
#include "Compiler/IR/Instruction.h"
#include "Compiler/IR/Constant.h"
#include "Compiler/IR/ImmediateValue.h"
#include "Compiler/IR/Function.h"
#include <stdexcept>

namespace Ryntra::VM {
    BytecodeGenerator::BytecodeGenerator() = default;

    std::vector<std::shared_ptr<BytecodeFunction>> BytecodeGenerator::generate(
        const std::shared_ptr<IR::Module>& module)
    {
        currentModule_ = module;
        functions_.clear();
        functionIndices_.clear();
        constantPool_.clear();

        // First pass: register all functions so call resolution works
        int32_t idx = 0;
        for (const auto& func : module->getFunctions()) {
            functionIndices_[func->getName()] = idx++;
            auto paramCount = static_cast<int32_t>(func->getParameters().size());
            functions_.push_back(std::make_shared<BytecodeFunction>(
                func->getName(), func->isExternal(), paramCount));
        }

        // Second pass: generate bytecode for each non-external function
        for (size_t i = 0; i < module->getFunctions().size(); ++i) {
            const auto& irFunc = module->getFunctions()[i];
            if (!irFunc->isExternal()) {
                currentFunction_ = functions_[i];
                for (const auto& block : irFunc->getBasicBlocks()) {
                    generateBasicBlock(block);
                }
            }
        }

        return functions_;
    }

    void BytecodeGenerator::generateBasicBlock(const std::shared_ptr<IR::BasicBlock>& block) {
        for (const auto& inst : block->getInstructions()) {
            generateInstruction(inst);
        }
    }

    void BytecodeGenerator::pushOperandValue(const std::shared_ptr<IR::Value>& operand) {
        if (auto imm = std::dynamic_pointer_cast<IR::ImmediateValue>(operand)) {
            VMValue val;
            if (imm->getType()->isInt32()) {
                std::string repr = imm->toString();
                auto spacePos = repr.find(' ');
                if (spacePos != std::string::npos) {
                    val = VMValue(std::stoi(repr.substr(spacePos + 1)));
                }
            }
            int32_t poolIdx = addConstant(val);
            currentFunction_->addInstruction(OpCode::LoadConst, poolIdx);
        } else if (auto argInst = std::dynamic_pointer_cast<IR::Instruction>(operand)) {
            if (argInst->getOpcode() == IR::Instruction::Opcode::Constant) {
                if (!argInst->getOperands().empty()) {
                    pushOperandValue(argInst->getOperands()[0]);
                }
            }
        }
    }

    void BytecodeGenerator::generateInstruction(const std::shared_ptr<IR::Instruction>& inst) {
        const auto& operands = inst->getOperands();

        switch (inst->getOpcode()) {
        case IR::Instruction::Opcode::LoadConstant: {
            if (!operands.empty()) {
                auto constant = std::dynamic_pointer_cast<IR::Constant>(operands[0]);
                if (constant) {
                    VMValue val;
                    if (constant->getType()->isInt32()) {
                        val = VMValue(std::get<int32_t>(constant->getValue()));
                    } else if (constant->getType()->isString()) {
                        val = VMValue(std::get<std::string>(constant->getValue()));
                    }
                    int32_t poolIdx = addConstant(val);
                    currentFunction_->addInstruction(OpCode::LoadConst, poolIdx);
                }
            }
            break;
        }

        case IR::Instruction::Opcode::Constant: {
            // Value is materialized at the use site, not eagerly
            break;
        }

        case IR::Instruction::Opcode::Call: {
            if (!operands.empty()) {
                auto callee = std::dynamic_pointer_cast<IR::Function>(operands[0]);
                if (callee) {
                    const std::string& name = callee->getName();
                    if (name.rfind("__builtin_", 0) == 0) {
                        // Push argument values onto the stack before the call
                        for (size_t i = 1; i < operands.size(); ++i) {
                            pushOperandValue(operands[i]);
                        }
                        int32_t builtinIdx = getBuiltinIndex(name);
                        currentFunction_->addInstruction(OpCode::BCall, builtinIdx);
                    } else {
                        // Push arguments for user-defined function calls
                        for (size_t i = 1; i < operands.size(); ++i) {
                            pushOperandValue(operands[i]);
                        }
                        int32_t funcIdx = getFunctionIndex(name);
                        currentFunction_->addInstruction(OpCode::Call, funcIdx);
                    }
                }
            }
            break;
        }

        case IR::Instruction::Opcode::Return: {
            if (!operands.empty()) {
                pushOperandValue(operands[0]);
            }
            currentFunction_->addInstruction(OpCode::Return);
            break;
        }

        case IR::Instruction::Opcode::BitNot: {
            // Unary: push the single operand
            for (const auto& op : operands) {
                pushOperandValue(op);
            }
            currentFunction_->addInstruction(OpCode::BitNot);
            break;
        }

        case IR::Instruction::Opcode::Add:
        case IR::Instruction::Opcode::Sub:
        case IR::Instruction::Opcode::Mul:
        case IR::Instruction::Opcode::Div:
        case IR::Instruction::Opcode::Mod:
        case IR::Instruction::Opcode::BitAnd:
        case IR::Instruction::Opcode::BitOr:
        case IR::Instruction::Opcode::BitXor:
        case IR::Instruction::Opcode::Shl:
        case IR::Instruction::Opcode::Shr: {
            for (const auto& op : operands) {
                pushOperandValue(op);
            }
            OpCode bcOp;
            switch (inst->getOpcode()) {
            case IR::Instruction::Opcode::Add: bcOp = OpCode::Add; break;
            case IR::Instruction::Opcode::Sub: bcOp = OpCode::Sub; break;
            case IR::Instruction::Opcode::Mul: bcOp = OpCode::Mul; break;
            case IR::Instruction::Opcode::Div: bcOp = OpCode::Div; break;
            case IR::Instruction::Opcode::Mod: bcOp = OpCode::Mod; break;
            case IR::Instruction::Opcode::BitAnd: bcOp = OpCode::BitAnd; break;
            case IR::Instruction::Opcode::BitOr: bcOp = OpCode::BitOr; break;
            case IR::Instruction::Opcode::BitXor: bcOp = OpCode::BitXor; break;
            case IR::Instruction::Opcode::Shl: bcOp = OpCode::Shl; break;
            case IR::Instruction::Opcode::Shr: bcOp = OpCode::Shr; break;
            default: bcOp = OpCode::Add; break;
            }
            currentFunction_->addInstruction(bcOp);
            break;
        }

        default:
            break;
        }
    }

    int32_t BytecodeGenerator::addConstant(const VMValue& value) {
        constantPool_.push_back(value);
        return static_cast<int32_t>(constantPool_.size() - 1);
    }

    int32_t BytecodeGenerator::getFunctionIndex(const std::string& name) {
        auto it = functionIndices_.find(name);
        if (it != functionIndices_.end()) {
            return it->second;
        }
        throw std::runtime_error("Unknown function: " + name);
    }

    int32_t BytecodeGenerator::getBuiltinIndex(const std::string& name) {
        static const std::vector<std::string> builtinTable = {
            "__builtin_print",  // 0
        };
        for (int32_t i = 0; i < static_cast<int32_t>(builtinTable.size()); ++i) {
            if (name == builtinTable[i] ||
                (name.rfind(builtinTable[i] + "_", 0) == 0)) return i;
        }
        throw std::runtime_error("Unknown builtin: " + name);
    }
} // namespace Ryntra::VM
