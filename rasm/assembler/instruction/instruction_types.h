#pragma once
#ifndef RASM_INSTRUCTION_TYPES_H
#define RASM_INSTRUCTION_TYPES_H

namespace Ryntra::rasm {
    enum class InstructionType {
        Unknown,
        
        // Number Operation
        ADD,    // Add
        SUB,    // Subtract
        MUL,    // Multiply
        DIV,    // Divide
        INC,    // Increment
        DEC,    // Decrement
        NEG,    // Negate
        
        // Logical Operation
        AND,    // Logical AND
        OR,     // Logical OR
        XOR,    // Logical XOR
        NOT,    // Logical NOT
        
        // Bit Manipulation Operation
        SHL,    // Shift Left
        SHR,    // Shift Right
        SAR,    // Shift Arithmetic Right
        ROL,    // Rotate Left
        ROR,    // Rotate Right
        
        // Data Transfer
        MOV,    // Move
        XCHG,   // Exchange
        LEA,    // Load Effective Address
        
        // Control Flow
        JMP,    // Unconditional Jump
        JE,     // Jump if Equal
        JZ,     // Jump if Zero (Same as JE)
        JNE,    // Jump if Not Equal
        JNZ,    // Jump if Not Zero (Same as JNE)
        JG,     // Jump if Greater
        JGE,    // Jump if Greater or Equal
        JGLE,   // Jump if Greater or Less Equal
        JL,     // Jump if Less
        JLE,    // Jump if Less or Equal
        JNGE,   // Jump if Not Greater or Equal
        CALL,   // Call Procedure
        RET,    // Return from Procedure
        NOP,    // No Operation
        
        // Comparison Operation
        CMP,    // Compare
        TEST,   // Test (Bitwise AND and set flags)
        
        // Stack Operation
        PUSH,   // Push onto Stack
        POP,    // Pop from Stack
        ENTER,  // Enter Procedure
        LEAVE,  // Leave Procedure
        
        // Floating Point Operation
        FLD,    // Load Floating Point
        FST,    // Store Floating Point
        FADD,   // Floating Point Add
        FSUB,   // Floating Point Subtract
        FMUL,   // Floating Point Multiply
        FDIV,   // Floating Point Divide
        
        // System Operation
        SYSCALL,// System Call
        SYSRET, // System Return
        INT,    // Software Interrupt
        IRET,   // Interrupt Return
        HLT,    // Halt
        CLI,    // Clear Interrupt Flag
        STI,    // Set Interrupt Flag
        
        // SIMD Operation
#ifdef USE_SSE
        // SSE Instructions
        MOVSS,  // Move Scalar Single-Precision
        ADDSS,  // Add Scalar Single-Precision
        SUBSS,  // Subtract Scalar Single-Precision
        MULSS,  // Multiply Scalar Single-Precision
        DIVSS,  // Divide Scalar Single-Precision
#endif

#ifdef USE_AVX
        // AVX Instructions
        VADDPS, // Vector Add Packed Single-Precision
        VMULPS, // Vector Multiply Packed Single-Precision
#endif

#ifdef ENABLE_AVX512
        // AVX-512 Instructions
        VADDPD, // Vector Add Packed Double-Precision
        VMULPD, // Vector Multiply Packed Double-Precision
#endif
    };
} // namespace Ryntra::rasm

#endif // RASM_INSTRUCTION_TYPES_H 