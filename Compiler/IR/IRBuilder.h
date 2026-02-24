#pragma once

#include "BasicBlock.h"
#include "Constant.h"
#include "Function.h"
#include "Instruction.h"
#include "Module.h"
#include "Type.h"
#include "Value.h"

namespace Ryntra::Compiler {
    class IRBuilder {
    public:
        IRBuilder(Module *m) : module(m), insertBlock(nullptr) {}

        void SetInsertPoint(BasicBlock *bb) { insertBlock = bb; }
        BasicBlock *GetInsertBlock() const { return insertBlock; }

        Function *CreateFunction(const std::string &name, Type *retType, std::vector<Type *> argTypes = {});
        Function *CreateExternalFunction(const std::string &name, Type *retType, std::vector<Type *> argTypes);

        BasicBlock *CreateBasicBlock(const std::string &name, Function *parent = nullptr);

        template <typename T, typename... Args>
        T *CreateConstant(Args &&...args) {
            auto c = std::make_unique<T>(std::forward<Args>(args)...);
            T *ptr = c.get();
            if constexpr (std::is_same_v<T, ConstantObject>) {
                module->addConstantObject(std::move(c));
            } else {
                module->addConstant(std::move(c));
            }
            return ptr;
        }

        Instruction *CreateLoad(ConstantObject *global);
        Instruction *CreateCall(Function *func, const std::vector<Value *> &args);
        Instruction *CreateRet(Value *val);

    private:
        std::string getNextRegisterName();

        Module *module;
        BasicBlock *insertBlock;
        size_t nextRegisterId = 0;
    };
} // namespace Ryntra::Compiler
