#pragma once

#include "Module.h"
#include <sstream>
#include <string>

namespace Ryntra::Compiler::IR {
    class LLIRBuilder {
    public:
        std::string emit(Module *module);

    private:
        void emitGlobals(Module *module, std::stringstream &ss);
        void emitFunctions(Module *module, std::stringstream &ss);
        void emitFunction(Function *func, std::stringstream &ss);
        void emitBasicBlock(BasicBlock *bb, std::stringstream &ss);
        void emitInstruction(Instruction *inst, std::stringstream &ss);
    };
} // namespace Ryntra::Compiler::IR
