#include "../SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {
    void SemanticAnalyzer::visit(FunctionCallNode &node) {
        auto funcNameNode = node.getFunctionName();
        std::string funcName = funcNameNode->getName();

        auto sym = symbolTable.resolve(funcName);

        const auto &args = node.getArguments();
        std::vector<std::shared_ptr<TypedExpressionNode>> typedArgs;
        for (size_t i = 0; i < args.size(); ++i) {
            args[i]->accept(*this);
            auto typedArg = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
            typedArgs.push_back(typedArg);
        }

        TypePtr stReturnType;
        std::vector<TypePtr> expectedParamTypes;

        if (!sym) {
            ErrorHandler::getInstance().makeError(
                "[RCE008]: Function '" + funcName + "' is not defined.",
                node.getLocation());
            stReturnType = makeSTType("unknown");
        } else if (auto overloadSet = std::dynamic_pointer_cast<OverloadSet>(sym)) {
            bool found = false;

            if (funcName == "__builtin_scan" && expectedReturnType) {
                for (const auto &overload : overloadSet->getFunctions()) {
                    auto overloadRetTyped = toTypedType(overload->getReturnType());
                    if (overloadRetTyped->equals(*expectedReturnType)) {
                        stReturnType = overload->getReturnType();
                        expectedParamTypes = overload->getParamTypes();
                        found = true;
                        break;
                    }
                }
            }

            if (!found)
                for (const auto &overload : overloadSet->getFunctions()) {
                    if (overload->getParamTypes().size() != args.size())
                        continue;

                    bool match = true;
                    for (size_t i = 0; i < args.size(); ++i) {
                        if (!typedArgs[i]) {
                            match = false;
                            break;
                        }
                        auto expectedTyped = toTypedType(overload->getParamTypes()[i]);
                        if (!expectedTyped->equals(*typedArgs[i]->getType()) &&
                            typedArgs[i]->getType()->toString() != "unknown") {
                            match = false;
                            break;
                        }
                    }

                    if (match) {
                        stReturnType = overload->getReturnType();
                        expectedParamTypes = overload->getParamTypes();
                        found = true;
                        break;
                    }
                }

            if (!found) {
                std::string expectedTypes;
                for (const auto &overload : overloadSet->getFunctions()) {
                    if (!expectedTypes.empty())
                        expectedTypes += " or ";
                    expectedTypes += "'" + toTypedType(overload->getParamTypes()[0])->toString() + "'";
                }
                ErrorHandler::getInstance().makeError(
                    "[RCE009]: No matching overload for function '" + funcName +
                        "'. Expected " + expectedTypes + " argument, but got '" +
                        (typedArgs.empty() || !typedArgs[0] ? "unknown" : typedArgs[0]->getType()->toString()) + "'.",
                    node.getLocation());
                stReturnType = makeSTType("unknown");
                if (!overloadSet->getFunctions().empty()) {
                    expectedParamTypes = overloadSet->getFunctions()[0]->getParamTypes();
                }
            }
        } else if (auto funcSym = std::dynamic_pointer_cast<FunctionSymbol>(sym)) {
            stReturnType = funcSym->getReturnType();
            expectedParamTypes = funcSym->getParamTypes();
        } else {
            ErrorHandler::getInstance().makeError(
                "[RCE010]: '" + funcName + "' is not a function.",
                node.getLocation());
            stReturnType = makeSTType("unknown");
        }

        auto returnType = toTypedType(stReturnType);

        if (sym && args.size() != expectedParamTypes.size() &&
            !std::dynamic_pointer_cast<OverloadSet>(sym)) {
            ErrorHandler::getInstance().makeError(
                "[RCE011]: Function '" + funcName + "' expects " +
                    std::to_string(expectedParamTypes.size()) + " arguments, but got " +
                    std::to_string(args.size()) + ".",
                node.getLocation());
        }

        for (size_t i = 0; i < typedArgs.size(); ++i) {
            auto typedArg = typedArgs[i];
            if (!typedArg)
                continue;

            if (i < expectedParamTypes.size()) {
                auto expectedTyped = toTypedType(expectedParamTypes[i]);
                auto actualType = typedArg->getType();
                if (!expectedTyped->equals(*actualType) &&
                    actualType->toString() != "unknown") {
                    ErrorHandler::getInstance().makeError(
                        "[RCE012]: Argument " + std::to_string(i + 1) +
                            " expects type '" + expectedTyped->toString() +
                            "', but got '" + actualType->toString() + "'.",
                        args[i]->getLocation());
                }
            }
        }

        std::vector<std::shared_ptr<Type>> paramTypeObjs;
        for (const auto &pt : expectedParamTypes)
            paramTypeObjs.push_back(toTypedType(pt));
        auto funcType = TypeFactory::getFunction(returnType, paramTypeObjs);

        auto typedFuncName = std::make_shared<TypedIdentifierNode>(funcName, funcType);
        typedFuncName->setLocation(funcNameNode->getLocation());

        auto typedCall = std::make_shared<TypedFunctionCallNode>(typedFuncName, typedArgs, returnType);
        typedCall->setLocation(node.getLocation());
        lastNode = typedCall;
    }
} // namespace Ryntra::Compiler::Semantic
