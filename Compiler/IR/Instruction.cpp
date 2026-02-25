#include "Instruction.h"
#include "BasicBlock.h"
#include "Function.h"
#include "Type.h"
#include <sstream>

namespace Ryntra::Compiler {
    std::string Instruction::print() const {
        std::stringstream ss;
        if (!name.empty()) {
            ss << "%" << name << " = ";
        }

        switch (opcode) {
        case OpCode::Load: ss << "load"; break;
        case OpCode::Call: ss << "call"; break;
        case OpCode::Ret: ss << "ret"; break;
        case OpCode::Module: ss << "module"; break;
        case OpCode::External: ss << "external"; break;
        case OpCode::Constant: ss << "constant"; break;
        case OpCode::Entry: ss << "entry"; break;
        case OpCode::Add: ss << "add"; break;
        case OpCode::Sub: ss << "sub"; break;
        case OpCode::Mul: ss << "mul"; break;
        case OpCode::Div: ss << "div"; break;
        case OpCode::CmpEQ: ss << "cmpeq"; break;
        case OpCode::CmpNE: ss << "cmpne"; break;
        case OpCode::CmpLT: ss << "cmplt"; break;
        case OpCode::CmpGT: ss << "cmpgt"; break;
        default: ss << "unknown_op"; break;
        }

        if (opcode == OpCode::Call) {
            // call @func(arg1, arg2)
            // Operand 0 is function
            if (operands.size() > 0) {
                ss << " " << operands[0]->toString() << "(";
                for (size_t i = 1; i < operands.size(); ++i) {
                    if (i > 1)
                        ss << ", ";
                    ss << (operands[i] ? operands[i]->toString() : "null");
                }
                ss << ")";
            }
        } else if (opcode == OpCode::Ret) {
            if (!operands.empty() && operands[0]) {
                ss << " " << operands[0]->getType()->toString() << " " << operands[0]->toString();
            } else {
                ss << " void";
            }
        } else {
            // Standard space separated operands
            for (auto *op : operands) {
                if (!op) {
                    ss << " null";
                    continue;
                }
                ss << " " << op->toString();
            }
        }

        return ss.str();
    }

    LoadInst::LoadInst(Value *ptr, const std::string &name, BasicBlock *parent)
        : Instruction(ptr->getType(), OpCode::Load, name, parent) { // Type should be element type?
        addOperand(ptr);
    }

    CallInst::CallInst(Function *func, const std::vector<Value *> &args, const std::string &name, BasicBlock *parent)
        : Instruction(func ? func->getReturnType() : Type::getVoidTy(), OpCode::Call, name, parent) {
        addOperand(func);
        for (auto *arg : args) {
            addOperand(arg);
        }
    }

    RetInst::RetInst(Value *val, BasicBlock *parent)
        : Instruction(Type::getVoidTy(), OpCode::Ret, "", parent) {
        if (val)
            addOperand(val);
    }
} // namespace Ryntra::Compiler
