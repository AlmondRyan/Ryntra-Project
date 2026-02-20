#pragma once

#include "Value.h"
#include <vector>

namespace Ryntra::Compiler {

enum class OpCode {
    LoadC,
    Syscall,
    Halt,
    Call,
    Ret
};

class Instruction : public Value {
public:
    Instruction(Type* ty, OpCode op, const std::string& name = "");
    
    OpCode getOpCode() const { return opcode; }
    const std::vector<Value*>& getOperands() const { return operands; }
    void addOperand(Value* v) { operands.push_back(v); }
    
    std::string toString() const override;

private:
    OpCode opcode;
    std::vector<Value*> operands;
};

}
