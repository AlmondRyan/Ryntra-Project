#include "VM/VMCodeGenerator.h"

namespace Ryntra::Compiler {
    using namespace Ryntra::VM;

    void VMCodeGenerator::visitProgram(std::shared_ptr<ProgramNode> node) {
        for (const auto& func : node->getFunctions()) {
            visit(func);
        }
    }

    void VMCodeGenerator::visitFunctionDefinition(std::shared_ptr<FunctionDefinitionNode> node) {
        currentFunctionName = node->getFunctionName();
        visit(node->getBody());
        emit(Instruction(OpCodes::HALT, 0));
    }

    void VMCodeGenerator::visitBlock(std::shared_ptr<BlockNode> node) {
        for (const auto& stmt : node->getStatements()) {
            visit(stmt);
        }
    }

    void VMCodeGenerator::visitParameter(std::shared_ptr<ParameterNode> node) {
    }

    void VMCodeGenerator::visitVariableDeclaration(std::shared_ptr<VariableDeclarationNode> node) {
        if (node->getVarType() != "int") {
            return;
        }

        int varIdx = getOrCreateVariableIndex(node->getVarName());

        auto init = node->getInitialValue();
        if (!init) {
            Value v;
            v.data = 0;
            int cidx = addConstant(v);
            emit(Instruction(OpCodes::LD_CONST, cidx));
            emit(Instruction(OpCodes::STORE_VAR, varIdx));
            return;
        }

        if (auto call = std::dynamic_pointer_cast<FunctionCallNode>(init)) {
            if (call->getFunctionName() == "__builtin_scan") {
                emit(Instruction(OpCodes::B_CALL, 1));
                emit(Instruction(OpCodes::STORE_VAR, varIdx));
                return;
            }
        }

        evaluateToStack(init);
        emit(Instruction(OpCodes::STORE_VAR, varIdx));
    }

    void VMCodeGenerator::visitReturnStatement(std::shared_ptr<ReturnStatementNode> node) {
        if (node->getReturnValue()) {
            evaluateToStack(node->getReturnValue());
        }
        emit(Instruction(OpCodes::RETURN, 0));
    }

    void VMCodeGenerator::visitFunctionCallStatement(std::shared_ptr<FunctionCallStatementNode> node) {
        visit(node->getFunctionCall());
    }

    void VMCodeGenerator::visitFunctionCall(std::shared_ptr<FunctionCallNode> node) {
        std::string funcName = node->getFunctionName();
        if (funcName == "__builtin_print") {
            if (!node->getArguments().empty()) {
                auto arg = node->getArguments()[0];
                if (auto intLit = std::dynamic_pointer_cast<IntegerLiteralNode>(arg)) {
                    Value v;
                    v.data = static_cast<int>(intLit->getValue());
                    int idx = addConstant(v);
                    emit(Instruction(OpCodes::LD_CONST, idx));
                } else if (auto strLit = std::dynamic_pointer_cast<StringLiteralNode>(arg)) {
                    Value v;
                    v.data = strLit->getValue();
                    int idx = addConstant(v);
                    emit(Instruction(OpCodes::LD_CONST, idx));
                } else if (auto ident = std::dynamic_pointer_cast<IdentifierNode>(arg)) {
                    int varIdx = getOrCreateVariableIndex(ident->getName());
                    emit(Instruction(OpCodes::LOAD_VAR, varIdx));
                } else {
                    evaluateToStack(arg);
                }
            }
            emit(Instruction(OpCodes::B_CALL, 0));
            return;
        }

        if (funcName == "__builtin_scan") {
            emit(Instruction(OpCodes::B_CALL, 1));
            return;
        }

        if (funcName == "__builtin_intToString") {
            if (!node->getArguments().empty()) {
                evaluateToStack(node->getArguments()[0]);
            }
            emit(Instruction(OpCodes::B_CALL, 2));
            return;
        }
    }

    void VMCodeGenerator::visitExpressionStatement(std::shared_ptr<ExpressionStatementNode> node) {
        if (node->getExpression()) {
            evaluateToStack(node->getExpression());
        }
    }

    void VMCodeGenerator::visitIdentifier(std::shared_ptr<IdentifierNode> node) {
        int idx = getOrCreateVariableIndex(node->getName());
        emit(Instruction(OpCodes::LOAD_VAR, idx));
    }

