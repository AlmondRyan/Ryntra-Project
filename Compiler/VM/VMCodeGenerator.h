#pragma once

#include "AST/ASTVisitor.h"
#include "VM/Instructions/Instruction.h"
#include "VM/VM.h"
#include <unordered_map>
#include <vector>

namespace Ryntra::Compiler {
    class VMCodeGenerator : public IASTVisitor {
    public:
        void visitProgram(std::shared_ptr<ProgramNode> node) override;
        void visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) override;
        void visitBlock(std::shared_ptr<BlockNode> node) override;
        void visitParameter(std::shared_ptr<ParameterNode> node) override;
        void visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) override;
        void visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) override;
        void visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) override;
        void visitFunctionCall(std::shared_ptr<FunctionCallNode> node) override;
        void visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) override;
        void visitIdentifier(std::shared_ptr<IdentifierNode> node) override;
        void visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) override;
        void visitFloatingLiteral(std::shared_ptr<FloatingLiteralNode> node) override;
        void visitStringLiteral(std::shared_ptr<StringLiteralNode> node) override;
        void visitBooleanLiteral(std::shared_ptr<BooleanLiteralNode> node) override;
        void visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) override;
        void visitIfStatement(std::shared_ptr<IfStatementNode> node) override;
        void visitBinaryExpression(std::shared_ptr<BinaryExpressionNode> node) override;
        void visitAssignmentExpression(std::shared_ptr<AssignmentExpressionNode> node) override;
        void visitUnaryExpression(std::shared_ptr<UnaryExpressionNode> node) override;
        void visitWhileStatement(std::shared_ptr<WhileStatementNode> node) override;
        void visitForStatement(std::shared_ptr<ForStatementNode> node) override;
        void visitPostfixExpression(std::shared_ptr<PostfixExpressionNode> node) override;
        void visitBreakStatement(std::shared_ptr<BreakStatementNode> node) override;
        void visitContinueStatement(std::shared_ptr<ContinueStatementNode> node) override;

        void visit(std::shared_ptr<IASTNode> node) {
            if (node) node->accept(this);
        }

        std::vector<Ryntra::VM::Instruction> getProgram() const { return program; }
        std::vector<Ryntra::VM::Value> getConstantPool() const { return constantPool; }

    private:
        void emit(const Ryntra::VM::Instruction& instr) { program.push_back(instr); }
        int addConstant(const Ryntra::VM::Value& v) {
            constantPool.push_back(v);
            return static_cast<int>(constantPool.size() - 1);
        }

        int getOrCreateVariableIndex(const std::string& name) {
            auto it = variableIndex.find(name);
            if (it != variableIndex.end()) return it->second;
            int idx = static_cast<int>(variableIndex.size());
            variableIndex[name] = idx;
            return idx;
        }

        void evaluateToStack(std::shared_ptr<IASTNode> node) {
            if (!node) return;
            node->accept(this);
        }

        std::vector<Ryntra::VM::Instruction> program;
        std::vector<Ryntra::VM::Value> constantPool;
        std::unordered_map<std::string, int> variableIndex;
        std::vector<std::vector<int>> breakPatchStack;
        std::vector<std::vector<int>> continuePatchStack;
        std::string currentFunctionName;
    };
}
