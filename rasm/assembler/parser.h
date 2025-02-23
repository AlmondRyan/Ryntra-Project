#pragma once
#include <string>
#include <vector>
#include "instruction.h"

namespace Ryntra::rasm {
    class Parser {
    public:
        static std::vector<Instruction> parse(const std::string& sourceCode);
        static Operand parseOperand(const std::string &op);
    private:
        static Instruction parseLine(const std::string& line);

    };
} 