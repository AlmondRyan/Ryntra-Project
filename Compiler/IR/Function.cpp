#include "Function.h"
#include "BasicBlock.h"
#include "Module.h"
#include <sstream>

namespace Ryntra::Compiler {
    Function::Function(const std::string &name, Type *retType, Module *parent, std::vector<Type *> argTypes)
        : Value(retType, name), parent(parent), argTypes(argTypes) {}

    BasicBlock *Function::addBasicBlock(std::unique_ptr<BasicBlock> bb) {
        basicBlocks.push_back(std::move(bb));
        return basicBlocks.back().get();
    }

    std::string Function::print() const {
        std::stringstream ss;
        if (isDeclaration()) {
            ss << "external func @" << getName() << "(";
        } else {
            ss << "func @" << getName() << "(";
        }

        for (size_t i = 0; i < argTypes.size(); ++i) {
            if (i > 0)
                ss << ", ";
            ss << argTypes[i]->toString();
        }
        ss << ") -> " << getType()->toString();

        if (isDeclaration()) {
        } else {
            ss << " {\n";
            for (const auto &bb : basicBlocks) {
                ss << bb->print();
            }
            ss << "}";
        }
        return ss.str();
    }
} // namespace Ryntra::Compiler
