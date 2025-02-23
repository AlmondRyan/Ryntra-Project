#pragma once
#ifndef RASM_ARITHMETIC_INSTRUCTION_H
#define RASM_ARITHMETIC_INSTRUCTION_H

#include "assembler/instruction/instruction_types.h"
#include "assembler/instruction/instruction_info.h"

namespace Ryntra::rasm::arithmetic {
    // 算术指令的具体信息
    const std::unordered_map<std::string, InstructionInfo> ARITHMETIC_INSTRUCTIONS = {
        // 基本算术运算
        {"add",  {InstructionType::ADD,  "Add two operands", "Arithmetic", 2, 2, false, RegisterType::Unknown}},
        {"sub",  {InstructionType::SUB,  "Subtract second operand from first", "Arithmetic", 2, 2, false, RegisterType::Unknown}},
        {"mul",  {InstructionType::MUL,  "Unsigned multiply", "Arithmetic", 1, 1, true, RegisterType::RAX}},
        {"div",  {InstructionType::DIV,  "Unsigned divide", "Arithmetic", 1, 1, true, RegisterType::RAX}},
        {"inc",  {InstructionType::INC,  "Increment by 1", "Arithmetic", 1, 1, false, RegisterType::Unknown}},
        {"dec",  {InstructionType::DEC,  "Decrement by 1", "Arithmetic", 1, 1, false, RegisterType::Unknown}},
        {"neg",  {InstructionType::NEG,  "Two's complement negation", "Arithmetic", 1, 1, false, RegisterType::Unknown}},
    };
} // namespace Ryntra::rasm::arithmetic

#endif // RASM_ARITHMETIC_INSTRUCTION_H
