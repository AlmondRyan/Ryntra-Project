#pragma once

#include <string>
#include <variant>
#include <memory>

namespace Ryntra::VM {
    // Runtime value representation
    class VMValue {
    public:
        enum class Type {
            Void,
            Int32,
            String,
            FunctionPtr
        };

        using ValueData = std::variant<std::monostate, int32_t, std::string, void*>;

        VMValue() : type_(Type::Void), data_(std::monostate{}) {}
        explicit VMValue(int32_t val) : type_(Type::Int32), data_(val) {}
        explicit VMValue(const std::string& val) : type_(Type::String), data_(val) {}
        explicit VMValue(void* ptr) : type_(Type::FunctionPtr), data_(ptr) {}

        Type getType() const { return type_; }

        int32_t asInt32() const { return std::get<int32_t>(data_); }
        const std::string& asString() const { return std::get<std::string>(data_); }
        void* asFunctionPtr() const { return std::get<void*>(data_); }

        bool isVoid() const { return type_ == Type::Void; }
        bool isInt32() const { return type_ == Type::Int32; }
        bool isString() const { return type_ == Type::String; }

    private:
        Type type_;
        ValueData data_;
    };
} // namespace Ryntra::VM
