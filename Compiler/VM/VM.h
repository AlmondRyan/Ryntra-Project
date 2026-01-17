#pragma once

#include "Instructions/Instruction.h"
#include <vector>
#include <variant>
#include <string>
#include <functional>

namespace Ryntra::VM {
    class RVM;

    struct Value {
        std::variant<int, long long, std::string, float, bool, double> data;
    };

    using BuiltinFunction = std::function<void(RVM &)>;

    class RVM {
    public:
        RVM(const std::vector<Instruction> prog, const std::vector<Value> &constPool) {
            program = prog;
            constantPool = constPool;
            builtins.resize(7);

            registerBuiltinFunction();
        }

        void operate();
        void registerBuiltinFunction();

        Value pop() { auto v =  stack.back(); stack.pop_back(); return v; }
        void push(const Value& v) { stack.push_back(v); }
        const std::vector<Value>& getVariables() const { return variables; }
        const Value& getReturnValue() const { return returnValue; }
        bool hasReturnValue() const { return hasReturn; }
    private:
        std::vector<Instruction> program;
        std::vector<Value> constantPool;
        std::vector<Value> stack;
        std::vector<Value> variables;
        std::vector<BuiltinFunction> builtins;

        Value returnValue{};
        bool hasReturn = false;

        size_t ip = 0;
    };
}
