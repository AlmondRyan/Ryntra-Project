#pragma once

#include "Instruction.h"
#include "Type.h"
#include <memory>
#include <string>
#include <vector>

namespace Ryntra::IR {
    class Value;

    class BasicBlock {
    public:
        BasicBlock(const std::string &name) : name_(name) {}

        const std::string &getName() const { return name_; }
        void setName(const std::string &name) { name_ = name; }

        void addInstruction(std::shared_ptr<Instruction> instruction) {
            instructions_.push_back(instruction);
        }

        const std::vector<std::shared_ptr<Instruction>> &getInstructions() const {
            return instructions_;
        }

        std::string toString() const {
            std::string result = name_ + ":\n";
            for (const auto &inst : instructions_) {
                result += "    " + inst->toString() + "\n";
            }
            return result;
        }

    private:
        std::string name_;
        std::vector<std::shared_ptr<Instruction>> instructions_;
    };
} // namespace Ryntra::IR