#include "../SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {
    void SemanticAnalyzer::visit(StringLiteralNode &node) {
        auto stType = std::make_shared<STType::StringType>();
        auto typedNode = std::make_shared<TypedStringLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(NullLiteralNode &node) {
        auto typedNode = std::make_shared<TypedNullLiteralNode>(
            TypeFactory::getPrimitive("null"));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(BoolLiteralNode &node) {
        auto stType = std::make_shared<STType::BoolType>();
        auto typedNode = std::make_shared<TypedBoolLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(IntegerLiteralNode &node) {
        auto stType = std::make_shared<STType::Int32Type>();
        auto typedNode = std::make_shared<TypedIntegerLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(LongLiteralNode &node) {
        auto stType = std::make_shared<STType::Int64Type>();
        auto typedNode = std::make_shared<TypedLongLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }
} // namespace Ryntra::Compiler::Semantic
