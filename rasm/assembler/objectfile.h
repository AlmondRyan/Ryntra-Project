#pragma once
#include <string>
#include <vector>
#include "instruction.h"

namespace Ryntra::rasm {
    class ObjectFileWriter {
    public:
        static bool writeToFile(const std::string& filename, 
                              const std::vector<Instruction>& instructions);
    };
} 