#pragma once
#ifndef RASM_INSTRUCTION_H
#define RASM_INSTRUCTION_H

// 包含所有指令相关的定义
#include "assembler/instruction/instruction_base.h"
#include "assembler/instruction/registers.h"
#include "assembler/instruction/instruction_types.h"
#include "assembler/instruction/instruction_info.h"

// 包含所有指令集
#include "assembler/instruction/instruction_sets/arithmetic.h"
#include "assembler/instruction/instruction_sets/logical.h"
#include "assembler/instruction/instruction_sets/control_flow.h"
#include "assembler/instruction/instruction_sets/data_transfer.h"
#include "assembler/instruction/instruction_sets/floating_point.h"
#include "assembler/instruction/instruction_sets/system.h"

namespace Ryntra::rasm {
    // 合并所有指令集的映射表
    const std::unordered_map<std::string, InstructionInfo> INSTRUCTION_MAP = []() {
        std::unordered_map<std::string, InstructionInfo> map;
        
        // 合并算术指令
        map.insert(arithmetic::ARITHMETIC_INSTRUCTIONS.begin(), 
                  arithmetic::ARITHMETIC_INSTRUCTIONS.end());
        
        // 合并逻辑指令
        map.insert(logical::LOGICAL_INSTRUCTIONS.begin(), 
                  logical::LOGICAL_INSTRUCTIONS.end());
        
        // 合并控制流指令
        map.insert(control_flow::CONTROL_FLOW_INSTRUCTIONS.begin(), 
                  control_flow::CONTROL_FLOW_INSTRUCTIONS.end());
        
        // 合并数据传输指令
        map.insert(data_transfer::DATA_TRANSFER_INSTRUCTIONS.begin(), 
                  data_transfer::DATA_TRANSFER_INSTRUCTIONS.end());
        
        // 合并浮点指令
        map.insert(floating_point::FLOATING_POINT_INSTRUCTIONS.begin(), 
                  floating_point::FLOATING_POINT_INSTRUCTIONS.end());
        
        // 合并系统指令
        map.insert(system::SYSTEM_INSTRUCTIONS.begin(), 
                  system::SYSTEM_INSTRUCTIONS.end());
        
        return map;
    }();
} // namespace Ryntra::rasm

#endif // RASM_INSTRUCTION_H 