    void VMCodeGenerator::visitIntegerLiteral(std::shared_ptr<IntegerLiteralNode> node) {
        Value v;
        v.data = static_cast<int>(node->getValue());
        int idx = addConstant(v);
        emit(Instruction(OpCodes::LD_CONST, idx));
    }

    void VMCodeGenerator::visitFloatingLiteral(std::shared_ptr<FloatingLiteralNode> node) {
    }

    void VMCodeGenerator::visitStringLiteral(std::shared_ptr<StringLiteralNode> node) {
        Value v;
        v.data = node->getValue();
        int idx = addConstant(v);
        emit(Instruction(OpCodes::LD_CONST, idx));
    }

    void VMCodeGenerator::visitBooleanLiteral(std::shared_ptr<BooleanLiteralNode> node) {
        Value v;
        v.data = node->getValue();
        int idx = addConstant(v);
        emit(Instruction(OpCodes::LD_CONST, idx));
    }

    void VMCodeGenerator::visitEmptyStatement(std::shared_ptr<EmptyStatementNode> node) {
    }

    void VMCodeGenerator::visitIfStatement(std::shared_ptr<IfStatementNode> node) {
        evaluateToStack(node->getCondition());

        int jzIndex = static_cast<int>(program.size());
        emit(Instruction(OpCodes::JZ, 0));

        visit(node->getThenBody());

        auto elseBody = node->getElseBody();
        if (elseBody) {
            int jmpIndex = static_cast<int>(program.size());
            emit(Instruction(OpCodes::JMP, 0));

            program[static_cast<size_t>(jzIndex)].operand = static_cast<int>(program.size());

            visit(elseBody);

            program[static_cast<size_t>(jmpIndex)].operand = static_cast<int>(program.size());
        } else {
            program[static_cast<size_t>(jzIndex)].operand = static_cast<int>(program.size());
        }
    }

    void VMCodeGenerator::visitBinaryExpression(std::shared_ptr<BinaryExpressionNode> node) {
        std::string op = node->getOp();
        evaluateToStack(node->getLeft());
        evaluateToStack(node->getRight());

        if (op == "+") {
            emit(Instruction(OpCodes::ADD, 0));
        } else if (op == "-") {
            emit(Instruction(OpCodes::SUB, 0));
        } else if (op == "*") {
            emit(Instruction(OpCodes::MUL, 0));
        } else if (op == "/") {
            emit(Instruction(OpCodes::DIV, 0));
        } else if (op == "%") {
            emit(Instruction(OpCodes::MOD, 0));
        } else if (op == "&") {
            emit(Instruction(OpCodes::AND, 0));
        } else if (op == "|") {
            emit(Instruction(OpCodes::OR, 0));
        } else if (op == "^") {
            emit(Instruction(OpCodes::XOR, 0));
        } else if (op == "<<") {
            emit(Instruction(OpCodes::SHL, 0));
        } else if (op == ">>") {
            emit(Instruction(OpCodes::SHR, 0));
        } else if (op == "==") {
            emit(Instruction(OpCodes::EQ, 0));
        } else if (op == "!=") {
            emit(Instruction(OpCodes::NE, 0));
        } else if (op == "<") {
            emit(Instruction(OpCodes::LT, 0));
        } else if (op == "<=") {
            emit(Instruction(OpCodes::LE, 0));
        } else if (op == ">") {
            emit(Instruction(OpCodes::GT, 0));
        } else if (op == ">=") {
            emit(Instruction(OpCodes::GE, 0));
        }
    }

    void VMCodeGenerator::visitAssignmentExpression(std::shared_ptr<AssignmentExpressionNode> node) {
        int idx = getOrCreateVariableIndex(node->getIdentifier());
        evaluateToStack(node->getExpression());
        emit(Instruction(OpCodes::STORE_VAR, idx));
    }

