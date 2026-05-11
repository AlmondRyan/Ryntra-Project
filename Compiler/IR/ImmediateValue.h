#pragma once

#include "Value.h"
#include <string>

namespace Ryntra::IR {
    class ImmediateValue : public Value {
    public:
        ImmediateValue(std::shared_ptr<Type> type, const std::string &literalValue)
            : Value(type, ""), literalValue_(literalValue) {}

        std::string toString() const override {
            return type_->toString() + " " + literalValue_;
        }

        std::string getReferenceName() const override {
            return toString();
        }

        const std::string& getLiteralValue() const { return literalValue_; }

    private:
        std::string literalValue_;
    };
} // namespace Ryntra::IR
