// ========== SourceRangeBuilder.h ==================================== *- C++ -* //
// Copyright (c) 2026 Remimwen Studio (Ryan "NvKopres" Almond).
// Licensed under Apache-2.0 License. See LICENSE for more info.
// ============================================================================== //

#pragma once

#include "SourceRange.h"
#include "antlr4-runtime.h"

/// \file
/// \brief Centralized ANTLR to \ref Ryntra::Compiler::SourceRange conversion.
/// \note This is the only header under \c Utility/ that pulls in the ANTLR runtime,
/// so it must stay out of broadly-included headers.

namespace Ryntra::Compiler {
    /// \brief Get the start position (line, column, offset) of the token.
    /// \param t The token, or \c nullptr
    /// \return The start position, or \c {0, 0, 0} for a null token
    inline SourceLocation tokenStart(antlr4::Token *t) {
        if (t == nullptr) {
            return {0, 0, 0};
        }
        return {static_cast<uint32_t>(t->getLine()),
            static_cast<uint32_t>(t->getCharPositionInLine()),
            static_cast<uint32_t>(t->getStartIndex())};
    }

    /// \brief Get the position just past the token, as required by a half-open range.
    /// \param t The token, or \c nullptr
    /// \return The exclusive end position, or \c {0, 0, 0} for a null token
    inline SourceLocation tokenEndExclusive(antlr4::Token *t) {
        if (t == nullptr || t->getType() == antlr4::Token::EOF) {
            return tokenStart(t);
        }

        const std::string text = t->getText();
        const size_t stopIndex = t->getStopIndex();
        const uint32_t offset = stopIndex == static_cast<size_t>(-1)
            ? static_cast<uint32_t>(t->getStartIndex()) + static_cast<uint32_t>(text.size())
            : static_cast<uint32_t>(stopIndex) + 1;

        uint32_t line = static_cast<uint32_t>(t->getLine());
        uint32_t column = static_cast<uint32_t>(t->getCharPositionInLine());
        for (const char c : text) {
            if (c == '\n') {
                ++line;
                column = 0;
            } else {
                ++column;
            }
        }
        return {line, column, offset};
    }

    /// \brief Build a half-open range spanning from \c beginTok through \c stopTok inclusive.
    /// \param beginTok The first token of the range
    /// \param stopTok The last token of the range, or \c nullptr
    /// \return The syntactic span \c [tokenStart(beginTok), end) ;
    /// when \c stopTok is null the range is empty at \c beginTok's start
    inline SourceRange makeSourceRange(antlr4::Token *beginTok, antlr4::Token *stopTok) {
        const SourceLocation begin = tokenStart(beginTok);
        if (stopTok == nullptr) {
            return {begin, begin};
        }
        if (stopTok->getType() == antlr4::Token::EOF) {
            return {begin, tokenStart(stopTok)};
        }
        return {begin, tokenEndExclusive(stopTok)};
    }

    /// \brief Build a half-open range covering a parser rule context.
    /// \param ctx The rule context, or \c nullptr
    /// \return The syntactic span of the context, or an empty range for \c nullptr
    inline SourceRange makeSourceRange(antlr4::ParserRuleContext *ctx) {
        if (ctx == nullptr) {
            return {{0, 0, 0}, {0, 0, 0}};
        }
        return makeSourceRange(ctx->getStart(), ctx->getStop());
    }

    /// \brief Build a half-open range covering a single terminal node.
    /// \param node The terminal node, or \c nullptr
    /// \return The syntactic span of the terminal, or an empty range for \c nullptr
    inline SourceRange makeSourceRange(antlr4::tree::TerminalNode *node) {
        if (node == nullptr) {
            return {{0, 0, 0}, {0, 0, 0}};
        }
        return makeSourceRange(node->getSymbol(), node->getSymbol());
    }
} // namespace Ryntra::Compiler
