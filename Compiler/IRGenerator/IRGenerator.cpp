#include "IRGenerator/IRGenerator.h"
#include <llvm/Support/raw_os_ostream.h>

namespace Ryntra::Compiler {
    std::any IRGenerator::visitProgram(std::shared_ptr<ProgramNode> node) {
        using namespace llvm;

        LLVMContext context;
        Module module("main", context);
        IRBuilder<> builder(context);
        std::shared_ptr<FunctionDefinitionNode> mainFunc = nullptr;
        for (auto &func: node->getFunctions()) {
            if (func->getFunctionName() == "main") {
                mainFunc = func;
                break;
            }
        }

        FunctionType *funcType = FunctionType::get(
            Type::getInt32Ty(context),
            false
        );

        Function *mainFunction = Function::Create(
            funcType,
            Function::ExternalLinkage,
            "main",
            &module
        );

        BasicBlock* entryBlock = BasicBlock::Create(context, "entry", mainFunction);
        builder.SetInsertPoint(entryBlock);
        builder.CreateRet(builder.getInt32(0));

        std::string n;
        raw_string_ostream stream(n);
        module.print(stream, nullptr);
        ir = n;
        return nullptr;
    }

    std::any IRGenerator::visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) {
        return {};
    }

    std::any IRGenerator::visitBlock(std::shared_ptr<BlockNode> node) {
        return {};
    }

    std::any IRGenerator::visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) {
        return {};
    }

    std::any IRGenerator::visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) {
        return {};
    }

    std::any IRGenerator::visitFunctionCall(std::shared_ptr<FunctionCallNode> node) {
        return {};
    }

    std::any IRGenerator::visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) {
        return {};
    }

    std::any IRGenerator::visitIdentifier(std::shared_ptr<IdentifierNode> node) {
        return {};
    }

    std::any IRGenerator::visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) {
        return {};
    }

    std::any IRGenerator::visitParameter(std::shared_ptr<ParameterNode> node) {
        return {};
    }

    std::any IRGenerator::visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) {
        return {};
    }

    std::any IRGenerator::visitStringLiteral(std::shared_ptr<StringLiteralNode> node) {
        return {};
    }

    std::any IRGenerator::visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) {
        return {};
    }
}
