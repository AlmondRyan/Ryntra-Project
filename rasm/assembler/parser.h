#pragma once
#include "instruction.h"
#include <string>
#include <vector>
#include <unordered_map>

namespace Ryntra::rasm {
    enum class SectionType {
        Unknown,
        Text,       // 代码段 (.text)
        Data,       // 已初始化数据段 (.data)
        Bss,        // 未初始化数据段 (.bss)
        Rodata,     // 只读数据段 (.rodata)
        Stack,      // 栈段 (.stack)
        Heap,       // 堆段 (.heap)
        Custom      // 用户自定义段
    };

    enum class DataType {
        Byte,       // db, 1字节
        Word,       // dw, 2字节
        DWord,      // dd, 4字节
        QWord,      // dq, 8字节
        TWord,      // dt, 10字节
        OWord,      // do/ddq, 16字节
        YWord,      // dy, 32字节
        ZWord,      // dz, 64字节
        String,     // 字符串
        Unknown
    };

    struct Section {
        SectionType type;
        std::string name;
        uint64_t address;
        std::vector<uint8_t> data;
        bool isReadable;     // 是否可读
        bool isWritable;     // 是否可写
        bool isExecutable;   // 是否可执行
        uint32_t align;      // 段对齐值
        uint64_t entryPoint; // 添加入口点
    };

    struct Symbol {
        std::string name;
        uint64_t address;
        bool isGlobal;
        bool isExtern;        // 是否是外部符号
        SectionType section;
        uint16_t type;        // 添加符号类型
    };

    struct DataDefinition {
        std::string label;      // 数据标签
        DataType type;          // 数据类型
        std::vector<uint8_t> data;  // 实际数据
        bool isArray;           // 是否是数组
        size_t count;           // 数组元素个数
    };

    class Parser {
    public:
        static std::vector<Instruction> parse(const std::string &sourceCode);
        static Operand parseOperand(const std::string &op);

        // 添加访问器方法
        static const std::vector<Section>& getSections() { return sections; }
        static const std::vector<DataDefinition>& getDataDefinitions() { return dataDefinitions; }
        static const std::unordered_map<std::string, Symbol>& getSymbols() { return symbols; }

    private:
        static Instruction parseLine(const std::string &line);
        static bool isSection(const std::string &line);
        static bool isLabel(const std::string &line);
        static bool isDirective(const std::string &line);
        static bool isGlobal(const std::string &line);   // 检查是否是global声明
        static bool isExtern(const std::string &line);   // 检查是否是extern声明
        static void handleGlobal(const std::string &line); // 处理global声明
        static void handleExtern(const std::string &line); // 处理extern声明
        static std::string extractComment(const std::string &line); // 提取注释
        static bool isDataDefinition(const std::string &line);
        static DataDefinition parseDataDefinition(const std::string &line);
        static std::vector<uint8_t> parseStringLiteral(const std::string &str);
        static std::vector<uint8_t> parseNumericLiteral(const std::string &str, DataType type);
        static Section createSection(const std::string& name, SectionType type);
        static SectionType currentSection;
        static std::unordered_map<std::string, Symbol> symbols;
        static std::vector<Section> sections;
        static std::vector<std::string> comments;  // 存储所有注释
        static std::vector<DataDefinition> dataDefinitions;  // 存储数据定义
    };
} // namespace Ryntra::rasm