#include "SemanticAnalyzer.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {

    // ---------------------------------------------------------------------------
    // Helpers
    // ---------------------------------------------------------------------------

    // Map a type-name string to an STType::TypePtr (SymbolTable type system)
    TypePtr SemanticAnalyzer::makeSTType(const std::string& name) {
        if (name == "void")   return std::make_shared<STType::VoidType>();
        if (name == "string") return std::make_shared<STType::StringType>();
        // int / int32 both map to Int32
        return std::make_shared<STType::Int32Type>();
    }

    // Convert STType::Type -> TypeSystem::Type (used by TypedAST nodes)
    std::shared_ptr<Type> SemanticAnalyzer::toTypedType(const TypePtr& stType) {
        if (!stType) return TypeFactory::getPrimitive("unknown");
        switch (stType->getKind()) {
            case STType::TypeKind::Void:   return TypeFactory::getVoid();
            case STType::TypeKind::String: return TypeFactory::getPrimitive("string");
            case STType::TypeKind::Int32:  return TypeFactory::getPrimitive("int");
            default:                       return TypeFactory::getPrimitive("unknown");
        }
    }

    // ---------------------------------------------------------------------------
    // Public API
    // ---------------------------------------------------------------------------

    void SemanticAnalyzer::analyze(const std::shared_ptr<IASTNode>& root) {
        if (!root) return;
        root->accept(*this);
    }

    // ---------------------------------------------------------------------------
    // Visitors
    // ---------------------------------------------------------------------------

    void SemanticAnalyzer::visit(ProgramNode &node) {
        // First pass: register all user-defined functions
        for (const auto &func : node.getFunctions()) {
            auto funcName      = func->getName()->getName();
            auto returnTypeName = func->getReturnType()->getName();
            auto returnType    = makeSTType(returnTypeName);

            if (symbolTable.resolve(funcName)) {
                ErrorHandler::getInstance().makeError(
                    "Semantic Error: Function '" + funcName + "' is already defined.",
                    func->getLocation());
                continue;
            }

            // Parameter types will be populated when we visit the function body;
            // for now register with empty param list so calls can resolve the symbol.
            symbolTable.define(
                std::make_shared<FunctionSymbol>(funcName, returnType, std::vector<TypePtr>{}),
                func->getLocation());
        }

        // Register print() built-in if not already present
        // (__builtin_print is registered by SymbolTable constructor)
        if (!symbolTable.resolve("print")) {
            std::vector<TypePtr> params{ std::make_shared<STType::StringType>() };
            symbolTable.define(
                std::make_shared<FunctionSymbol>("print",
                    std::make_shared<STType::VoidType>(), std::move(params)),
                SourceLocation{0, 0});
        }

        // Validate main
        auto mainSym = symbolTable.resolve("main");
        if (!mainSym) {
            ErrorHandler::getInstance().makeError(
                "Semantic Error: 'main' function is not defined.", node.getLocation());
        } else {
            auto mainFuncSym = std::dynamic_pointer_cast<FunctionSymbol>(mainSym);
            if (!mainFuncSym) {
                ErrorHandler::getInstance().makeError(
                    "Semantic Error: 'main' is not a function.", node.getLocation());
            } else if (!mainFuncSym->getReturnType() ||
                       mainFuncSym->getReturnType()->getKind() != STType::TypeKind::Int32) {
                ErrorHandler::getInstance().makeError(
                    "Semantic Error: 'main' function must return 'int'.", node.getLocation());
            }
        }

        // Second pass: analyse bodies
        std::vector<std::shared_ptr<TypedFunctionDefinitionNode>> typedFunctions;
        for (const auto &func : node.getFunctions()) {
            func->accept(*this);
            if (auto typedFunc = std::dynamic_pointer_cast<TypedFunctionDefinitionNode>(lastNode)) {
                typedFunctions.push_back(typedFunc);
            }
        }

        typedProgram = std::make_shared<TypedProgramNode>(std::move(typedFunctions));
        typedProgram->setLocation(node.getLocation());
        lastNode = typedProgram;
    }

    void SemanticAnalyzer::visit(FunctionDefinitionNode &node) {
        node.getReturnType()->accept(*this);
        auto returnType = lastType ? lastType : makeSTType("void");
        currentFunctionReturnType = returnType;

        auto funcName = node.getName()->getName();

        symbolTable.enterScope();
        node.getBody()->accept(*this);
        auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);
        symbolTable.exitScope();

        if (typedBody) {
            auto typedFunc = std::make_shared<TypedFunctionDefinitionNode>(
                funcName, toTypedType(returnType), typedBody);
            typedFunc->setLocation(node.getLocation());
            lastNode = typedFunc;

            if (funcName == "main") {
                bool hasReturn = false;
                for (const auto& stmt : typedBody->getStatements()) {
                    if (std::dynamic_pointer_cast<TypedReturnNode>(stmt)) {
                        hasReturn = true;
                        break;
                    }
                }
                if (!hasReturn) {
                    ErrorHandler::getInstance().makeError(
                        "Semantic Error: 'main' function must explicitly return a value.",
                        node.getLocation());
                }
            }
        } else {
            lastNode = nullptr;
        }
        currentFunctionReturnType = nullptr;
    }

    void SemanticAnalyzer::visit(ReturnNode &node) {
        node.getValue()->accept(*this);
        auto typedExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (typedExpr) {
            if (currentFunctionReturnType) {
                auto expectedTyped = toTypedType(currentFunctionReturnType);
                auto actualType    = typedExpr->getType();

                if (!expectedTyped->equals(*actualType) && actualType->toString() != "unknown") {
                    ErrorHandler::getInstance().makeError(
                        "Semantic Error: Return type mismatch. Expected '" +
                        expectedTyped->toString() + "', but got '" +
                        actualType->toString() + "'.",
                        node.getLocation());
                }
            }
            auto typedReturn = std::make_shared<TypedReturnNode>(typedExpr);
            typedReturn->setLocation(node.getLocation());
            lastNode = typedReturn;
        } else {
            lastNode = nullptr;
        }
    }

    void SemanticAnalyzer::visit(BlockNode &node) {
        std::vector<std::shared_ptr<TypedStatementNode>> typedStatements;
        for (const auto &stmt : node.getStatements()) {
            stmt->accept(*this);
            if (auto typedStmt = std::dynamic_pointer_cast<TypedStatementNode>(lastNode)) {
                typedStatements.push_back(typedStmt);
            }
        }
        auto typedBlock = std::make_shared<TypedBlockNode>(std::move(typedStatements));
        typedBlock->setLocation(node.getLocation());
        lastNode = typedBlock;
    }

    void SemanticAnalyzer::visit(ExpressionStatementNode &node) {
        node.getExpression()->accept(*this);
        if (auto typedExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode)) {
            auto typedStmt = std::make_shared<TypedExpressionStatementNode>(typedExpr);
            typedStmt->setLocation(node.getLocation());
            lastNode = typedStmt;
        } else {
            lastNode = nullptr;
        }
    }

    void SemanticAnalyzer::visit(StringLiteralNode &node) {
        auto stType    = std::make_shared<STType::StringType>();
        auto typedNode = std::make_shared<TypedStringLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(IntegerLiteralNode &node) {
        auto stType    = std::make_shared<STType::Int32Type>();
        auto typedNode = std::make_shared<TypedIntegerLiteralNode>(
            node.getValue(), toTypedType(stType));
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(IdentifierNode &node) {
        auto name = node.getName();
        auto sym  = symbolTable.resolve(name);

        std::shared_ptr<Type> type;
        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "Semantic Error: Identifier '" + name + "' is not defined.",
                node.getLocation());
            type = TypeFactory::getPrimitive("unknown");
        } else if (auto funcSym = std::dynamic_pointer_cast<FunctionSymbol>(sym)) {
            std::vector<std::shared_ptr<Type>> paramTypes;
            for (const auto& p : funcSym->getParamTypes())
                paramTypes.push_back(toTypedType(p));
            type = TypeFactory::getFunction(toTypedType(funcSym->getReturnType()), paramTypes);
        } else if (auto varSym = std::dynamic_pointer_cast<VariableSymbol>(sym)) {
            type = toTypedType(varSym->getType());
        } else {
            type = TypeFactory::getPrimitive("unknown");
        }

        auto typedNode = std::make_shared<TypedIdentifierNode>(name, type);
        typedNode->setLocation(node.getLocation());
        lastNode = typedNode;
    }

    void SemanticAnalyzer::visit(FunctionCallNode &node) {
        auto funcNameNode = node.getFunctionName();
        std::string funcName = funcNameNode->getName();

        auto sym = symbolTable.resolve(funcName);
        TypePtr stReturnType;
        std::vector<TypePtr> expectedParamTypes;

        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "Semantic Error: Function '" + funcName + "' is not defined.",
                node.getLocation());
            stReturnType = makeSTType("unknown");
        } else {
            auto funcSym = std::dynamic_pointer_cast<FunctionSymbol>(sym);
            if (!funcSym) {
                ErrorHandler::getInstance().makeError(
                    "Semantic Error: '" + funcName + "' is not a function.",
                    node.getLocation());
                stReturnType = makeSTType("unknown");
            } else {
                stReturnType       = funcSym->getReturnType();
                expectedParamTypes = funcSym->getParamTypes();
            }
        }

        auto returnType = toTypedType(stReturnType);

        // Process arguments
        const auto& args = node.getArguments();
        if (sym && args.size() != expectedParamTypes.size()) {
            ErrorHandler::getInstance().makeError(
                "Semantic Error: Function '" + funcName + "' expects " +
                std::to_string(expectedParamTypes.size()) + " arguments, but got " +
                std::to_string(args.size()) + ".",
                node.getLocation());
        }

        std::vector<std::shared_ptr<TypedExpressionNode>> typedArgs;
        for (size_t i = 0; i < args.size(); ++i) {
            args[i]->accept(*this);
            auto typedArg = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
            if (!typedArg) continue;
            typedArgs.push_back(typedArg);

            if (i < expectedParamTypes.size()) {
                auto expectedTyped = toTypedType(expectedParamTypes[i]);
                auto actualType    = typedArg->getType();
                if (!expectedTyped->equals(*actualType) &&
                    actualType->toString() != "unknown") {
                    ErrorHandler::getInstance().makeError(
                        "Semantic Error: Argument " + std::to_string(i + 1) +
                        " expects type '" + expectedTyped->toString() +
                        "', but got '" + actualType->toString() + "'.",
                        args[i]->getLocation());
                }
            }
        }

        std::vector<std::shared_ptr<Type>> paramTypeObjs;
        for (const auto& pt : expectedParamTypes)
            paramTypeObjs.push_back(toTypedType(pt));
        auto funcType = TypeFactory::getFunction(returnType, paramTypeObjs);

        auto typedFuncName = std::make_shared<TypedIdentifierNode>(funcName, funcType);
        typedFuncName->setLocation(funcNameNode->getLocation());

        auto typedCall = std::make_shared<TypedFunctionCallNode>(typedFuncName, typedArgs, returnType);
        typedCall->setLocation(node.getLocation());
        lastNode = typedCall;
    }

    void SemanticAnalyzer::visit(TypeSpecifierNode &node) {
        lastType = makeSTType(node.getName());
    }

} // namespace Ryntra::Compiler::Semantic
