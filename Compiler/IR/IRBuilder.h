#pragma once

#include "Type.h"
#include "Value.h"
#include "Constant.h"
#include "Instruction.h"
#include "BasicBlock.h"
#include "Function.h"
#include "Module.h"

namespace Ryntra::Compiler {

// --- IRBuilder ---
class IRBuilder {
public:
    IRBuilder(Module* m) : module(m), insertBlock(nullptr) {}

    void SetInsertPoint(BasicBlock* bb) { insertBlock = bb; }
    BasicBlock* GetInsertBlock() const { return insertBlock; }

    // Helpers to create structural elements
    Function* CreateFunction(const std::string& name, Type* retType, std::vector<Type*> argTypes = {});
    BasicBlock* CreateBasicBlock(const std::string& name, Function* parent);
    
    // Create a string constant.
    // If name is provided, it will be prefixed with '@' automatically if not present.
    ConstantObject* CreateConstantString(const std::string& name, const std::string& val);
    // Overload for auto-naming (str0, str1, ...).
    ConstantObject* CreateConstantString(const std::string& val);

    // Helpers to create instructions
    Instruction* CreateLoadC(ConstantObject* global, const std::string& destName = "");
    Instruction* CreateSyscall(int code);
    Instruction* CreateHalt();
    Instruction* CreateCall(Function* func, const std::vector<Value*>& args, const std::string& destName = "");
    Instruction* CreateRet(Value* val);

private:
    Module* module;
    BasicBlock* insertBlock;
    size_t tempVarCounter = 0;
};

}
