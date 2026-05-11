#include "SymbolTable.h"

#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {

    void OverloadSet::addFunction(std::shared_ptr<FunctionSymbol> fn) {
        functions.push_back(std::move(fn));
    }

    SymbolTable::SymbolTable() {
        enterScope(); // Global scope

        auto voidType = std::make_shared<STType::VoidType>();
        auto int32Type = std::make_shared<STType::Int32Type>();
        auto int64Type = std::make_shared<STType::Int64Type>();
        auto stringType = std::make_shared<STType::StringType>();

        auto overloadSet = std::make_shared<OverloadSet>("__builtin_print");
        {
            std::vector<TypePtr> params;
            params.push_back(stringType);
            overloadSet->addFunction(
                std::make_shared<FunctionSymbol>("__builtin_print", voidType, std::move(params)));
        }
        {
            std::vector<TypePtr> params;
            params.push_back(int32Type);
            overloadSet->addFunction(
                std::make_shared<FunctionSymbol>("__builtin_print", voidType, std::move(params)));
        }
        {
            std::vector<TypePtr> params;
            params.push_back(int64Type);
            overloadSet->addFunction(
                std::make_shared<FunctionSymbol>("__builtin_print", voidType, std::move(params)));
        }

        scopes.back()->symbols["__builtin_print"] = std::move(overloadSet);
    }

    void SymbolTable::enterScope() {
        auto scope = std::make_unique<Scope>();
        scope->parent = scopes.empty() ? nullptr : scopes.back().get();
        scope->kind = Scope::Kind::Global;
        scopes.emplace_back(std::move(scope));
    }

    void SymbolTable::exitScope() {
        if (scopes.empty()) {
            ErrorHandler::getInstance().makeError("[RCE015]: No scope to exit", SourceLocation(0, 0));
            return;
        }
        scopes.pop_back();
    }

    void SymbolTable::define(std::shared_ptr<Symbol> symbol, SourceLocation location) {
        if (scopes.empty()) {
            ErrorHandler::getInstance().makeError("[RCE016]: No scope to define symbol", location);
            return;
        }
        auto& currentScope = scopes.back();
        if (currentScope->find(symbol->getName()) != nullptr) {
             ErrorHandler::getInstance().makeError("[RCE017]: Symbol '" + symbol->getName() + "' is already defined in the current scope.", location);
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
