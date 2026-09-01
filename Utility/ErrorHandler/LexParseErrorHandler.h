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
        enum class ErrorCode : int {
            SYNTAX_ERROR = 83,
            MISSING_TOKEN = 84,
            UNEXPECTED_TOKEN = 85,
            EXTRA_TOKEN = 86,
            UNRECOGNIZED_TOKEN = 87,
            AMBIGUOUS_GRAMMAR = 88,
            LEXER_ERROR = 89,
            NO_VIABLE_ALT = 90,
            INPUT_MISMATCH = 91,
            FAILED_PREDICATE = 92
        };

        /// \brief Override the \c syntaxError() function in ANTLR runtime.
        /// Use our error handler to make sure the format consistency.
        void syntaxError(antlr4::Recognizer *recognizer,
                         antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
                         const std::string &msg, std::exception_ptr e) override;

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

        ErrorCode determineErrorCode(antlr4::RecognitionException *e, const std::string &msg);
    };
}