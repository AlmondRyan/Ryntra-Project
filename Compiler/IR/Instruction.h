#pragma once

#include "Value.h"
#include <memory>
#include <vector>

namespace Ryntra::IR {
    class Instruction : public Value {
    public:
        enum class Opcode {
            LoadConstant,
            Call,
            Return,
            Add,
            Sub,
            Mul,
            Div
        };

        Instruction(Opcode opcode, std::shared_ptr<Type> type,
                    const std::vector<std::shared_ptr<Value>> &operands = {},
                    const std::string &name = "")
            : Value(type, name), opcode_(opcode), operands_(operands) {}

        Opcode getOpcode() const { return opcode_; }
        const std::vector<std::shared_ptr<Value>> &getOperands() const { return operands_; }

        std::string toString() const override {
            std::string result;

            if (!name_.empty()) {
                result = "%" + name_ + " = ";
            }

            switch (opcode_) {
            case Opcode::LoadConstant:
                result += "loadc ";
                break;
            case Opcode::Call:
                result += "call ";
                break;
            case Opcode::Return:
                result += "ret ";
                break;
            case Opcode::Add:
                result += "add ";
                break;
            case Opcode::Sub:
                result += "sub ";
                break;
            case Opcode::Mul:
                result += "mul ";
                break;
            case Opcode::Div:
                result += "div ";
                break;
            }

            for (size_t i = 0; i < operands_.size(); ++i) {
                if (i > 0)
                    result += ", ";
                result += operands_[i]->getReferenceName();
            }

            return result;
        }

    private:
        Opcode opcode_;
        std::vector<std::shared_ptr<Value>> operands_;
    };
} // namespace Ryntra::IR
