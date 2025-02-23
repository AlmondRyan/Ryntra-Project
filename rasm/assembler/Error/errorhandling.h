#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <memory>

namespace Ryntra::rasm {
    enum class MessageType {
        Error,      // 严重错误，会导致汇编失败
        Warning,    // 警告，不会导致汇编失败但可能有潜在问题
        Info        // 信息性消息
    };

    class Message {
    public:
        Message(MessageType type, const std::string& msg, size_t line = 0)
            : type(type), message(msg), lineNumber(line) {}

        void print() const {
            switch (type) {
                case MessageType::Error:
                    std::cout << "[Error] ";
                    break;
                case MessageType::Warning:
                    std::cout << "[Warning] ";
                    break;
                case MessageType::Info:
                    std::cout << "[Info] ";
                    break;
            }
            if (lineNumber > 0) {
                std::cout << "at line " << lineNumber << ": ";
            }
            std::cout << message << std::endl;
        }

    private:
        MessageType type;
        std::string message;
        size_t lineNumber;
    };

    class ErrorHandler {
    public:
        static ErrorHandler& getInstance() {
            static ErrorHandler instance;
            return instance;
        }

        void addError(const std::string& msg, size_t line = 0) {
            messages.push_back(std::make_shared<Message>(MessageType::Error, msg, line));
            hasErrors = true;
        }

        void addWarning(const std::string& msg, size_t line = 0) {
            messages.push_back(std::make_shared<Message>(MessageType::Warning, msg, line));
        }

        void addInfo(const std::string& msg, size_t line = 0) {
            messages.push_back(std::make_shared<Message>(MessageType::Info, msg, line));
        }

        void printAll() const {
            for (const auto& msg : messages) {
                msg->print();
            }
        }

        [[nodiscard]] bool hasErrorMessages() const {
            return hasErrors;
        }

        void clear() {
            messages.clear();
            hasErrors = false;
        }

    private:
        ErrorHandler() = default;
        std::vector<std::shared_ptr<Message>> messages;
        bool hasErrors = false;
    };
} 