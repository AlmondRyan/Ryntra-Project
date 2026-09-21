// ========== ErrorHandler.cpp ======================================== *- C++ -* //
// Copyright (c) 2026 Remimwen Studio (Ryan "NvKopres" Almond).
// Licensed under Apache-2.0 License. See LICENSE for more info.
// ============================================================================== //

#include "ErrorHandler.h"
#include "ColoredTextManager/ColoredTextManager.h"
#include "SourceLocation/SourceRange.h"
#include <iostream>

namespace Ryntra::Compiler {
    ErrorHandler &ErrorHandler::getInstance() {
        static ErrorHandler instance;
        return instance;
    }

    std::string ErrorHandler::formatRange(const SourceRange &range) {
        std::string text = "(" + std::to_string(range.begin.line) + ":" + std::to_string(range.begin.column);
        if (!range.isEmpty()) {
            text += "-" + std::to_string(range.end.line) + ":" + std::to_string(range.end.column);
        }
        text += ")";
        return text;
    }

    void ErrorHandler::makeHint(const std::string &desc, const SourceRange &range) {
        errorObjects.emplace_back(kHint, range, desc);
    }

    void ErrorHandler::makeError(const std::string &desc, const SourceRange &range) {
        errorObjects.emplace_back(kError, range, desc);
    }

    void ErrorHandler::makeWarning(const std::string &desc, const SourceRange &range) {
        errorObjects.emplace_back(kWarning, range, desc);
    }

    void ErrorHandler::makeHint(const std::string &desc, const SourceLocation &location) {
        makeHint(desc, SourceRange(location));
    }

    void ErrorHandler::makeError(const std::string &desc, const SourceLocation &location) {
        makeError(desc, SourceRange(location));
    }

    void ErrorHandler::makeWarning(const std::string &desc, const SourceLocation &location) {
        makeWarning(desc, SourceRange(location));
    }

    void ErrorHandler::print() const {
        for (const auto &i : errorObjects) {
            const std::string location = formatRange(i.range);
            if (i.type == kError) {
                std::cout << "[" << COLORED_TEXT_RED << "Error" << COLORED_TEXT_DEFAULT << "]: "
                          << location << " " << i.description << std::endl;
            } else if (i.type == kWarning) {
                std::cout << "[" << COLORED_TEXT_YELLOW << "Warning" << COLORED_TEXT_DEFAULT << "]: "
                          << location << " " << i.description << std::endl;
            } else if (i.type == kHint) {
                std::cout << "[" << COLORED_TEXT_CYAN << "Hint" << COLORED_TEXT_DEFAULT << "]: "
                          << location << " " << i.description << std::endl;
            }
        }
    }
} // namespace Ryntra::Compiler
