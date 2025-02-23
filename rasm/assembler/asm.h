#ifndef ASM_H
#define ASM_H

#include <fstream>
#include <sstream>
#include <iostream>
#include "assembler/utils/targetPlat.h"
#include "assembler/parser.h"
#include "assembler/objectfile.h"
#include "assembler/Error/errorhandling.h"

namespace Ryntra::rasm {
    /**
     * @brief A x86 and x86_64 (AMD64) Assembler.
     */
    class RAssembler {
    public:
        RAssembler() {
            ErrorHandler::getInstance().clear(); // 清除之前的错误信息
        }

        // 从文件汇编
        bool assemble(const std::string &inputFile, TargetPlatform targetPlatform) {
            std::ifstream file(inputFile);
            if (!file.is_open()) {
                ErrorHandler::getInstance().addError("Cannot open input file: " + inputFile);
                return false;
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            return assembleFromString(buffer.str(), targetPlatform);
        }

        // 从字符串汇编
        bool assembleFromString(const std::string &sourceCode, TargetPlatform targetPlatform) {
            auto& errorHandler = ErrorHandler::getInstance();
            auto instructions = Parser::parse(sourceCode);
            
            // 打印解析结果
            errorHandler.addInfo("Parse " + std::to_string(instructions.size()) + " Instruction(s)");
            
            for (const auto& inst : instructions) {
                std::cout << "\nInstruction: " << inst.mnemonic << std::endl;
                printInstructionType(inst.type);
                
                // 检查是否是 mul/div 指令，添加隐式操作数
                if (inst.type == InstructionType::MUL || inst.type == InstructionType::DIV) {
                    std::cout << "Operand: " << (inst.operands.size() + 1) << " (s)" << std::endl;
                    // 打印隐式操作数 RAX/EAX
                    Operand implicitOp;
                    implicitOp.type = OperandType::Register;
                    implicitOp.reg = (targetPlatform == TargetPlatform::x64) ? RegisterType::RAX : RegisterType::EAX;
                    implicitOp.value = (targetPlatform == TargetPlatform::x64) ? "rax" : "eax";
                    printOperand(implicitOp, true);
                } else {
                    std::cout << "Operand: " << inst.operands.size() << " (s)" << std::endl;
                }

                // 打印常规操作数
                for (const auto& op : inst.operands) {
                    // 检查 x64 模式下的 # 前缀
                    if (targetPlatform == TargetPlatform::x64 && 
                        op.type == OperandType::Immediate && 
                        op.value[0] == '#') {
                        errorHandler.addWarning("'#' prefix is not needed in x64 mode for immediate value");
                    }
                    printOperand(op, false);
                }
            }
            
            // 打印所有错误和警告
            errorHandler.printAll();
            
            // 如果有错误，返回false
            return !errorHandler.hasErrorMessages();
        }

    private:
        // 辅助函数：打印操作数信息
        void printOperand(const Operand& op, bool isImplicit) const {
            std::cout << "    Type: ";
            switch (op.type) {
                case OperandType::Register:
                    std::cout << "Register (" << op.value << ")" 
                             << (isImplicit ? " [Implicit]" : "");
                    break;
                case OperandType::Immediate:
                    std::cout << "Immediate (" << op.immediate << ")";
                    break;
                case OperandType::Memory:
                    std::cout << "Memory (" << op.value << ")";
                    break;
                case OperandType::Label:
                    std::cout << "Label (" << op.value << ")";
                    break;
            }
            std::cout << std::endl;
        }

        // 辅助函数：打印指令类型
        void printInstructionType(InstructionType type) const {
            std::cout << "Instruction Type: ";
            switch (type) {
                // Number Operation
                case InstructionType::ADD: std::cout << "ADD"; break;
                case InstructionType::SUB: std::cout << "SUB"; break;
                case InstructionType::MUL: std::cout << "MUL"; break;
                case InstructionType::DIV: std::cout << "DIV"; break;
                // Logical Operation
                case InstructionType::AND: std::cout << "AND"; break;
                case InstructionType::OR:  std::cout << "OR";  break;
                case InstructionType::XOR: std::cout << "XOR"; break;
                // Data Transfer Operation
                case InstructionType::LEA: std::cout << "LEA"; break;
                case InstructionType::MOV: std::cout << "MOV"; break;
                case InstructionType::XCHG: std::cout << "XCHG"; break;
                // Control Stream Operation
                case InstructionType::JMP: std::cout << "JMP"; break;
                case InstructionType::JE:  std::cout << "JE"; break;
                case InstructionType::JZ:  std::cout << "JZ"; break;
                case InstructionType::JNE: std::cout << "JNE"; break;
                case InstructionType::JNZ: std::cout << "JNZ"; break;
                case InstructionType::JG:  std::cout << "JG"; break;
                case InstructionType::JGLE: std::cout << "JGE"; break;
                case InstructionType::JL:   std::cout << "JL"; break;
                case InstructionType::JNGE: std::cout << "JLE"; break;
                case InstructionType::CALL: std::cout << "CALL"; break;
                case InstructionType::RET:  std::cout << "RET"; break;
                case InstructionType::NOP:  std::cout << "NOP"; break;
                // Comparison Operation
                case InstructionType::CMP:  std::cout << "CMP"; break;
                case InstructionType::TEST: std::cout << "TEST"; break;
                // Bit Manipulation Operation
                case InstructionType::SHL: std::cout << "SHL"; break;
                case InstructionType::SHR: std::cout << "SHR"; break;
                case InstructionType::SAR: std::cout << "SAR"; break;
                case InstructionType::ROL: std::cout << "ROL"; break;
                case InstructionType::ROR: std::cout << "ROR"; break;
                // Stack Operation
                case InstructionType::PUSH:  std::cout << "PUSH"; break;
                case InstructionType::POP:   std::cout << "POP"; break;
                case InstructionType::ENTER: std::cout << "ENTER"; break;
                case InstructionType::LEAVE: std::cout << "LEAVE"; break;
                // Float Operation
                case InstructionType::FLD:  std::cout << "FLD"; break;
                case InstructionType::FST:  std::cout << "FST"; break;
                case InstructionType::FADD: std::cout << "FADD"; break;
                case InstructionType::FSUB: std::cout << "FSUB"; break;
                case InstructionType::FMUL: std::cout << "FMUL"; break;
                case InstructionType::FDIV: std::cout << "FDIV"; break;
                // Misc Operation
                case InstructionType::SYSCALL: std::cout << "SYSCALL"; break;
                case InstructionType::SYSRET:  std::cout << "SYSRET"; break;
                case InstructionType::INT:     std::cout << "INT"; break;
                case InstructionType::IRET:    std::cout << "IRET"; break;
                case InstructionType::HLT:     std::cout << "HLT"; break;
                // Unknown
                case InstructionType::Unknown: std::cout << "Unknown"; break;
            }
            std::cout << std::endl;
        }
    };
}

#endif // ASM_H