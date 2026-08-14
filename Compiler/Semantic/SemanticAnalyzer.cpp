#include "SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace Ryntra::Compiler::Semantic {
    static std::string trimWhitespace(const std::string &s) {
        size_t first = s.find_first_not_of(" \t\r\n");
        if (first == std::string::npos)
            return "";
        size_t last = s.find_last_not_of(" \t\r\n");
        return s.substr(first, last - first + 1);
    }

    // A plain type name is a bare identifier (e.g. `int`, `NonexistentType`) without
    // generic wrappers (`<`, `>`) or function-signature parentheses.
    static bool isPlainTypeName(const std::string &name) {
        return name.find_first_of("<>()[]") == std::string::npos;
    }

    void SemanticAnalyzer::checkKnownTypeNames(const std::string &rawName, const SourceLocation &loc) {
        auto name = trimWhitespace(rawName);
        if (name.empty())
            return;

        if (isPlainTypeName(name)) {
            auto sym = symbolTable.resolve(name);
            bool isKnownType = sym && std::dynamic_pointer_cast<TypeSymbol>(sym);
            if (!isKnownType) {
                ErrorHandler::getInstance().makeError(
                    "[RCE074]: '" + name + "' is not a known type.",
                    loc);
            }
            return;
        }

        // Function types: "Fn<ret(params)>" (canonical) or bare "ret(params)"
        std::string inner;
        if (name.rfind("Fn<", 0) == 0 && name.size() > 5 && name.back() == '>') {
            inner = name.substr(3, name.size() - 4);
        } else if (name.find('(') != std::string::npos && name.back() == ')') {
            inner = name;
        }
        if (!inner.empty()) {
            auto parenPos = inner.find('(');
            if (parenPos != std::string::npos) {
                checkKnownTypeNames(inner.substr(0, parenPos), loc);
                auto paramSection = inner.substr(parenPos + 1);
                if (!paramSection.empty() && paramSection.back() == ')')
                    paramSection.pop_back();
                size_t start = 0;
                while (start <= paramSection.size()) {
                    auto commaPos = paramSection.find(',', start);
                    if (commaPos == std::string::npos)
                        commaPos = paramSection.size();
                    auto paramName = trimWhitespace(paramSection.substr(start, commaPos - start));
                    if (!paramName.empty())
                        checkKnownTypeNames(paramName, loc);
                    if (commaPos == paramSection.size())
                        break;
                    start = commaPos + 1;
                }
            }
            return;
        }

        // Generic wrappers: "ptr<...>" / "ref<...>"
        if ((name.rfind("ptr<", 0) == 0 || name.rfind("ref<", 0) == 0) &&
            name.size() > 5 && name.back() == '>') {
            checkKnownTypeNames(name.substr(4, name.size() - 5), loc);
            return;
        }
    }

    TypePtr SemanticAnalyzer::makeSTType(const std::string &name) {
        if (name == "void")
            return std::make_shared<STType::VoidType>();
        if (name == "string")
            return std::make_shared<STType::StringType>();
        if (name == "long")
            return std::make_shared<STType::Int64Type>();
        if (name == "bool")
            return std::make_shared<STType::BoolType>();
        if (name.rfind("ref<", 0) == 0 && name.size() > 5 && name.back() == '>') {
            auto innerName = name.substr(4, name.size() - 5);
            auto innerType = makeSTType(innerName);
            return std::make_shared<STType::ReferenceType>(innerType);
        }
        if (name.rfind("ptr<", 0) == 0 && name.size() > 5 && name.back() == '>') {
            auto innerName = name.substr(4, name.size() - 5);
            auto innerType = makeSTType(innerName);
            return std::make_shared<STType::PointerType>(innerType);
        }
        // Function types: "Fn<ret(params)>" (canonical) or bare "ret(params)"
        // (bare form is accepted here so that `ptr<int(int, int)>` etc. still
        // produce a reasonable type after the semantic error has been reported).
        std::string functionInner;
        if (name.rfind("Fn<", 0) == 0 && name.size() > 5 && name.back() == '>') {
            functionInner = name.substr(3, name.size() - 4);
        } else if (name.find('(') != std::string::npos && name.back() == ')') {
            functionInner = name;
        }
        if (!functionInner.empty()) {
            auto parenPos = functionInner.find('(');
            if (parenPos != std::string::npos) {
                auto returnType = makeSTType(trimWhitespace(functionInner.substr(0, parenPos)));
                auto paramSection = functionInner.substr(parenPos + 1);
                if (!paramSection.empty() && paramSection.back() == ')')
                    paramSection.pop_back();
                std::vector<TypePtr> paramTypes;
                size_t start = 0;
                while (start <= paramSection.size()) {
                    auto commaPos = paramSection.find(',', start);
                    if (commaPos == std::string::npos)
                        commaPos = paramSection.size();
                    auto paramName = trimWhitespace(paramSection.substr(start, commaPos - start));
                    if (!paramName.empty())
                        paramTypes.push_back(makeSTType(paramName));
                    if (commaPos == paramSection.size())
                        break;
                    start = commaPos + 1;
                }
                return std::make_shared<STType::FunctionType>(returnType, std::move(paramTypes));
            }
        }
        return std::make_shared<STType::Int32Type>();
    }

    std::string SemanticAnalyzer::getPtrVarName(const std::shared_ptr<TypedExpressionNode> &expr,
                                                  const SourceLocation &loc) {
        if (auto varNode = std::dynamic_pointer_cast<TypedVariableNode>(expr)) {
            return varNode->getName();
        }
        if (auto ptrCreateNode = std::dynamic_pointer_cast<TypedPtrCreateNode>(expr)) {
            return ptrCreateNode->getVariableName();
        }
        if (auto ptrOffsetNode = std::dynamic_pointer_cast<TypedPtrOffsetNode>(expr)) {
            return ptrOffsetNode->getPtrVarName();
        }
        ErrorHandler::getInstance().makeError(
            "[RCE059]: Expected a pointer variable or pointer expression.",
            loc);
        return "";
    }

    std::shared_ptr<FunctionType> SemanticAnalyzer::functionTypeOf(const std::shared_ptr<FunctionSymbol> &fn) {
        std::vector<std::shared_ptr<Type>> paramTypes;
        for (const auto &paramSTType : fn->getParamTypes()) {
            paramTypes.push_back(toTypedType(paramSTType));
        }
        return TypeFactory::getFunction(toTypedType(fn->getReturnType()), paramTypes);
    }

    std::shared_ptr<FunctionSymbol> SemanticAnalyzer::pickFunctionForAddress(const std::shared_ptr<OverloadSet> &ovSet,
                                                                             const SourceLocation &loc) {
        const auto &functions = ovSet->getFunctions();

        if (expectedReturnType && expectedReturnType->getKind() == TypeKind::POINTER) {
            auto &expectedPtr = static_cast<const PointerType &>(*expectedReturnType);
            auto expectedElem = expectedPtr.getElementType();
            if (expectedElem->getKind() == TypeKind::FUNCTION) {
                auto &expectedFn = static_cast<const FunctionType &>(*expectedElem);
                for (const auto &fn : functions) {
                    if (expectedFn.equals(*functionTypeOf(fn))) {
                        return fn;
                    }
                }
                ErrorHandler::getInstance().makeError(
                    "[RCE069]: No overload of function '" + ovSet->getName() +
                        "' matches the expected function type '" + expectedFn.toString() + "'.",
                    loc);
                return nullptr;
            }
        }

        if (functions.size() == 1) {
            return functions[0];
        }

        ErrorHandler::getInstance().makeError(
            "[RCE068]: Cannot take the address of overloaded function '" + ovSet->getName() +
                "' without a matching expected function type.",
            loc);
        return nullptr;
    }

    std::shared_ptr<Type> SemanticAnalyzer::toTypedType(const TypePtr &stType) {
        if (!stType)
            return TypeFactory::getPrimitive("unknown");
        switch (stType->getKind()) {
        case STType::TypeKind::Void:
            return TypeFactory::getVoid();
        case STType::TypeKind::String:
            return TypeFactory::getPrimitive("string");
        case STType::TypeKind::Int32:
            return TypeFactory::getPrimitive("int");
        case STType::TypeKind::Int64:
            return TypeFactory::getPrimitive("long");
        case STType::TypeKind::Bool:
            return TypeFactory::getPrimitive("bool");
        case STType::TypeKind::Array: {
            auto &arrSTType = static_cast<const STType::ArrayType &>(*stType);
            return TypeFactory::getArray(toTypedType(arrSTType.getElementType()));
        }
        case STType::TypeKind::Reference: {
            auto &refSTType = static_cast<const STType::ReferenceType &>(*stType);
            return TypeFactory::getReference(toTypedType(refSTType.getElementType()));
        }
        case STType::TypeKind::Pointer: {
            auto &ptrSTType = static_cast<const STType::PointerType &>(*stType);
            return TypeFactory::getPointer(toTypedType(ptrSTType.getElementType()));
        }
        case STType::TypeKind::Function: {
            auto &fnSTType = static_cast<const STType::FunctionType &>(*stType);
            std::vector<std::shared_ptr<Type>> paramTypes;
            for (const auto &paramSTType : fnSTType.getParamTypes()) {
                paramTypes.push_back(toTypedType(paramSTType));
            }
            return TypeFactory::getFunction(toTypedType(fnSTType.getReturnType()), paramTypes);
        }
        default:
            return TypeFactory::getPrimitive("unknown");
        }
    }

    void SemanticAnalyzer::analyze(const std::shared_ptr<IASTNode> &root) {
        if (!root)
            return;
        root->accept(*this);
    }
} // namespace Ryntra::Compiler::Semantic
