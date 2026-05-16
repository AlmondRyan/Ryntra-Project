#include "BytecodeGenerator.h"
#include "Compiler/IR/Constant.h"
#include "Compiler/IR/Function.h"
#include "Compiler/IR/ImmediateValue.h"
#include "Compiler/IR/Instruction.h"
#include <stdexcept>

namespace Ryntra::VM {
    BytecodeGenerator::BytecodeGenerator() = default;

    std::vector<std::shared_ptr<BytecodeFunction>> BytecodeGenerator::generate(
        const std::shared_ptr<IR::Module> &module) {
        currentModule_ = module;
        functions_.clear();
        functionIndices_.clear();
        constantPool_.clear();

        // First pass: register all functions so call resolution works
        int32_t idx = 0;
        for (const auto &func : module->getFunctions()) {
            functionIndices_[func->getName()] = idx++;
            auto paramCount = static_cast<int32_t>(func->getParameters().size());
            functions_.push_back(std::make_shared<BytecodeFunction>(
                func->getName(), func->isExternal(), paramCount));
        }

        // Second pass: generate bytecode for each non-external function
        for (size_t i = 0; i < module->getFunctions().size(); ++i) {
            const auto &irFunc = module->getFunctions()[i];
            if (!irFunc->isExternal()) {
                generateFunction(irFunc);
            }
        }

        return functions_;
    }

    void BytecodeGenerator::generateFunction(const std::shared_ptr<IR::Function> &func) {
        instructionSlots_.clear();
        nextSlot_ = 0;

        // Find the matching BytecodeFunction index
        int32_t idx = getFunctionIndex(func->getName());
        currentFunction_ = functions_[idx];

        blockOffsets_.clear();
        fixups_.clear();

        for (const auto &block : func->getBasicBlocks()) {
            blockOffsets_[block->getName()] = static_cast<int32_t>(currentFunction_->instructions.size());
            generateBasicBlock(block);
        }

        // Resolve fixups: patch branch target offsets
        for (const auto &fixup : fixups_) {
            auto it = blockOffsets_.find(fixup.targetBlockName);
            if (it != blockOffsets_.end()) {
                currentFunction_->instructions[fixup.instructionIndex].operand = it->second;
            }
        }
    }

    void BytecodeGenerator::generateBasicBlock(const std::shared_ptr<IR::BasicBlock> &block) {
        for (const auto &inst : block->getInstructions()) {
            generateInstruction(inst);
        }
    }

    void BytecodeGenerator::pushOperandValue(const std::shared_ptr<IR::Value> &operand) {
        if (auto imm = std::dynamic_pointer_cast<IR::ImmediateValue>(operand)) {
            VMValue val;
            if (imm->getType()->isInt32()) {
                std::string repr = imm->toString();
                auto spacePos = repr.find(' ');
                if (spacePos != std::string::npos) {
                    val = VMValue(std::stoi(repr.substr(spacePos + 1)));
                }
            } else if (imm->getType()->isBool()) {
                std::string repr = imm->toString();
                auto spacePos = repr.find(' ');
                if (spacePos != std::string::npos) {
                    val = VMValue(static_cast<int32_t>(std::stoi(repr.substr(spacePos + 1))));
                }
            } else if (imm->getType()->isInt64()) {
                std::string repr = imm->toString();
                auto spacePos = repr.find(' ');
                if (spacePos != std::string::npos) {
                    val = VMValue(static_cast<int64_t>(std::stoll(repr.substr(spacePos + 1))));
                }
            }
            int32_t poolIdx = addConstant(val);
            currentFunction_->addInstruction(OpCode::LoadConst, poolIdx);
        } else if (auto argInst = std::dynamic_pointer_cast<IR::Instruction>(operand)) {
            if (argInst->getOpcode() == IR::Instruction::Opcode::Constant) {
                if (!argInst->getOperands().empty()) {
                    pushOperandValue(argInst->getOperands()[0]);
                }
            } else {
                auto it = instructionSlots_.find(argInst.get());
                if (it != instructionSlots_.end()) {
                    currentFunction_->addInstruction(OpCode::LoadLocal, it->second);
                }
            }
        }
    }

