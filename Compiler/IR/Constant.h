#pragma once

#include "Type.h"
#include "Value.h"
#include <cstdint>
#include <memory>
#include <string>
#include <variant>

namespace Ryntra::IR {
    class Constant : public Value {
    public:
        using ValueType = std::variant<int32_t, int64_t, std::string>;

        Constant(std::shared_ptr<Type> type, ValueType value, const std::string &name = "")
            : Value(type, name), value_(value) {}

        virtual ~Constant() = default;

        const ValueType &getValue() const { return value_; }

        std::string toString() const override {
            std::string result = name_.empty() ? "" : "@" + name_ + " = ";
            result += "global constant " + type_->toString() + " ";

            if (std::holds_alternative<int32_t>(value_)) {
                result += std::to_string(std::get<int32_t>(value_));
            } else if (std::holds_alternative<int64_t>(value_)) {
                result += std::to_string(std::get<int64_t>(value_));
            } else if (std::holds_alternative<std::string>(value_)) {
                std::string strValue = std::get<std::string>(value_);
                result += "\"" + escapeString(strValue) + "\"";
            }

            return result;
        }

        static std::shared_ptr<Constant> createInt32Constant(int32_t value, const std::string &name = "") {
            return std::make_shared<Constant>(Type::getInt32Type(), value, name);
        }

        static std::shared_ptr<Constant> createStringConstant(const std::string &value, const std::string &name = "") {
            return std::make_shared<Constant>(Type::getStringType(), value, name);
        }

        static std::shared_ptr<Constant> createInt64Constant(int64_t value, const std::string &name = "") {
            return std::make_shared<Constant>(Type::getInt64Type(), value, name);
        }

    private:
        static std::string escapeString(const std::string &str) {
            std::string result;
            for (char c : str) {
                switch (c) {
                case '\0':
                    result += "\\0";
                    break;
                case '\n':
                    result += "\\n";
                    break;
                case '\t':
                    result += "\\t";
                    break;
                case '\r':
                    result += "\\r";
                    break;
                case '\"':
                    result += "\\\"";
                    break;
                case '\\':
                    result += "\\\\";
                    break;
                default:
                    result += c;
                    break;
                }
            }
            return result;
        }

    private:
        ValueType value_;
    };
} // namespace Ryntra::IR