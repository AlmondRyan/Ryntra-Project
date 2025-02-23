#pragma once
#ifndef RASM_DATA_TRANSFER_INSTRUCTION_H
#define RASM_DATA_TRANSFER_INSTRUCTION_H

#include "assembler/instruction/instruction_types.h"
#include "assembler/instruction/instruction_info.h"

namespace Ryntra::rasm::data_transfer {
    // 数据传输指令的具体信息
    const std::unordered_map<std::string, InstructionInfo> DATA_TRANSFER_INSTRUCTIONS = {
        // 基本数据传输
        {"mov",  {InstructionType::MOV,  "Move data", "Data Transfer", 2, 2, false, RegisterType::Unknown}},
        {"xchg", {InstructionType::XCHG, "Exchange data", "Data Transfer", 2, 2, false, RegisterType::Unknown}},
        {"lea",  {InstructionType::LEA,  "Load effective address", "Data Transfer", 2, 2, false, RegisterType::Unknown}},
        
        // 栈操作
        {"push", {InstructionType::PUSH, "Push onto stack", "Data Transfer", 1, 1, false, RegisterType::Unknown}},
        {"pop",  {InstructionType::POP,  "Pop from stack", "Data Transfer", 1, 1, false, RegisterType::Unknown}},
        
#ifdef USE_SSE
        // SSE 数据传输
        {"movss", {InstructionType::MOVSS, "Move scalar single-precision", "SIMD", 2, 2, false, RegisterType::Unknown}},
#endif
    };
} // namespace Ryntra::rasm::data_transfer

#endif // RASM_DATA_TRANSFER_INSTRUCTION_H
