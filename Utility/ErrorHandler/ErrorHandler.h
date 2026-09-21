// ========== ErrorHandler.h ========================================== *- C++ -* //
// Copyright (c) 2026 Remimwen Studio (Ryan "NvKopres" Almond).
// Licensed under Apache-2.0 License. See LICENSE for more info.
// ============================================================================== //

#pragma once

#include <string>
#include <utility>
#include <vector>

#include "SourceLocation/SourceRange.h"

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
        SourceRange range;

        /// \brief Constructor. Accepts the error type, the source range and the description
        /// \param type The error type
        /// \param range The source range the diagnostic refers to
        /// \param desc The description
        ErrorObject(const ErrorType type, const SourceRange &range, std::string desc)
            : type(type), description(std::move(desc)), range(range) {
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
        /// \param range The source range
        void makeWarning(const std::string &desc, const SourceRange &range);

        /// \brief Make a hint object then push into the error object list.
        /// \param desc The description
        /// \param range The source range
        void makeHint(const std::string &desc, const SourceRange &range);

        /// \brief Make an error object then push into the error object list.
        /// \param desc The description
        /// \param range The source range
        void makeError(const std::string &desc, const SourceRange &range);

        /// \brief Deprecated compatibility overload. Forwards to the range version as an
        /// empty half-open range at \c location . Use the \c SourceRange overload instead.
        /// \param desc The description
        /// \param location The source location
        RYNTRA_DEPRECATED_LOCATION_OVERLOAD void makeWarning(const std::string &desc, const SourceLocation &location);

        /// \brief Deprecated compatibility overload. Forwards to the range version as an
        /// empty half-open range at \c location . Use the \c SourceRange overload instead.
        /// \param desc The description
        /// \param location The source location
        RYNTRA_DEPRECATED_LOCATION_OVERLOAD void makeHint(const std::string &desc, const SourceLocation &location);

        /// \brief Deprecated compatibility overload. Forwards to the range version as an
        /// empty half-open range at \c location . Use the \c SourceRange overload instead.
        /// \param desc The description
        /// \param location The source location
        RYNTRA_DEPRECATED_LOCATION_OVERLOAD void makeError(const std::string &desc, const SourceLocation &location);

        /// \brief Print ALL the error object in the list in the format of
        /// \code [TYPE] (line:column) DESC \endcode for an empty range, or
        /// \code [TYPE] (line:column-end.line:end.column) DESC \endcode for a span.
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

        /// \brief Format a range as \c (line:column) when empty, otherwise as
        /// \c (line:column-end.line:end.column) .
        /// \param range The range to format
        /// \return The formatted location string
        static std::string formatRange(const SourceRange &range);

        std::vector<ErrorObject> errorObjects;
    };
} // namespace Ryntra::Compiler
