#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace Ryntra::VM {
    // clang-format off
    enum class OpCode : uint8_t {
        LoadConst,      // Load constant onto stack
        Call,           // Call user-defined function by index
        BCall,          // Call builtin function by builtin table index (0=print, ...)
        Return,         // Return from function
        Add,            // Add two values
        Sub,            // Subtract
        Mul,            // Multiply
        Div,            // Divide
        Mod,            // Modulo
        BitNot,         // Bitwise NOT (~)
        LogicalNot,     // Logical NOT (!)
        BitAnd,         // Bitwise AND (&)
        BitOr,          // Bitwise OR (|)
        BitXor,         // Bitwise XOR (^)
        Shl,            // Shift left (<<)
        Shr,            // Shift right (>>)
        SExt,           // Sign extend i32 → i64
        Trunc,          // Truncate i64 → i32
        Eq,             // == (push i32 0/1)
        Ne,             // !=
        Lt,             // <
        Gt,             // >
        Le,             // <=
        Ge,             // >=
            Dup,            // Duplicate top of stack
            Pop,            // Pop value from stack
            StoreLocal,     // Store value from stack into local variable slot
            LoadLocal,      // Load value from local variable slot onto stack
            Jmp,            // Unconditional jump to instruction offset
            Jz,             // Pop value, jump if zero to instruction offset
            NewArray,       // Pop size, create array, push reference
            ArrGet,         // Pop index, pop array, push element
            ArrSet,         // Pop value, pop index, pop array, set element
            RefCreate,      // Pop slot index (from alloca), create ref, push ref
            RefLoad,        // Pop ref, load value from referenced slot, push value
            RefStore,       // Pop value, pop ref, store value to referenced slot
            PtrCreate,      // Pop slot index (from alloca), create ptr, push ptr
            PtrLoad,        // Pop ptr, load value from pointed-to slot, push value
            PtrStore,       // Pop value, pop ptr, store value to pointed-to slot
            Halt            // Stop execution
    };
    // clang-format on

    struct Instruction {
        OpCode opcode;
        int32_t operand; // Index into constant pool or other data

        Instruction(OpCode op, int32_t operand = 0)
            : opcode(op), operand(operand) {}
    };

    class BytecodeFunction {
    public:
        std::string name;
        std::vector<Instruction> instructions;
        bool isExternal;
        int32_t paramCount; // number of parameters this function expects

        BytecodeFunction(const std::string &name, bool external = false, int32_t paramCount = 0)
            : name(name), isExternal(external), paramCount(paramCount) {}

        void addInstruction(OpCode op, int32_t operand = 0) {
            instructions.emplace_back(op, operand);
        }
    };
} // namespace Ryntra::VM
