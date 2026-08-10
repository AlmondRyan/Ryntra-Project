#pragma once

#include "Bytecode.h"
#include "VMValue.h"
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace Ryntra::VM {
    using NativeFunction = std::function<VMValue(const std::vector<VMValue> &)>;

    struct CallFrame {
        BytecodeFunction *func;
        size_t ip;
        std::vector<VMValue> locals;
        size_t stackBase;
    };

    class VirtualMachine {
    public:
        VirtualMachine();

        void load(const std::vector<std::shared_ptr<BytecodeFunction>> &funcs,
                  const std::vector<VMValue> &constantPool);

        VMValue execute(const std::string &entryPoint = "main");

        void disassemble() const;

    private:
        std::vector<VMValue> stack_;
        std::vector<VMValue> constantPool_;
        std::vector<std::shared_ptr<BytecodeFunction>> functionList_;
        std::unordered_map<std::string, std::shared_ptr<BytecodeFunction>> functionMap_;

        std::vector<CallFrame> callStack_;
        std::vector<VMValue> heap_; // Separate heap storage
        std::vector<NativeFunction> builtins_;
        std::vector<int> builtinArgCounts_;

        void push(const VMValue &value);
        VMValue pop();
    };
} // namespace Ryntra::VM
