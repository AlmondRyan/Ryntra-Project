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
        if (!type) return Type::getVoidTy();

        switch (type->getKind()) {
            case Semantic::TypeKind::PRIMITIVE: {
                auto prim = std::static_pointer_cast<Semantic::PrimitiveType>(type);
                if (prim->getName() == "int" || prim->getName() == "i32")
                    return Type::getInt32Ty();
                if (prim->getName() == "string")
                    return Type::getStringTy();
                if (prim->getName() == "void")
                    return Type::getVoidTy();
                break;
            }
            case Semantic::TypeKind::VOID:
                return Type::getVoidTy();
            case Semantic::TypeKind::FUNCTION:
                // For now, we don't have function types as first-class in IR Types,
                // but we can return void or implement it if needed.
                return Type::getVoidTy();
            default:
                return Type::getVoidTy();
        }
        return Type::getVoidTy();
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
        // 1. Check if we already have this string constant to avoid duplicates
        std::string val = "\"" + node.getValue() + "\"";
        ConstantObject* global = nullptr;
        for (const auto& co : module->getConstantObjects()) {
            if (co->getInitValue() == val) {
                global = co.get();
                break;
            }
        }
        
        if (!global) {
            std::string name = "str" + std::to_string(module->getNextStringConstantId());
            global = builder->CreateConstant<ConstantObject>(Type::getStringTy(), name, val);
        }
        
        // 2. Load the constant into a register
        lastValue = builder->CreateLoad(global);
    }

    void HLIRBuilder::visit(Semantic::TypedIntegerLiteralNode &node) {
        // Integers are usually used as literals in instructions
        lastValue = builder->CreateConstant<ConstantInt>(node.getValue());
    }

    void HLIRBuilder::visit(Semantic::TypedIdentifierNode &node) {
        auto name = node.getName();
        
        // Try to resolve as a global constant
        auto global = module->getConstantObject(name);
        if (global) {
            lastValue = builder->CreateLoad(global);
            return;
        }
        
        // Try to resolve as a function (for calls, though CallNode handles this usually)
        auto func = module->getFunction(name);
        if (func) {
            lastValue = func;
            return;
        }

        // TODO: Handle local variables when we have them
        std::cerr << "IR Generation Error: Identifier " << name << " not found." << std::endl;
        lastValue = nullptr;
    }

    void HLIRBuilder::visit(Semantic::TypedFunctionCallNode &node) {
        auto funcName = node.getFunctionName()->getName();
        auto func = module->getFunction(funcName);

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
