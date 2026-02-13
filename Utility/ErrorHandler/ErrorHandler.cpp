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
        errorObjects.emplace_back(ET_HINT, location, desc);
    }

    void ErrorHandler::makeError(const std::string &desc, SourceLocation location) {
        errorObjects.emplace_back(ET_ERROR, location, desc);
    }

    void ErrorHandler::makeWarning(const std::string &desc, SourceLocation location) {
        errorObjects.emplace_back(ET_WARNING, location, desc);
    }

    void ErrorHandler::print() const {
        for (const auto &i : errorObjects) {
            if (i.type == ET_ERROR) {
                std::cout << "[" << COLORED_TEXT_RED << "Error" << COLORED_TEXT_DEFAULT << "]: "
                          << "(l: " << i.location.line << ", c: " << i.location.column << ") " << i.description << std::endl;
            } else if (i.type == ET_WARNING) {
                std::cout << "[" << COLORED_TEXT_YELLOW << "Warning" << COLORED_TEXT_DEFAULT << "]: "
                          << "(l: " << i.location.line << ", c: " << i.location.column << ") " << i.description << std::endl;
            } else if (i.type == ET_HINT) {
                std::cout << "[" << COLORED_TEXT_CYAN << "Hint" << COLORED_TEXT_DEFAULT << "]: "
                          << "(l: " << i.location.line << ", c: " << i.location.column << ") " << i.description << std::endl;
            }
        }
    }
} // namespace Ryntra::Compiler