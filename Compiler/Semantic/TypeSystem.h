#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>

namespace Ryntra::Compiler::Semantic {

    enum class TypeKind {
        PRIMITIVE,
        FUNCTION,
        VOID,
        UNKNOWN
    };

    class Type {
    public:
        virtual ~Type() = default;
        virtual TypeKind getKind() const = 0;
        virtual std::string toString() const = 0;
        virtual bool equals(const Type& other) const = 0;
    };

    class PrimitiveType : public Type {
    public:
        explicit PrimitiveType(std::string name) : name(std::move(name)) {}
        
        TypeKind getKind() const override { return TypeKind::PRIMITIVE; }
        
        std::string toString() const override { return name; }
        
        bool equals(const Type& other) const override {
            if (other.getKind() != TypeKind::PRIMITIVE) return false;
            return name == static_cast<const PrimitiveType&>(other).name;
        }

        const std::string& getName() const { return name; }

    private:
        std::string name;
    };

    class VoidType : public Type {
    public:
        TypeKind getKind() const override { return TypeKind::VOID; }
        std::string toString() const override { return "void"; }
        bool equals(const Type& other) const override {
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
                if (i > 0) s += ", ";
                s += paramTypes[i]->toString();
            }
            s += ") -> " + returnType->toString();
            return s;
        }

        bool equals(const Type& other) const override {
            if (other.getKind() != TypeKind::FUNCTION) return false;
            const auto& ft = static_cast<const FunctionType&>(other);
            if (!returnType->equals(*ft.returnType)) return false;
            if (paramTypes.size() != ft.paramTypes.size()) return false;
            for (size_t i = 0; i < paramTypes.size(); ++i) {
                if (!paramTypes[i]->equals(*ft.paramTypes[i])) return false;
            }
            return true;
        }

        std::shared_ptr<Type> getReturnType() const { return returnType; }
        const std::vector<std::shared_ptr<Type>>& getParamTypes() const { return paramTypes; }

    private:
        std::shared_ptr<Type> returnType;
        std::vector<std::shared_ptr<Type>> paramTypes;
    };

    // Helper to create types
    class TypeFactory {
    public:
        static std::shared_ptr<PrimitiveType> getPrimitive(const std::string& name) {
            return std::make_shared<PrimitiveType>(name);
        }
        static std::shared_ptr<VoidType> getVoid() {
            return std::make_shared<VoidType>();
        }
        static std::shared_ptr<FunctionType> getFunction(std::shared_ptr<Type> ret, std::vector<std::shared_ptr<Type>> params) {
            return std::make_shared<FunctionType>(std::move(ret), std::move(params));
        }
    };

} // namespace Ryntra::Compiler::Semantic
