#pragma once
#ifndef RASM_FLOATING_POINT_INSTRUCTION_H
#define RASM_FLOATING_POINT_INSTRUCTION_H

#include "assembler/instruction/instruction_types.h"
#include "assembler/instruction/instruction_info.h"

namespace Ryntra::rasm::floating_point {
    // 浮点指令的具体信息
    const std::unordered_map<std::string, InstructionInfo> FLOATING_POINT_INSTRUCTIONS = {
#ifdef USE_SSE
        // SSE 标量运算
        {"addss", {InstructionType::ADDSS, "Add scalar single-precision", "SIMD", 2, 2, false, RegisterType::Unknown}},
        {"subss", {InstructionType::SUBSS, "Subtract scalar single-precision", "SIMD", 2, 2, false, RegisterType::Unknown}},
        {"mulss", {InstructionType::MULSS, "Multiply scalar single-precision", "SIMD", 2, 2, false, RegisterType::Unknown}},
        {"divss", {InstructionType::DIVSS, "Divide scalar single-precision", "SIMD", 2, 2, false, RegisterType::Unknown}},
#endif

#ifdef USE_AVX
        // AVX 向量运算
        {"vaddps", {InstructionType::VADDPS, "Vector add packed single-precision", "SIMD", 3, 3, false, RegisterType::Unknown}},
        {"vmulps", {InstructionType::VMULPS, "Vector multiply packed single-precision", "SIMD", 3, 3, false, RegisterType::Unknown}},
#endif

#ifdef ENABLE_AVX512
        // AVX-512 向量运算
        {"vaddpd", {InstructionType::VADDPD, "Vector add packed double-precision", "SIMD", 3, 3, false, RegisterType::Unknown}},
        {"vmulpd", {InstructionType::VMULPD, "Vector multiply packed double-precision", "SIMD", 3, 3, false, RegisterType::Unknown}},
#endif
    };
} // namespace Ryntra::rasm::floating_point

#endif // RASM_FLOATING_POINT_INSTRUCTION_H
