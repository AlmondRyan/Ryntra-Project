#include "VirtualMachine.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace Ryntra::VM {
    VirtualMachine::VirtualMachine() {
        // Builtin table — index must match BytecodeGenerator::getBuiltinIndex
        builtins_ = {
            // 0: __builtin_print (generic, handles all types at runtime)
            [](const std::vector<VMValue> &args) -> VMValue {
                if (!args.empty()) {
                    if (args[0].isString()) {
                        const std::string &s = args[0].asString();
                        for (char c : s) {
                            if (c == '\0')
                                break;
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
            [](const std::vector<VMValue> &args) -> VMValue {
                if (!args.empty() && args[0].isInt32()) {
                    std::cout << args[0].asInt32();
                }
                return VMValue();
            },
            // 2: __builtin_print_i64 — prints int64
            [](const std::vector<VMValue> &args) -> VMValue {
                if (!args.empty() && args[0].isInt64()) {
                    std::cout << args[0].asInt64();
                }
                return VMValue();
            },
            // 3: __builtin_print_bool — prints "true" or "false"
            [](const std::vector<VMValue> &args) -> VMValue {
                if (!args.empty() && args[0].isInt32()) {
                    std::cout << (args[0].asInt32() ? "true" : "false");
                }
                return VMValue();
            },
            // 4: __builtin_print_string — prints string
            [](const std::vector<VMValue> &args) -> VMValue {
                if (!args.empty() && args[0].isString()) {
                    const std::string &s = args[0].asString();
                    for (char c : s) {
                        if (c == '\0')
                            break;
                        std::cout << c;
                    }
                }
                return VMValue();
            },
            // 5: __builtin_scan_bool — reads bool from stdin
            [](const std::vector<VMValue> &args) -> VMValue {
                std::string input;
                std::cin >> input;
                std::transform(input.begin(), input.end(), input.begin(), ::tolower);
                if (input == "true") {
                    return VMValue(static_cast<int32_t>(1));
                } else if (input == "false") {
                    return VMValue(static_cast<int32_t>(0));
                } else {
                    try {
                        int32_t val = std::stoi(input);
                        return VMValue(val != 0 ? static_cast<int32_t>(1) : static_cast<int32_t>(0));
                    } catch (...) {
                        return VMValue(static_cast<int32_t>(0));
                    }
                }
            },
            // 6: __builtin_scan_i32 — reads int32 from stdin
            [](const std::vector<VMValue> &args) -> VMValue {
                int32_t val;
                std::cin >> val;
                return VMValue(val);
            },
            // 7: __builtin_scan_i64 — reads int64 from stdin
            [](const std::vector<VMValue> &args) -> VMValue {
                int64_t val;
                std::cin >> val;
                return VMValue(val);
            },
        };

        builtinArgCounts_ = {1, 1, 1, 1, 1, 0, 0, 0}; // arg count per builtin index
    }

    void VirtualMachine::load(const std::vector<std::shared_ptr<BytecodeFunction>> &funcs,
                              const std::vector<VMValue> &constantPool) {
        functionList_ = funcs;
        constantPool_ = constantPool;
        functionMap_.clear();
        for (const auto &f : funcs) {
            functionMap_[f->name] = f;
        }
    }

    VMValue VirtualMachine::execute(const std::string &entryPoint) {
        auto it = functionMap_.find(entryPoint);
        if (it == functionMap_.end()) {
            throw std::runtime_error("Entry point not found: " + entryPoint);
        }
        return executeFunction(it->second.get(), {});
    }

    VMValue VirtualMachine::executeFunction(BytecodeFunction *func, const std::vector<VMValue> &args) {

        locals_.clear();
        size_t ip = 0;
        while (ip < func->instructions.size()) {
            const auto &inst = func->instructions[ip];

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
                auto *callee = functionList_[inst.operand].get();

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
                size_t argCount = static_cast<size_t>(builtinArgCounts_[inst.operand]);
                std::vector<VMValue> callArgs(argCount);
                for (int i = static_cast<int>(argCount) - 1; i >= 0; --i) {
                    callArgs[i] = pop();
                }
                VMValue result = builtins_[inst.operand](callArgs);
                if (!result.isVoid())
                    push(result);
                break;
            }

            case OpCode::Return: {
                if (!stack_.empty()) {
                    return pop();
                }
                return VMValue();
            }

            case OpCode::Add: {
                auto b = pop();
                auto a = pop();
                if (a.isInt64() && b.isInt64())
                    push(VMValue(a.asInt64() + b.asInt64()));
                else if (a.isInt32() && b.isInt32())
                    push(VMValue(a.asInt32() + b.asInt32()));
                break;
            }
            case OpCode::Sub: {
                auto b = pop();
                auto a = pop();
                if (a.isInt64() && b.isInt64())
                    push(VMValue(a.asInt64() - b.asInt64()));
                else if (a.isInt32() && b.isInt32())
                    push(VMValue(a.asInt32() - b.asInt32()));
                break;
            }
            case OpCode::Mul: {
                auto b = pop();
                auto a = pop();
                if (a.isInt64() && b.isInt64())
                    push(VMValue(a.asInt64() * b.asInt64()));
                else if (a.isInt32() && b.isInt32())
                    push(VMValue(a.asInt32() * b.asInt32()));
                break;
            }
            case OpCode::Div: {
                auto b = pop();
                auto a = pop();
                if (a.isInt64() && b.isInt64() && b.asInt64() != 0)
                    push(VMValue(a.asInt64() / b.asInt64()));
                else if (a.isInt32() && b.isInt32() && b.asInt32() != 0)
                    push(VMValue(a.asInt32() / b.asInt32()));
                break;
            }
            case OpCode::Mod: {
                auto b = pop();
                auto a = pop();
                if (a.isInt64() && b.isInt64() && b.asInt64() != 0)
                    push(VMValue(a.asInt64() % b.asInt64()));
                else if (a.isInt32() && b.isInt32() && b.asInt32() != 0)
                    push(VMValue(a.asInt32() % b.asInt32()));
                break;
            }

            case OpCode::BitNot: {
                auto a = pop();
                if (a.isInt64())
                    push(VMValue(~a.asInt64()));
                else if (a.isInt32())
                    push(VMValue(~a.asInt32()));
                break;
            }
            case OpCode::BitAnd: {
                auto b = pop();
                auto a = pop();
                if (a.isInt64() && b.isInt64())
                    push(VMValue(a.asInt64() & b.asInt64()));
                else if (a.isInt32() && b.isInt32())
                    push(VMValue(a.asInt32() & b.asInt32()));
                break;
            }
            case OpCode::BitOr: {
                auto b = pop();
                auto a = pop();
                if (a.isInt64() && b.isInt64())
                    push(VMValue(a.asInt64() | b.asInt64()));
                else if (a.isInt32() && b.isInt32())
                    push(VMValue(a.asInt32() | b.asInt32()));
                break;
            }
            case OpCode::BitXor: {
                auto b = pop();
                auto a = pop();
                if (a.isInt64() && b.isInt64())
                    push(VMValue(a.asInt64() ^ b.asInt64()));
                else if (a.isInt32() && b.isInt32())
                    push(VMValue(a.asInt32() ^ b.asInt32()));
                break;
            }
            case OpCode::Shl: {
                auto b = pop();
                auto a = pop();
                if (a.isInt64() && b.isInt64())
                    push(VMValue(a.asInt64() << (b.asInt64() & 63)));
                else if (a.isInt32() && b.isInt32())
                    push(VMValue(a.asInt32() << (b.asInt32() & 31)));
                break;
            }
            case OpCode::Shr: {
                auto b = pop();
                auto a = pop();
                if (a.isInt64() && b.isInt64())
                    push(VMValue(a.asInt64() >> (b.asInt64() & 63)));
                else if (a.isInt32() && b.isInt32())
                    push(VMValue(a.asInt32() >> (b.asInt32() & 31)));
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

            case OpCode::Dup: {
                if (!stack_.empty()) {
                    push(stack_.back());
                }
                break;
            }

            case OpCode::Pop:
                if (!stack_.empty())
                    pop();
                break;

            case OpCode::StoreLocal: {
                auto val = pop();
                int32_t idx = inst.operand;
                if (idx >= static_cast<int32_t>(locals_.size()))
                    locals_.resize(idx + 1);
                locals_[idx] = val;
                break;
            }

            case OpCode::LoadLocal: {
                int32_t idx = inst.operand;
                if (idx >= 0 && idx < static_cast<int32_t>(locals_.size()))
                    push(locals_[idx]);
                break;
            }

            case OpCode::Halt:
                return VMValue();

            default:
                break;
            }

            ++ip;
        }

        return VMValue();
    }

    static const char *opcodeNames[] = {
        "LoadConst",
        "Call",
        "BCall",
        "Return",
        "Add",
        "Sub",
        "Mul",
        "Div",
        "Mod",
        "BitNot",
        "BitAnd",
        "BitOr",
        "BitXor",
        "Shl",
        "Shr",
        "SExt",
        "Trunc",
        "Dup",
        "Pop",
        "StoreLocal",
        "LoadLocal",
        "Halt",
    };

    void VirtualMachine::disassemble() const {
        for (const auto &func : functionList_) {
            std::cout << "function " << func->name
                      << " (paramCount=" << func->paramCount
                      << ", external=" << (func->isExternal ? "true" : "false") << "):\n";
            if (func->instructions.empty()) {
                std::cout << "  (no instructions)\n";
            } else {
                for (size_t i = 0; i < func->instructions.size(); ++i) {
                    const auto &inst = func->instructions[i];
                    uint8_t idx = static_cast<uint8_t>(inst.opcode);
                    const char *name = (idx < sizeof(opcodeNames) / sizeof(opcodeNames[0]))
                                           ? opcodeNames[idx]
                                           : "???";
                    std::cout << "  " << i << ": " << name;
                    if (inst.opcode == OpCode::LoadConst ||
                        inst.opcode == OpCode::StoreLocal ||
                        inst.opcode == OpCode::LoadLocal) {
                        std::cout << " " << inst.operand;
                    } else if (inst.opcode == OpCode::Call || inst.opcode == OpCode::BCall) {
                        std::cout << " " << inst.operand;
                    }
                    std::cout << "\n";
                }
            }
            std::cout << "\n";
        }
    }

    void VirtualMachine::push(const VMValue &value) {
        stack_.push_back(value);
    }

    VMValue VirtualMachine::pop() {
        if (stack_.empty())
            throw std::runtime_error("Stack underflow");
        VMValue v = stack_.back();
        stack_.pop_back();
        return v;
    }
} // namespace Ryntra::VM
