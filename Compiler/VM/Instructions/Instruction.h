#pragma once

#include "OpCode.h"
#include <optional>

namespace Ryntra::VM {
    struct Instruction {
        OpCodes opCode;
        int operand;

        Instruction() = default;
        Instruction(const OpCodes op, const int opr) : opCode(op), operand(opr) {}
    };
}