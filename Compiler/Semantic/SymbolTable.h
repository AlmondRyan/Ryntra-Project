#pragma once
#include "Symbol.h"
#include <map>
#include <string>
#include <optional>

namespace Ryntra::Compiler {
    class SymbolTable {
    public:
        SymbolTable() {
            registerBuiltinFunction();
        }

        bool addSymbol(const Symbol &symbol) {
            auto [it, inserted] = symbols.emplace(symbol.name, symbol);
            return inserted;
        }

        std::optional<Symbol> lookupSymbol(const std::string &name) const {
            auto it = symbols.find(name);
            if (it != symbols.end()) {
                return it->second;
            }
            return std::nullopt;
        }

        bool addFunction(const FunctionSymbol& func) {
            auto [it, inserted] = functions.emplace(func.name, func);
            return inserted;
        }

        std::optional<FunctionSymbol> lookupFunction(const std::string& name) const {
            auto it = functions.find(name);
            if (it != functions.end()) {
                return it->second;
            }
            return std::nullopt;
        }

        bool isSymbolExists(const std::string& name) const {
            return symbols.find(name) != symbols.end();
        }

        bool isFunctionExists(const std::string& name) const {
            return functions.find(name) != functions.end();
        }

        const std::map<std::string, Symbol>& getAllSymbols() const {
            return symbols;
        }

        const std::map<std::string, FunctionSymbol>& getAllFunctions() const {
            return functions;
        }

        void clear() {
            symbols.clear();
            registerBuiltinFunction();
        }
    private:
        void registerBuiltinFunction() {
            FunctionSymbol sBuiltinPrint;
            sBuiltinPrint.name = "__builtin_print";
            sBuiltinPrint.returnType = {TypeKind::Void, ""};
            Symbol stringParam({TypeKind::String, ""}, "value", SymbolKind::Parameter);
            sBuiltinPrint.parameters.push_back(stringParam);

            FunctionSymbol sBuiltinIntToString;
            sBuiltinIntToString.name = "__builtin_intToString";
            sBuiltinIntToString.returnType = {TypeKind::String, ""};
            Symbol intParam({TypeKind::Int, ""}, "value", SymbolKind::Parameter);
            sBuiltinIntToString.parameters.push_back(intParam);

            functions.emplace(sBuiltinPrint.name, sBuiltinPrint);
            functions.emplace(sBuiltinIntToString.name, sBuiltinIntToString);
        }
    public:
        void enterScope() {
            scopeStack.emplace_back();
        }

        void exitScope() {
            if (!scopeStack.empty()) {
                scopeStack.pop_back();
            }
        }

        bool addSymbolToCurrentScope(const Symbol& symbol) {
            if (scopeStack.empty()) {
                return addSymbol(symbol);
            }

            auto& currentScope = scopeStack.back();
            auto [it, inserted] = currentScope.emplace(symbol.name, symbol);
            return inserted;
        }

        std::optional<Symbol> lookupSymbolInScopes(const std::string& name) const {
            for (auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it) {
                auto symbolIt = it->find(name);
                if (symbolIt != it->end()) {
                    return symbolIt->second;
                }
            }

            return lookupSymbol(name);
        }
    private:
        std::map<std::string, Symbol> symbols;                  // Variables
        std::map<std::string, FunctionSymbol> functions;        // Functions
        std::vector<std::map<std::string, Symbol>> scopeStack;
    };

    inline Type createIntType() {
        return {TypeKind::Int, ""};
    }

    inline Type createStringType() {
        return {TypeKind::String, ""};
    }

    inline Type createCustomType(const std::string& name) {
        return {TypeKind::Custom, name};
    }

    inline Symbol createVariableSymbol(const std::string& name, const Type& type) {
        return Symbol(type, name, SymbolKind::Variable);
    }

    inline Symbol createParameterSymbol(const std::string& name, const Type& type) {
        return Symbol(type, name, SymbolKind::Parameter);
    }

    inline Symbol createGlobalSymbol(const std::string& name, const Type& type) {
        return Symbol(type, name, SymbolKind::Global);
    }
}