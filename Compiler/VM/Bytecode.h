#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace Ryntra::VM {
    enum class OpCode : uint8_t {
        LoadConst,      // Load constant onto stack
        Call,           // Call function
        Return,         // Return from function
        Add,            // Add two values
        Sub,            // Subtract
        Mul,            // Multiply
        Div,            // Divide
        Pop,            // Pop value from stack
        Halt            // Stop execution
    };

    struct Instruction {
        OpCode opcode;
        int32_t operand;  // Index into constant pool or other data

        Instruction(OpCode op, int32_t operand = 0)
            : opcode(op), operand(operand) {}
    };

    class BytecodeFunction {
    public:
        std::string name;
        std::vector<Instruction> instructions;
        bool isExternal;
        int32_t paramCount;  // number of parameters this function expects

        BytecodeFunction(const std::string& name, bool external = false, int32_t paramCount = 0)
            : name(name), isExternal(external), paramCount(paramCount) {}

        void addInstruction(OpCode op, int32_t operand = 0) {
            instructions.emplace_back(op, operand);
        }
    };
} // namespace Ryntra::VM
