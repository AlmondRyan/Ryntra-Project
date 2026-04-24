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

        // Load all functions and the shared constant pool from BytecodeGenerator output
        void load(const std::vector<std::shared_ptr<BytecodeFunction>>& funcs,
                  const std::vector<VMValue>& constantPool);

        void registerNativeFunction(const std::string& name, NativeFunction func);

        VMValue execute(const std::string& entryPoint = "main");

    private:
        VMValue executeFunction(BytecodeFunction* func, const std::vector<VMValue>& args);

        std::vector<VMValue> stack_;
        std::vector<VMValue> constantPool_;
        std::vector<std::shared_ptr<BytecodeFunction>> functionList_;  // indexed by position
        std::unordered_map<std::string, std::shared_ptr<BytecodeFunction>> functionMap_;
        std::unordered_map<std::string, NativeFunction> nativeFunctions_;

        void push(const VMValue& value);
        VMValue pop();
    };
} // namespace Ryntra::VM
