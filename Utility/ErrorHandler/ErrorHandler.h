#pragma once
#ifndef COMPILER_UTILITY_ERRORHANDLER_H
#define COMPILER_UTILITY_ERRORHANDLER_H

#include <string>
#include <utility>
#include <vector>

#include "SourceLocation/SourceLocation.h"

namespace Ryntra::Compiler {
    enum ErrorType {
        ET_HINT,
        ET_WARNING,
        ET_ERROR
    };

    struct ErrorObject {
        ErrorType      type;
        std::string    description;
        SourceLocation location;

        ErrorObject(const ErrorType type, const SourceLocation _l, std::string desc)
            : type(type), description(std::move(desc)), location(_l) {
        }
    };

    class ErrorHandler {
    public:
        static ErrorHandler &getInstance();

        void makeWarning(const std::string &desc, SourceLocation location);
        void makeHint(const std::string &desc, SourceLocation location);
        void makeError(const std::string &desc, SourceLocation location);

        void print() const;

        ErrorHandler(const ErrorHandler &) = delete;
        ErrorHandler &operator=(const ErrorHandler &) = delete;
        ErrorHandler(ErrorHandler &&) = delete;
        ErrorHandler &operator=(ErrorHandler &&) = delete;

        [[nodiscard]] std::vector<ErrorObject> getErrorObjects() const {
            return errorObjects;
        }

    private:
        ErrorHandler() = default;
        std::vector<ErrorObject> errorObjects;
    };
} // namespace Ryntra::Compiler

#endif // COMPILER_UTILITY_ERRORHANDLER_H
