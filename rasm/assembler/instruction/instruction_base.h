#pragma once
#ifndef RASM_INSTRUCTION_BASE_H
#define RASM_INSTRUCTION_BASE_H

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include "assembler/instruction/registers.h"
#include "assembler/instruction/instruction_types.h"

namespace Ryntra::rasm {
    // 操作数类型
    enum class OperandType {
        Register,   // 寄存器操作数
        Immediate,  // 立即数操作数
        Memory,     // 内存操作数
        Label      // 标签操作数
    };

    // 操作数大小
    enum class OperandSize {
        Bit8,    // 1字节
        Bit16,   // 2字节
        Bit32,   // 4字节
        Bit64,   // 8字节
        Bit128,  // 16字节 (XMM)
        Bit256,  // 32字节 (YMM)
        Bit512   // 64字节 (ZMM)
    };

    // 操作数结构
    struct Operand {
        OperandType type;
        OperandSize size;
        std::string value;
        RegisterType reg = RegisterType::Unknown;
        int64_t immediate = 0;
        bool isIndirect = false;  // 是否为间接寻址
        int32_t displacement = 0; // 内存寻址的偏移量
    };

    // 指令结构
    struct Instruction {
        InstructionType type = InstructionType::Unknown;
        std::string mnemonic;
        std::vector<Operand> operands;
        uint64_t address = 0;
        std::vector<uint8_t> machineCode;
        bool hasPrefix = false;
        uint8_t prefix = 0;
    };
} // namespace Ryntra::rasm

#endif // RASM_INSTRUCTION_BASE_H 