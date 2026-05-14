#pragma once

#include "Bytecode.h"
#include "Compiler/IR/Module.h"
#include "VMValue.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Ryntra::VM {
    class BytecodeGenerator {
    public:
        BytecodeGenerator();

        std::vector<std::shared_ptr<BytecodeFunction>> generate(const std::shared_ptr<IR::Module> &module);
        const std::vector<VMValue> &getConstantPool() const { return constantPool_; }

    private:
        void generateFunction(const std::shared_ptr<IR::Function> &func);
        void generateBasicBlock(const std::shared_ptr<IR::BasicBlock> &block);
        void generateInstruction(const std::shared_ptr<IR::Instruction> &inst);

        void pushOperandValue(const std::shared_ptr<IR::Value> &operand);

        int32_t addConstant(const VMValue &value);
        int32_t getFunctionIndex(const std::string &name);
        int32_t getBuiltinIndex(const std::string &name);

        std::vector<VMValue> constantPool_;
        std::vector<std::shared_ptr<BytecodeFunction>> functions_;
        std::unordered_map<std::string, int32_t> functionIndices_;
        std::shared_ptr<BytecodeFunction> currentFunction_;
        std::shared_ptr<IR::Module> currentModule_;
        std::unordered_map<const IR::Value *, int32_t> instructionSlots_;
        int32_t nextSlot_;
    };
} // namespace Ryntra::VM
