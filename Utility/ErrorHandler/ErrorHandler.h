// ========== ErrorHandler.h ========================================== *- C++ -* //
// Copyright (c) 2026 Remimwen Studio (Ryan "NvKopres" Almond).
// Licensed under Apache-2.0 License. See LICENSE for more info.
// ============================================================================== //

#pragma once

#include <string>
#include <utility>
#include <vector>

#include "SourceLocation/SourceLocation.h"

namespace Ryntra::Compiler {
    /// \brief An enumeration that contains three error types: Hint, Warning, Error.
    enum ErrorType {
        kHint,
        kWarning,
        kError
    };

    /// \brief A simple structure that represents an object of an error.
    struct ErrorObject {
        ErrorType type;
        std::string description;
        SourceLocation location;

        /// \brief Constructor. Accepts the error type, the source location and the description
        /// \param type The error type
        /// \param loc The source location
        /// \param desc The description
        ErrorObject(const ErrorType type, const SourceLocation loc, std::string desc)
            : type(type), description(std::move(desc)), location(loc) {
        }
    };

    /// \brief The error handler itself, which is a singleton class that make sures there's only one instance
    /// in the context.
    class ErrorHandler {
    public:
        /// \brief Static instance. Use it as \code ErrorHandler::getInstance() \endcode
        static ErrorHandler &getInstance();

        /// \brief Make a warning object then push into the error object list.
        /// \param desc The description
        /// \param location The source location
        void makeWarning(const std::string &desc, SourceLocation location);

        /// \brief Make a hint object then push into the error object list.
        /// \param desc The description
        /// \param location The source location
        void makeHint(const std::string &desc, SourceLocation location);

        /// \brief Make an error object then push into the error object list.
        /// \param desc The description
        /// \param location The source location
        void makeError(const std::string &desc, SourceLocation location);

        /// \brief Print ALL the error object in the list in the format of
        /// \code [TYPE] (l: LINE, c: COL) DESC \endcode
        void print() const;

        ErrorHandler(const ErrorHandler &) = delete;
        ErrorHandler &operator=(const ErrorHandler &) = delete;
        ErrorHandler(ErrorHandler &&) = delete;
        ErrorHandler &operator=(ErrorHandler &&) = delete;

        /// \brief Get the error object list. Use to check is there only warning or hint.
        [[nodiscard]] std::vector<ErrorObject> getErrorObjects() const {
            return errorObjects;
        }

    private:
        ErrorHandler() = default;
        std::vector<ErrorObject> errorObjects;
    };
} // namespace Ryntra::Compiler