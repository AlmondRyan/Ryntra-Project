#pragma once

#include "Value.h"
#include "SourceLocation/SourceLocation.h"
#include <vector>
#include <string>

namespace Ryntra::Compiler {

// 1. Define instruction enums with hex codes (starting from 0x01)
enum class OpCode {
    Module   = 0x01,
    External = 0x02,
    Constant = 0x03,
    Load     = 0x04,
    Call     = 0x05,
    Ret      = 0x06,
    // Add other instructions as needed for completeness, but these are the required ones.
    Entry    = 0x07, // Label/Block entry
};

class BasicBlock;
class Function;

// 2. Define Instruction base class, containing SourceLocation and owning function/basic block
class Instruction : public Value {
public:
    Instruction(Type* ty, OpCode op, const std::string& name = "", BasicBlock* parent = nullptr)
        : Value(ty, name), opcode(op), parent(parent) {}
    
    virtual ~Instruction() = default;

    OpCode getOpCode() const { return opcode; }
    
    void setSourceLocation(const SourceLocation& loc) { location = loc; }
    SourceLocation getSourceLocation() const { return location; }

    BasicBlock* getParent() const { return parent; }
    void setParent(BasicBlock* bb) { parent = bb; }

    const std::vector<Value*>& getOperands() const { return operands; }
    void addOperand(Value* v) { operands.push_back(v); }
    void setOperand(size_t index, Value* v) {
        if (index < operands.size()) operands[index] = v;
        else operands.push_back(v); // Simple append for now
    }

    // Returns the full instruction string (e.g. "%0 = load ...")
    std::string print() const;

    // Value::toString returns the name (e.g. "%0")
    std::string toString() const override { return "%" + getName(); }

protected:
    OpCode opcode;
    std::vector<Value*> operands;
    SourceLocation location;
    BasicBlock* parent;
};

// 3. Define specific instructions
// We can use subclasses or just the base class with OpCode.
// For better structure, let's use subclasses for the required ones.

class LoadInst : public Instruction {
public:
    LoadInst(Value* ptr, const std::string& name = "", BasicBlock* parent = nullptr);
};

class CallInst : public Instruction {
public:
    CallInst(Function* func, const std::vector<Value*>& args, const std::string& name = "", BasicBlock* parent = nullptr);
};

class RetInst : public Instruction {
public:
    RetInst(Value* val = nullptr, BasicBlock* parent = nullptr);
};

// External and Constant are usually declarations, but user asked for them as instructions.
// We can treat them as special instructions or just declarations.
// Given the file structure, "external func" is a declaration.
// "constant string" is a global variable definition.
// "module" is a container.

}
