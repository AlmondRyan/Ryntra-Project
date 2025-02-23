#pragma once
#ifndef RASM_LOGICAL_INSTRUCTION_H
#define RASM_LOGICAL_INSTRUCTION_H

#include "assembler/instruction/instruction_types.h"
#include "assembler/instruction/instruction_info.h"

namespace Ryntra::rasm::logical {
    // 逻辑指令的具体信息
    const std::unordered_map<std::string, InstructionInfo> LOGICAL_INSTRUCTIONS = {
        // 基本逻辑运算
        {"and",  {InstructionType::AND,  "Logical AND", "Logical", 2, 2, false, RegisterType::Unknown}},
        {"or",   {InstructionType::OR,   "Logical OR", "Logical", 2, 2, false, RegisterType::Unknown}},
        {"xor",  {InstructionType::XOR,  "Logical XOR", "Logical", 2, 2, false, RegisterType::Unknown}},
        {"not",  {InstructionType::NOT,  "Logical NOT", "Logical", 1, 1, false, RegisterType::Unknown}},
        
        // 位移操作
        {"shl",  {InstructionType::SHL,  "Shift left", "Logical", 2, 2, false, RegisterType::Unknown}},
        {"shr",  {InstructionType::SHR,  "Shift right", "Logical", 2, 2, false, RegisterType::Unknown}},
        {"rol",  {InstructionType::ROL,  "Rotate left", "Logical", 2, 2, false, RegisterType::Unknown}},
        {"ror",  {InstructionType::ROR,  "Rotate right", "Logical", 2, 2, false, RegisterType::Unknown}},
    };
} // namespace Ryntra::rasm::logical

#endif // RASM_LOGICAL_INSTRUCTION_H
