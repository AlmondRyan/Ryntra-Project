#include "Instruction.h"
#include "Type.h"
#include "Function.h"
#include "BasicBlock.h"
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
        default: ss << "unknown_op"; break;
    }

    if (opcode == OpCode::Call) {
        // call @func(arg1, arg2)
        // Operand 0 is function
        if (operands.size() > 0) {
            ss << " " << operands[0]->toString() << "(";
            for (size_t i = 1; i < operands.size(); ++i) {
                if (i > 1) ss << ", ";
                ss << (operands[i] ? operands[i]->toString() : "null");
            }
            ss << ")";
        }
    } else if (opcode == OpCode::Ret) {
        // ret type val
        if (!operands.empty() && operands[0]) {
            ss << " " << operands[0]->getType()->toString() << " " << operands[0]->toString();
        } else {
             // If operands empty, assume ret void.
             // But if function returns void, user might call CreateRet(nullptr) or similar.
             // For safety:
             ss << " void";
        }
    } else {
        // Standard space separated operands
        for (auto* op : operands) {
            if (!op) {
                ss << " null";
                continue;
            }
            ss << " " << op->toString();
        }
    }

    return ss.str();
}

LoadInst::LoadInst(Value* ptr, const std::string& name, BasicBlock* parent)
    : Instruction(ptr->getType(), OpCode::Load, name, parent) { // Type should be element type? 
    // In IRReference, load %obj -> value. 
    // Usually load takes a pointer and returns a value.
    // Assuming ptr type has element type info, but here Type is simple.
    // For now, assume Load returns the type of the value pointed to.
    // But our Type system is simple.
    // Let's assume Load returns the type of the operand if it's a reference, or we need more type info.
    // For HelloWorld, "load @str_hello" (string constant) -> string value?
    // In LLVM load i8* -> i8.
    // Here @str_hello is constant string. load @str_hello -> string.
    addOperand(ptr);
}

CallInst::CallInst(Function* func, const std::vector<Value*>& args, const std::string& name, BasicBlock* parent)
    : Instruction(func ? func->getReturnType() : Type::getVoidTy(), OpCode::Call, name, parent) {
    addOperand(func);
    for (auto* arg : args) {
        addOperand(arg);
    }
}

RetInst::RetInst(Value* val, BasicBlock* parent)
    : Instruction(Type::getVoidTy(), OpCode::Ret, "", parent) {
    if (val) addOperand(val);
}

}
