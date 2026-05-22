#pragma once

#include "BasicBlock.h"
#include "Constant.h"
#include "Function.h"
#include "Instruction.h"
#include "Module.h"
#include <memory>
#include <string>

namespace Ryntra::IR {
    class IRBuilder {
    public:
        IRBuilder();

        std::shared_ptr<Module> createModule(const std::string &name);

        std::shared_ptr<Function> createFunction(const std::string &name,
                                                 std::shared_ptr<Type> returnType,
                                                 const std::vector<Function::Parameter> &parameters = {},
                                                 bool isExternal = false);

        std::shared_ptr<BasicBlock> createBasicBlock(const std::string &name);

        std::shared_ptr<Constant> createGlobalConstant(const std::string &name,
                                                       std::shared_ptr<Type> type,
                                                       Constant::ValueType value);

        std::shared_ptr<Constant> createGlobalConstant(std::shared_ptr<Type> type,
                                                       Constant::ValueType value);

        std::shared_ptr<Instruction> createLoadConstant(const std::string &name,
                                                        std::shared_ptr<Constant> constant);

        std::shared_ptr<Instruction> createConstant(const std::string &name,
                                                    std::shared_ptr<Type> type,
                                                    std::shared_ptr<Value> value);

        std::shared_ptr<Instruction> createAlloca(const std::string &name,
                                                   std::shared_ptr<Type> elementType);

        std::shared_ptr<Instruction> createLoad(const std::string &name,
                                                 std::shared_ptr<Instruction> allocaInst,
                                                 std::shared_ptr<Type> loadType);

        std::shared_ptr<Instruction> createStore(std::shared_ptr<Value> value,
                                                  std::shared_ptr<Instruction> allocaInst);

        std::shared_ptr<Instruction> createCall(const std::string &name,
                                                 std::shared_ptr<Function> function,
                                                 const std::vector<std::shared_ptr<Value>> &args);

        std::shared_ptr<Instruction> createReturn(const std::string &name,
                                                  std::shared_ptr<Value> value = nullptr);

        std::shared_ptr<Instruction> createReturnInt32(const std::string &name,
                                                       int32_t value);

        std::shared_ptr<Instruction> createUnaryOp(Instruction::Opcode opcode,
                                                   const std::string &name,
                                                   std::shared_ptr<Value> operand);

        std::shared_ptr<Instruction> createSExt(const std::string &name,
                                                std::shared_ptr<Value> operand,
                                                std::shared_ptr<Type> targetType);

        std::shared_ptr<Instruction> createTrunc(const std::string &name,
                                                 std::shared_ptr<Value> operand,
                                                 std::shared_ptr<Type> targetType);

        std::shared_ptr<Instruction> createBinaryOp(Instruction::Opcode opcode,
                                                    const std::string &name,
                                                    std::shared_ptr<Value> lhs,
                                                    std::shared_ptr<Value> rhs);

        std::shared_ptr<Instruction> createCompare(Instruction::Opcode opcode,
                                                    const std::string &name,
                                                    std::shared_ptr<Value> lhs,
                                                    std::shared_ptr<Value> rhs);

        std::shared_ptr<Instruction> createBr(const std::string &targetBlockName);

        std::shared_ptr<Instruction> createCondBr(std::shared_ptr<Value> condition,
                                                   const std::string &trueBlockName,
                                                   const std::string &falseBlockName);

        std::shared_ptr<Instruction> createNewArray(const std::string &name,
                                                     std::shared_ptr<Type> elementType,
                                                     std::shared_ptr<Value> size);

        std::shared_ptr<Instruction> createArrLoad(const std::string &name,
                                                    std::shared_ptr<Value> array,
                                                    std::shared_ptr<Value> index,
                                                    std::shared_ptr<Type> elementType);

        std::shared_ptr<Instruction> createArrStore(std::shared_ptr<Value> array,
                                                      std::shared_ptr<Value> index,
                                                      std::shared_ptr<Value> value);

        std::shared_ptr<Instruction> createRefCreate(const std::string &name,
                                                      std::shared_ptr<Type> refType,
                                                      std::shared_ptr<Value> alloca);

        std::shared_ptr<Instruction> createRefLoad(const std::string &name,
                                                    std::shared_ptr<Value> refValue,
                                                    std::shared_ptr<Type> loadType);

        std::shared_ptr<Instruction> createRefStore(std::shared_ptr<Value> refValue,
                                                      std::shared_ptr<Value> value);

        std::shared_ptr<Instruction> createPtrCreate(const std::string &name,
                                                      std::shared_ptr<Type> ptrType,
                                                      std::shared_ptr<Value> alloca);

        std::shared_ptr<Instruction> createPtrLoad(const std::string &name,
                                                     std::shared_ptr<Value> ptrValue,
                                                     std::shared_ptr<Type> loadType);

        std::shared_ptr<Instruction> createPtrStore(std::shared_ptr<Value> ptrValue,
                                                      std::shared_ptr<Value> value);

        void setInsertPoint(std::shared_ptr<BasicBlock> block);
        std::shared_ptr<BasicBlock> getInsertPoint() const;

        void addInstruction(std::shared_ptr<Instruction> instruction);

        std::shared_ptr<Module> getModule() const { return currentModule_; }

        std::string generateUniqueName(const std::string &base = "temp");

    private:
        std::shared_ptr<Module> currentModule_;
        std::shared_ptr<BasicBlock> currentBlock_;
        int unnamedCounter_;
    };
} // namespace Ryntra::IR
