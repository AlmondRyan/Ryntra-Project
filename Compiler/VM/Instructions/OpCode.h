#pragma once

namespace Ryntra::VM {
    enum class OpCodes {
        LD_CONST,                      // LD_CONST [index]
        STORE_VAR,                     // STORE_VAR [index]
        LOAD_VAR,                      // LOAD_VAR [index]
        ADD,
        SUB,
        MUL,
        DIV,
        MOD,
        AND,
        OR,
        XOR,
        SHL,
        SHR,
        EQ,
        NE,
        LT,
        LE,
        GT,
        GE,
        NOT,
        JMP,
        JZ,
        RETURN,
        HALT,                          // HALT
        B_CALL,                        // B_CALL [index]
        NOP,                           // NOP
    };
} // namespace Ryntra::VM
