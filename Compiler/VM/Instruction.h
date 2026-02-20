#pragma once

#include "OpCode.h"
#include "Value.h"
#include <vector>

namespace Ryntra::Compiler::VM {
    struct Instruction {
        OpCode op;
        Value operand;

        Instruction(OpCode op) : op(op) {}
        Instruction(OpCode op, Value operand) : op(op), operand(operand) {}
    };
} // namespace Ryntra::Compiler::VM
