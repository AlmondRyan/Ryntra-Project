#pragma once

#include "Instruction.h"
#include "Value.h"
#include <list>
#include <memory>
#include <string>

namespace Ryntra::Compiler {
    class Function; // Forward declaration

    class BasicBlock : public Value {
    public:
        BasicBlock(const std::string &name, Function *parent);

        Function *getParent() const { return parent; }
        const std::list<std::unique_ptr<Instruction>> &getInstructions() const { return instructions; }

        Instruction *addInstruction(std::unique_ptr<Instruction> inst);

        std::string print() const;

        // Returns label name as operand (e.g. "%entry")
        std::string toString() const override { return "%" + getName(); }

    private:
        Function *parent;
        std::list<std::unique_ptr<Instruction>> instructions;
    };
} // namespace Ryntra::Compiler
