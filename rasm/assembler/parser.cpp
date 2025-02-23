#include "parser.h"
#include <sstream>
#include <algorithm>
#include <cctype>

namespace Ryntra::rasm {
    std::string trim(const std::string &str) {
        size_t first = str.find_first_not_of(" \t");
        if (first == std::string::npos) return "";
        size_t last = str.find_last_not_of(" \t");
        return str.substr(first, last - first + 1);
    }

    std::vector<std::string> split(const std::string &str, char delim) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delim)) {
            token = trim(token);
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }
        return tokens;
    }

    // 将字符串转换为小写
    std::string toLower(const std::string& str) {
        std::string lower = str;
        std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        return lower;
    }

    Operand Parser::parseOperand(const std::string &op) {
        Operand operand;
        std::string value = trim(op);
        
        // 移除可能的方括号
        bool isMemoryRef = false;
        if (value.front() == '[' && value.back() == ']') {
            isMemoryRef = true;
            value = value.substr(1, value.length() - 2);
        }
        
        // 检查是否为寄存器
        std::string lowerValue = toLower(value);
        auto regIt = REGISTER_MAP.find(lowerValue);
        
        if (regIt != REGISTER_MAP.end()) {
            if (isMemoryRef) {
                operand.type = OperandType::Memory;
                operand.value = value;
            } else {
                operand.type = OperandType::Register;
                operand.reg = regIt->second;
                operand.value = value;
            }
            return operand;
        }
        
        // 检查是否为立即数
        if (value[0] == '#' || std::isdigit(value[0]) || value[0] == '-') {
            operand.type = OperandType::Immediate;
            if (value[0] == '#') {
                value = value.substr(1);
            }
            operand.immediate = std::stoll(value);
            operand.value = value;
            return operand;
        }
        
        // 如果是内存引用或其他
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
        
        // 分割指令和操作数
        size_t spacePos = trimmedLine.find(' ');
        if (spacePos == std::string::npos) {
            inst.mnemonic = trimmedLine;
        } else {
            inst.mnemonic = trim(trimmedLine.substr(0, spacePos));
            std::string operandsStr = trimmedLine.substr(spacePos + 1);
            
            // 分割操作数
            auto operands = split(operandsStr, ',');
            for (const auto &op : operands) {
                inst.operands.push_back(parseOperand(op));
            }
        }
        
        // 转换指令类型
        std::string lowerMnemonic = toLower(inst.mnemonic);
        auto it = INSTRUCTION_MAP.find(lowerMnemonic);
        if (it != INSTRUCTION_MAP.end()) {
            inst.type = it->second;
        } else {
            inst.type = InstructionType::Unknown;
        }
        
        return inst;
    }

    std::vector<Instruction> Parser::parse(const std::string &sourceCode) {
        std::vector<Instruction> instructions;
        std::istringstream stream(sourceCode);
        std::string line;
        
        while (std::getline(stream, line)) {
            auto inst = parseLine(line);
            if (inst.type != InstructionType::Unknown) {
                instructions.push_back(inst);
            }
        }
        
        return instructions;
    }

} // namespace Ryntra::rasm 