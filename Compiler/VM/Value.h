#pragma once

#include <iostream>
#include <string>
#include <variant>

namespace Ryntra::Compiler::VM {
    struct Value {
        enum class Type {
            Integer,
            String,
            Void
        } type;

        int intVal = 0;
        std::string strVal;

        Value() : type(Type::Void) {}
        Value(int v) : type(Type::Integer), intVal(v) {}
        Value(const std::string &s) : type(Type::String), strVal(s) {}

        std::string toString() const {
            if (type == Type::Integer)
                return std::to_string(intVal);
            if (type == Type::String)
                return strVal;
            return "void";
        }
    };

} // namespace Ryntra::Compiler::VM
