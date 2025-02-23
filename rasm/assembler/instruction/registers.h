#pragma once
#include <unordered_map>
#include <string>

namespace Ryntra::rasm {
    enum class RegisterType {
        // 64-bits General Purpose Registers
        RAX, RBX, RCX, RDX,                   // Accumulator, Base, Counter, Data
        RSI, RDI, RBP, RSP,                   // Source Index, Destination Index, Base Pointer, Stack Pointer
        R8,  R9,  R10, R11,                   // General Purpose
        R12, R13, R14, R15,                   // General Purpose
        
        // 32-bits General Purpose Registers
        EAX, EBX, ECX, EDX,                   // Accumulator, Base, Counter, Data
        
        Unknown
    };

    const std::unordered_map<std::string, RegisterType> REGISTER_MAP = {
        {"rax", RegisterType::RAX}, {"rbx", RegisterType::RBX},
        {"rcx", RegisterType::RCX}, {"rdx", RegisterType::RDX},
        // ... 其他寄存器映射
    };
} 