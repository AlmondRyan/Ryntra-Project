#pragma once

namespace Ryntra::rasm {
    enum class InstructionType {
        Unknown,
        // Number Operations
        ADD, SUB, MUL, DIV,
        // Logical Operations
        AND, OR, XOR,
    };
} 