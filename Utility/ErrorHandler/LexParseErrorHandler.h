#pragma once
#include "ErrorHandler.h"
#include "antlr4-runtime.h"

namespace Ryntra::Compiler {
    class LexParseErrorHandler : public antlr4::ANTLRErrorListener {
    public:
        void syntaxError(antlr4::Recognizer *recognizer,
                         antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
                         const std::string &msg, std::exception_ptr e) override {
            ErrorHandler::getInstance().makeError(msg, SourceLocation(line, charPositionInLine));
        }
    };
}