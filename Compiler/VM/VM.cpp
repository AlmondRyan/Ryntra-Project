#include "VM.h"
#include "../IR/Constant.h"
#include <stdexcept>

namespace Ryntra::Compiler::VM {
    VM::VM() : currentModule(nullptr), returning(false) {
        registerIntrinsic("__builtin_print", [](const std::vector<RuntimeValue>& args) {
            for (const auto& arg : args) {
                std::cout << arg.toString();
            }
            return RuntimeValue();
        });
    }

    VM::~VM() = default;

    void VM::registerIntrinsic(const std::string& name, IntrinsicHandler handler) {
        intrinsics[name] = std::move(handler);
    }

    RuntimeValue VM::run(Module* module, const std::string& entryFunc) {
        currentModule = module;
        Function* main = module->getFunction(entryFunc);
        if (!main) {
            throw std::runtime_error("Entry function not found: " + entryFunc);
        }

        return callFunction(main, {});
    }

    RuntimeValue VM::callFunction(Function* func, std::vector<RuntimeValue> args) {
        // Handle external functions (intrinsics) via registered handlers
        if (func->isDeclaration()) {
            auto it = intrinsics.find(func->getName());
            if (it != intrinsics.end()) {
                return it->second(args);
            }
            throw std::runtime_error("Unknown external function: " + func->getName());
        }

        // Create new frame
        auto frame = std::make_unique<Frame>(func, std::move(args));
        callStack.push_back(std::move(frame));

        bool oldReturning = returning;
        returning = false;

        while (!returning) {
            Instruction* inst = callStack.back()->getNextInstruction();
            if (!inst) break;
            executeInstruction(inst);
        }

        RuntimeValue result = std::move(returnValue);
        callStack.pop_back();
        returning = oldReturning; // Restore returning state for the caller
        
        return result;
    }

    void VM::executeInstruction(Instruction* inst) {
        switch (inst->getOpCode()) {
            case OpCode::Load: {
                Value* operand = inst->getOperands()[0];
                RuntimeValue val = resolveValue(operand);
                stack.push(val);
                if (!inst->getName().empty()) {
                    callStack.back()->setLocal(inst->getName(), val);
                }
                break;
            }
            case OpCode::Add:
            case OpCode::Sub:
            case OpCode::Mul:
            case OpCode::Div: {
                RuntimeValue rhs = resolveValue(inst->getOperands()[1]);
                RuntimeValue lhs = resolveValue(inst->getOperands()[0]);
                stack.push(lhs);
                stack.push(rhs);
                
                RuntimeValue b = stack.pop();
                RuntimeValue a = stack.pop();
                
                RuntimeValue res;
                if (inst->getOpCode() == OpCode::Add) res = RuntimeValue(a.asInt() + b.asInt());
                else if (inst->getOpCode() == OpCode::Sub) res = RuntimeValue(a.asInt() - b.asInt());
                else if (inst->getOpCode() == OpCode::Mul) res = RuntimeValue(a.asInt() * b.asInt());
                else if (inst->getOpCode() == OpCode::Div) res = RuntimeValue(a.asInt() / b.asInt());
                
                stack.push(res);
                if (!inst->getName().empty()) {
                    callStack.back()->setLocal(inst->getName(), res);
                }
                break;
            }
            case OpCode::CmpEQ:
            case OpCode::CmpNE:
            case OpCode::CmpLT:
            case OpCode::CmpGT: {
                RuntimeValue rhs = resolveValue(inst->getOperands()[1]);
                RuntimeValue lhs = resolveValue(inst->getOperands()[0]);
                stack.push(lhs);
                stack.push(rhs);
                
                RuntimeValue b = stack.pop();
                RuntimeValue a = stack.pop();
                
                bool res = false;
                if (inst->getOpCode() == OpCode::CmpEQ) res = (a.asInt() == b.asInt());
                else if (inst->getOpCode() == OpCode::CmpNE) res = (a.asInt() != b.asInt());
                else if (inst->getOpCode() == OpCode::CmpLT) res = (a.asInt() < b.asInt());
                else if (inst->getOpCode() == OpCode::CmpGT) res = (a.asInt() > b.asInt());
                
                RuntimeValue resVal(res ? 1 : 0);
                stack.push(resVal);
                if (!inst->getName().empty()) {
                    callStack.back()->setLocal(inst->getName(), resVal);
                }
                break;
            }
            case OpCode::Call: {
                // CallInst: operands[0] is function, rest are args
                Value* funcVal = inst->getOperands()[0];
                Function* func = dynamic_cast<Function*>(funcVal);
                if (!func) throw std::runtime_error("Invalid call target");

                std::vector<RuntimeValue> args;
                for (size_t i = 1; i < inst->getOperands().size(); ++i) {
                    // Push each argument onto stack
                    RuntimeValue arg = resolveValue(inst->getOperands()[i]);
                    stack.push(arg);
                }

                // Pop arguments from stack for the call
                std::vector<RuntimeValue> callArgs(inst->getOperands().size() - 1);
                for (int i = (int)callArgs.size() - 1; i >= 0; --i) {
                    callArgs[i] = stack.pop();
                }

                RuntimeValue result = callFunction(func, std::move(callArgs));
                
                // Push result back to stack
                stack.push(result);

                if (!inst->getName().empty()) {
                    callStack.back()->setLocal(inst->getName(), result);
                }
                break;
            }
            case OpCode::Ret: {
                if (!inst->getOperands().empty()) {
                    RuntimeValue val = resolveValue(inst->getOperands()[0]);
                    stack.push(val);
                    returnValue = stack.pop();
                } else {
                    returnValue = RuntimeValue();
                }
                returning = true;
                break;
            }
            default:
                throw std::runtime_error("Unsupported opcode");
        }
    }

    RuntimeValue VM::resolveValue(Value* val) {
        if (auto* ci = dynamic_cast<ConstantInt*>(val)) {
            return RuntimeValue(ci->getValue());
        }
        if (auto* co = dynamic_cast<ConstantObject*>(val)) {
            return RuntimeValue(co->getInitValue());
        }
        if (auto* inst = dynamic_cast<Instruction*>(val)) {
            return callStack.back()->getLocal(inst->getName());
        }

        throw std::runtime_error("Cannot resolve value: " + val->toString());
    }
} // namespace Ryntra::Compiler::VM