    void BytecodeGenerator::generateInstruction(const std::shared_ptr<IR::Instruction> &inst) {
        const auto &operands = inst->getOperands();

        // Assign a local slot for instructions that produce a runtime value
        bool needsSlot = inst->getOpcode() != IR::Instruction::Opcode::Constant && !inst->getType()->isVoid();
        int32_t slot = -1;
        if (needsSlot) {
            slot = nextSlot_++;
            instructionSlots_[inst.get()] = slot;
        }

        switch (inst->getOpcode()) {
        case IR::Instruction::Opcode::LoadConstant: {
            if (!operands.empty()) {
                auto constant = std::dynamic_pointer_cast<IR::Constant>(operands[0]);
                if (constant) {
                    VMValue val;
                    if (constant->getType()->isInt32()) {
                        val = VMValue(std::get<int32_t>(constant->getValue()));
                    } else if (constant->getType()->isInt64()) {
                        val = VMValue(std::get<int64_t>(constant->getValue()));
                    } else if (constant->getType()->isBool()) {
                        val = VMValue(static_cast<int32_t>(std::get<bool>(constant->getValue()) ? 1 : 0));
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
                    const std::string &name = callee->getName();
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

        case IR::Instruction::Opcode::SExt: {
            for (const auto &op : operands) {
                pushOperandValue(op);
            }
            currentFunction_->addInstruction(OpCode::SExt);
            break;
        }

        case IR::Instruction::Opcode::Trunc: {
            for (const auto &op : operands) {
                pushOperandValue(op);
            }
            currentFunction_->addInstruction(OpCode::Trunc);
            break;
        }

        case IR::Instruction::Opcode::Eq:
        case IR::Instruction::Opcode::Ne:
        case IR::Instruction::Opcode::Lt:
        case IR::Instruction::Opcode::Gt:
        case IR::Instruction::Opcode::Le:
        case IR::Instruction::Opcode::Ge: {
            for (const auto &op : operands) {
                pushOperandValue(op);
            }
            OpCode bcOp;
            switch (inst->getOpcode()) {
            case IR::Instruction::Opcode::Eq: bcOp = OpCode::Eq; break;
            case IR::Instruction::Opcode::Ne: bcOp = OpCode::Ne; break;
            case IR::Instruction::Opcode::Lt: bcOp = OpCode::Lt; break;
            case IR::Instruction::Opcode::Gt: bcOp = OpCode::Gt; break;
            case IR::Instruction::Opcode::Le: bcOp = OpCode::Le; break;
            case IR::Instruction::Opcode::Ge: bcOp = OpCode::Ge; break;
            default: bcOp = OpCode::Eq; break;
            }
            currentFunction_->addInstruction(bcOp);
            break;
        }

        case IR::Instruction::Opcode::BitNot:
        case IR::Instruction::Opcode::LogicalNot: {
            // Unary: push the single operand
            for (const auto &op : operands) {
                pushOperandValue(op);
            }
            OpCode bcOp = (inst->getOpcode() == IR::Instruction::Opcode::LogicalNot) ? OpCode::LogicalNot : OpCode::BitNot;
            currentFunction_->addInstruction(bcOp);
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
            for (const auto &op : operands) {
                pushOperandValue(op);
            }
            OpCode bcOp;
            switch (inst->getOpcode()) {
            case IR::Instruction::Opcode::Add:
                bcOp = OpCode::Add;
                break;
            case IR::Instruction::Opcode::Sub:
                bcOp = OpCode::Sub;
                break;
            case IR::Instruction::Opcode::Mul:
                bcOp = OpCode::Mul;
                break;
            case IR::Instruction::Opcode::Div:
                bcOp = OpCode::Div;
                break;
            case IR::Instruction::Opcode::Mod:
                bcOp = OpCode::Mod;
                break;
            case IR::Instruction::Opcode::BitAnd:
                bcOp = OpCode::BitAnd;
                break;
            case IR::Instruction::Opcode::BitOr:
                bcOp = OpCode::BitOr;
                break;
            case IR::Instruction::Opcode::BitXor:
                bcOp = OpCode::BitXor;
                break;
            case IR::Instruction::Opcode::Shl:
                bcOp = OpCode::Shl;
                break;
            case IR::Instruction::Opcode::Shr:
                bcOp = OpCode::Shr;
                break;
            default:
                bcOp = OpCode::Add;
                break;
            }
            currentFunction_->addInstruction(bcOp);
            break;
        }

        case IR::Instruction::Opcode::Br: {
            auto targetName = std::dynamic_pointer_cast<IR::ImmediateValue>(operands[0])->getLiteralValue();
            size_t instIdx = currentFunction_->instructions.size();
            currentFunction_->addInstruction(OpCode::Jmp, 0);
            fixups_.push_back({instIdx, targetName});
            break;
        }

        case IR::Instruction::Opcode::CondBr: {
            pushOperandValue(operands[0]);
            auto falseName = std::dynamic_pointer_cast<IR::ImmediateValue>(operands[2])->getLiteralValue();
            size_t jzIdx = currentFunction_->instructions.size();
            currentFunction_->addInstruction(OpCode::Jz, 0);
            fixups_.push_back({jzIdx, falseName});
            auto trueName = std::dynamic_pointer_cast<IR::ImmediateValue>(operands[1])->getLiteralValue();
            size_t jmpIdx = currentFunction_->instructions.size();
            currentFunction_->addInstruction(OpCode::Jmp, 0);
            fixups_.push_back({jmpIdx, trueName});
            break;
        }

        default:
            break;
        }

        if (slot >= 0) {
            currentFunction_->addInstruction(OpCode::StoreLocal, slot);
        }
    }

    int32_t BytecodeGenerator::addConstant(const VMValue &value) {
        constantPool_.push_back(value);
        return static_cast<int32_t>(constantPool_.size() - 1);
    }

    int32_t BytecodeGenerator::getFunctionIndex(const std::string &name) {
        auto it = functionIndices_.find(name);
        if (it != functionIndices_.end()) {
            return it->second;
        }
        throw std::runtime_error("Unknown function: " + name);
    }

    int32_t BytecodeGenerator::getBuiltinIndex(const std::string &name) {
        static const std::vector<std::string> builtinTable = {
            "__builtin_print",          // 0
            "__builtin_print_i32",      // 1 (int32 print)
            "__builtin_print_i64",      // 2 (int64 print)
            "__builtin_print_bool",     // 3 (bool print)
            "__builtin_print_string",   // 4 (string print)
            "__builtin_scan_bool",      // 5 (bool scan)
            "__builtin_scan_i32",       // 6 (int32 scan)
            "__builtin_scan_i64",       // 7 (int64 scan)
        };
        for (int32_t i = 0; i < static_cast<int32_t>(builtinTable.size()); ++i) {
            if (name == builtinTable[i])
                return i;
        }
        throw std::runtime_error("Unknown builtin: " + name);
    }
} // namespace Ryntra::VM
