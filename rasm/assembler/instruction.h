#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

namespace Ryntra::rasm {
    enum class OperandType {
        Register,
        Immediate,
        Memory,
        Label
    };

    enum class RegisterType {
        RAX, RBX, RCX, RDX,                   // 64-bits General Registers, Accumulator / Base / Count / Data Registers
        RSI, RDI, RBP, RSP,                   // 64-bits General Registers, Source Index / Destination Index,
                                              //                            Base Pointer / Stack Pointer Registers
        R8,  R9,  R10, R11,                   // 64-bits General Registers
        R12, R13, R14, R15,                   // 64-bits General Registers
        EAX, EBX, ECX, EDX,                   // 32-bits General Registers, Accumulator / Base / Count / Data Registers
        Unknown
    };

    struct Operand {
        OperandType type;
        std::string value;
        RegisterType reg = RegisterType::Unknown;
        int64_t immediate = 0;
    };

    enum class InstructionType {
        Unknown,
        // Number Operation ====================================================================
        ADD,                                  // Add (Add operation)
        SUB,                                  // Sub (Subtract / Minus operation)
        MUL,                                  // Mul (Multiply operation)
        DIV,                                  // Div (Divide operation)
        // Logical Operation ===================================================================
        AND,                                  // And (And logical operation)
        OR,                                   // Or (Or logical operation)
        XOR,                                  // Xor (Exclusive Or logical operation)
        // Data Transfer Operation =============================================================
        LEA,                                  // Lea (Load Effective Address operation)
        MOV,                                  // Mov (Move operation)
        XCHG,                                 // Xchg (Exchange Operation)
        // Control Stream Operation ============================================================
        JMP,                                  // Jmp (Jump operation)
        JE,                                   // Je (Jump if equal (or the zero flag bit is 1))
        JZ,                                   // Jz (Same as Je)
        JNE,                                  // Jne (Jump if not equal (or the zero flag bit is 0))
        JNZ,                                  // Jnz (Same as Jne)
        JG,                                   // Jg (Jump if greater than)
        JGLE,                                 // Jge (Jump if greater than)
        JL,                                   // Jl (Jump if less than)
        JNGE,                                 // Jle (Jump if less than)
        CALL,                                 // Call (Call a Sub-Application or Function)
        RET,                                  // Ret (Return from Function or Sub-Application)
        NOP,                                  // Nop (No Operation) (Almond Ryan: Or simply nope haha)
        // Comparison Operation ================================================================
        CMP,                                  // Cmp (Compare operation, set the flag register)
        TEST,                                 // Test (Test operation, or bitwise and, set the flag register)
        // Bit Manipulation Operation ==========================================================
        SHL,                                  // Shl (Shift Left operation)
        SHR,                                  // Shr (Shift Right operation)
        SAR,                                  // Sar (Shift Arithmetic Right operation)
        ROL,                                  // Rol (Rotate Left operation)
        ROR,                                  // Ror (Rotate Right operation)
        // Stack Operation =====================================================================
        PUSH,                                 // Push (Push a value onto the stack)
        POP,                                  // Pop (Pop a value from the stack)
        ENTER,                                // Enter (Enter a new stack frame)
        LEAVE,                                // Leave (Leave a stack frame)
        // Float Operation =====================================================================
        FLD,                                  // Fld (Load a floating point value onto the stack)
        FST,                                  // Fst (Store a floating point value from the stack)
        FADD,                                 // Fadd (Add a floating point value)
        FSUB,                                 // Fsub (Subtract a floating point value)
        FMUL,                                 // Fmul (Multiply a floating point value)
        FDIV,                                 // Fdiv (Divide a floating point value)
        // Misc Operation ======================================================================
        SYSCALL,                              // Syscall (System Call)
        SYSRET,                               // Sysret (System Return)
        INT,                                  // Int (Interrupt)
        IRET,                                 // Iret (Interrupt Return)
        HLT,                                  // Hlt (Halt)
    };

    struct Instruction {
        InstructionType type = InstructionType::Unknown;
        std::string mnemonic;
        std::vector<Operand> operands;
        uint64_t address = 0;
        std::vector<uint8_t> machineCode;
    };

    const std::unordered_map<std::string, InstructionType> INSTRUCTION_MAP = {
        // Number Operation
        {"add", InstructionType::ADD},
        {"sub", InstructionType::SUB},
        {"mul", InstructionType::MUL},
        {"div", InstructionType::DIV},
        // Logical Operation
        {"and", InstructionType::AND},
        {"or",  InstructionType::OR},
        {"xor", InstructionType::XOR},
        // Data Transfer Operation
        {"lea", InstructionType::LEA},
        {"mov", InstructionType::MOV},
        {"xchg", InstructionType::XCHG},
        // Control Stream Operation
        {"jmp", InstructionType::JMP},
        {"je",  InstructionType::JE},
        {"jz",  InstructionType::JZ},
        {"jne", InstructionType::JNE},
        {"jnz", InstructionType::JNZ},
        {"jg",  InstructionType::JG},
        {"jge", InstructionType::JGLE},
        {"jl",  InstructionType::JL},
        {"jle", InstructionType::JNGE},
        {"call", InstructionType::CALL},
        {"ret", InstructionType::RET},
        {"nop", InstructionType::NOP},
        // Comparison Operation
        {"cmp", InstructionType::CMP},
        {"test", InstructionType::TEST},
        // Bit Manipulation Operation
        {"shl", InstructionType::SHL},
        {"shr", InstructionType::SHR},
        {"sar", InstructionType::SAR},
        {"rol", InstructionType::ROL},
        {"ror", InstructionType::ROR},
        // Stack Operation
        {"push", InstructionType::PUSH},
        {"pop", InstructionType::POP},
        {"enter", InstructionType::ENTER},
        {"leave", InstructionType::LEAVE},
        // Float Operation
        {"fld", InstructionType::FLD},
        {"fst", InstructionType::FST},
        {"fadd", InstructionType::FADD},
        {"fsub", InstructionType::FSUB},
        {"fmul", InstructionType::FMUL},
        {"fdiv", InstructionType::FDIV},
        // Misc Operation
        {"syscall", InstructionType::SYSCALL},
        {"sysret", InstructionType::SYSRET},
        {"int", InstructionType::INT},
        {"iret", InstructionType::IRET},
        {"hlt", InstructionType::HLT}
    };

    const std::unordered_map<std::string, RegisterType> REGISTER_MAP = {
        {"rax", RegisterType::RAX},
        {"rbx", RegisterType::RBX},
        {"rcx", RegisterType::RCX},
        {"rdx", RegisterType::RDX},
        {"rsi", RegisterType::RSI},
        {"rdi", RegisterType::RDI},
        {"rbp", RegisterType::RBP},
        {"rsp", RegisterType::RSP},
        {"r8",  RegisterType::R8},
        {"r9",  RegisterType::R9},
        {"r10", RegisterType::R10},
        {"r11", RegisterType::R11},
        {"r12", RegisterType::R12},
        {"r13", RegisterType::R13},
        {"r14", RegisterType::R14},
        {"r15", RegisterType::R15},
        {"eax", RegisterType::EAX},
        {"ebx", RegisterType::EBX},
        {"ecx", RegisterType::ECX},
        {"edx", RegisterType::EDX}
    };
} 