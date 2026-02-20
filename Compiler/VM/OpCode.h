#pragma once

namespace Ryntra::Compiler::VM {

enum class OpCode {
    LoadConst,
    Syscall,
    Halt,
    // Additional opcodes for completeness based on LLIR
    Call,
    Ret,
    Print // If we want a dedicated print opcode, or use Syscall
};

}
