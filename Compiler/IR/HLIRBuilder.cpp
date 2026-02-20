#include "HLIRBuilder.h"
#include "../Semantic/TypeSystem.h"

namespace Ryntra::Compiler::IR {

    HLIRBuilder::HLIRBuilder() {
        module = std::make_unique<Module>("main_module");
        builder = std::make_unique<IRBuilder>(module.get());

        // Pre-declare builtins
        // declare __builtin_print(string) -> void
        builder->CreateFunction("__builtin_print", Type::getVoidTy(), {Type::getStringTy()});
    }

    Type *HLIRBuilder::mapType(std::shared_ptr<Semantic::Type> type) {
        if (type->getKind() == Semantic::TypeKind::PRIMITIVE) {
            auto prim = std::static_pointer_cast<Semantic::PrimitiveType>(type);
            if (prim->getName() == "int")
                return Type::getInt32Ty();
            if (prim->getName() == "string")
                return Type::getStringTy();
            if (prim->getName() == "void")
                return Type::getVoidTy();
        }
        if (type->getKind() == Semantic::TypeKind::VOID) {
            return Type::getVoidTy();
        }
        return Type::getVoidTy(); // Fallback
    }

    void HLIRBuilder::visit(Semantic::TypedProgramNode &node) {
        for (const auto &func : node.getFunctions()) {
            func->accept(*this);
        }
    }

    void HLIRBuilder::visit(Semantic::TypedFunctionDefinitionNode &node) {
        auto retType = mapType(node.getReturnType());
        auto func = builder->CreateFunction(node.getName(), retType);

        auto entryBlock = builder->CreateBasicBlock("entry", func);
        builder->SetInsertPoint(entryBlock);

        node.getBody()->accept(*this);
    }

    void HLIRBuilder::visit(Semantic::TypedBlockNode &node) {
        for (const auto &stmt : node.getStatements()) {
            stmt->accept(*this);
        }
    }

    void HLIRBuilder::visit(Semantic::TypedExpressionStatementNode &node) {
        node.getExpression()->accept(*this);
    }

    void HLIRBuilder::visit(Semantic::TypedReturnNode &node) {
        node.getValue()->accept(*this);
        builder->CreateRet(lastValue);
    }

    void HLIRBuilder::visit(Semantic::TypedStringLiteralNode &node) {
        lastValue = builder->CreateConstantString(node.getValue());
    }

    void HLIRBuilder::visit(Semantic::TypedIntegerLiteralNode &node) {
        auto constant = std::make_unique<ConstantInt>(node.getValue());
        lastValue = constant.get();
        module->addConstant(std::move(constant));
    }

    void HLIRBuilder::visit(Semantic::TypedIdentifierNode &node) {
        auto global = module->getConstantObject(node.getName());
        if (global) {
            lastValue = global;
        } else {
            auto func = module->getFunction(node.getName());
            if (func) {
                lastValue = func;
            } else {
                lastValue = nullptr;
            }
        }
    }

    void HLIRBuilder::visit(Semantic::TypedFunctionCallNode &node) {
        auto funcName = node.getFunctionName()->getName();
        auto func = module->getFunction(funcName);

        if (!func) {
            func = module->getFunction("@" + funcName);
        }

        if (!func) {
            std::cerr << "IR Generation Error: Function " << funcName << " not found." << std::endl;
            lastValue = nullptr;
            return;
        }

        std::vector<Value *> args;
        for (const auto &arg : node.getArguments()) {
            arg->accept(*this);
            args.push_back(lastValue);
        }

        lastValue = builder->CreateCall(func, args);
    }
} // namespace Ryntra::Compiler::IR
