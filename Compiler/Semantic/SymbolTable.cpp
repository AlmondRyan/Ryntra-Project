#include "SymbolTable.h"

#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {

    SymbolTable::SymbolTable() {
        enterScope(); // Global scope

        auto voidType = std::make_shared<STType::VoidType>();
        // auto int32Type = std::make_shared<Type::Int32Type>();
        auto stringType = std::make_shared<STType::StringType>();

        std::vector<TypePtr> paramTypes;
        paramTypes.push_back(stringType);
        
        define(std::make_shared<FunctionSymbol>("__builtin_print", voidType, std::move(paramTypes)),
            SourceLocation(0, 0));
    }

    void SymbolTable::enterScope() {
        auto scope = std::make_unique<Scope>();
        scope->parent = scopes.empty() ? nullptr : scopes.back().get();
        scope->kind = Scope::Kind::Global;
        scopes.emplace_back(std::move(scope));
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
        if (currentScope->find(symbol->getName()) != nullptr) {
             ErrorHandler::getInstance().makeError("Symbol '" + symbol->getName() + "' is already defined in the current scope.", location);
             return;
        }
        currentScope->symbols[symbol->getName()] = std::move(symbol);
    }

    std::shared_ptr<Symbol> SymbolTable::resolve(const std::string& name) {
        if (scopes.empty()) {
            return nullptr;
        }
        return scopes.back()->find(name);
    }

}
