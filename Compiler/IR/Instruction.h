#pragma once

#include "ImmediateValue.h"
#include "Value.h"
#include <memory>
#include <vector>

namespace Ryntra::IR {
    class Instruction : public Value {
    public:
        enum class Opcode {
            LoadConstant,
            Constant,
            Call,
            Return,
            Add,
            Sub,
            Mul,
            Div,
            Mod,
            BitNot,     // ~
            LogicalNot, // !
            BitAnd,     // &
            BitOr,  // |
            BitXor, // ^
            Shl,    // <<
            Shr,    // >>
            SExt,   // sign extend i32 → i64
            Trunc,  // truncate i64 → i32
            Eq,     // ==
            Ne,     // !=
            Lt,     // <
            Gt,     // >
            Le,     // <=
            Ge,     // >=
            Alloca, // allocate a local variable slot
            Load,   // load value from alloca slot
            Store,  // store value to alloca slot
            Br,     // unconditional branch to basic block
            CondBr, // conditional branch to basic block
            NewArray, // allocate array on heap
            ArrLoad,  // load element from array by index
            ArrStore  // store element to array by index
        };

        Instruction(Opcode opcode, std::shared_ptr<Type> type,
                    const std::vector<std::shared_ptr<Value>> &operands = {},
                    const std::string &name = "")
            : Value(type, name), opcode_(opcode), operands_(operands) {}

        Opcode getOpcode() const { return opcode_; }
        const std::vector<std::shared_ptr<Value>> &getOperands() const { return operands_; }

        // SSA instructions are local values — reference with %
        std::string getReferenceName() const override {
            return name_.empty() ? "" : "%" + name_;
        }
        bool isLocal() const override { return true; }

        std::string toString() const override {
            std::string result;

            // ret never produces a value; call only produces one when non-void
            bool hasResult = !name_.empty() && opcode_ != Opcode::Return && !(opcode_ == Opcode::Call && type_->isVoid());

            if (hasResult) {
                result = "%" + name_ + " = ";
            }

            switch (opcode_) {
            case Opcode::LoadConstant:
                result += "loadc ";
                for (const auto &op : operands_)
                    result += op->getReferenceName();
                break;

            case Opcode::Constant:
                result += "constant ";
                for (const auto &op : operands_)
                    result += op->getReferenceName();
                break;

            case Opcode::Call: {
                result += "call ";
                // operands[0] is the callee (Function), rest are args
                result += operands_[0]->getReferenceName() + "(";
                for (size_t i = 1; i < operands_.size(); ++i) {
                    if (i > 1)
                        result += ", ";
                    result += operands_[i]->getReferenceName();
                }
                result += ")";
                break;
            }

            case Opcode::Return:
                result += "ret ";
                if (!operands_.empty())
                    result += operands_[0]->getReferenceName();
                else
                    result += "void";
                break;

            case Opcode::Add:
            case Opcode::Sub:
            case Opcode::Mul:
            case Opcode::Div:
            case Opcode::Mod:
            case Opcode::BitAnd:
            case Opcode::BitOr:
            case Opcode::BitXor:
            case Opcode::Shl:
            case Opcode::Shr: {
                switch (opcode_) {
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
                case Opcode::Mod:
                    result += "mod ";
                    break;
                case Opcode::BitAnd:
                    result += "bitand ";
                    break;
                case Opcode::BitOr:
                    result += "bitor ";
                    break;
                case Opcode::BitXor:
                    result += "bitxor ";
                    break;
                case Opcode::Shl:
                    result += "shl ";
                    break;
                case Opcode::Shr:
                    result += "shr ";
                    break;
                default:
                    break;
                }
                for (size_t i = 0; i < operands_.size(); ++i) {
                    if (i > 0)
                        result += ", ";
                    result += operands_[i]->getReferenceName();
                }
                break;
            }

            case Opcode::BitNot: {
                result += "bitnot ";
                if (!operands_.empty())
                    result += operands_[0]->getReferenceName();
                break;
            }

            case Opcode::LogicalNot: {
                result += "logicalnot ";
                if (!operands_.empty())
                    result += operands_[0]->getReferenceName();
                break;
            }

            case Opcode::Eq:
            case Opcode::Ne:
            case Opcode::Lt:
            case Opcode::Gt:
            case Opcode::Le:
            case Opcode::Ge: {
                switch (opcode_) {
                case Opcode::Eq: result += "eq "; break;
                case Opcode::Ne: result += "ne "; break;
                case Opcode::Lt: result += "lt "; break;
                case Opcode::Gt: result += "gt "; break;
                case Opcode::Le: result += "le "; break;
                case Opcode::Ge: result += "ge "; break;
                default: break;
                }
                for (size_t i = 0; i < operands_.size(); ++i) {
                    if (i > 0) result += ", ";
                    result += operands_[i]->getReferenceName();
                }
                break;
            }

            case Opcode::SExt: {
                result += "sext ";
                if (!operands_.empty())
                    result += operands_[0]->getReferenceName();
                break;
            }

            case Opcode::Trunc: {
                result += "trunc ";
                if (!operands_.empty())
                    result += operands_[0]->getReferenceName();
                break;
            }

            case Opcode::Alloca: {
                result += "alloca ";
                if (!operands_.empty())
                    result += operands_[0]->getReferenceName();
                break;
            }

            case Opcode::Load: {
                result += "load ";
                if (operands_.size() >= 1)
                    result += operands_[0]->getReferenceName();
                break;
            }

            case Opcode::Store: {
                result += "store ";
                if (operands_.size() >= 1)
                    result += operands_[0]->getReferenceName();
                if (operands_.size() >= 2)
                    result += ", " + operands_[1]->getReferenceName();
                break;
            }

            case Opcode::Br: {
                result += "br label ";
                if (!operands_.empty()) {
                    if (auto *imm = dynamic_cast<ImmediateValue *>(operands_[0].get()))
                        result += imm->getLiteralValue();
                }
                break;
            }

            case Opcode::CondBr: {
                result += "condbr ";
                if (!operands_.empty()) {
                    result += operands_[0]->getType()->toString() + " ";
                    result += operands_[0]->getReferenceName();
                }
                if (operands_.size() >= 2) {
                    result += ", label ";
                    if (auto *imm = dynamic_cast<ImmediateValue *>(operands_[1].get()))
                        result += imm->getLiteralValue();
                }
                if (operands_.size() >= 3) {
                    result += ", label ";
                    if (auto *imm = dynamic_cast<ImmediateValue *>(operands_[2].get()))
                        result += imm->getLiteralValue();
                }
                break;
            }

            case Opcode::NewArray: {
                result += "newarray ";
                if (!operands_.empty())
                    result += operands_[0]->getReferenceName();
                break;
            }

            case Opcode::ArrLoad: {
                result += "arrload ";
                for (size_t i = 0; i < operands_.size(); ++i) {
                    if (i > 0) result += ", ";
                    result += operands_[i]->getReferenceName();
                }
                break;
            }

            case Opcode::ArrStore: {
                result += "arrstore ";
                for (size_t i = 0; i < operands_.size(); ++i) {
                    if (i > 0) result += ", ";
                    result += operands_[i]->getReferenceName();
                }
                break;
            }

            default:
                break;
            }

            return result;
        }

    private:
        Opcode opcode_;
        std::vector<std::shared_ptr<Value>> operands_;
    };
} // namespace Ryntra::IR
