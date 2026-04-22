#pragma once

#include "Bytecode.h"
#include "VMValue.h"
#include "Compiler/IR/Module.h"
#include <memory>
#include <vector>
#include <unordered_map>

namespace Ryntra::VM {
    class BytecodeGenerator {
    public:
        BytecodeGenerator();

        std::vector<std::shared_ptr<BytecodeFunction>> generate(const std::shared_ptr<IR::Module>& module);
        const std::vector<VMValue>& getConstantPool() const { return constantPool_; }

    private:
        void generateFunction(const std::shared_ptr<IR::Function>& func);
        void generateBasicBlock(const std::shared_ptr<IR::BasicBlock>& block);
        void generateInstruction(const std::shared_ptr<IR::Instruction>& inst);

        int32_t addConstant(const VMValue& value);
        int32_t getFunctionIndex(const std::string& name);

        std::vector<VMValue> constantPool_;
        std::vector<std::shared_ptr<BytecodeFunction>> functions_;
        std::unordered_map<std::string, int32_t> functionIndices_;
        std::shared_ptr<BytecodeFunction> currentFunction_;
        std::shared_ptr<IR::Module> currentModule_;
    };
} // namespace Ryntra::VM
