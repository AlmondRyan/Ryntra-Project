#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include "registers.h"
#include "instruction_types.h"

namespace Ryntra::rasm {
    enum class OperandType {
        Register,
        Immediate,
        Memory,
        Label
    };

    struct Operand {
        OperandType type;
        std::string value;
        RegisterType reg = RegisterType::Unknown;
        int64_t immediate = 0;
    };

    struct Instruction {
        InstructionType type = InstructionType::Unknown;
        std::string mnemonic;
        std::vector<Operand> operands;
        uint64_t address = 0;
        std::vector<uint8_t> machineCode;
    };
} 