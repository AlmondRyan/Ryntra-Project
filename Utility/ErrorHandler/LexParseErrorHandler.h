// ========== LexParseErrorHandler.h ================================== *- C++ -* //
// Copyright (c) 2026 Remimwen Studio (Ryan "NvKopres" Almond).
// Licensed under Apache-2.0 License. See LICENSE for more info.
// ============================================================================== //
#pragma once
#include "ErrorHandler.h"
#include "antlr4-runtime.h"

namespace Ryntra::Compiler {
    class LexParseErrorHandler : public antlr4::ANTLRErrorListener {
    public:
        /// \brief Override the \c syntaxError() function in ANTLR runtime.
        /// Use our error handler to make sure the format consistency.
        void syntaxError(antlr4::Recognizer *recognizer,
                         antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
                         const std::string &msg, std::exception_ptr e) override {
            ErrorHandler::getInstance().makeError(msg, SourceLocation(static_cast<int>(line),
                static_cast<int>(charPositionInLine)));
        }

        /// \brief Override the \c reportAmbiguity() function in ANTLR runtime.
        /// Now it's an empty implementation.
        void reportAmbiguity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa,
            size_t startIndex, size_t stopIndex, bool exact, const antlrcpp::BitSet &ambigAlts,
            antlr4::atn::ATNConfigSet *configs) override {}

        /// \brief Override the \c reportAttemptingFullContext() function in ANTLR runtime.
        /// Now it's an empty implementation.
        void reportAttemptingFullContext(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa,
            size_t startIndex, size_t stopIndex, const antlrcpp::BitSet &conflictingAlts,
            antlr4::atn::ATNConfigSet *configs) override {}

        /// \brief Override the \c reportContextSensitivity() function in ANTLR runtime.
        /// Now it's an empty implementation.
        void reportContextSensitivity(antlr4::Parser *recognizer, const antlr4::dfa::DFA &dfa,
            size_t startIndex, size_t stopIndex, size_t prediction,
            antlr4::atn::ATNConfigSet *configs) override {}
    };
}