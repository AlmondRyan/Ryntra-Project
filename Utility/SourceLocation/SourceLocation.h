// ========== SourceLocation.h ======================================== *- C++ -* //
// Copyright (c) 2026 Remimwen Studio (Ryan "NvKopres" Almond).
// Licensed under Apache-2.0 License. See LICENSE for more info.
// ============================================================================== //

#pragma once

namespace Ryntra::Compiler {
    /// \brief A simple structure represents the location in the source file.
    struct SourceLocation {
        int line;
        int column;

        /// \brief Constructor. Use default behavior.
        SourceLocation() = default;

        /// \brief Constructor. Accepts the \c line and \c column .
        /// \param _line Current line
        /// \param _column Current column
        SourceLocation(const int _line, const int _column) : line(_line), column(_column) {}
    };
} // namespace Ryntra::Compiler