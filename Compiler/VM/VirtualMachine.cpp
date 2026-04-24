#include "VirtualMachine.h"
#include <iostream>
#include <stdexcept>

namespace Ryntra::VM {
    VirtualMachine::VirtualMachine() {
        // Register built-in functions
        registerNativeFunction("__builtin_print", [](const std::vector<VMValue>& args) -> VMValue {
            if (!args.empty() && args[0].isString()) {
                // Strip the null terminator that Ryntra strings carry
                const std::string& s = args[0].asString();
                for (char c : s) {
                    if (c == '\0') break;
                    std::cout << c;
                }
            }
            return VMValue(); // void
        });
    }

    void VirtualMachine::load(const std::vector<std::shared_ptr<BytecodeFunction>>& funcs,
                              const std::vector<VMValue>& constantPool)
    {
        functionList_ = funcs;
        constantPool_ = constantPool;
        functionMap_.clear();
        for (const auto& f : funcs) {
            functionMap_[f->name] = f;
        }
    }

    void VirtualMachine::registerNativeFunction(const std::string& name, NativeFunction func) {
        nativeFunctions_[name] = func;
    }

    VMValue VirtualMachine::execute(const std::string& entryPoint) {
        auto it = functionMap_.find(entryPoint);
        if (it == functionMap_.end()) {
            throw std::runtime_error("Entry point not found: " + entryPoint);
        }
        return executeFunction(it->second.get(), {});
    }

    VMValue VirtualMachine::executeFunction(BytecodeFunction* func, const std::vector<VMValue>& args) {
        if (func->isExternal) {
            auto it = nativeFunctions_.find(func->name);
            if (it != nativeFunctions_.end()) {
                return it->second(args);
            }
            throw std::runtime_error("Native function not implemented: " + func->name);
        }

        size_t ip = 0;
        while (ip < func->instructions.size()) {
            const auto& inst = func->instructions[ip];

            switch (inst.opcode) {
            case OpCode::LoadConst: {
                if (inst.operand >= 0 && inst.operand < static_cast<int32_t>(constantPool_.size())) {
                    push(constantPool_[inst.operand]);
                }
                break;
            }

            case OpCode::Call: {
                if (inst.operand < 0 || inst.operand >= static_cast<int32_t>(functionList_.size())) {
                    throw std::runtime_error("Invalid function index: " + std::to_string(inst.operand));
                }
                auto* callee = functionList_[inst.operand].get();

                // Collect arguments based on the callee's declared parameter count
                size_t argCount = static_cast<size_t>(callee->paramCount);

                std::vector<VMValue> callArgs(argCount);
                for (int i = static_cast<int>(argCount) - 1; i >= 0; --i) {
                    callArgs[i] = pop();
                }

                VMValue result = executeFunction(callee, callArgs);
                if (!result.isVoid()) {
                    push(result);
                }
                break;
            }

            case OpCode::Return: {
                if (!stack_.empty()) {
                    return pop();
                }
                return VMValue();
            }

            case OpCode::Add: {
                auto b = pop(); auto a = pop();
                if (a.isInt32() && b.isInt32()) push(VMValue(a.asInt32() + b.asInt32()));
                break;
            }
            case OpCode::Sub: {
                auto b = pop(); auto a = pop();
                if (a.isInt32() && b.isInt32()) push(VMValue(a.asInt32() - b.asInt32()));
                break;
            }
            case OpCode::Mul: {
                auto b = pop(); auto a = pop();
                if (a.isInt32() && b.isInt32()) push(VMValue(a.asInt32() * b.asInt32()));
                break;
            }
            case OpCode::Div: {
                auto b = pop(); auto a = pop();
                if (a.isInt32() && b.isInt32() && b.asInt32() != 0)
                    push(VMValue(a.asInt32() / b.asInt32()));
                break;
            }

            case OpCode::Pop:
                if (!stack_.empty()) pop();
                break;

            case OpCode::Halt:
                return VMValue();

            default:
                break;
            }

            ++ip;
        }

        return VMValue();
    }

    void VirtualMachine::push(const VMValue& value) {
        stack_.push_back(value);
    }

    VMValue VirtualMachine::pop() {
        if (stack_.empty()) throw std::runtime_error("Stack underflow");
        VMValue v = stack_.back();
        stack_.pop_back();
        return v;
    }
} // namespace Ryntra::VM
