#pragma once
#ifndef COMPILER_UTILITY_ERRORHANDLER_H
#define COMPILER_UTILITY_ERRORHANDLER_H

#include <string>
#include <vector>

#include "SourceLocation/SourceLocation.h"

namespace Ryntra::Compiler {
    enum ErrorType {
        ET_HINT,
        ET_WARNING,
        ET_ERROR
    };

    struct ErrorObject {
        ErrorType type;
        std::string description;
        SourceLocation location;

        ErrorObject(ErrorType type, SourceLocation _l, const std::string &desc)
            : type(type), description(desc), location(_l) {
        }
    };

    class ErrorHandler {
    public:
        static ErrorHandler& getInstance();

        void makeWarning(const std::string &desc, SourceLocation location);
        void makeHint(const std::string &desc, SourceLocation location);
        void makeError(const std::string &desc, SourceLocation location);

        void print();

        ErrorHandler(const ErrorHandler&) = delete;
        ErrorHandler& operator=(const ErrorHandler&) = delete;
        ErrorHandler(ErrorHandler&&) = delete;
        ErrorHandler& operator=(ErrorHandler&&) = delete;

        [[nodiscard]] std::vector<ErrorObject> getErrorObjects() const {
            return errorObjects;
        }
    private:
        ErrorHandler() = default;
        std::vector<ErrorObject> errorObjects;
    };
}

#endif // COMPILER_UTILITY_ERRORHANDLER_H
