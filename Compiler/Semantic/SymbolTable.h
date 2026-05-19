#pragma once

#include "SourceLocation/SourceLocation.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace Ryntra::Compiler::Semantic {
    namespace STType {
        // clang-format off
        enum class TypeKind {
            Void,
            Bool,                     // i1
            Char,                     // unsigned i16, implicitly cast from int or to int is not allowed
            Int8,                     // byte
            Int16,
            Int32,                    // int or long (depends on the platform that vm runs on)
            Int64,                    // long long

            UnsignedInt8,
            UnsignedInt16,
            UnsignedInt32,
            UnsignedInt64,

            Float32,                  // float
            Float64,                  // double
            Float128,                 // decimal

            String,
            Array
        };
        // clang-format on

        class Type {
        public:
            virtual ~Type() = default;
            virtual TypeKind getKind() const = 0;

            bool isNumeric() const {
                TypeKind k = this->getKind();
                return (k >= TypeKind::Int8 && k <= TypeKind::Float128);
            }

            bool isIntegral() const {
                TypeKind k = this->getKind();
                return (k >= TypeKind::Int8 && k <= TypeKind::UnsignedInt64);
            }

            bool isCharacter() const {
                TypeKind k = this->getKind();
                return k == TypeKind::Char;
            }

            // Maybe there's more in the future
        };

        class VoidType : public Type {
        public:
            TypeKind getKind() const override { return TypeKind::Void; }
        };

        class Int32Type : public Type {
        public:
            TypeKind getKind() const override { return TypeKind::Int32; }
        };

        class Int64Type : public Type {
        public:
            TypeKind getKind() const override { return TypeKind::Int64; }
        };

        class StringType : public Type {
        public:
            TypeKind getKind() const override { return TypeKind::String; }
        };

        class BoolType : public Type {
        public:
            TypeKind getKind() const override { return TypeKind::Bool; }
        };

        class ArrayType : public Type {
        public:
            ArrayType(std::shared_ptr<Type> elementType) : elementType(std::move(elementType)) {}
            TypeKind getKind() const override { return TypeKind::Array; }
            const std::shared_ptr<Type> &getElementType() const { return elementType; }
        private:
            std::shared_ptr<Type> elementType;
        };

        // TODO: More in the future
    } // namespace STType

    using TypePtr = std::shared_ptr<STType::Type>;

    enum class SymbolKind {
        Variable,
        Function,
        OverloadSet,
        Type,
        Field
    };

    class Symbol {
    public:
        virtual ~Symbol() = default;
        explicit Symbol(std::string name) : name(std::move(name)) {}
        const std::string &getName() const { return name; }

        virtual SymbolKind getKind() const = 0;

    private:
        std::string name;
    };

    class FunctionSymbol : public Symbol {
    public:
        FunctionSymbol(std::string name, TypePtr returnType, std::vector<TypePtr> paramTypes)
            : Symbol(std::move(name)), returnType(std::move(returnType)), paramTypes(std::move(paramTypes)) {}

        const TypePtr &getReturnType() const { return returnType; }
        const std::vector<TypePtr> &getParamTypes() const { return paramTypes; }
        SymbolKind getKind() const override { return SymbolKind::Function; }

    private:
        TypePtr returnType;
        std::vector<TypePtr> paramTypes;
    };

    class VariableSymbol : public Symbol {
    public:
        VariableSymbol(std::string name, TypePtr type)
            : Symbol(std::move(name)), type(std::move(type)) {}

        const TypePtr &getType() const { return type; }
        SymbolKind getKind() const override { return SymbolKind::Variable; }

    private:
        TypePtr type;
    };

    class OverloadSet : public Symbol {
    public:
        OverloadSet(std::string name) : Symbol(std::move(name)) {}

        void addFunction(std::shared_ptr<FunctionSymbol> fn);
        const std::vector<std::shared_ptr<FunctionSymbol>> &getFunctions() const {
            return functions;
        }
        SymbolKind getKind() const override { return SymbolKind::OverloadSet; }

    private:
        std::vector<std::shared_ptr<FunctionSymbol>> functions;
    };

    class Scope {
    public:
        Scope *parent;

        enum class Kind {
            Global,
            Function,
            Block,
            Class
        } kind;

        std::shared_ptr<Symbol> find(const std::string &name) {
            auto iterator = symbols.find(name);
            if (iterator != symbols.end()) {
                return iterator->second;
            }

            if (parent) {
                return parent->find(name);
            }

            return nullptr;
        }

        std::unordered_map<std::string, std::shared_ptr<Symbol>> symbols;
    };

    class SymbolTable {
    public:
        SymbolTable();

        void enterScope();
        void exitScope();

        void define(std::shared_ptr<Symbol> symbol, SourceLocation location);
        std::shared_ptr<Symbol> resolve(const std::string &name);

    private:
        std::vector<std::unique_ptr<Scope>> scopes;
    };
} // namespace Ryntra::Compiler::Semantic
