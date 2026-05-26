#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace Ryntra::Compiler::Semantic {

    enum class TypeKind {
        PRIMITIVE,
        FUNCTION,
        VOID,
        UNKNOWN,
        ARRAY,
        REFERENCE,
        POINTER
    };

    class Type {
    public:
        virtual ~Type() = default;
        virtual TypeKind getKind() const = 0;
        virtual std::string toString() const = 0;
        virtual bool equals(const Type &other) const = 0;
    };

    class PrimitiveType : public Type {
    public:
        explicit PrimitiveType(std::string name) : name(std::move(name)) {}

        TypeKind getKind() const override { return TypeKind::PRIMITIVE; }

        std::string toString() const override { return name; }

        bool equals(const Type &other) const override {
            if (other.getKind() != TypeKind::PRIMITIVE)
                return false;
            return name == static_cast<const PrimitiveType &>(other).name;
        }

        const std::string &getName() const { return name; }

    private:
        std::string name;
    };

    class ArrayType : public Type {
    public:
        ArrayType(std::shared_ptr<Type> elementType) : elementType(std::move(elementType)) {}

        TypeKind getKind() const override { return TypeKind::ARRAY; }

        std::string toString() const override {
            return elementType->toString() + "[]";
        }

        bool equals(const Type &other) const override {
            if (other.getKind() != TypeKind::ARRAY)
                return false;
            return elementType->equals(*static_cast<const ArrayType &>(other).elementType);
        }

        std::shared_ptr<Type> getElementType() const { return elementType; }

    private:
        std::shared_ptr<Type> elementType;
    };

    class ReferenceType : public Type {
    public:
        ReferenceType(std::shared_ptr<Type> elementType) : elementType(std::move(elementType)) {}

        TypeKind getKind() const override { return TypeKind::REFERENCE; }

        std::string toString() const override {
            return "ref<" + elementType->toString() + ">";
        }

        bool equals(const Type &other) const override {
            if (other.getKind() != TypeKind::REFERENCE)
                return false;
            return elementType->equals(*static_cast<const ReferenceType &>(other).elementType);
        }

        std::shared_ptr<Type> getElementType() const { return elementType; }

    private:
        std::shared_ptr<Type> elementType;
    };

    class PointerType : public Type {
    public:
        PointerType(std::shared_ptr<Type> elementType) : elementType(std::move(elementType)) {}

        TypeKind getKind() const override { return TypeKind::POINTER; }

        std::string toString() const override {
            return "ptr<" + elementType->toString() + ">";
        }

        bool equals(const Type &other) const override {
            if (other.getKind() != TypeKind::POINTER)
                return false;
            return elementType->equals(*static_cast<const PointerType &>(other).elementType);
        }

        std::shared_ptr<Type> getElementType() const { return elementType; }

    private:
        std::shared_ptr<Type> elementType;
    };

    class VoidType : public Type {
    public:
        TypeKind getKind() const override { return TypeKind::VOID; }
        std::string toString() const override { return "void"; }
        bool equals(const Type &other) const override {
            return other.getKind() == TypeKind::VOID;
        }
    };

    class FunctionType : public Type {
    public:
        FunctionType(std::shared_ptr<Type> returnType, std::vector<std::shared_ptr<Type>> paramTypes)
            : returnType(std::move(returnType)), paramTypes(std::move(paramTypes)) {}

        TypeKind getKind() const override { return TypeKind::FUNCTION; }

        std::string toString() const override {
            std::string s = "fn(";
            for (size_t i = 0; i < paramTypes.size(); ++i) {
                if (i > 0)
                    s += ", ";
                s += paramTypes[i]->toString();
            }
            s += ") -> " + returnType->toString();
            return s;
        }

        bool equals(const Type &other) const override {
            if (other.getKind() != TypeKind::FUNCTION)
                return false;
            const auto &ft = static_cast<const FunctionType &>(other);
            if (!returnType->equals(*ft.returnType))
                return false;
            if (paramTypes.size() != ft.paramTypes.size())
                return false;
            for (size_t i = 0; i < paramTypes.size(); ++i) {
                if (!paramTypes[i]->equals(*ft.paramTypes[i]))
                    return false;
            }
            return true;
        }

        std::shared_ptr<Type> getReturnType() const { return returnType; }
        const std::vector<std::shared_ptr<Type>> &getParamTypes() const { return paramTypes; }

    private:
        std::shared_ptr<Type> returnType;
        std::vector<std::shared_ptr<Type>> paramTypes;
    };

    // Helper to create types
    class TypeFactory {
    public:
        static std::shared_ptr<PrimitiveType> getPrimitive(const std::string &name) {
            return std::make_shared<PrimitiveType>(name);
        }
        static std::shared_ptr<VoidType> getVoid() {
            return std::make_shared<VoidType>();
        }
        static std::shared_ptr<FunctionType> getFunction(std::shared_ptr<Type> ret, std::vector<std::shared_ptr<Type>> params) {
            return std::make_shared<FunctionType>(std::move(ret), std::move(params));
        }
        static std::shared_ptr<ArrayType> getArray(std::shared_ptr<Type> elementType) {
            return std::make_shared<ArrayType>(std::move(elementType));
        }
        static std::shared_ptr<ReferenceType> getReference(std::shared_ptr<Type> elementType) {
            return std::make_shared<ReferenceType>(std::move(elementType));
        }
        static std::shared_ptr<PointerType> getPointer(std::shared_ptr<Type> elementType) {
            return std::make_shared<PointerType>(std::move(elementType));
        }
    };

} // namespace Ryntra::Compiler::Semantic
