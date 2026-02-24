#include "BasicBlock.h"
#include "Function.h"
#include <sstream>

namespace Ryntra::Compiler {

BasicBlock::BasicBlock(const std::string& name, Function* parent)
    : Value(nullptr, name), parent(parent) {}

Instruction* BasicBlock::addInstruction(std::unique_ptr<Instruction> inst) {
    inst->setParent(this);
    instructions.push_back(std::move(inst));
    return instructions.back().get();
}

std::string BasicBlock::print() const {
    std::stringstream ss;
    ss << getName() << ":\n";
    for (const auto& inst : instructions) {
        ss << "    " << inst->print() << "\n";
    }
    return ss.str();
}

}
