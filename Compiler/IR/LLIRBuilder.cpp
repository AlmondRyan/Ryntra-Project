#include "LLIRBuilder.h"
#include <iostream>

namespace Ryntra::Compiler::IR {
    std::string LLIRBuilder::emit(Module *module) {
        std::stringstream ss;

        // Section .cdata
        ss << "section .cdata\n";
        emitGlobals(module, ss);
        ss << "\n";

        // Section .code
        ss << "section .code\n";
        emitFunctions(module, ss);

        return ss.str();
    }

    void LLIRBuilder::emitGlobals(Module *module, std::stringstream &ss) {
        for (const auto &global : module->getConstantObjects()) {
            ss << "    " << global->getType()->toString() << " " << global->getName() << " = " << global->getInitValue() << "\n";
        }
    }

    void LLIRBuilder::emitFunctions(Module *module, std::stringstream &ss) {
        for (const auto &func : module->getFunctions()) {
            emitFunction(func.get(), ss);
        }
    }

    void LLIRBuilder::emitFunction(Function *func, std::stringstream &ss) {
        if (func->isDeclaration())
            return;

        ss << "    func " << func->getName() << "() -> " << "i32" << " {\n"; // TODO: Fix return type string

        for (const auto &bb : func->getBasicBlocks()) {
            emitBasicBlock(bb.get(), ss);
        }

        ss << "    }\n";
    }

    void LLIRBuilder::emitBasicBlock(BasicBlock *bb, std::stringstream &ss) {
        for (const auto &inst : bb->getInstructions()) {
            emitInstruction(inst.get(), ss);
        }
    }

    void LLIRBuilder::emitInstruction(Instruction *inst, std::stringstream &ss) {
        ss << "        ";
        switch (inst->getOpCode()) {
        case OpCode::Call: {
            auto operands = inst->getOperands();
            for (auto *op : operands) {
                if (auto *constObj = dynamic_cast<ConstantObject *>(op)) {
                    if (constObj->getType()->getID() == TypeID::String) {
                        ss << "load_const.string " << constObj->getName() << "\n        ";
                    }
                }
            }

            if (!operands.empty()) {
                if (auto *func = dynamic_cast<Function *>(operands[0])) {
                    std::string funcName = func->getName();
                    if (funcName.find("__builtin") == 0) {
                        ss << "call.native " << funcName;
                    } else {
                        ss << "call " << funcName;
                    }
                }
            }
            break;
        }
        case OpCode::Ret: {
            // ret.i32 0
            auto operands = inst->getOperands();
            if (operands.empty()) {
                ss << "ret void";
            } else {
                auto *val = operands[0];
                std::string typeStr = "void";
                if (val->getType()->getID() == TypeID::Integer32)
                    typeStr = "i32";
                if (val->getType()->getID() == TypeID::String)
                    typeStr = "string";

                ss << "ret." << typeStr << " " << val->toString();
            }
            break;
        }
        default:
            ss << "; Unknown instruction";
            break;
        }
        ss << "\n";
    }

} // namespace Ryntra::Compiler::IR
