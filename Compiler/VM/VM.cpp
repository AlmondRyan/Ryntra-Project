#include "VM.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <variant>

namespace Ryntra::VM {
    namespace {
        int getNumericRank(const Value& v) {
            if (std::holds_alternative<double>(v.data)) return 5;
            if (std::holds_alternative<float>(v.data)) return 4;
            if (std::holds_alternative<long long>(v.data)) return 3;
            if (std::holds_alternative<int>(v.data)) return 1;
            if (std::holds_alternative<bool>(v.data)) return 1;
            return 0;
        }

        double toDoubleNumeric(const Value& v) {
            if (std::holds_alternative<double>(v.data)) return std::get<double>(v.data);
            if (std::holds_alternative<float>(v.data)) return static_cast<double>(std::get<float>(v.data));
            if (std::holds_alternative<long long>(v.data)) return static_cast<double>(std::get<long long>(v.data));
            if (std::holds_alternative<int>(v.data)) return static_cast<double>(std::get<int>(v.data));
            if (std::holds_alternative<bool>(v.data)) return std::get<bool>(v.data) ? 1.0 : 0.0;
            return 0.0;
        }

        long long toLongLongNumeric(const Value& v) {
            if (std::holds_alternative<long long>(v.data)) return std::get<long long>(v.data);
            if (std::holds_alternative<int>(v.data)) return static_cast<long long>(std::get<int>(v.data));
            if (std::holds_alternative<bool>(v.data)) return std::get<bool>(v.data) ? 1LL : 0LL;
            return 0LL;
        }
    }

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
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                Value result;
                if (rank == 5) {
                    double lhs = toDoubleNumeric(lhsValue);
                    double rhs = toDoubleNumeric(rhsValue);
                    result.data = lhs + rhs;
                } else if (rank == 4) {
                    float lhs = static_cast<float>(toDoubleNumeric(lhsValue));
                    float rhs = static_cast<float>(toDoubleNumeric(rhsValue));
                    result.data = lhs + rhs;
                } else if (rank == 3) {
                    long long lhs = toLongLongNumeric(lhsValue);
                    long long rhs = toLongLongNumeric(rhsValue);
                    result.data = lhs + rhs;
                } else {
                    int lhs = static_cast<int>(toLongLongNumeric(lhsValue));
                    int rhs = static_cast<int>(toLongLongNumeric(rhsValue));
                    result.data = lhs + rhs;
                }
                push(result);
                break;
            }
            case OpCodes::SUB: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                Value result;
                if (rank == 5) {
                    double lhs = toDoubleNumeric(lhsValue);
                    double rhs = toDoubleNumeric(rhsValue);
                    result.data = lhs - rhs;
                } else if (rank == 4) {
                    float lhs = static_cast<float>(toDoubleNumeric(lhsValue));
                    float rhs = static_cast<float>(toDoubleNumeric(rhsValue));
                    result.data = lhs - rhs;
                } else if (rank == 3) {
                    long long lhs = toLongLongNumeric(lhsValue);
                    long long rhs = toLongLongNumeric(rhsValue);
                    result.data = lhs - rhs;
                } else {
                    int lhs = static_cast<int>(toLongLongNumeric(lhsValue));
                    int rhs = static_cast<int>(toLongLongNumeric(rhsValue));
                    result.data = lhs - rhs;
                }
                push(result);
                break;
            }
            case OpCodes::MUL: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                Value result;
                if (rank == 5) {
                    double lhs = toDoubleNumeric(lhsValue);
                    double rhs = toDoubleNumeric(rhsValue);
                    result.data = lhs * rhs;
                } else if (rank == 4) {
                    float lhs = static_cast<float>(toDoubleNumeric(lhsValue));
                    float rhs = static_cast<float>(toDoubleNumeric(rhsValue));
                    result.data = lhs * rhs;
                } else if (rank == 3) {
                    long long lhs = toLongLongNumeric(lhsValue);
                    long long rhs = toLongLongNumeric(rhsValue);
                    result.data = lhs * rhs;
                } else {
                    int lhs = static_cast<int>(toLongLongNumeric(lhsValue));
                    int rhs = static_cast<int>(toLongLongNumeric(rhsValue));
                    result.data = lhs * rhs;
                }
                push(result);
                break;
            }
            case OpCodes::DIV: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                Value result;
                if (rank == 5) {
                    double lhs = toDoubleNumeric(lhsValue);
                    double rhs = toDoubleNumeric(rhsValue);
                    result.data = lhs / rhs;
                } else if (rank == 4) {
                    float lhs = static_cast<float>(toDoubleNumeric(lhsValue));
                    float rhs = static_cast<float>(toDoubleNumeric(rhsValue));
                    result.data = lhs / rhs;
                } else if (rank == 3) {
                    long long lhs = toLongLongNumeric(lhsValue);
                    long long rhs = toLongLongNumeric(rhsValue);
                    result.data = lhs / rhs;
                } else {
                    int lhs = static_cast<int>(toLongLongNumeric(lhsValue));
                    int rhs = static_cast<int>(toLongLongNumeric(rhsValue));
                    result.data = lhs / rhs;
                }
                push(result);
                break;
            }
            case OpCodes::MOD: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                Value result;
                if (rank >= 3) {
                    long long lhs = toLongLongNumeric(lhsValue);
                    long long rhs = toLongLongNumeric(rhsValue);
                    result.data = lhs % rhs;
                } else {
                    int lhs = static_cast<int>(toLongLongNumeric(lhsValue));
                    int rhs = static_cast<int>(toLongLongNumeric(rhsValue));
                    result.data = lhs % rhs;
                }
                push(result);
                break;
            }
            case OpCodes::AND: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                Value result;
                if (rank >= 3) {
                    long long lhs = toLongLongNumeric(lhsValue);
                    long long rhs = toLongLongNumeric(rhsValue);
                    result.data = lhs & rhs;
                } else {
                    int lhs = static_cast<int>(toLongLongNumeric(lhsValue));
                    int rhs = static_cast<int>(toLongLongNumeric(rhsValue));
                    result.data = lhs & rhs;
                }
                push(result);
                break;
            }
            case OpCodes::OR: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                Value result;
                if (rank >= 3) {
                    long long lhs = toLongLongNumeric(lhsValue);
                    long long rhs = toLongLongNumeric(rhsValue);
                    result.data = lhs | rhs;
                } else {
                    int lhs = static_cast<int>(toLongLongNumeric(lhsValue));
                    int rhs = static_cast<int>(toLongLongNumeric(rhsValue));
                    result.data = lhs | rhs;
                }
                push(result);
                break;
            }
            case OpCodes::XOR: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                Value result;
                if (rank >= 3) {
                    long long lhs = toLongLongNumeric(lhsValue);
                    long long rhs = toLongLongNumeric(rhsValue);
                    result.data = lhs ^ rhs;
                } else {
                    int lhs = static_cast<int>(toLongLongNumeric(lhsValue));
                    int rhs = static_cast<int>(toLongLongNumeric(rhsValue));
                    result.data = lhs ^ rhs;
                }
                push(result);
                break;
            }
            case OpCodes::SHL: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                Value result;
                if (rank >= 3) {
                    long long lhs = toLongLongNumeric(lhsValue);
                    long long rhs = toLongLongNumeric(rhsValue);
                    result.data = lhs << rhs;
                } else {
                    int lhs = static_cast<int>(toLongLongNumeric(lhsValue));
                    int rhs = static_cast<int>(toLongLongNumeric(rhsValue));
                    result.data = lhs << rhs;
                }
                push(result);
                break;
            }
            case OpCodes::SHR: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                Value result;
                if (rank >= 3) {
                    long long lhs = toLongLongNumeric(lhsValue);
                    long long rhs = toLongLongNumeric(rhsValue);
                    result.data = lhs >> rhs;
                } else {
                    int lhs = static_cast<int>(toLongLongNumeric(lhsValue));
                    int rhs = static_cast<int>(toLongLongNumeric(rhsValue));
                    result.data = lhs >> rhs;
                }
                push(result);
                break;
            }
            case OpCodes::EQ: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                bool res = false;
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                if (rank > 0) {
                    res = toDoubleNumeric(lhsValue) == toDoubleNumeric(rhsValue);
                } else if (std::holds_alternative<bool>(lhsValue.data) && std::holds_alternative<bool>(rhsValue.data)) {
                    res = std::get<bool>(lhsValue.data) == std::get<bool>(rhsValue.data);
                }
                Value result;
                result.data = res;
                push(result);
                break;
            }
            case OpCodes::NE: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                bool res = false;
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                if (rank > 0) {
                    res = toDoubleNumeric(lhsValue) != toDoubleNumeric(rhsValue);
                } else if (std::holds_alternative<bool>(lhsValue.data) && std::holds_alternative<bool>(rhsValue.data)) {
                    res = std::get<bool>(lhsValue.data) != std::get<bool>(rhsValue.data);
                }
                Value result;
                result.data = res;
                push(result);
                break;
            }
            case OpCodes::LT: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                bool res = false;
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                if (rank > 0) {
                    res = toDoubleNumeric(lhsValue) < toDoubleNumeric(rhsValue);
                }
                Value result;
                result.data = res;
                push(result);
                break;
            }
            case OpCodes::LE: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                bool res = false;
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                if (rank > 0) {
                    res = toDoubleNumeric(lhsValue) <= toDoubleNumeric(rhsValue);
                }
                Value result;
                result.data = res;
                push(result);
                break;
            }
            case OpCodes::GT: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                bool res = false;
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                if (rank > 0) {
                    res = toDoubleNumeric(lhsValue) > toDoubleNumeric(rhsValue);
                }
                Value result;
                result.data = res;
                push(result);
                break;
            }
            case OpCodes::GE: {
                Value rhsValue = pop();
                Value lhsValue = pop();
                bool res = false;
                int rank = std::max(getNumericRank(lhsValue), getNumericRank(rhsValue));
                if (rank > 0) {
                    res = toDoubleNumeric(lhsValue) >= toDoubleNumeric(rhsValue);
                }
                Value result;
                result.data = res;
                push(result);
                break;
            }
            case OpCodes::NOT: {
                Value value = pop();
                bool cond = false;
                if (std::holds_alternative<int>(value.data)) {
                    cond = std::get<int>(value.data) != 0;
                } else if (std::holds_alternative<long long>(value.data)) {
                    cond = std::get<long long>(value.data) != 0;
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
                } else if (std::holds_alternative<long long>(value.data)) {
                    cond = std::get<long long>(value.data) != 0;
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

        builtins[3] = [](RVM& vm) {
            Value precisionValue = vm.pop();
            Value numberValue = vm.pop();

            int precision = 6;
            if (std::holds_alternative<int>(precisionValue.data)) {
                precision = std::get<int>(precisionValue.data);
            }

            double number = 0.0;
            if (std::holds_alternative<float>(numberValue.data)) {
                number = static_cast<double>(std::get<float>(numberValue.data));
            } else if (std::holds_alternative<double>(numberValue.data)) {
                number = std::get<double>(numberValue.data);
            } else if (std::holds_alternative<int>(numberValue.data)) {
                number = static_cast<double>(std::get<int>(numberValue.data));
            }

            std::ostringstream oss;
            oss.setf(std::ios::fmtflags(0), std::ios::floatfield);
            oss.setf(std::ios::fmtflags(0), std::ios::floatfield);
            oss.precision(precision);
            oss << number;

            Value v;
            v.data = oss.str();
            vm.push(v);
        };

        builtins[4] = [](RVM& vm) {
            Value precisionValue = vm.pop();
            Value numberValue = vm.pop();

            int precision = 6;
            if (std::holds_alternative<int>(precisionValue.data)) {
                precision = std::get<int>(precisionValue.data);
            }

            double number = 0.0;
            if (std::holds_alternative<double>(numberValue.data)) {
                number = std::get<double>(numberValue.data);
            } else if (std::holds_alternative<float>(numberValue.data)) {
                number = static_cast<double>(std::get<float>(numberValue.data));
            } else if (std::holds_alternative<int>(numberValue.data)) {
                number = static_cast<double>(std::get<int>(numberValue.data));
            }

            std::ostringstream oss;
            oss.setf(std::ios::fmtflags(0), std::ios::floatfield);
            oss.precision(precision);
            oss << number;

            Value v;
            v.data = oss.str();
            vm.push(v);
        };

        builtins[5] = [](RVM& vm) {
            auto value = vm.pop();
            long long i = toLongLongNumeric(value);
            Value v;
            v.data = std::to_string(i);
            vm.push(v);
        };

        builtins[6] = [](RVM& vm) {
            auto value = vm.pop();
            long long i = toLongLongNumeric(value);
            Value v;
            v.data = std::to_string(i);
            vm.push(v);
        };
    }
} // namespace Ryntra::VM
