#pragma once

namespace Ryntra::Compiler {
    struct SourceLocation {
        int line;
        int column;

        SourceLocation() = default;
        SourceLocation(const int _line, const int _column) : line(_line), column(_column) {}
    };
}