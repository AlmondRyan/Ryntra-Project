#pragma once

namespace Ryntra::rasm {
    /**
     * @brief Enumeration - Which platform the assembler is targeting, x86 or x64 (a.k.a. AMD64 or x86_64)
     */
    enum class TargetPlatform {
        x86,
        x64
    };
}