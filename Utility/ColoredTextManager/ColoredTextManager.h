#pragma once
#ifndef COMPILER_UTILITY_COLOREDTEXTMANAGER_H
#define COMPILER_UTILITY_COLOREDTEXTMANAGER_H

#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif // WIN32

namespace Ryntra::Compiler {
    enum class Colors {
        CTM_Default,
        CTM_Red,
        CTM_Green,
        CTM_Yellow,
        CTM_Blue,
        CTM_Purple,
        CTM_Cyan,
        CTM_White
    };

    class ConsoleTextManager {
    public:
        ConsoleTextManager() = default;
        ~ConsoleTextManager() = default;

        static void setColor(std::ostream &os, Colors color) {
            if (&os == &std::cout || &os == &std::cerr) {
#ifdef _WIN32
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                switch (color) {
                case Colors::CTM_Red:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_Green:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_Yellow:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_Blue:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_Purple:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_Cyan:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_White:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                    break;
                case Colors::CTM_Default:
                    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                    break;
                }
#else
                switch (color) {
                case Colors::CTM_Red:
                    os << "\033[31m";
                    break;
                case Colors::CTM_Green:
                    os << "\033[32m";
                    break;
                case Colors::CTM_Yellow:
                    os << "\033[33m";
                    break;
                case Colors::CTM_Blue:
                    os << "\033[34m";
                    break;
                case Colors::CTM_Purple:
                    os << "\033[35m";
                    break;
                case Colors::CTM_Cyan:
                    os << "\033[36m";
                    break;
                case Colors::CTM_White:
                    os << "\033[37m";
                    break;
                case Colors::CTM_Default:
                    os << "\033[0m";
                    break;
                }
#endif
            }
        }

        static void resetColor(std::ostream &os = std::cout) {
            setColor(os, Colors::CTM_Default);
        }
    };

    inline std::ostream &operator<<(std::ostream &os, Colors color) {
        ConsoleTextManager::setColor(os, color);
        return os;
    }
} // namespace Ryntra::Compiler

#define COLORED_TEXT_CYAN Ryntra::Compiler::Colors::CTM_Cyan
#define COLORED_TEXT_DEFAULT Ryntra::Compiler::Colors::CTM_Default
#define COLORED_TEXT_GREEN Ryntra::Compiler::Colors::CTM_Green
#define COLORED_TEXT_PURPLE Ryntra::Compiler::Colors::CTM_Purple
#define COLORED_TEXT_RED Ryntra::Compiler::Colors::CTM_Red
#define COLORED_TEXT_WHITE Ryntra::Compiler::Colors::CTM_White
#define COLORED_TEXT_YELLOW Ryntra::Compiler::Colors::CTM_Yellow

#endif // COMPILER_UTILITY_COLOREDTEXTMANAGER_H