#include "../IRGenerator.h"
#include "../ImmediateValue.h"

namespace Ryntra::IR {
    namespace Sem = Compiler::Semantic;

    void IRGenerator::visit(Sem::TypedStringLiteralNode &node) {
        auto constant = builder_.createGlobalConstant(
            Type::getStringType(),
            node.getValue());
        lastValue_ = builder_.createLoadConstant(
            builder_.generateUniqueName(""), constant);
    }

    void IRGenerator::visit(Sem::TypedBoolLiteralNode &node) {
        lastValue_ = std::make_shared<ImmediateValue>(
            Type::getBoolType(),
            node.getValue() ? "1" : "0");
    }

    void IRGenerator::visit(Sem::TypedIntegerLiteralNode &node) {
        lastValue_ = std::make_shared<ImmediateValue>(
            Type::getInt32Type(),
            std::to_string(node.getValue()));
    }

    void IRGenerator::visit(Sem::TypedLongLiteralNode &node) {
        lastValue_ = std::make_shared<ImmediateValue>(
            Type::getInt64Type(),
            std::to_string(node.getValue()));
    }

    void IRGenerator::visit(Sem::TypedNullLiteralNode &node) {
        lastValue_ = std::make_shared<ImmediateValue>(
            Type::getInt32Type(), "-1");
    }

    void IRGenerator::visit(Sem::TypedIdentifierNode &node) {
        auto funcIt = functionMap_.find(node.getName());
        if (funcIt != functionMap_.end()) {
            lastValue_ = funcIt->second;
            return;
        }

        auto varIt = allocaMap_.find(node.getName());
        if (varIt != allocaMap_.end()) {
            auto loadType = toIRType(node.getType());
            lastValue_ = builder_.createLoad(
                builder_.generateUniqueName(""),
                varIt->second,
                loadType);
            return;
        }

        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedFunctionCallNode &node) {
        const std::string &calleeName = node.getFunctionName()->getName();

        std::vector<std::shared_ptr<Value>> argValues;
        for (const auto &arg : node.getArguments()) {
            arg->accept(*this);
            if (lastValue_)
                argValues.push_back(lastValue_);
        }

        std::string actualName = calleeName;
        if (calleeName.rfind("__builtin_", 0) == 0) {
            if (!argValues.empty()) {
                std::string suffix;
                auto argType = argValues[0]->getType();
                if (argType->isInt32())
                    suffix = "i32";
                else if (argType->isInt64())
                    suffix = "i64";
                else if (argType->isBool())
                    suffix = "bool";
                else if (argType->isString())
                    suffix = "string";
                actualName = calleeName + "_" + suffix;
            } else if (calleeName == "__builtin_scan") {
                std::string suffix;
                auto retType = node.getType();
                if (retType->toString() == "int")
                    suffix = "i32";
                else if (retType->toString() == "long")
                    suffix = "i64";
                else if (retType->toString() == "bool")
                    suffix = "bool";
                actualName = calleeName + "_" + suffix;
            }
        }

        auto it = functionMap_.find(actualName);
        std::shared_ptr<Function> callee;
        if (it != functionMap_.end()) {
            callee = it->second;
        } else {
            auto retType = toIRType(node.getType());
            std::vector<Function::Parameter> params;
            for (size_t i = 0; i < argValues.size(); ++i) {
                params.emplace_back("p" + std::to_string(i), argValues[i]->getType());
            }
            callee = builder_.createFunction(actualName, retType, params, /*isExternal=*/true);
            functionMap_[actualName] = callee;
        }

        bool isVoidCall = callee->getReturnType()->isVoid();
        std::string callName = isVoidCall ? "" : builder_.generateUniqueName("");
        auto callInst = builder_.createCall(callName, callee, argValues);
        lastValue_ = isVoidCall ? nullptr : callInst;
    }
} // namespace Ryntra::IR
