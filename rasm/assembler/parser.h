#pragma once
#include "instruction.h"
#include <string>
#include <vector>

namespace Ryntra::rasm {
    class Parser {
    public:
        static std::vector<Instruction> parse(const std::string &sourceCode);
        static Operand                  parseOperand(const std::string &op);

    private:
        static Instruction parseLine(const std::string &line);
    };
} // namespace Ryntra::rasm