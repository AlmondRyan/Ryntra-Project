#pragma once

#include <string>
#include <vector>

namespace Ryntra::Compiler {
    enum class TypeKind {
        Int,
        String,
        Void,
        Custom,
        ErrorType
    };

    enum class SymbolKind {
        Variable,
        Parameter,
        Global
    };

    struct Type {
        TypeKind kind;
        std::string name;  // when kind == Custom
    };

    struct Symbol {
        Type type;
        std::string name;
        SymbolKind symbolKind;

        Symbol(Type _t, std::string _n, SymbolKind _sk) : type(_t), name(_n), symbolKind(_sk) {}
    };

    struct FunctionSymbol {
        std::string name;
        Type returnType;
        std::vector<Symbol> parameters;

        // std::string signature() const; || Implement in the future.
    };
}