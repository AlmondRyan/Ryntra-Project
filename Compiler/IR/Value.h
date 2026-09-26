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

        // Global values (constants, functions) use @; local SSA values use %
        virtual std::string getReferenceName() const {
            return name_.empty() ? "" : "@" + name_;
        }

        virtual bool isLocal() const { return false; }

    protected:
        std::shared_ptr<Type> type_;
        std::string name_;
    };

    // An incoming function parameter. Refers to the argument slot at `index` in
    // the callee frame; used to copy parameters into their alloca slots.
    class Argument : public Value {
    public:
        Argument(std::shared_ptr<Type> type, const std::string &name, int index)
            : Value(type, name), index_(index) {}

        int getIndex() const { return index_; }

        std::string toString() const override { return type_->toString() + " %" + name_; }
        std::string getReferenceName() const override { return name_.empty() ? "" : "%" + name_; }
        bool isLocal() const override { return true; }

    private:
        int index_;
    };
} // namespace Ryntra::IR
