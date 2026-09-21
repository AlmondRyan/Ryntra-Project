// ========== SourceRange.h =========================================== *- C++ -* //
// Copyright (c) 2026 Remimwen Studio (Ryan "NvKopres" Almond).
// Licensed under Apache-2.0 License. See LICENSE for more info.
// ============================================================================== //

#pragma once

#include "SourceLocation.h"
#include <utility>

namespace Ryntra::Compiler {
    /// \brief A half-open source range \c [begin, end) , left-closed and right-open.
    /// \note \c end points just past the last character of the range. For a point
    /// location both ends are equal, making the range empty.
    struct SourceRange {
        SourceLocation begin;
        SourceLocation end;

        /// \brief Constructor. Use default behavior.
        SourceRange() = default;

        /// \brief Constructor. Accepts the exclusive \c begin and \c end .
        /// \param b The first position of the range
        /// \param e The position just past the last character of the range
        SourceRange(SourceLocation b, SourceLocation e) : begin(std::move(b)), end(std::move(e)) {}

        /// \brief Constructor. Builds an empty half-open range at the point \c p .
        /// \param p The point location
        explicit SourceRange(const SourceLocation &p) : begin(p), end(p) {}

        /// \brief Check whether the range is empty, i.e. both ends are the same point.
        /// \return \c true when \c begin equals \c end , otherwise \c false
        [[nodiscard]] bool isEmpty() const {
            return begin.line == end.line
                && begin.column == end.column
                && begin.offset == end.offset;
        }
    };
} // namespace Ryntra::Compiler
