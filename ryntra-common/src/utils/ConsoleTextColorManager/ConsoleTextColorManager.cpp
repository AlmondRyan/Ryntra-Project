/// \file ConsoleTextColorManager.cpp

#include "include/utils/ConsoleTextColorManager/ConsoleTextColorManager.hpp"
#include "include/defs/ryntra_exceptions.h"

#ifdef _WIN32
#include <VersionHelpers.h>
#endif

namespace Ryntra::Common::utils::ConsoleTextColorManager {
    /**
     * @brief Set the color of the console text.
     * @param os - The output stream to which the color will be applied.
     * @param color - The color to be set.
     */
    void ConsoleTextColorManager::setColor(std::ostream &os, Ryntra::Common::utils::ConsoleTextColorManager::Color color) {
#ifdef _WIN32
        if (!IsWindows10OrGreater()) {
            throw new Ryntra::Exceptions::WindowsVersionNotSupported("Error: You are currently running a version that "
                                                                     "not supported by Ryntra. Please upgrade your system.");
        }
#endif
        if (&os == &std::cout || &os == &std::cerr) {
#ifdef _WIN32
            switch (color) {
            case Color::CTCM_Blue:
                os << "\033[38;2;0;0;255m";
                break;
            case Color::CTCM_Cyan:
                os << "\033[38;2;0;255;255m";
                break;
            case Color::CTCM_Default:
                os << "\033[0m";
                break;
            case Color::CTCM_Green:
                os << "\033[38;2;0;255;0m";
                break;
            case Color::CTCM_Purple:
                os << "\033[38;2;255;0;255m";
                break;
            case Color::CTCM_Red:
                os << "\033[38;2;255;0;0m";
                break;
            case Color::CTCM_White:
                os << "\033[38;2;255;255;255m";
                break;
            case Color::CTCM_Yellow:
                os << "\033[38;2;255;255;0m";
                break;
            default:
                break;
            }
#else
            switch (color) {
            case Color::CTCM_Blue:
                os << "\033[31m";
                break;
            case Color::CTCM_Cyan:
                os << "\033[32m";
                break;
            case Color::CTCM_Default:
                os << "\033[0m";
                break;
            case Color::CTCM_Green:
                os << "\033[33m";
                break;
            case Color::CTCM_Purple:
                os << "\033[34m";
                break;
            case Color::CTCM_Red:
                os << "\033[35m";
                break;
            case Color::CTCM_White:
                os << "\033[36m";
                break;
            case Color::CTCM_Yellow:
                os << "\033[37m";
                break;
            default:
                break;
            }
#endif
        }
    }

    /**
     * @brief Reset the color of the console text.
     * @param os - The output stream to which the color will be reset.
     */
    void ConsoleTextColorManager::resetColor(std::ostream &os) {
        setColor(os, Color::CTCM_Default);
    }

    /**
     * @brief Overload output stream operator
     * @param os - The output stream to which the color will be applied.
     * @param color - The color to be set.
     * @return @c std::ostream&
     */
    std::ostream &ConsoleTextColorManager::operator<<(std::ostream &os, Ryntra::Common::utils::ConsoleTextColorManager::Color color) {
        ConsoleTextColorManager::setColor(os, color);
        return os;
    }
} // namespace Ryntra::Common::utils::ConsoleTextColorManager