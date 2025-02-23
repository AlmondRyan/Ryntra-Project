#pragma once
#ifndef RASM_CONTROL_FLOW_INSTRUCTION_H
#define RASM_CONTROL_FLOW_INSTRUCTION_H

#include "assembler/instruction/instruction_types.h"
#include "assembler/instruction/instruction_info.h"

namespace Ryntra::rasm::control_flow {
    // 控制流指令的具体信息
    const std::unordered_map<std::string, InstructionInfo> CONTROL_FLOW_INSTRUCTIONS = {
        // 无条件跳转
        {"jmp",  {InstructionType::JMP,  "Unconditional jump", "Control Flow", 1, 1, false, RegisterType::Unknown}},
        
        // 条件跳转
        {"je",   {InstructionType::JE,   "Jump if equal (ZF=1)", "Control Flow", 1, 1, false, RegisterType::Unknown}},
        {"jne",  {InstructionType::JNE,  "Jump if not equal (ZF=0)", "Control Flow", 1, 1, false, RegisterType::Unknown}},
        {"jg",   {InstructionType::JG,   "Jump if greater (ZF=0 and SF=OF)", "Control Flow", 1, 1, false, RegisterType::Unknown}},
        {"jge",  {InstructionType::JGE,  "Jump if greater or equal (SF=OF)", "Control Flow", 1, 1, false, RegisterType::Unknown}},
        {"jl",   {InstructionType::JL,   "Jump if less (SF!=OF)", "Control Flow", 1, 1, false, RegisterType::Unknown}},
        {"jle",  {InstructionType::JLE,  "Jump if less or equal (ZF=1 or SF!=OF)", "Control Flow", 1, 1, false, RegisterType::Unknown}},
        
        // 子程序调用
        {"call", {InstructionType::CALL, "Call procedure", "Control Flow", 1, 1, false, RegisterType::Unknown}},
        {"ret",  {InstructionType::RET,  "Return from procedure", "Control Flow", 0, 0, false, RegisterType::Unknown}},
    };
} // namespace Ryntra::rasm::control_flow

#endif // RASM_CONTROL_FLOW_INSTRUCTION_H
