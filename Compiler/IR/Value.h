#pragma once

#include "Type.h"
#include <memory>
#include <string>

namespace Ryntra::IR {
    class Value {
    public:
        Value(std::shared_ptr<Type> type, const std::string &name = "")
            : type_(type), name_(name) {}

        virtual ~Value() = default;

        std::shared_ptr<Type> getType() const { return type_; }
        const std::string &getName() const { return name_; }
        void setName(const std::string &name) { name_ = name; }

        virtual std::string toString() const = 0;

        virtual std::string getReferenceName() const {
            return name_.empty() ? "" : "@" + name_;
        }

    protected:
        std::shared_ptr<Type> type_;
        std::string name_;
    };
} // namespace Ryntra::IR
