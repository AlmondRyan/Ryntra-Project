#pragma once

#include "Type.h"
#include <string>

namespace Ryntra::Compiler {
    class Value {
    public:
        virtual ~Value() = default;
        Type *getType() const { return type; }
        std::string getName() const { return name; }
        void setName(const std::string &n) { name = n; }

        virtual std::string toString() const;

    protected:
        Value(Type *ty, const std::string &name = "") : type(ty), name(name) {}
        Type *type;
        std::string name;
    };
} // namespace Ryntra::Compiler
