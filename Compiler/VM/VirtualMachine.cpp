#include "VirtualMachine.h"
#include <iostream>
#include <stdexcept>

namespace Ryntra::VM {
    VirtualMachine::VirtualMachine() {
        // Builtin table — index must match BytecodeGenerator::getBuiltinIndex
        builtins_ = {
            // 0: __builtin_print (generic, handles all types at runtime)
            [](const std::vector<VMValue>& args) -> VMValue {
                if (!args.empty()) {
                    if (args[0].isString()) {
                        const std::string& s = args[0].asString();
                        for (char c : s) {
                            if (c == '\0') break;
                            std::cout << c;
                        }
                    } else if (args[0].isInt32()) {
                        std::cout << args[0].asInt32();
                    } else if (args[0].isInt64()) {
                        std::cout << args[0].asInt64();
                    }
                }
                return VMValue();
            },
            // 1: __builtin_print_i32 — prints int32
            [](const std::vector<VMValue>& args) -> VMValue {
                if (!args.empty() && args[0].isInt32()) {
                    std::cout << args[0].asInt32();
                }
                return VMValue();
            },
            // 2: __builtin_print_i64 — prints int64
            [](const std::vector<VMValue>& args) -> VMValue {
                if (!args.empty() && args[0].isInt64()) {
                    std::cout << args[0].asInt64();
                }
                return VMValue();
            },
        };
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


    VMValue VirtualMachine::execute(const std::string& entryPoint) {
        auto it = functionMap_.find(entryPoint);
        if (it == functionMap_.end()) {
            throw std::runtime_error("Entry point not found: " + entryPoint);
        }
        return executeFunction(it->second.get(), {});
    }

    VMValue VirtualMachine::executeFunction(BytecodeFunction* func, const std::vector<VMValue>& args) {

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

            case OpCode::BCall: {
                if (inst.operand < 0 || inst.operand >= static_cast<int32_t>(builtins_.size())) {
                    throw std::runtime_error("Invalid builtin index: " + std::to_string(inst.operand));
                }
                std::vector<VMValue> callArgs;
                if (!stack_.empty()) callArgs.push_back(pop());
                VMValue result = builtins_[inst.operand](callArgs);
                if (!result.isVoid()) push(result);
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
                if (a.isInt64() && b.isInt64()) push(VMValue(a.asInt64() + b.asInt64()));
                else if (a.isInt32() && b.isInt32()) push(VMValue(a.asInt32() + b.asInt32()));
                break;
            }
            case OpCode::Sub: {
                auto b = pop(); auto a = pop();
                if (a.isInt64() && b.isInt64()) push(VMValue(a.asInt64() - b.asInt64()));
                else if (a.isInt32() && b.isInt32()) push(VMValue(a.asInt32() - b.asInt32()));
                break;
            }
            case OpCode::Mul: {
                auto b = pop(); auto a = pop();
                if (a.isInt64() && b.isInt64()) push(VMValue(a.asInt64() * b.asInt64()));
                else if (a.isInt32() && b.isInt32()) push(VMValue(a.asInt32() * b.asInt32()));
                break;
            }
            case OpCode::Div: {
                auto b = pop(); auto a = pop();
                if (a.isInt64() && b.isInt64() && b.asInt64() != 0)
                    push(VMValue(a.asInt64() / b.asInt64()));
                else if (a.isInt32() && b.isInt32() && b.asInt32() != 0)
                    push(VMValue(a.asInt32() / b.asInt32()));
                break;
            }
            case OpCode::Mod: {
                auto b = pop(); auto a = pop();
                if (a.isInt64() && b.isInt64() && b.asInt64() != 0)
                    push(VMValue(a.asInt64() % b.asInt64()));
                else if (a.isInt32() && b.isInt32() && b.asInt32() != 0)
                    push(VMValue(a.asInt32() % b.asInt32()));
                break;
            }

            case OpCode::BitNot: {
                auto a = pop();
                if (a.isInt64()) push(VMValue(~a.asInt64()));
                else if (a.isInt32()) push(VMValue(~a.asInt32()));
                break;
            }
            case OpCode::BitAnd: {
                auto b = pop(); auto a = pop();
                if (a.isInt64() && b.isInt64()) push(VMValue(a.asInt64() & b.asInt64()));
                else if (a.isInt32() && b.isInt32()) push(VMValue(a.asInt32() & b.asInt32()));
                break;
            }
            case OpCode::BitOr: {
                auto b = pop(); auto a = pop();
                if (a.isInt64() && b.isInt64()) push(VMValue(a.asInt64() | b.asInt64()));
                else if (a.isInt32() && b.isInt32()) push(VMValue(a.asInt32() | b.asInt32()));
                break;
            }
            case OpCode::BitXor: {
                auto b = pop(); auto a = pop();
                if (a.isInt64() && b.isInt64()) push(VMValue(a.asInt64() ^ b.asInt64()));
                else if (a.isInt32() && b.isInt32()) push(VMValue(a.asInt32() ^ b.asInt32()));
                break;
            }
            case OpCode::Shl: {
                auto b = pop(); auto a = pop();
                if (a.isInt64() && b.isInt64()) push(VMValue(a.asInt64() << (b.asInt64() & 63)));
                else if (a.isInt32() && b.isInt32()) push(VMValue(a.asInt32() << (b.asInt32() & 31)));
                break;
            }
            case OpCode::Shr: {
                auto b = pop(); auto a = pop();
                if (a.isInt64() && b.isInt64()) push(VMValue(a.asInt64() >> (b.asInt64() & 63)));
                else if (a.isInt32() && b.isInt32()) push(VMValue(a.asInt32() >> (b.asInt32() & 31)));
                break;
            }

            case OpCode::SExt: {
                auto a = pop();
                if (a.isInt32()) {
                    push(VMValue(static_cast<int64_t>(a.asInt32())));
                } else {
                    push(a);
                }
                break;
            }

            case OpCode::Trunc: {
                auto a = pop();
                if (a.isInt64()) {
                    push(VMValue(static_cast<int32_t>(a.asInt64())));
                } else {
                    push(a);
                }
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
