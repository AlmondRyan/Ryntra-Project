#include "IRBuilder.h"
#include "BasicBlock.h"
#include "Constant.h"
#include "Function.h"
#include "Instruction.h"
#include "Module.h"
#include "Type.h"

namespace Ryntra::Compiler {
    Function *IRBuilder::CreateFunction(const std::string &name, Type *retType, std::vector<Type *> argTypes) {
        nextRegisterId = 0; // Reset for new function
        auto func = std::make_unique<Function>(name, retType, module, argTypes);
        Function *ptr = func.get();
        module->addFunction(std::move(func));
        return ptr;
    }

    BasicBlock *IRBuilder::CreateBasicBlock(const std::string &name, Function *parent) {
        auto bb = std::make_unique<BasicBlock>(name, parent);
        BasicBlock *ptr = bb.get();
        if (parent) {
            parent->addBasicBlock(std::move(bb));
        }
        return ptr;
    }

    Instruction *IRBuilder::CreateLoad(ConstantObject *global) {
        auto inst = std::make_unique<LoadInst>(global, getNextRegisterName(), insertBlock);
        Instruction *ptr = inst.get();
        if (insertBlock)
            insertBlock->addInstruction(std::move(inst));
        return ptr;
    }

    Instruction *IRBuilder::CreateCall(Function *func, const std::vector<Value *> &args) {
        // If function returns void, it doesn't need a register name
        std::string name = (func && func->getReturnType()->getID() != TypeID::Void) ? getNextRegisterName() : "";
        auto inst = std::make_unique<CallInst>(func, args, name, insertBlock);
        Instruction *ptr = inst.get();
        if (insertBlock)
            insertBlock->addInstruction(std::move(inst));
        return ptr;
    }

    Instruction *IRBuilder::CreateRet(Value *val) {
        auto inst = std::make_unique<RetInst>(val, insertBlock);
        Instruction *ptr = inst.get();
        if (insertBlock)
            insertBlock->addInstruction(std::move(inst));
        return ptr;
    }

    std::string IRBuilder::getNextRegisterName() {
        return std::to_string(nextRegisterId++);
    }

    Function *IRBuilder::CreateExternalFunction(const std::string &name, Type *retType, std::vector<Type *> argTypes) {
        return CreateFunction(name, retType, argTypes);
    }
} // namespace Ryntra::Compiler
