#ifndef ASM_H
#define ASM_H

#include <fstream>
#include <sstream>
#include <iostream>

#include "assembler/utils/targetPlat.h"
#include "assembler/parser.h"
#include "assembler/objectfile.h"
#include "assembler/Error/errorhandling.h"
#include "assembler/utils/path_utils.h"

namespace Ryntra::rasm {
    /**
     * @brief A x86 and x86_64 (AMD64) Assembler.
     */
    class RAssembler {
    public:
        RAssembler() {
            ErrorHandler::getInstance().clear();
        }

        // 从文件汇编
        /**
         * @brief Assemble from a source file.
         *
         * @param inputFile - The file you want to assemble.
         * @param targetPlatform - Which platform? x86 or x64?
         * @return The Status of Assembling.
         */
        bool assemble(const std::string &inputFile, TargetPlatform targetPlatform) {
            std::ifstream file(inputFile);
            if (!file.is_open()) {
                ErrorHandler::getInstance().addError("Cannot open input file: " + inputFile);
                return false;
            }

            std::stringstream buffer;
            buffer << file.rdbuf();
            
            // 获取输出文件名（将.asm替换为.obj）
            std::string outputFile = inputFile;
            size_t extPos = outputFile.rfind('.');
            if (extPos != std::string::npos) {
                outputFile = outputFile.substr(0, extPos);
            }
            outputFile += ".obj";

            bool success = assembleFromString(buffer.str(), targetPlatform);
            if (success) {
                // 生成目标文件
                success = ObjectFileWriter::writeToFile(outputFile, 
                                                      Parser::getSections(),
                                                      Parser::getDataDefinitions(),
                                                      Parser::getSymbols());
            }

            return success;
        }

        /**
         * @brief Assemble from a source code string.
         *
         * @param sourceCode - The Source Code String
         * @param targetPlatform - Which platform? x86 or x64?
         * @return The Status of Assembling.
         */
        bool assembleFromString(const std::string &sourceCode, TargetPlatform targetPlatform) {
            auto& errorHandler = ErrorHandler::getInstance();
            auto instructions = Parser::parse(sourceCode);
            
            errorHandler.addInfo("Parse " + std::to_string(instructions.size()) + " Instruction(s)");
            
            for (const auto& inst : instructions) {
                std::cout << "\nInstruction: " << inst.mnemonic << std::endl;
                printInstructionType(inst.type);
                
                if (inst.type == InstructionType::MUL || inst.type == InstructionType::DIV) {
                    std::cout << "Operand: " << (inst.operands.size() + 1) << " (s)" << std::endl;
                    Operand implicitOp;
                    implicitOp.type = OperandType::Register;
                    implicitOp.reg = (targetPlatform == TargetPlatform::x64) ? RegisterType::RAX : RegisterType::EAX;
                    implicitOp.value = (targetPlatform == TargetPlatform::x64) ? "rax" : "eax";
                    printOperand(implicitOp, true);
                } else {
                    std::cout << "Operand: " << inst.operands.size() << " (s)" << std::endl;
                }

                for (const auto& op : inst.operands) {
                    if (targetPlatform == TargetPlatform::x64 &&
                        op.type == OperandType::Immediate && 
                        op.value[0] == '#') {
                        errorHandler.addWarning("'#' prefix is not needed in x64 mode for immediate value");
                    }
                    printOperand(op, false);
                }
            }
            
            // 生成目标文件
            std::string outputPath = PathUtils::generateOutputFilename("output");
            bool success = ObjectFileWriter::writeToFile(outputPath,
                                                       Parser::getSections(),
                                                       Parser::getDataDefinitions(),
                                                       Parser::getSymbols());

            if (success) {
                errorHandler.addInfo("Generated object file: " + outputPath);
            }
            
            errorHandler.printAll();
            return !errorHandler.hasErrorMessages();
        }

    private:
        /**
         * @brief Helper method, print all the operands of the instruction in Assembly File.
         *
         * @param op - The operand.
         * @param isImplicit - Is this operand implicit? Just like `mul` or `div`.
         */
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

        /**
         * @brief Helper method, print the instruction type.
         *
         * @param type - The Instruction Type you want to print to the console.
         */
        void printInstructionType(InstructionType type) const {
            std::cout << "Instruction Type: ";
            switch (type) {
                // Number Operation
                case InstructionType::ADD: std::cout << "ADD"; break;
                case InstructionType::SUB: std::cout << "SUB"; break;
                case InstructionType::MUL: std::cout << "MUL"; break;
                case InstructionType::DIV: std::cout << "DIV"; break;
                case InstructionType::INC: std::cout << "INC"; break;
                case InstructionType::DEC: std::cout << "DEC"; break;
                case InstructionType::NEG: std::cout << "NEG"; break;
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
                default: std::cout << "Unknown"; break;
            }
            std::cout << std::endl;
        }
    };
}

#endif // ASM_H