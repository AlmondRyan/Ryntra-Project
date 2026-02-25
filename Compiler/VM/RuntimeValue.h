#pragma once

#include "../IR/Type.h"
#include <string>
#include <variant>
#include <cstdint>

namespace Ryntra::Compiler::VM {
    struct RuntimeValue {
        std::variant<int32_t, std::string, std::monostate> value;

        RuntimeValue() : value(std::monostate{}) {}
        explicit RuntimeValue(int32_t i) : value(i) {}
        explicit RuntimeValue(const std::string& s) : value(s) {}

        bool isInt() const { return std::holds_alternative<int32_t>(value); }
        bool isString() const { return std::holds_alternative<std::string>(value); }
        bool isVoid() const { return std::holds_alternative<std::monostate>(value); }

        int32_t asInt() const { return std::get<int32_t>(value); }
        const std::string& asString() const { return std::get<std::string>(value); }

        std::string toString() const {
            if (isInt()) return std::to_string(asInt());
            if (isString()) return asString();
            return "void";
        }
    };
} // namespace Ryntra::Compiler::VM
