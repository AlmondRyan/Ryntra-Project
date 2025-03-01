#pragma once
#ifndef RASM_OBJECTFILE_H
#define RASM_OBJECTFILE_H

#include <string>
#include <vector>
#include <cstdint>
#include "assembler/instruction.h"
#include "assembler/parser.h"

namespace Ryntra::rasm {
    // COFF 文件头
    struct COFFHeader {
        uint16_t Machine;          // 目标机器类型
        uint16_t NumberOfSections; // 节数量
        uint32_t TimeDateStamp;    // 文件创建时间戳
        uint32_t PointerToSymbolTable; // 符号表偏移
        uint32_t NumberOfSymbols;      // 符号数量
        uint16_t SizeOfOptionalHeader; // 可选头大小（对于obj文件为0）
        uint16_t Characteristics;      // 文件特征
    };

    // COFF 节头
    struct SectionHeader {
        char Name[8];              // 节名称
        uint32_t VirtualSize;      // 虚拟大小
        uint32_t VirtualAddress;   // 虚拟地址
        uint32_t SizeOfRawData;    // 原始数据大小
        uint32_t PointerToRawData; // 原始数据偏移
        uint32_t PointerToRelocations; // 重定位表偏移
        uint32_t PointerToLinenumbers; // 行号表偏移
        uint16_t NumberOfRelocations;  // 重定位项数量
        uint16_t NumberOfLinenumbers;  // 行号项数量
        uint32_t Characteristics;      // 节特征
    };

    // COFF 符号表项
    struct SymbolTableEntry {
        char Name[8];              // 符号名称
        uint32_t Value;            // 符号值
        int16_t SectionNumber;     // 所属节号
        uint16_t Type;             // 符号类型
        uint8_t StorageClass;      // 存储类别
        uint8_t NumberOfAuxSymbols; // 辅助符号数量
    };

    class ObjectFileWriter {
    public:
        static bool writeToFile(const std::string& filename, 
                              const std::vector<Section>& sections,
                              const std::vector<DataDefinition>& dataDefinitions,
                              const std::unordered_map<std::string, Symbol>& symbols);

    private:
        static void writeCOFFHeader(std::ofstream& file, uint16_t numSections, uint32_t numSymbols);
        static void writeSectionHeaders(std::ofstream& file, const std::vector<Section>& sections);
        static void writeSectionData(std::ofstream& file, const std::vector<Section>& sections);
        static void writeSymbolTable(std::ofstream& file, const std::unordered_map<std::string, Symbol>& symbols);
        static void writeStringTable(std::ofstream& file);
    };
} // namespace Ryntra::rasm

#endif // RASM_OBJECTFILE_H