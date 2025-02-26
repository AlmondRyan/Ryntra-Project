#pragma once
#include "instruction.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace Ryntra::rasm {
    enum class SectionType {
        Unknown,
        Text,       // 代码段
        Data,       // 数据段
        Bss,        // 未初始化数据段
        Rodata      // 只读数据段
    };

    struct Section {
        SectionType type;
        std::string name;
        uint64_t address;
        std::vector<uint8_t> data;
    };

    struct Symbol {
        std::string name;
        uint64_t address;
        bool isGlobal;
        SectionType section;
    };

    class Parser {
    public:
        static std::vector<Instruction> parse(const std::string &sourceCode);
        static Operand parseOperand(const std::string &op);

    private:
        static Instruction parseLine(const std::string &line);
        static bool isSection(const std::string &line);
        static bool isLabel(const std::string &line);
        static bool isDirective(const std::string &line);
        static SectionType currentSection;
        static std::unordered_map<std::string, Symbol> symbols;
        static std::vector<Section> sections;
    };
} // namespace Ryntra::rasm