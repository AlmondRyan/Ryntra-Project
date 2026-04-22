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

    void BytecodeGenerator::generateInstruction(const std::shared_ptr<IR::Instruction>& inst) {
        const auto& operands = inst->getOperands();

        switch (inst->getOpcode()) {
        case IR::Instruction::Opcode::LoadConstant: {
            // operands[0] is a Constant
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

        case IR::Instruction::Opcode::Call: {
            // operands[0] = callee Function, operands[1..] = args
            // Args are already on the stack from prior LoadConst/Call instructions.
            // We just need to emit the Call with the function index.
            if (!operands.empty()) {
                auto callee = std::dynamic_pointer_cast<IR::Function>(operands[0]);
                if (callee) {
                    int32_t funcIdx = getFunctionIndex(callee->getName());
                    currentFunction_->addInstruction(OpCode::Call, funcIdx);
                }
            }
            break;
        }

        case IR::Instruction::Opcode::Return: {
            if (!operands.empty()) {
                // If the return value is an ImmediateValue (e.g. ret i32 0), push it first
                auto imm = std::dynamic_pointer_cast<IR::ImmediateValue>(operands[0]);
                if (imm) {
                    VMValue val;
                    if (imm->getType()->isInt32()) {
                        // toString() returns "i32 <literal>", extract the number
                        std::string repr = imm->toString();
                        auto spacePos = repr.find(' ');
                        if (spacePos != std::string::npos) {
                            val = VMValue(std::stoi(repr.substr(spacePos + 1)));
                        }
                    }
                    int32_t poolIdx = addConstant(val);
                    currentFunction_->addInstruction(OpCode::LoadConst, poolIdx);
                }
                // Otherwise the value is already on the stack (result of prior instruction)
            }
            currentFunction_->addInstruction(OpCode::Return);
            break;
        }

        case IR::Instruction::Opcode::Add:
            currentFunction_->addInstruction(OpCode::Add);
            break;
        case IR::Instruction::Opcode::Sub:
            currentFunction_->addInstruction(OpCode::Sub);
            break;
        case IR::Instruction::Opcode::Mul:
            currentFunction_->addInstruction(OpCode::Mul);
            break;
        case IR::Instruction::Opcode::Div:
            currentFunction_->addInstruction(OpCode::Div);
            break;

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
} // namespace Ryntra::VM
