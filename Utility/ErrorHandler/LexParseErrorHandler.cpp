#include "LexParseErrorHandler.h"
#include "antlr4-runtime.h"

namespace Ryntra::Compiler {
    LexParseErrorHandler::ErrorCode LexParseErrorHandler::determineErrorCode(antlr4::RecognitionException *e, const std::string &msg) {
        if (!e) {
            return ErrorCode::SYNTAX_ERROR;
        }

        if (dynamic_cast<antlr4::NoViableAltException *>(e)) {
            return ErrorCode::NO_VIABLE_ALT;
        } else if (dynamic_cast<antlr4::InputMismatchException *>(e)) {
            return ErrorCode::INPUT_MISMATCH;
        } else if (dynamic_cast<antlr4::FailedPredicateException *>(e)) {
            return ErrorCode::FAILED_PREDICATE;
        } else if (dynamic_cast<antlr4::LexerNoViableAltException *>(e)) {
            return ErrorCode::LEXER_ERROR;
        }

        if (msg.find("missing") != std::string::npos) {
            return ErrorCode::MISSING_TOKEN;
        } else if (msg.find("extraneous") != std::string::npos) {
            return ErrorCode::EXTRA_TOKEN;
        } else if (msg.find("mismatched") != std::string::npos) {
            return ErrorCode::UNEXPECTED_TOKEN;
        } else if (msg.find("no viable") != std::string::npos) {
            return ErrorCode::NO_VIABLE_ALT;
        }

        return ErrorCode::SYNTAX_ERROR;
    }

    void LexParseErrorHandler::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr e) {
        antlr4::RecognitionException *exception = nullptr;
        try {
            if (e) {
                std::rethrow_exception(e);
            }
        } catch (antlr4::RecognitionException &re) {
            exception = &re;
        } catch (...) {
            // maybe something here
        }

        auto errorCode = determineErrorCode(exception, msg);
        std::string offendingText;
        if (offendingSymbol) {
            offendingText = offendingSymbol->getText();
            if (offendingText.empty()) {
                offendingText = "<EOF>";
            }
        }

        std::string errorMsg;
        switch (errorCode) {
        case ErrorCode::SYNTAX_ERROR:
            errorMsg = "Syntax error";
            break;
        case ErrorCode::MISSING_TOKEN:
            errorMsg = "Missing symbol";
            break;
        case ErrorCode::UNEXPECTED_TOKEN:
            errorMsg = "Unexpected symbol";
            break;
        case ErrorCode::EXTRA_TOKEN:
            errorMsg = "Extra symbol";
            break;
        case ErrorCode::UNRECOGNIZED_TOKEN:
            errorMsg = "Unrecognized symbol";
            break;
        case ErrorCode::AMBIGUOUS_GRAMMAR:
            errorMsg = "Ambiguous grammar";
            break;
        case ErrorCode::LEXER_ERROR:
            errorMsg = "Lexer error";
            break;
        case ErrorCode::NO_VIABLE_ALT:
            errorMsg = "No matching grammar branch";
            break;
        case ErrorCode::INPUT_MISMATCH:
            errorMsg = "Mismatch input";
            break;
        case ErrorCode::FAILED_PREDICATE:
            errorMsg = "Cannot verify the predicate";
            break;
        default:
            errorMsg = "Unknown error";
            break;
        }

        std::string description = "[RCE0" + std::to_string(static_cast<int>(errorCode)) + "]: " + errorMsg;
        ErrorHandler::getInstance().makeError(description, {static_cast<uint32_t>(line),
        static_cast<uint32_t>(charPositionInLine), static_cast<uint32_t>(offendingSymbol->getStartIndex())});
    }
} // namespace Ryntra::Compiler