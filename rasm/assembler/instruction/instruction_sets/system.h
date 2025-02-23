#pragma once
#ifndef RASM_SYSTEM_INSTRUCTION_H
#define RASM_SYSTEM_INSTRUCTION_H

#include "assembler/instruction/instruction_types.h"
#include "assembler/instruction/instruction_info.h"

namespace Ryntra::rasm::system {
    // 系统指令的具体信息
    const std::unordered_map<std::string, InstructionInfo> SYSTEM_INSTRUCTIONS = {
        // 系统调用
        {"syscall", {InstructionType::SYSCALL, "System call", "System", 0, 0, false, RegisterType::Unknown}},
        {"int",     {InstructionType::INT,     "Software interrupt", "System", 1, 1, false, RegisterType::Unknown}},
        
        // 特权指令
        {"cli",     {InstructionType::CLI,     "Clear interrupt flag", "System", 0, 0, false, RegisterType::Unknown}},
        {"sti",     {InstructionType::STI,     "Set interrupt flag", "System", 0, 0, false, RegisterType::Unknown}},
        {"hlt",     {InstructionType::HLT,     "Halt processor", "System", 0, 0, false, RegisterType::Unknown}},
    };
} // namespace Ryntra::rasm::system

#endif // RASM_SYSTEM_INSTRUCTION_H
