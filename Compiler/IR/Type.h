#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Ryntra::IR {
    class Type {
    public:
        enum class Kind {
            Void,
            Int32,
            Int64,
            Bool,
            String,
            Function
        };

        Type(Kind kind) : kind_(kind) {}
        virtual ~Type() = default;

        Kind getKind() const { return kind_; }

        virtual std::string toString() const = 0;
        virtual bool isEqual(const Type *other) const = 0;

        bool isVoid() const { return kind_ == Kind::Void; }
        bool isInt32() const { return kind_ == Kind::Int32; }
        bool isInt64() const { return kind_ == Kind::Int64; }
        bool isBool() const { return kind_ == Kind::Bool; }
        bool isString() const { return kind_ == Kind::String; }
        bool isFunction() const { return kind_ == Kind::Function; }

        static std::shared_ptr<Type> getVoidType();
        static std::shared_ptr<Type> getInt32Type();
        static std::shared_ptr<Type> getInt64Type();
        static std::shared_ptr<Type> getBoolType();
        static std::shared_ptr<Type> getStringType();

    private:
        Kind kind_;
    };

    class VoidType : public Type {
    public:
        VoidType() : Type(Kind::Void) {}

        std::string toString() const override {
            return "void";
        }

        bool isEqual(const Type *other) const override {
            return other->isVoid();
        }
    };

    class Int32Type : public Type {
    public:
        Int32Type() : Type(Kind::Int32) {}

        std::string toString() const override {
            return "i32";
        }

        bool isEqual(const Type *other) const override {
            return other->isInt32();
        }
    };

    class Int64Type : public Type {
    public:
        Int64Type() : Type(Kind::Int64) {}

        std::string toString() const override {
            return "i64";
        }

        bool isEqual(const Type *other) const override {
            return other->isInt64();
        }
    };

    class BoolType : public Type {
    public:
        BoolType() : Type(Kind::Bool) {}

        std::string toString() const override {
            return "i1";
        }

        bool isEqual(const Type *other) const override {
            return other->isBool();
        }
    };

    class StringType : public Type {
    public:
        StringType() : Type(Kind::String) {}

        std::string toString() const override {
            return "string";
        }

        bool isEqual(const Type *other) const override {
            return other->isString();
        }
    };

    class FunctionType : public Type {
    public:
        FunctionType(std::shared_ptr<Type> returnType,
                     std::vector<std::shared_ptr<Type>> paramTypes)
            : Type(Kind::Function),
              returnType_(returnType),
              paramTypes_(paramTypes) {}

        std::shared_ptr<Type> getReturnType() const { return returnType_; }
        const std::vector<std::shared_ptr<Type>> &getParamTypes() const { return paramTypes_; }

        std::string toString() const override {
            std::string result = "(";
            for (size_t i = 0; i < paramTypes_.size(); ++i) {
                if (i > 0)
                    result += ", ";
                result += paramTypes_[i]->toString();
            }
            result += ") -> " + returnType_->toString();
            return result;
        }

        bool isEqual(const Type *other) const override {
            if (!other->isFunction())
                return false;
            const FunctionType *funcType = static_cast<const FunctionType *>(other);

            if (!returnType_->isEqual(funcType->returnType_.get()))
                return false;
            if (paramTypes_.size() != funcType->paramTypes_.size())
                return false;

            for (size_t i = 0; i < paramTypes_.size(); ++i) {
                if (!paramTypes_[i]->isEqual(funcType->paramTypes_[i].get()))
                    return false;
            }
            return true;
        }

    private:
        std::shared_ptr<Type> returnType_;
        std::vector<std::shared_ptr<Type>> paramTypes_;
    };

    inline std::shared_ptr<Type> Type::getVoidType() {
        static std::shared_ptr<Type> voidType = std::make_shared<VoidType>();
        return voidType;
    }

    inline std::shared_ptr<Type> Type::getInt32Type() {
        static std::shared_ptr<Type> int32Type = std::make_shared<Int32Type>();
        return int32Type;
    }

    inline std::shared_ptr<Type> Type::getStringType() {
        static std::shared_ptr<Type> stringType = std::make_shared<StringType>();
        return stringType;
    }

    inline std::shared_ptr<Type> Type::getInt64Type() {
        static std::shared_ptr<Type> int64Type = std::make_shared<Int64Type>();
        return int64Type;
    }

    inline std::shared_ptr<Type> Type::getBoolType() {
        static std::shared_ptr<Type> boolType = std::make_shared<BoolType>();
        return boolType;
    }
} // namespace Ryntra::IR
