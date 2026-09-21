#pragma once

#include "SourceLocation/SourceRange.h"

#include <iostream>
#include <source_location>

namespace Ryntra::Compiler {
    class InternalCompilerError {
    public:
        [[noreturn]]
        static void raise(std::string_view msg, std::source_location loc = std::source_location::current()) {
            std::cerr << std::format("Internal compiler error: {}, at {}:{}:{}", msg, loc.file_name(),
                                     loc.line(), loc.column());
            std::abort();
        }

        [[noreturn]]
        static void raise(std::string_view msg, SourceRange range, std::source_location loc = std::source_location::current()) {
            std::cerr << std::format("Internal compiler error: {}, caused at {}-{}, source at {}:{}:{}",
                                     msg, range.begin.offset, range.end.offset, loc.file_name(), loc.line(), loc.column());
            std::abort();
        }
    };
} // namespace Ryntra::Compiler

#define RYNTRA_ASSERT(condition)                                                                                              \
    do {                                                                                                                      \
        if (!(condition)) {                                                                                                   \
            Ryntra::Compiler::InternalCompilerError::raise("Assertion failed: " #condition, std::source_location::current()); \
        }                                                                                                                     \
    } while (false)

#define RYNTRA_UNREACHABLE()                                                                                  \
    do {                                                                                                      \
        Ryntra::Compiler::InternalCompilerError::raise("Unreachable Code.", std::source_location::current()); \
    } while (false)
