#include "SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

namespace Ryntra::Compiler::Semantic {
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
