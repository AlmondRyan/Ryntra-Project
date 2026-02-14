#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include "SourceLocation/SourceLocation.h"

namespace Ryntra::Compiler::Semantic {
    class Symbol {
    public:
        virtual ~Symbol() = default;
        explicit Symbol(std::string name) : name(std::move(name)) {}
        const std::string& getName() const { return name; }
    private:
        std::string name;
    };

    class FunctionSymbol : public Symbol {
    public:
        FunctionSymbol(std::string name, std::string returnType, std::vector<std::string> paramTypes)
            : Symbol(std::move(name)), returnType(std::move(returnType)), paramTypes(std::move(paramTypes)) {}
        
        const std::string& getReturnType() const { return returnType; }
        const std::vector<std::string>& getParamTypes() const { return paramTypes; }

    private:
        std::string returnType;
        std::vector<std::string> paramTypes;
    };

    class SymbolTable {
    public:
        SymbolTable();
        
        void enterScope();
        void exitScope();
        
        void define(std::shared_ptr<Symbol> symbol, SourceLocation location);
        std::shared_ptr<Symbol> resolve(const std::string& name);

    private:
        std::vector<std::unordered_map<std::string, std::shared_ptr<Symbol>>> scopes;
    };
}