    void VMCodeGenerator::visitUnaryExpression(std::shared_ptr<UnaryExpressionNode> node) {
        std::string op = node->getOp();
        if (op == "-") {
            auto inner = node->getExpression();
            if (auto intLit = std::dynamic_pointer_cast<IntegerLiteralNode>(inner)) {
                Value v;
                v.data = static_cast<int>(-intLit->getValue());
                int idx = addConstant(v);
                emit(Instruction(OpCodes::LD_CONST, idx));
            } else {
                evaluateToStack(inner);
            }
        } else if (op == "~") {
            evaluateToStack(node->getExpression());
            Value v;
            v.data = static_cast<int>(-1);
            int idx = addConstant(v);
            emit(Instruction(OpCodes::LD_CONST, idx));
            emit(Instruction(OpCodes::XOR, 0));
        } else if (op == "!") {
            evaluateToStack(node->getExpression());
            emit(Instruction(OpCodes::NOT, 0));
        } else {
            evaluateToStack(node->getExpression());
        }
    }

    void VMCodeGenerator::visitWhileStatement(std::shared_ptr<WhileStatementNode> node) {
        int condPos = static_cast<int>(program.size());
        evaluateToStack(node->getCondition());

        int jzIndex = static_cast<int>(program.size());
        emit(Instruction(OpCodes::JZ, 0));

        breakPatchStack.emplace_back();
        continuePatchStack.emplace_back();

        visit(node->getBody());

        emit(Instruction(OpCodes::JMP, condPos));
        int endPos = static_cast<int>(program.size());

        program[static_cast<size_t>(jzIndex)].operand = endPos;

        for (int idx : breakPatchStack.back()) {
            program[static_cast<size_t>(idx)].operand = endPos;
        }
        for (int idx : continuePatchStack.back()) {
            program[static_cast<size_t>(idx)].operand = condPos;
        }

        breakPatchStack.pop_back();
        continuePatchStack.pop_back();
    }

    void VMCodeGenerator::visitForStatement(std::shared_ptr<ForStatementNode> node) {
        if (node->getInit()) {
            visit(node->getInit());
        }

        int condPos = static_cast<int>(program.size());
        if (node->getCondition()) {
            evaluateToStack(node->getCondition());
        } else {
            Value v;
            v.data = true;
            int idx = addConstant(v);
            emit(Instruction(OpCodes::LD_CONST, idx));
        }

        int jzIndex = static_cast<int>(program.size());
        emit(Instruction(OpCodes::JZ, 0));

        breakPatchStack.emplace_back();
        continuePatchStack.emplace_back();

        visit(node->getBody());

        int incPos = static_cast<int>(program.size());
        if (node->getIncrement()) {
            visit(node->getIncrement());
        }

        emit(Instruction(OpCodes::JMP, condPos));
        int endPos = static_cast<int>(program.size());

        program[static_cast<size_t>(jzIndex)].operand = endPos;

        for (int idx : breakPatchStack.back()) {
            program[static_cast<size_t>(idx)].operand = endPos;
        }
        for (int idx : continuePatchStack.back()) {
            program[static_cast<size_t>(idx)].operand = incPos;
        }

        breakPatchStack.pop_back();
        continuePatchStack.pop_back();
    }

    void VMCodeGenerator::visitPostfixExpression(std::shared_ptr<PostfixExpressionNode> node) {
        int idx = getOrCreateVariableIndex(node->getVarName());
        std::string op = node->getOp();

        emit(Instruction(OpCodes::LOAD_VAR, idx));

        Value one;
        one.data = static_cast<int>(1);
        int constIdx = addConstant(one);
        emit(Instruction(OpCodes::LD_CONST, constIdx));

        if (op == "++") {
            emit(Instruction(OpCodes::ADD, 0));
        } else if (op == "--") {
            emit(Instruction(OpCodes::SUB, 0));
        }

        emit(Instruction(OpCodes::STORE_VAR, idx));
    }

    void VMCodeGenerator::visitBreakStatement(std::shared_ptr<BreakStatementNode> node) {
        if (breakPatchStack.empty()) {
            return;
        }
        int idx = static_cast<int>(program.size());
        emit(Instruction(OpCodes::JMP, 0));
        breakPatchStack.back().push_back(idx);
    }

    void VMCodeGenerator::visitContinueStatement(std::shared_ptr<ContinueStatementNode> node) {
        if (continuePatchStack.empty()) {
            return;
        }
        int idx = static_cast<int>(program.size());
        emit(Instruction(OpCodes::JMP, 0));
        continuePatchStack.back().push_back(idx);
    }
}
