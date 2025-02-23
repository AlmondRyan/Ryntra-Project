#pragma once
#include <string>
#include <unordered_map>
#include "instruction_types.h"

namespace Ryntra::rasm {
    struct InstructionInfo {
        InstructionType type;
        std::string description;
        std::string category;
    };

    const std::unordered_map<std::string, InstructionInfo> INSTRUCTION_INFO = {
        {"add", {InstructionType::ADD, "Add operation", "Number Operation"}},
        {"sub", {InstructionType::SUB, "Subtract operation", "Number Operation"}},
        // ... 其他指令信息
    };
} 