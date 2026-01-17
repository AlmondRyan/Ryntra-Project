#include "VM.h"
#include <iostream>
#include <variant>

namespace Ryntra::VM {
    void RVM::operate() {
        ip = 0;
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
            std::string result;
            std::getline(std::cin, result);
            Value v;
            v.data = result;
            vm.push(v);
        };
    }
} // namespace Ryntra::VM
