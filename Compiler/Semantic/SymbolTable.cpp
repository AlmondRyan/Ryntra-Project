#include "SymbolTable.h"

#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {

    SymbolTable::SymbolTable() {
        enterScope(); // Global scope

        // vvv This definitely not the final version, it just a placeholder that type is declared in string. vvv
        define(std::make_shared<FunctionSymbol>("__builtin_print", "void", std::vector<std::string>{"string"}), SourceLocation(0, 0));
    }

    void SymbolTable::enterScope() {
        scopes.emplace_back();
    }

    void SymbolTable::exitScope() {
        if (scopes.empty()) {
            ErrorHandler::getInstance().makeError("SymbolTable: No scope to exit", SourceLocation(0, 0));
            return;
        }
        scopes.pop_back();
    }

    void SymbolTable::define(std::shared_ptr<Symbol> symbol, SourceLocation location) {
        if (scopes.empty()) {
            ErrorHandler::getInstance().makeError("SymbolTable: No scope to define symbol", location);
            return;
        }
        auto& currentScope = scopes.back();
        if (currentScope.find(symbol->getName()) != currentScope.end()) {
             ErrorHandler::getInstance().makeError("Symbol '" + symbol->getName() + "' is already defined in the current scope.", location);
             return;
        }
        currentScope[symbol->getName()] = std::move(symbol);
    }

    std::shared_ptr<Symbol> SymbolTable::resolve(const std::string& name) {
        for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
            auto found = it->find(name);
            if (found != it->end()) {
                return found->second;
            }
        }
        return nullptr;
    }

}
