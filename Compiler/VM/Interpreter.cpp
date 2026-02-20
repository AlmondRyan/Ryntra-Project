#include "Interpreter.h"
#include <iostream>

namespace Ryntra::Compiler::VM {

    void Interpreter::execute(const std::vector<Instruction> &program) {
        size_t ip = 0; // Instruction Pointer

        while (ip < program.size()) {
            const auto &inst = program[ip];

            switch (inst.op) {
            case OpCode::LoadConst:
                push(inst.operand);
                break;

            case OpCode::Syscall: {
                // Assuming operand is the syscall code or we pop it?
                // The IR usually has syscall code as operand.
                // Let's assume operand has the syscall ID if it's an int.
                // Or if operand is void, maybe we pop the ID?
                // In IRBuilder::CreateSyscall, it adds an operand.
                // Let's assume the operand carries the syscall ID.

                // For this specific task, let's implement a simple print syscall
                // if syscall ID is 1 (for example) or just inspect the operand.

                // If the user meant "Syscall" as in "Call Native",
                // in LLIR: call.native __builtin_print
                // This might be mapped to a Syscall in VM.

                // For "HelloWorld.rsir": call __builtin_print
                // This likely maps to a specific syscall or native call.
                // Let's implement a simple print for testing.

                int syscallId = inst.operand.intVal;
                if (syscallId == 0) { // Print
                    Value val = pop();
                    std::cout << val.toString() << std::endl;
                }
                break;
            }

            case OpCode::Halt:
                return;

            case OpCode::Call:
                // TODO: Implement function calls
                break;

            case OpCode::Ret:
                // TODO: Implement return
                break;

            case OpCode::Print: // Helper if we mapped __builtin_print to this
            {
                Value val = pop();
                std::cout << val.toString() << std::endl;
            } break;

            default:
                std::cerr << "Unknown OpCode" << std::endl;
                break;
            }

            ip++;
        }
    }

    void Interpreter::push(Value v) {
        stack.push_back(v);
    }

    Value Interpreter::pop() {
        if (stack.empty()) {
            std::cerr << "Stack underflow" << std::endl;
            return Value();
        }
        Value v = stack.back();
        stack.pop_back();
        return v;
    }

} // namespace Ryntra::Compiler::VM
