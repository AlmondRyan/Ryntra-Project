#include "parser.h"
#include "instruction/instruction_encoder.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <regex>
#include <iostream>

namespace Ryntra::rasm {
    // 静态成员初始化
    SectionType Parser::currentSection = SectionType::Unknown;
    std::unordered_map<std::string, Symbol> Parser::symbols;
    std::vector<Section> Parser::sections;
    std::vector<std::string> Parser::comments;
    std::vector<DataDefinition> Parser::dataDefinitions;

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
        std::string trimmedLine = trim(line);
        return trimmedLine.find("section") == 0 || trimmedLine.find(".section") == 0;
    }

    bool Parser::isLabel(const std::string &line) {
        return line.find(':') != std::string::npos;
    }

    bool Parser::isDirective(const std::string &line) {
        return line[0] == '.';
    }

    bool Parser::isGlobal(const std::string &line) {
        std::string trimmedLine = trim(line);
        return trimmedLine.find("global") == 0;
    }

    bool Parser::isExtern(const std::string &line) {
        std::string trimmedLine = trim(line);
        return trimmedLine.find("extern") == 0;
    }

    bool Parser::isDataDefinition(const std::string &line) {
        std::string trimmedLine = trim(line);
        return trimmedLine.find("db") != std::string::npos ||
               trimmedLine.find("dw") != std::string::npos ||
               trimmedLine.find("dd") != std::string::npos ||
               trimmedLine.find("dq") != std::string::npos;
    }

    std::string Parser::extractComment(const std::string &line) {
        size_t commentPos = line.find(';');
        if (commentPos != std::string::npos) {
            return trim(line.substr(commentPos + 1));
        }
        return "";
    }

    void Parser::handleGlobal(const std::string &line) {
        std::string symbolList = line.substr(6); // 跳过"global"
        auto symbols = split(symbolList, ',');
        for (const auto& sym : symbols) {
            std::string symbolName = trim(sym);
            if (!symbolName.empty()) {
                auto it = Parser::symbols.find(symbolName);
                if (it != Parser::symbols.end()) {
                    it->second.isGlobal = true;
                } else {
                    // 创建一个新的符号，等待后续定义
                    Symbol symbol;
                    symbol.name = symbolName;
                    symbol.isGlobal = true;
                    symbol.isExtern = false;
                    symbol.section = SectionType::Unknown;
                    Parser::symbols[symbolName] = symbol;
                }
            }
        }
    }

    void Parser::handleExtern(const std::string &line) {
        std::string symbolList = line.substr(6); // 跳过"extern"
        auto symbols = split(symbolList, ',');
        for (const auto& sym : symbols) {
            std::string symbolName = trim(sym);
            if (!symbolName.empty()) {
                Symbol symbol;
                symbol.name = symbolName;
                symbol.isGlobal = true;
                symbol.isExtern = true;
                symbol.section = SectionType::Unknown;
                Parser::symbols[symbolName] = symbol;
            }
        }
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

    Section Parser::createSection(const std::string& name, SectionType type) {
        Section section;
        section.name = name;
        section.type = type;
        section.address = 0;
        section.align = 16; // 默认16字节对齐

        // 设置段的默认属性
        switch (type) {
            case SectionType::Text:
                section.isReadable = true;
                section.isWritable = false;
                section.isExecutable = true;
                break;
            case SectionType::Data:
                section.isReadable = true;
                section.isWritable = true;
                section.isExecutable = false;
                break;
            case SectionType::Bss:
                section.isReadable = true;
                section.isWritable = true;
                section.isExecutable = false;
                break;
            case SectionType::Rodata:
                section.isReadable = true;
                section.isWritable = false;
                section.isExecutable = false;
                break;
            case SectionType::Stack:
                section.isReadable = true;
                section.isWritable = true;
                section.isExecutable = false;
                break;
            case SectionType::Heap:
                section.isReadable = true;
                section.isWritable = true;
                section.isExecutable = false;
                break;
            case SectionType::Custom:
                section.isReadable = true;
                section.isWritable = true;
                section.isExecutable = false;
                break;
            default:
                section.isReadable = false;
                section.isWritable = false;
                section.isExecutable = false;
                break;
        }

        return section;
    }

    std::vector<uint8_t> Parser::parseStringLiteral(const std::string &str) {
        std::vector<uint8_t> data;
        
        for (size_t i = 0; i < str.length(); ++i) {
            if (str[i] == '\\') {
                if (i + 1 < str.length()) {
                    i++;
                    switch (str[i]) {
                        case 'n': data.push_back('\n'); break;
                        case 't': data.push_back('\t'); break;
                        case 'r': data.push_back('\r'); break;
                        case '0': data.push_back('\0'); break;
                        case '\\': data.push_back('\\'); break;
                        case '"': data.push_back('"'); break;
                        case 'x': 
                            if (i + 2 < str.length()) {
                                std::string hex = str.substr(i + 1, 2);
                                data.push_back(static_cast<uint8_t>(std::stoi(hex, nullptr, 16)));
                                i += 2;
                            }
                            break;
                        default: data.push_back(str[i]);
                    }
                }
            } else {
                data.push_back(static_cast<uint8_t>(str[i]));
            }
        }
        return data;
    }

    std::vector<uint8_t> Parser::parseNumericLiteral(const std::string &str, DataType type) {
        std::vector<uint8_t> data;
        uint64_t value = 0;

        // 处理不同进制的数字
        if (str.find("0x") == 0) {
            // 十六进制
            value = std::stoull(str.substr(2), nullptr, 16);
        } else if (str[0] == '0') {
            // 八进制
            value = std::stoull(str, nullptr, 8);
        } else {
            // 十进制
            value = std::stoull(str, nullptr, 10);
        }

        // 根据数据类型确定字节数
        size_t size = 0;
        switch (type) {
            case DataType::Byte:  size = 1; break;
            case DataType::Word:  size = 2; break;
            case DataType::DWord: size = 4; break;
            case DataType::QWord: size = 8; break;
            default: size = 1; break;
        }

        // 将值转换为字节数组
        for (size_t i = 0; i < size; ++i) {
            data.push_back(static_cast<uint8_t>(value & 0xFF));
            value >>= 8;
        }

        return data;
    }

    DataDefinition Parser::parseDataDefinition(const std::string &line) {
        DataDefinition def;
        std::string trimmedLine = trim(line);

        // 解析标签
        size_t labelEnd = trimmedLine.find(' ');
        if (labelEnd != std::string::npos) {
            def.label = trim(trimmedLine.substr(0, labelEnd));
            trimmedLine = trim(trimmedLine.substr(labelEnd));
        }

        // 确定数据类型
        if (trimmedLine.find("db") != std::string::npos) {
            def.type = DataType::Byte;
            trimmedLine = trim(trimmedLine.substr(trimmedLine.find("db") + 2));
        } else if (trimmedLine.find("dw") != std::string::npos) {
            def.type = DataType::Word;
            trimmedLine = trim(trimmedLine.substr(trimmedLine.find("dw") + 2));
        } else if (trimmedLine.find("dd") != std::string::npos) {
            def.type = DataType::DWord;
            trimmedLine = trim(trimmedLine.substr(trimmedLine.find("dd") + 2));
        } else if (trimmedLine.find("dq") != std::string::npos) {
            def.type = DataType::QWord;
            trimmedLine = trim(trimmedLine.substr(trimmedLine.find("dq") + 2));
        }

        // 解析数据值
        if (trimmedLine[0] == '"') {
            // 字符串字面量
            def.type = DataType::String;
            size_t endQuote = trimmedLine.find('"', 1);
            if (endQuote != std::string::npos) {
                std::string strContent = trimmedLine.substr(1, endQuote - 1);
                def.data = parseStringLiteral(strContent);
            }
        } else {
            // 处理可能的多个数值（用逗号分隔）
            std::vector<std::string> values = split(trimmedLine, ',');
            for (const auto& value : values) {
                auto numData = parseNumericLiteral(trim(value), def.type);
                def.data.insert(def.data.end(), numData.begin(), numData.end());
            }
        }

        return def;
    }

    Instruction Parser::parseLine(const std::string &line) {
        Instruction inst;
        std::string trimmedLine = trim(line);

        // 处理注释
        std::string comment = extractComment(line);
        if (!comment.empty()) {
            comments.push_back(comment);
        }

        // 忽略空行和纯注释行
        if (trimmedLine.empty() || trimmedLine[0] == ';') {
            inst.type = InstructionType::Unknown;
            return inst;
        }

        // 移除行尾注释
        size_t commentPos = trimmedLine.find(';');
        if (commentPos != std::string::npos) {
            trimmedLine = trim(trimmedLine.substr(0, commentPos));
        }

        // 处理global声明
        if (isGlobal(trimmedLine)) {
            handleGlobal(trimmedLine);
            inst.type = InstructionType::Unknown;
            return inst;
        }

        // 处理extern声明
        if (isExtern(trimmedLine)) {
            handleExtern(trimmedLine);
            inst.type = InstructionType::Unknown;
            return inst;
        }

        // 处理段定义
        if (isSection(trimmedLine)) {
            inst.type = InstructionType::Unknown;
            
            // 提取段名和属性
            std::string sectionDef = trimmedLine.substr(trimmedLine.find("section") + 7);
            std::vector<std::string> tokens = split(sectionDef, ',');
            std::string sectionName = trim(tokens[0]);
            
            // 创建新段
            Section newSection;
            if (sectionName == ".text" || sectionName == "text") {
                newSection = createSection(sectionName, SectionType::Text);
                currentSection = SectionType::Text;
            } else if (sectionName == ".data" || sectionName == "data") {
                newSection = createSection(sectionName, SectionType::Data);
                currentSection = SectionType::Data;
            } else if (sectionName == ".bss" || sectionName == "bss") {
                newSection = createSection(sectionName, SectionType::Bss);
                currentSection = SectionType::Bss;
            } else if (sectionName == ".rodata" || sectionName == "rodata") {
                newSection = createSection(sectionName, SectionType::Rodata);
                currentSection = SectionType::Rodata;
            } else {
                newSection = createSection(sectionName, SectionType::Custom);
                currentSection = SectionType::Custom;
            }

            // 处理段属性
            for (size_t i = 1; i < tokens.size(); i++) {
                std::string attr = trim(tokens[i]);
                if (attr == "read") {
                    newSection.isReadable = true;
                } else if (attr == "write") {
                    newSection.isWritable = true;
                } else if (attr == "execute") {
                    newSection.isExecutable = true;
                } else if (attr.find("align=") == 0) {
                    newSection.align = std::stoi(attr.substr(6));
                }
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
            symbol.address = (currentSection == SectionType::Text) ? 
                            sections.back().data.size() : 0;
            
            // 设置入口点
            if (labelName == "_start") {
                symbol.isGlobal = true;
                symbol.type = 0x20;  // 函数类型
                sections.back().entryPoint = symbol.address;
            } else {
                symbol.isGlobal = false;
            }
            
            symbols[labelName] = symbol;
            return inst;
        }

        // 处理数据定义
        if (isDataDefinition(trimmedLine)) {
            auto dataDef = parseDataDefinition(trimmedLine);
            dataDefinitions.push_back(dataDef);
            
            // 将数据添加到当前节
            if (currentSection == SectionType::Data) {
                auto& currentSectionData = sections.back().data;
                currentSectionData.insert(currentSectionData.end(), 
                                        dataDef.data.begin(), 
                                        dataDef.data.end());
            }
            
            // 更新符号表
            if (!dataDef.label.empty()) {
                Symbol symbol;
                symbol.name = dataDef.label;
                symbol.section = currentSection;
                symbol.address = sections.back().data.size() - dataDef.data.size(); // 设置正确的偏移量
                symbol.isGlobal = false;
                symbol.isExtern = false;
                symbols[dataDef.label] = symbol;
            }

            inst.type = InstructionType::Unknown;
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

        // 在 parseLine 函数中，处理指令时添加机器码生成
        if (inst.type != InstructionType::Unknown) {
            // 生成机器码
            inst.machineCode = InstructionEncoder::encode(inst);
            
            // 将机器码添加到代码段
            if (currentSection == SectionType::Text) {
                auto& currentSectionData = sections.back().data;
                currentSectionData.insert(currentSectionData.end(), 
                                        inst.machineCode.begin(), 
                                        inst.machineCode.end());
            }
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
        comments.clear();
        dataDefinitions.clear();

        std::cout << "\n=== Start Parsing ===\n";

        while (std::getline(stream, line)) {
            // 打印原始行
            std::cout << "\nParsing line: " << line << std::endl;

            // 处理注释
            std::string comment = extractComment(line);
            if (!comment.empty()) {
                comments.push_back(comment);
                std::cout << "Found comment: " << comment << std::endl;
            }

            auto inst = parseLine(line);

            // 打印段信息
            if (isSection(line)) {
                std::cout << "Found section: " << sections.back().name << std::endl;
                std::cout << "  Readable: " << (sections.back().isReadable ? "yes" : "no") << std::endl;
                std::cout << "  Writable: " << (sections.back().isWritable ? "yes" : "no") << std::endl;
                std::cout << "  Executable: " << (sections.back().isExecutable ? "yes" : "no") << std::endl;
            }

            // 打印数据定义信息
            if (isDataDefinition(line)) {
                const auto& dataDef = dataDefinitions.back();
                std::cout << "Found data definition:" << std::endl;
                std::cout << "  Label: " << dataDef.label << std::endl;
                std::cout << "  Type: ";
                switch (dataDef.type) {
                    case DataType::Byte: std::cout << "db"; break;
                    case DataType::Word: std::cout << "dw"; break;
                    case DataType::DWord: std::cout << "dd"; break;
                    case DataType::QWord: std::cout << "dq"; break;
                    case DataType::String: std::cout << "string"; break;
                    default: std::cout << "unknown"; break;
                }
                std::cout << std::endl;

                std::cout << "  Data: ";
                if (dataDef.type == DataType::String) {
                    // 打印字符串内容
                    std::cout << "\"";
                    for (uint8_t byte : dataDef.data) {
                        if (byte >= 32 && byte <= 126) { // 可打印字符
                            std::cout << static_cast<char>(byte);
                        } else {
                            std::cout << "\\x" << std::hex << static_cast<int>(byte);
                        }
                    }
                    std::cout << "\"";
                } else {
                    // 打印数值数据
                    std::cout << "[ ";
                    for (uint8_t byte : dataDef.data) {
                        std::cout << std::hex << "0x" << static_cast<int>(byte) << " ";
                    }
                    std::cout << "]";
                }
                std::cout << std::endl;
            }

            // 打印标签信息
            if (isLabel(line)) {
                std::string labelName = line.substr(0, line.find(':'));
                std::cout << "Found label: " << labelName << std::endl;
                if (symbols[labelName].isGlobal) {
                    std::cout << "  Global: yes" << std::endl;
                }
            }

            // 打印指令信息
            if (inst.type != InstructionType::Unknown) {
                instructions.push_back(inst);
                std::cout << "Found instruction:" << std::endl;
                std::cout << "  Mnemonic: " << inst.mnemonic << std::endl;
                std::cout << "  Operands: " << inst.operands.size() << std::endl;
                for (size_t i = 0; i < inst.operands.size(); ++i) {
                    const auto& op = inst.operands[i];
                    std::cout << "    Operand " << (i + 1) << ": ";
                    switch (op.type) {
                        case OperandType::Register:
                            std::cout << "Register (" << op.value << ")";
                            break;
                        case OperandType::Immediate:
                            std::cout << "Immediate (" << op.value << ")";
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
            }
        }

        std::cout << "\n=== Parsing Summary ===\n";
        std::cout << "Total instructions: " << instructions.size() << std::endl;
        std::cout << "Total sections: " << sections.size() << std::endl;
        std::cout << "Total symbols: " << symbols.size() << std::endl;
        std::cout << "Total data definitions: " << dataDefinitions.size() << std::endl;
        std::cout << "Total comments: " << comments.size() << std::endl;
        std::cout << "==================\n\n";

        return instructions;
    }
} // namespace Ryntra::rasm