#pragma once

#include "VMValue.h"
#include "Bytecode.h"
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

namespace Ryntra::VM {
    using NativeFunction = std::function<VMValue(const std::vector<VMValue>&)>;

    class VirtualMachine {
    public:
        VirtualMachine();

        void load(const std::vector<std::shared_ptr<BytecodeFunction>>& funcs,
                  const std::vector<VMValue>& constantPool);

        VMValue execute(const std::string& entryPoint = "main");

        void disassemble() const;

    private:
        VMValue executeFunction(BytecodeFunction* func, const std::vector<VMValue>& args);

        std::vector<VMValue> stack_;
        std::vector<VMValue> constantPool_;
        std::vector<std::shared_ptr<BytecodeFunction>> functionList_;
        std::unordered_map<std::string, std::shared_ptr<BytecodeFunction>> functionMap_;

        std::vector<VMValue> locals_;

        // Indexed builtin table — index matches BytecodeGenerator::getBuiltinIndex
        std::vector<NativeFunction> builtins_;
        std::vector<int> builtinArgCounts_;

        void push(const VMValue& value);
        VMValue pop();
    };
} // namespace Ryntra::VM
