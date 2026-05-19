#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <variant>
#include <vector>

namespace Ryntra::VM {
    class VMValue;

    struct ArrayData {
        std::vector<VMValue> elements;
    };

    // Runtime value representation
    class VMValue {
    public:
        enum class Type {
            Void,
            Int32,
            Int64,
            String,
            FunctionPtr,
            Array
        };

        using ValueData = std::variant<std::monostate, int32_t, int64_t, std::string, void *, std::shared_ptr<ArrayData>>;

        VMValue() : type_(Type::Void), data_(std::monostate{}) {}
        explicit VMValue(int32_t val) : type_(Type::Int32), data_(val) {}
        explicit VMValue(int64_t val) : type_(Type::Int64), data_(val) {}
        explicit VMValue(const std::string &val) : type_(Type::String), data_(val) {}
        explicit VMValue(void *ptr) : type_(Type::FunctionPtr), data_(ptr) {}
        explicit VMValue(std::shared_ptr<ArrayData> arr) : type_(Type::Array), data_(std::move(arr)) {}

        Type getType() const { return type_; }

        int32_t asInt32() const { return std::get<int32_t>(data_); }
        int64_t asInt64() const { return std::get<int64_t>(data_); }
        const std::string &asString() const { return std::get<std::string>(data_); }
        void *asFunctionPtr() const { return std::get<void *>(data_); }
        std::shared_ptr<ArrayData> asArray() const { return std::get<std::shared_ptr<ArrayData>>(data_); }

        bool isVoid() const { return type_ == Type::Void; }
        bool isInt32() const { return type_ == Type::Int32; }
        bool isInt64() const { return type_ == Type::Int64; }
        bool isString() const { return type_ == Type::String; }
        bool isArray() const { return type_ == Type::Array; }

    private:
        Type type_;
        ValueData data_;
    };
} // namespace Ryntra::VM
