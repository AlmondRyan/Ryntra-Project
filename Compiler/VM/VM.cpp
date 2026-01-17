#include "VM.h"
#include <iostream>
#include <variant>
#include <limits>

namespace Ryntra::VM {
    void RVM::operate() {
        ip = 0;
        hasReturn = false;
        while (ip < program.size()) {
            Instruction& instruction = program[ip];
            switch (instruction.opCode) {
            case OpCodes::LD_CONST: {
                stack.push_back(constantPool[instruction.operand]);
                break;
            }
            case OpCodes::STORE_VAR: {
                Value value = pop();
                if (instruction.operand >= static_cast<int>(variables.size())) {
                    variables.resize(static_cast<size_t>(instruction.operand) + 1);
                }
                variables[static_cast<size_t>(instruction.operand)] = value;
                break;
            }
            case OpCodes::LOAD_VAR: {
                if (instruction.operand < static_cast<int>(variables.size())) {
                    push(variables[static_cast<size_t>(instruction.operand)]);
                }
                break;
            }
            case OpCodes::ADD: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs + rhs;
                push(result);
                break;
            }
            case OpCodes::SUB: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs - rhs;
                push(result);
                break;
            }
            case OpCodes::MUL: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs * rhs;
                push(result);
                break;
            }
            case OpCodes::DIV: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs / rhs;
                push(result);
                break;
            }
            case OpCodes::MOD: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs % rhs;
                push(result);
                break;
            }
            case OpCodes::AND: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs & rhs;
                push(result);
                break;
            }
            case OpCodes::OR: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs | rhs;
                push(result);
                break;
            }
            case OpCodes::XOR: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs ^ rhs;
                push(result);
                break;
            }
            case OpCodes::SHL: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs << rhs;
                push(result);
                break;
            }
            case OpCodes::SHR: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs >> rhs;
                push(result);
                break;
            }
            case OpCodes::EQ: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs == rhs;
                push(result);
                break;
            }
            case OpCodes::NE: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs != rhs;
                push(result);
                break;
            }
            case OpCodes::LT: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs < rhs;
                push(result);
                break;
            }
            case OpCodes::LE: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs <= rhs;
                push(result);
                break;
            }
            case OpCodes::GT: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs > rhs;
                push(result);
                break;
            }
            case OpCodes::GE: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rhs = std::get<int>(rhsValue.data);
                int lhs = std::get<int>(lhsValue.data);
                Value result;
                result.data = lhs >= rhs;
                push(result);
                break;
            }
            case OpCodes::NOT: {
                Value value = pop();
                bool cond = false;
                if (std::holds_alternative<int>(value.data)) {
                    cond = std::get<int>(value.data) != 0;
                } else if (std::holds_alternative<bool>(value.data)) {
                    cond = std::get<bool>(value.data);
                }
                Value result;
                result.data = !cond;
                push(result);
                break;
            }
            case OpCodes::JMP: {
                ip = static_cast<size_t>(instruction.operand);
                continue;
            }
            case OpCodes::JZ: {
                Value value = pop();
                bool cond = false;
                if (std::holds_alternative<int>(value.data)) {
                    cond = std::get<int>(value.data) != 0;
                } else if (std::holds_alternative<bool>(value.data)) {
                    cond = std::get<bool>(value.data);
                } else {
                    cond = true;
                }
                if (!cond) {
                    ip = static_cast<size_t>(instruction.operand);
                    continue;
                }
                break;
            }
            case OpCodes::RETURN: {
                if (!stack.empty()) {
                    returnValue = pop();
                } else {
                    Value v;
                    v.data = 0;
                    returnValue = v;
                }
                hasReturn = true;
                return;
            }
            case OpCodes::HALT:
                return;
            case OpCodes::NOP:
                break;
            case OpCodes::B_CALL:
                builtins[instruction.operand](*this);
                break;
            }

            ++ip;
        }
    }

    void RVM::registerBuiltinFunction() {
        builtins[0] = [](RVM& vm) {
            auto value = vm.pop();
            std::visit([](auto&& v) {
                std::cout << v;
            }, value.data);
        };

        builtins[1] = [](RVM& vm) {
            int input = 0;
            if (!(std::cin >> input)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                input = 0;
            }
            Value v;
            v.data = input;
            vm.push(v);
        };

        builtins[2] = [](RVM& vm) {
            auto value = vm.pop();
            int i = std::get<int>(value.data);
            Value v;
            v.data = std::to_string(i);
            vm.push(v);
        };
    }
} // namespace Ryntra::VM
