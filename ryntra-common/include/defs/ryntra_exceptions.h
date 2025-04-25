#pragma once
#ifndef RYNTRA_EXCEPTIONS
#define RYNTRA_EXCEPTIONS

#include <exception>
#include <string>

namespace Ryntra::Exceptions {
    class WindowsVersionNotSupported : public std::exception {
    public:
        explicit WindowsVersionNotSupported(const std::string& message)
            : m_message(message) {}

        const char* what() const noexcept override {
            return m_message.c_str();
        }

    private:
        std::string m_message;
    };
} // namespace Ryntra::Exceptions

#endif