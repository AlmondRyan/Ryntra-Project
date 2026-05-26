// ========== ErrorHandler.cpp ======================================== *- C++ -* //
// Copyright (c) 2026 Remimwen Studio (Ryan "NvKopres" Almond).
// Licensed under Apache-2.0 License. See LICENSE for more info.
// ============================================================================== //

#include "ErrorHandler.h"
#include "ColoredTextManager/ColoredTextManager.h"
#include "SourceLocation/SourceLocation.h"
#include <iostream>

namespace Ryntra::Compiler {
    ErrorHandler &ErrorHandler::getInstance() {
        static ErrorHandler instance;
        return instance;
    }

    void ErrorHandler::makeHint(const std::string &desc, SourceLocation location) {
        errorObjects.emplace_back(kHint, location, desc);
    }

    void ErrorHandler::makeError(const std::string &desc, SourceLocation location) {
        errorObjects.emplace_back(kError, location, desc);
    }

    void ErrorHandler::makeWarning(const std::string &desc, SourceLocation location) {
        errorObjects.emplace_back(kWarning, location, desc);
    }

    void ErrorHandler::print() const {
        for (const auto &i : errorObjects) {
            if (i.type == kError) {
                std::cout << "[" << COLORED_TEXT_RED << "Error" << COLORED_TEXT_DEFAULT << "]: "
                          << "(l: " << i.location.line << ", c: " << i.location.column << ") " << i.description << std::endl;
            } else if (i.type == kWarning) {
                std::cout << "[" << COLORED_TEXT_YELLOW << "Warning" << COLORED_TEXT_DEFAULT << "]: "
                          << "(l: " << i.location.line << ", c: " << i.location.column << ") " << i.description << std::endl;
            } else if (i.type == kHint) {
                std::cout << "[" << COLORED_TEXT_CYAN << "Hint" << COLORED_TEXT_DEFAULT << "]: "
                          << "(l: " << i.location.line << ", c: " << i.location.column << ") " << i.description << std::endl;
            }
        }
    }
} // namespace Ryntra::Compiler