#pragma once
#ifndef RASM_REGISTER_H
#define RASM_REGISTER_H

#include <string>
#include <unordered_map>

// clang-format off
namespace Ryntra::rasm {
    enum class RegisterType {
        // 64-bits General Purpose Registers
        RAX, RBX, RCX, RDX,                   // Accumulator, Base, Counter, Data
        RSI, RDI, RBP, RSP,                   // Source Index, Destination Index, Base Pointer, Stack Pointer
        R8,  R9,  R10, R11,                   // General Purpose
        R12, R13, R14, R15,                   // General Purpose

        // 32-bits General Purpose Registers
        EAX, EBX, ECX, EDX,                   // Accumulator, Base, Counter, Data

        // Special Registers
        RIP,                                  // Instruction Pointer Register
        RFLAGS,                               // CPU Flags Register

        // Control Registers
        CR0,                                  // Control Register 0 (System Control)
        CR1,                                  // Reserved
        CR2,                                  // Page Fault Linear Address
        CR3,                                  // Page Directory Base
        CR4,                                  // Extensions Control

        // Debug Registers
        DR0,                                  // Debug Address Register 0
        DR1,                                  // Debug Address Register 1
        DR2,                                  // Debug Address Register 2
        DR3,                                  // Debug Address Register 3
        DR4,                                  // Reserved (Alias of DR6)
        DR5,                                  // Reserved (Alias of DR7)
        DR6,                                  // Debug Status
        DR7,                                  // Debug Control

#ifdef USE_SSE
        // SSE 128-bit SIMD Registers
        XMM0,  XMM1,  XMM2,  XMM3,           // XMM Registers 0-3
        XMM4,  XMM5,  XMM6,  XMM7,           // XMM Registers 4-7
        XMM8,  XMM9,  XMM10, XMM11,          // XMM Registers 8-11
        XMM12, XMM13, XMM14, XMM15,          // XMM Registers 12-15
#endif

#ifdef USE_AVX
        // AVX 256-bit SIMD Registers
        YMM0,  YMM1,  YMM2,  YMM3,           // YMM Registers 0-3
        YMM4,  YMM5,  YMM6,  YMM7,           // YMM Registers 4-7
        YMM8,  YMM9,  YMM10, YMM11,          // YMM Registers 8-11
        YMM12, YMM13, YMM14, YMM15,          // YMM Registers 12-15
#endif

#ifdef ENABLE_AVX512
        // AVX-512 512-bit SIMD Registers
        ZMM0,  ZMM1,  ZMM2,  ZMM3,           // ZMM Registers 0-3
        ZMM4,  ZMM5,  ZMM6,  ZMM7,           // ZMM Registers 4-7
        ZMM8,  ZMM9,  ZMM10, ZMM11,          // ZMM Registers 8-11
        ZMM12, ZMM13, ZMM14, ZMM15,          // ZMM Registers 12-15
        ZMM16, ZMM17, ZMM18, ZMM19,          // ZMM Registers 16-19
        ZMM20, ZMM21, ZMM22, ZMM23,          // ZMM Registers 20-23
        ZMM24, ZMM25, ZMM26, ZMM27,          // ZMM Registers 24-27
        ZMM28, ZMM29, ZMM30, ZMM31,          // ZMM Registers 28-31
#endif

        Unknown
    };

