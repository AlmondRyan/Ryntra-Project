#pragma once

#include "../IR/Module.h"
#include "Stack.h"
#include "Frame.h"
#include <vector>
#include <memory>
#include <iostream>
#include <functional>
#include <map>

namespace Ryntra::Compiler::VM {
    using IntrinsicHandler = std::function<RuntimeValue(const std::vector<RuntimeValue>&)>;

    class VM {
    public:
        VM();
        ~VM();

        void registerIntrinsic(const std::string& name, IntrinsicHandler handler);
        RuntimeValue run(Module* module, const std::string& entryFunc = "main");

    private:
        RuntimeValue callFunction(Function* func, std::vector<RuntimeValue> args);
        void executeInstruction(Instruction* inst);
        RuntimeValue resolveValue(Value* val);

        Stack stack;
        std::vector<std::unique_ptr<Frame>> callStack;
        Module* currentModule;
        std::map<std::string, IntrinsicHandler> intrinsics;
        bool returning;
        RuntimeValue returnValue;
    };
} // namespace Ryntra::Compiler::VM
