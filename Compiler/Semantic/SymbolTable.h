#pragma once

#include "SourceLocation/SourceRange.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace Ryntra::Compiler::Semantic {
    class Scope;
    class Symbol;
    class FunctionSymbol;
    class FieldSymbol;

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
            Array,
            Reference,
            Pointer,
            Function,
            Struct
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

        class ReferenceType : public Type {
        public:
            ReferenceType(std::shared_ptr<Type> elementType) : elementType(std::move(elementType)) {}
            TypeKind getKind() const override { return TypeKind::Reference; }
            const std::shared_ptr<Type> &getElementType() const { return elementType; }
        private:
            std::shared_ptr<Type> elementType;
        };

        class PointerType : public Type {
        public:
            PointerType(std::shared_ptr<Type> elementType) : elementType(std::move(elementType)) {}
            TypeKind getKind() const override { return TypeKind::Pointer; }
            const std::shared_ptr<Type> &getElementType() const { return elementType; }
        private:
            std::shared_ptr<Type> elementType;
        };

        class FunctionType : public Type {
        public:
            FunctionType(std::shared_ptr<Type> returnType, std::vector<std::shared_ptr<Type>> paramTypes)
                : returnType(std::move(returnType)), paramTypes(std::move(paramTypes)) {}
            TypeKind getKind() const override { return TypeKind::Function; }
            const std::shared_ptr<Type> &getReturnType() const { return returnType; }
            const std::vector<std::shared_ptr<Type>> &getParamTypes() const { return paramTypes; }
        private:
            std::shared_ptr<Type> returnType;
            std::vector<std::shared_ptr<Type>> paramTypes;
        };

        class StructType : public Type {
        public:
            explicit StructType(std::string name);
            ~StructType() override;

            TypeKind getKind() const override { return TypeKind::Struct; }
            const std::string &getName() const { return name; }

            // Registers a field type and the matching FieldSymbol in the member scope.
            void addField(const std::string &fieldName, std::shared_ptr<Type> fieldType);
            std::shared_ptr<Type> getField(const std::string &fieldName) const {
                auto it = fields.find(fieldName);
                return it == fields.end() ? nullptr : it->second;
            }
            const std::unordered_map<std::string, std::shared_ptr<Type>> &getFields() const { return fields; }

            // Member symbol table (fields and methods). The scope has `Scope::Kind::Class`.
            void defineMethod(std::shared_ptr<FunctionSymbol> method);
            std::shared_ptr<Symbol> lookupMember(const std::string &memberName) const;
            Scope &getMemberScope() const;

        private:
            void ensureMemberScope() const;

            std::string name;
            std::unordered_map<std::string, std::shared_ptr<Type>> fields;
            mutable std::shared_ptr<Scope> memberScope;
        };
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

    class FieldSymbol : public Symbol {
    public:
        FieldSymbol(std::string name, TypePtr type)
            : Symbol(std::move(name)), type(std::move(type)) {}

        const TypePtr &getType() const { return type; }
        SymbolKind getKind() const override { return SymbolKind::Field; }

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

    class TypeSymbol : public Symbol {
    public:
        TypeSymbol(std::string name, TypePtr type)
            : Symbol(std::move(name)), type(std::move(type)) {}

        const TypePtr &getType() const { return type; }
        SymbolKind getKind() const override { return SymbolKind::Type; }

    private:
        TypePtr type;
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

        void enterScope(Scope::Kind kind = Scope::Kind::Global);
        void exitScope();

        void define(std::shared_ptr<Symbol> symbol, const SourceRange &range);
        std::shared_ptr<Symbol> resolve(const std::string &name);

        // True if the symbol is an entity whose address can be taken
        // (a variable or a function; `Type`/`Field` symbols are not addressable).
        static bool isAddressable(const std::shared_ptr<Symbol> &symbol);

    private:
        std::vector<std::unique_ptr<Scope>> scopes;
    };
} // namespace Ryntra::Compiler::Semantic
