#ifndef RYNTRA_GLOBAL_CONSOLE_TEXT_COLOR_MANAGER
#define RYNTRA_GLOBAL_CONSOLE_TEXT_COLOR_MANAGER

#ifdef _WIN32
#include <windows.h>
#endif

#include "include/defs/ryntra_defs.h"
#include <iostream>

namespace Ryntra::Common::utils::ConsoleTextColorManager {
    enum class Color {
        CTCM_Default,
        CTCM_Red,
        CTCM_Green,
        CTCM_Yellow,
        CTCM_Blue,
        CTCM_Purple,
        CTCM_Cyan,
        CTCM_White
    };

    class ConsoleTextColorManager {
    public:
        ConsoleTextColorManager() = default;
        ~ConsoleTextColorManager() = default;

        static void setColor(std::ostream &os, Color color);
        static void resetColor(std::ostream &os = std::cout);
        R_INLINE std::ostream &operator<<(std::ostream &os, Color color);
    };
}

#endif // RYNTRA_GLOBAL_CONSOLE_TEXT_COLOR_MANAGER