#include "SymbolTable.h"

#include "ErrorHandler/ErrorHandler.h"
#include "ErrorHandler/InternalCompilerError.h"

namespace Ryntra::Compiler::Semantic {

    void OverloadSet::addFunction(std::shared_ptr<FunctionSymbol> fn) {
        functions.push_back(std::move(fn));
    }

    namespace STType {
        StructType::StructType(std::string name) : name(std::move(name)) {}

        StructType::~StructType() = default;

        void StructType::ensureMemberScope() const {
            if (!memberScope) {
                memberScope = std::make_shared<Scope>();
                memberScope->parent = nullptr;
                memberScope->kind = Scope::Kind::Class;
            }
        }

        void StructType::addField(const std::string &fieldName, std::shared_ptr<Type> fieldType) {
            if (fields.find(fieldName) == fields.end()) {
                fieldOrder.push_back(fieldName);
            }
            fields[fieldName] = fieldType;
            ensureMemberScope();
            memberScope->symbols[fieldName] = std::make_shared<FieldSymbol>(fieldName, std::move(fieldType));
        }

        void StructType::defineMethod(std::shared_ptr<FunctionSymbol> method) {
            ensureMemberScope();

            auto &symbols = memberScope->symbols;
            auto iterator = symbols.find(method->getName());
            if (iterator == symbols.end()) {
                auto overloadSet = std::make_shared<OverloadSet>(method->getName());
                overloadSet->addFunction(std::move(method));
                symbols[overloadSet->getName()] = std::move(overloadSet);
                return;
            }

            if (auto overloadSet = std::dynamic_pointer_cast<OverloadSet>(iterator->second)) {
                for (const auto &existing : overloadSet->getFunctions()) {
                    if (existing->getParamTypes().size() != method->getParamTypes().size()) {
                        continue;
                    }
                    bool match = true;
                    for (size_t i = 0; i < existing->getParamTypes().size(); ++i) {
                        if (existing->getParamTypes()[i]->getKind() != method->getParamTypes()[i]->getKind()) {
                            match = false;
                            break;
                        }
                    }
                    if (match) {
                        return; // Already registered
                    }
                }
                overloadSet->addFunction(std::move(method));
                return;
            }

            // A member with the same name is not an overload set (e.g. a field):
            // replace it with a fresh overload set for the method.
            auto overloadSet = std::make_shared<OverloadSet>(method->getName());
            overloadSet->addFunction(std::move(method));
            symbols[overloadSet->getName()] = std::move(overloadSet);
        }

        std::shared_ptr<Symbol> StructType::lookupMember(const std::string &memberName) const {
            if (!memberScope) {
                return nullptr;
            }
            return memberScope->find(memberName);
        }

        Scope &StructType::getMemberScope() const {
            ensureMemberScope();
            return *memberScope;
        }
    } // namespace STType

    SymbolTable::SymbolTable() {
        enterScope(Scope::Kind::Global); // Global scope

        auto voidType = std::make_shared<STType::VoidType>();
        auto int32Type = std::make_shared<STType::Int32Type>();
        auto int64Type = std::make_shared<STType::Int64Type>();
        auto stringType = std::make_shared<STType::StringType>();
        auto boolType = std::make_shared<STType::BoolType>();

        scopes.back()->symbols["void"] = std::make_shared<TypeSymbol>("void", voidType);
        scopes.back()->symbols["int"] = std::make_shared<TypeSymbol>("int", int32Type);
        scopes.back()->symbols["long"] = std::make_shared<TypeSymbol>("long", int64Type);
        scopes.back()->symbols["bool"] = std::make_shared<TypeSymbol>("bool", boolType);
        scopes.back()->symbols["string"] = std::make_shared<TypeSymbol>("string", stringType);

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
        {
            std::vector<TypePtr> params;
            params.push_back(boolType);
            overloadSet->addFunction(
                std::make_shared<FunctionSymbol>("__builtin_print", voidType, std::move(params)));
        }

        scopes.back()->symbols["__builtin_print"] = std::move(overloadSet);
    }

    void SymbolTable::enterScope(Scope::Kind kind) {
        auto scope = std::make_unique<Scope>();
        scope->parent = scopes.empty() ? nullptr : scopes.back().get();
        scope->kind = kind;
        scopes.emplace_back(std::move(scope));
    }

    void SymbolTable::exitScope() {
        // if (scopes.empty()) {
        //     // ErrorHandler::getInstance().makeError("[RCE015]: No scope to exit", SourceLocation(0, 0, 0));
        //     return;
        // }
        RYNTRA_ASSERT(!scopes.empty());

        scopes.pop_back();
    }

    void SymbolTable::define(std::shared_ptr<Symbol> symbol, const SourceRange &range) {
        if (scopes.empty()) {
            ErrorHandler::getInstance().makeError("[RCE016]: No scope to define symbol", range);
            return;
        }
        auto &currentScope = scopes.back();
        if (currentScope->find(symbol->getName()) != nullptr) {
            ErrorHandler::getInstance().makeError("[RCE017]: Symbol '" + symbol->getName() + "' is already defined in the current scope.", range);
            return;
        }
        currentScope->symbols[symbol->getName()] = std::move(symbol);
    }

    std::shared_ptr<Symbol> SymbolTable::resolve(const std::string &name) {
        if (scopes.empty()) {
            return nullptr;
        }
        return scopes.back()->find(name);
    }

    bool SymbolTable::isAddressable(const std::shared_ptr<Symbol> &symbol) {
        if (!symbol) {
            return false;
        }
        auto kind = symbol->getKind();
        return kind == SymbolKind::Variable ||
               kind == SymbolKind::Function ||
               kind == SymbolKind::OverloadSet;
    }

} // namespace Ryntra::Compiler::Semantic
