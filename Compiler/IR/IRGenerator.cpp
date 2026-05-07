#include "IRGenerator.h"
#include "ImmediateValue.h"
#include "Compiler/Semantic/TypeSystem.h"

namespace Ryntra::IR {
    namespace Sem = Compiler::Semantic;

    IRGenerator::IRGenerator() = default;

    std::shared_ptr<Module> IRGenerator::generate(Sem::TypedProgramNode &program,
                                                   const std::string &moduleName) {
        builder_.createModule(moduleName);
        program.accept(*this);
        return builder_.getModule();
    }

    std::shared_ptr<Type> IRGenerator::toIRType(const std::shared_ptr<Sem::Type> &semType) {
        if (!semType) return Type::getVoidType();

        switch (semType->getKind()) {
        case Sem::TypeKind::VOID:
            return Type::getVoidType();

        case Sem::TypeKind::PRIMITIVE: {
            const auto &name = static_cast<const Sem::PrimitiveType &>(*semType).getName();
            if (name == "i32" || name == "int")
                return Type::getInt32Type();
            if (name == "string" || name == "str")
                return Type::getStringType();
            return Type::getInt32Type();
        }

        case Sem::TypeKind::FUNCTION: {
            const auto &ft = static_cast<const Sem::FunctionType &>(*semType);
            auto retIR = toIRType(ft.getReturnType());
            std::vector<std::shared_ptr<Type>> params;
            for (const auto &p : ft.getParamTypes())
                params.push_back(toIRType(p));
            return std::make_shared<IR::FunctionType>(retIR, params);
        }

        default:
            return Type::getVoidType();
        }
    }

    void IRGenerator::visit(Sem::TypedProgramNode &node) {
        for (const auto &func : node.getFunctions()) {
            auto retType = toIRType(func->getReturnType());
            auto irFunc = builder_.createFunction(func->getName(), retType, {});
            functionMap_[func->getName()] = irFunc;
        }

        for (const auto &func : node.getFunctions()) {
            func->accept(*this);
        }
    }

    void IRGenerator::visit(Sem::TypedFunctionDefinitionNode &node) {
        auto irFunc = functionMap_[node.getName()];
        if (!irFunc) return;

        auto entry = builder_.createBasicBlock("entry");
        irFunc->addBasicBlock(entry);
        builder_.setInsertPoint(entry);

        node.getBody()->accept(*this);

        if (irFunc->getReturnType()->isVoid()) {
            auto &insts = entry->getInstructions();
            if (insts.empty() ||
                insts.back()->getOpcode() != Instruction::Opcode::Return) {
                builder_.createReturn("");
            }
        }
    }

    void IRGenerator::visit(Sem::TypedBlockNode &node) {
        for (const auto &stmt : node.getStatements()) {
            stmt->accept(*this);
        }
    }

    void IRGenerator::visit(Sem::TypedExpressionStatementNode &node) {
        node.getExpression()->accept(*this);
    }

    void IRGenerator::visit(Sem::TypedReturnNode &node) {
        node.getValue()->accept(*this);
        auto retVal = lastValue_;
        // ret never produces an SSA value — pass empty name
        builder_.createReturn("", retVal);
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedStringLiteralNode &node) {
        auto constant = builder_.createGlobalConstant(
            Type::getStringType(),
            node.getValue());
        lastValue_ = builder_.createLoadConstant(
            builder_.generateUniqueName(""), constant);
    }

    void IRGenerator::visit(Sem::TypedIntegerLiteralNode &node) {
        lastValue_ = std::make_shared<ImmediateValue>(
            Type::getInt32Type(),
            std::to_string(node.getValue()));
    }

    void IRGenerator::visit(Sem::TypedIdentifierNode &node) {
        auto it = functionMap_.find(node.getName());
        if (it != functionMap_.end()) {
            lastValue_ = it->second;
        } else {
            lastValue_ = std::make_shared<ImmediateValue>(
                toIRType(node.getType()), node.getName());
        }
    }

    void IRGenerator::visit(Sem::TypedFunctionCallNode &node) {
        const std::string &calleeName = node.getFunctionName()->getName();

        // Evaluate arguments first so we can infer parameter types for unknown callees
        std::vector<std::shared_ptr<Value>> argValues;
        for (const auto &arg : node.getArguments()) {
            arg->accept(*this);
            if (lastValue_) argValues.push_back(lastValue_);
        }

        // Mangle __builtin_ function names based on argument types
        std::string actualName = calleeName;
        if (calleeName.rfind("__builtin_", 0) == 0 && !argValues.empty()) {
            std::string suffix;
            auto argType = argValues[0]->getType();
            if (argType->isInt32())
                suffix = "i32";
            else if (argType->isString())
                suffix = "string";
            actualName = calleeName + "_" + suffix;
        }

        auto it = functionMap_.find(actualName);
        std::shared_ptr<Function> callee;
        if (it != functionMap_.end()) {
            callee = it->second;
        } else {
            // Declare external: infer parameter types from the evaluated arguments
            auto retType = toIRType(node.getType());
            std::vector<Function::Parameter> params;
            for (size_t i = 0; i < argValues.size(); ++i) {
                params.emplace_back("p" + std::to_string(i), argValues[i]->getType());
            }
            callee = builder_.createFunction(actualName, retType, params, /*isExternal=*/true);
            functionMap_[actualName] = callee;
        }

        // Only assign an SSA name when the call produces a value (non-void return)
        bool isVoidCall = callee->getReturnType()->isVoid();
        std::string callName = isVoidCall ? "" : builder_.generateUniqueName("");
        auto callInst = builder_.createCall(callName, callee, argValues);
        lastValue_ = isVoidCall ? nullptr : callInst;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedVariableDeclarationNode &node) {
        if (node.getInitializer()) {
            node.getInitializer()->accept(*this);
            if (lastValue_) {
                auto varName = node.getName();
                if (std::dynamic_pointer_cast<ImmediateValue>(lastValue_)) {
                    auto constInst = builder_.createConstant(
                        builder_.generateUniqueName(""),
                        lastValue_->getType(),
                        lastValue_);
                    variableMap_[varName] = constInst;
                } else {
                    variableMap_[varName] = lastValue_;
                }
                lastValue_ = nullptr;
            }
        }
    }

    void IRGenerator::visit(Compiler::Semantic::TypedVariableNode &node) {
        auto it = variableMap_.find(node.getName());
        if (it != variableMap_.end()) {
            lastValue_ = it->second;
        } else {
            lastValue_ = nullptr;
        }
    }
} // namespace Ryntra::IR