    const std::unordered_map<std::string, RegisterType> REGISTER_MAP = {
        // General Purpose Registers (64-bit)
        {"rax", RegisterType::RAX}, {"rbx", RegisterType::RBX},
        {"rcx", RegisterType::RCX}, {"rdx", RegisterType::RDX},
        {"rsi", RegisterType::RSI}, {"rdi", RegisterType::RDI},
        {"rbp", RegisterType::RBP}, {"rsp", RegisterType::RSP},
        {"r8",  RegisterType::R8},  {"r9",  RegisterType::R9},
        {"r10", RegisterType::R10}, {"r11", RegisterType::R11},
        {"r12", RegisterType::R12}, {"r13", RegisterType::R13},
        {"r14", RegisterType::R14}, {"r15", RegisterType::R15},

        // General Purpose Registers (32-bit)
        {"eax", RegisterType::EAX}, {"ebx", RegisterType::EBX},
        {"ecx", RegisterType::ECX}, {"edx", RegisterType::EDX},

        // Special Registers
        {"rip", RegisterType::RIP},
        {"rflags", RegisterType::RFLAGS},

        // Control Registers
        {"cr0", RegisterType::CR0}, {"cr1", RegisterType::CR1},
        {"cr2", RegisterType::CR2}, {"cr3", RegisterType::CR3},
        {"cr4", RegisterType::CR4},

        // Debug Registers
        {"dr0", RegisterType::DR0}, {"dr1", RegisterType::DR1},
        {"dr2", RegisterType::DR2}, {"dr3", RegisterType::DR3},
        {"dr4", RegisterType::DR4}, {"dr5", RegisterType::DR5},
        {"dr6", RegisterType::DR6}, {"dr7", RegisterType::DR7},

#ifdef USE_SSE
        // SSE Registers
        {"xmm0",  RegisterType::XMM0},  {"xmm1",  RegisterType::XMM1},
        {"xmm2",  RegisterType::XMM2},  {"xmm3",  RegisterType::XMM3},
        {"xmm4",  RegisterType::XMM4},  {"xmm5",  RegisterType::XMM5},
        {"xmm6",  RegisterType::XMM6},  {"xmm7",  RegisterType::XMM7},
        {"xmm8",  RegisterType::XMM8},  {"xmm9",  RegisterType::XMM9},
        {"xmm10", RegisterType::XMM10}, {"xmm11", RegisterType::XMM11},
        {"xmm12", RegisterType::XMM12}, {"xmm13", RegisterType::XMM13},
        {"xmm14", RegisterType::XMM14}, {"xmm15", RegisterType::XMM15},
#endif

#ifdef USE_AVX
        // AVX Registers
        {"ymm0",  RegisterType::YMM0},  {"ymm1",  RegisterType::YMM1},
        {"ymm2",  RegisterType::YMM2},  {"ymm3",  RegisterType::YMM3},
        {"ymm4",  RegisterType::YMM4},  {"ymm5",  RegisterType::YMM5},
        {"ymm6",  RegisterType::YMM6},  {"ymm7",  RegisterType::YMM7},
        {"ymm8",  RegisterType::YMM8},  {"ymm9",  RegisterType::YMM9},
        {"ymm10", RegisterType::YMM10}, {"ymm11", RegisterType::YMM11},
        {"ymm12", RegisterType::YMM12}, {"ymm13", RegisterType::YMM13},
        {"ymm14", RegisterType::YMM14}, {"ymm15", RegisterType::YMM15},
#endif

#ifdef ENABLE_AVX512
        // AVX-512 Registers
        {"zmm0",  RegisterType::ZMM0},  {"zmm1",  RegisterType::ZMM1},
        {"zmm2",  RegisterType::ZMM2},  {"zmm3",  RegisterType::ZMM3},
        {"zmm4",  RegisterType::ZMM4},  {"zmm5",  RegisterType::ZMM5},
        {"zmm6",  RegisterType::ZMM6},  {"zmm7",  RegisterType::ZMM7},
        {"zmm8",  RegisterType::ZMM8},  {"zmm9",  RegisterType::ZMM9},
        {"zmm10", RegisterType::ZMM10}, {"zmm11", RegisterType::ZMM11},
        {"zmm12", RegisterType::ZMM12}, {"zmm13", RegisterType::ZMM13},
        {"zmm14", RegisterType::ZMM14}, {"zmm15", RegisterType::ZMM15},
        {"zmm16", RegisterType::ZMM16}, {"zmm17", RegisterType::ZMM17},
        {"zmm18", RegisterType::ZMM18}, {"zmm19", RegisterType::ZMM19},
        {"zmm20", RegisterType::ZMM20}, {"zmm21", RegisterType::ZMM21},
        {"zmm22", RegisterType::ZMM22}, {"zmm23", RegisterType::ZMM23},
        {"zmm24", RegisterType::ZMM24}, {"zmm25", RegisterType::ZMM25},
        {"zmm26", RegisterType::ZMM26}, {"zmm27", RegisterType::ZMM27},
        {"zmm28", RegisterType::ZMM28}, {"zmm29", RegisterType::ZMM29},
        {"zmm30", RegisterType::ZMM30}, {"zmm31", RegisterType::ZMM31},
#endif
    };
    // clang-format on
} // namespace Ryntra::rasm

#endif // RASM_REGISTER_H