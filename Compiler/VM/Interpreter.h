#pragma once

#include "Instruction.h"
#include "Value.h"
#include <stack>
#include <vector>

namespace Ryntra::Compiler::VM {
    class Interpreter {
    public:
        void execute(const std::vector<VM::Instruction> &program);

    private:
        std::vector<Value> stack;

        void push(Value v);
        Value pop();
    };
} // namespace Ryntra::VM
