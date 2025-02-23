#pragma once
#ifndef RASM_INSTRUCTION_INFO_H
#define RASM_INSTRUCTION_INFO_H

#include <string>
#include <vector>
#include <unordered_map>
#include "assembler/instruction/instruction_types.h"

namespace Ryntra::rasm {
    // 指令信息结构
    struct InstructionInfo {
        InstructionType type;
        std::string description;
        std::string category;
        uint8_t minOperands;
        uint8_t maxOperands;
        bool hasImplicitOperand;
        RegisterType implicitReg;
    };

    // 指令信息映射
    const std::unordered_map<std::string, InstructionInfo> INSTRUCTION_INFO = {
        // 数值运算指令
        {"add",  {InstructionType::ADD,  "Add two operands", "Arithmetic", 2, 2, false, RegisterType::Unknown}},
        {"sub",  {InstructionType::SUB,  "Subtract second operand from first", "Arithmetic", 2, 2, false, RegisterType::Unknown}},
        {"mul",  {InstructionType::MUL,  "Unsigned multiply", "Arithmetic", 1, 1, true, RegisterType::RAX}},
        {"div",  {InstructionType::DIV,  "Unsigned divide", "Arithmetic", 1, 1, true, RegisterType::RAX}},
        {"inc",  {InstructionType::INC,  "Increment by 1", "Arithmetic", 1, 1, false, RegisterType::Unknown}},
        {"dec",  {InstructionType::DEC,  "Decrement by 1", "Arithmetic", 1, 1, false, RegisterType::Unknown}},
        
        // 逻辑运算指令
        {"and",  {InstructionType::AND,  "Logical AND", "Logical", 2, 2, false, RegisterType::Unknown}},
        {"or",   {InstructionType::OR,   "Logical OR", "Logical", 2, 2, false, RegisterType::Unknown}},
        {"xor",  {InstructionType::XOR,  "Logical XOR", "Logical", 2, 2, false, RegisterType::Unknown}},
        {"not",  {InstructionType::NOT,  "Logical NOT", "Logical", 1, 1, false, RegisterType::Unknown}},
        
        // 数据传输指令
        {"mov",  {InstructionType::MOV,  "Move data", "Data Transfer", 2, 2, false, RegisterType::Unknown}},
        {"xchg", {InstructionType::XCHG, "Exchange data", "Data Transfer", 2, 2, false, RegisterType::Unknown}},
        {"lea",  {InstructionType::LEA,  "Load effective address", "Data Transfer", 2, 2, false, RegisterType::Unknown}},

#ifdef USE_SSE
        {"movss", {InstructionType::MOVSS, "Move Scalar Single-Precision", "SIMD", 2, 2, false, RegisterType::Unknown}},
#endif

#ifdef USE_AVX
        {"vaddps", {InstructionType::VADDPS, "Vector Add Packed Single-Precision", "SIMD", 3, 3, false, RegisterType::Unknown}},
#endif
    };
} // namespace Ryntra::rasm

#endif // RASM_INSTRUCTION_INFO_H 