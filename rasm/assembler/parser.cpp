#include "parser.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <regex>

namespace Ryntra::rasm {
    // 静态成员初始化
    SectionType Parser::currentSection = SectionType::Unknown;
    std::unordered_map<std::string, Symbol> Parser::symbols;
    std::vector<Section> Parser::sections;

    std::string trim(const std::string &str) {
        size_t first = str.find_first_not_of(" \t");
        if (first == std::string::npos)
            return "";
        size_t last = str.find_last_not_of(" \t");
        return str.substr(first, last - first + 1);
    }

    std::vector<std::string> split(const std::string &str, char delim) {
        std::vector<std::string> tokens;
        std::string              token;
        std::istringstream       tokenStream(str);
        while (std::getline(tokenStream, token, delim)) {
            token = trim(token);
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }
        return tokens;
    }

    std::string toLower(const std::string &str) {
        std::string lower = str;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }

    bool Parser::isSection(const std::string &line) {
        return line.find("section") == 0;
    }

    bool Parser::isLabel(const std::string &line) {
        return line.find(':') != std::string::npos;
    }

    bool Parser::isDirective(const std::string &line) {
        return line[0] == '.';
    }

    Operand Parser::parseOperand(const std::string &op) {
        Operand operand;
        std::string value = trim(op);

        // 检查是否是内存引用
        bool isMemoryRef = false;
        if (value.front() == '[' && value.back() == ']') {
            isMemoryRef = true;
            value = value.substr(1, value.length() - 2);
        }

        // 检查是否是寄存器
        std::string lowerValue = toLower(value);
        auto regIt = REGISTER_MAP.find(lowerValue);
        if (regIt != REGISTER_MAP.end()) {
            if (isMemoryRef) {
                operand.type = OperandType::Memory;
                operand.value = value;
                operand.reg = regIt->second;
                operand.isIndirect = true;
            } else {
                operand.type = OperandType::Register;
                operand.reg = regIt->second;
                operand.value = value;
            }
            return operand;
        }

        // 检查是否是立即数
        if (std::isdigit(value[0]) || value[0] == '-' || value[0] == '+') {
            operand.type = OperandType::Immediate;
            operand.immediate = std::stoll(value);
            operand.value = value;
            return operand;
        }

        // 检查是否是标签或变量
        if (symbols.find(value) != symbols.end()) {
            operand.type = OperandType::Label;
            operand.value = value;
            return operand;
        }

        // 其他情况当作内存引用或标签处理
        operand.type = isMemoryRef ? OperandType::Memory : OperandType::Label;
        operand.value = value;
        return operand;
    }

    Instruction Parser::parseLine(const std::string &line) {
        Instruction inst;
        std::string trimmedLine = trim(line);

        // 忽略空行和注释
        if (trimmedLine.empty() || trimmedLine[0] == ';') {
            inst.type = InstructionType::Unknown;
            return inst;
        }

        // 移除行尾注释
        size_t commentPos = trimmedLine.find(';');
        if (commentPos != std::string::npos) {
            trimmedLine = trim(trimmedLine.substr(0, commentPos));
        }

        // 处理段定义
        if (isSection(trimmedLine)) {
            inst.type = InstructionType::Unknown;
            std::string sectionName = trimmedLine.substr(8); // 跳过"section "
            sectionName = trim(sectionName);
            
            Section newSection;
            newSection.name = sectionName;
            if (sectionName == ".text") {
                currentSection = SectionType::Text;
                newSection.type = SectionType::Text;
            } else if (sectionName == ".data") {
                currentSection = SectionType::Data;
                newSection.type = SectionType::Data;
            }
            sections.push_back(newSection);
            return inst;
        }

        // 处理标签
        if (isLabel(trimmedLine)) {
            inst.type = InstructionType::Unknown;
            std::string labelName = trimmedLine.substr(0, trimmedLine.find(':'));
            Symbol symbol;
            symbol.name = labelName;
            symbol.section = currentSection;
            symbol.isGlobal = (labelName == "_start"); // 特殊处理_start标签
            symbols[labelName] = symbol;
            return inst;
        }

        // 处理指令
        size_t spacePos = trimmedLine.find(' ');
        if (spacePos == std::string::npos) {
            inst.mnemonic = trimmedLine;
        } else {
            inst.mnemonic = trim(trimmedLine.substr(0, spacePos));
            std::string operandsStr = trimmedLine.substr(spacePos + 1);

            auto operands = split(operandsStr, ',');
            for (const auto &op : operands) {
                inst.operands.push_back(parseOperand(trim(op)));
            }
        }

        // 查找指令类型
        std::string lowerMnemonic = toLower(inst.mnemonic);
        auto it = INSTRUCTION_MAP.find(lowerMnemonic);
        if (it != INSTRUCTION_MAP.end()) {
            inst.type = it->second.type;
        } else {
            inst.type = InstructionType::Unknown;
        }

        return inst;
    }

    std::vector<Instruction> Parser::parse(const std::string &sourceCode) {
        std::vector<Instruction> instructions;
        std::istringstream stream(sourceCode);
        std::string line;

        // 清除之前的状态
        currentSection = SectionType::Unknown;
        symbols.clear();
        sections.clear();

        while (std::getline(stream, line)) {
            auto inst = parseLine(line);
            if (inst.type != InstructionType::Unknown) {
                instructions.push_back(inst);
            }
        }

        return instructions;
    }
} // namespace Ryntra::rasm