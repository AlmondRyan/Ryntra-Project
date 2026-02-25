#pragma once

#include "SourceLocation/SourceLocation.h"
#include "Value.h"
#include <string>
#include <vector>

namespace Ryntra::Compiler {
    enum class OpCode {
        Module = 0x01,
        External = 0x02,
        Constant = 0x03,
        Load = 0x04,
        Call = 0x05,
        Ret = 0x06,
        Entry = 0x07,
        // Arithmetic
        Add = 0x10,
        Sub = 0x11,
        Mul = 0x12,
        Div = 0x13,
        // Comparison
        CmpEQ = 0x20,
        CmpNE = 0x21,
        CmpLT = 0x22,
        CmpGT = 0x23,
    };

    class BasicBlock;
    class Function;

    class Instruction : public Value {
    public:
        Instruction(Type *ty, OpCode op, const std::string &name = "", BasicBlock *parent = nullptr)
            : Value(ty, name), opcode(op), parent(parent) {}

        virtual ~Instruction() = default;

        OpCode getOpCode() const { return opcode; }

        void setSourceLocation(const SourceLocation &loc) { location = loc; }
        SourceLocation getSourceLocation() const { return location; }

        BasicBlock *getParent() const { return parent; }
        void setParent(BasicBlock *bb) { parent = bb; }

        const std::vector<Value *> &getOperands() const { return operands; }
        void addOperand(Value *v) { operands.push_back(v); }
        void setOperand(size_t index, Value *v) {
            if (index < operands.size())
                operands[index] = v;
            else
                operands.push_back(v);
        }

        std::string print() const;

        std::string toString() const override { return "%" + getName(); }

    protected:
        OpCode opcode;
        std::vector<Value *> operands;
        SourceLocation location;
        BasicBlock *parent;
    };

    // 3. Define specific instructions
    class LoadInst : public Instruction {
    public:
        LoadInst(Value *ptr, const std::string &name = "", BasicBlock *parent = nullptr);
    };

    class CallInst : public Instruction {
    public:
        CallInst(Function *func, const std::vector<Value *> &args, const std::string &name = "", BasicBlock *parent = nullptr);
    };

    class RetInst : public Instruction {
    public:
        RetInst(Value *val = nullptr, BasicBlock *parent = nullptr);
    };
} // namespace Ryntra::Compiler
