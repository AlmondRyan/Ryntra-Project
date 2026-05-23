#include "IRGenerator.h"
#include "Compiler/Semantic/TypeSystem.h"
#include "ImmediateValue.h"

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
        if (!semType)
            return Type::getVoidType();

        switch (semType->getKind()) {
        case Sem::TypeKind::VOID:
            return Type::getVoidType();

        case Sem::TypeKind::PRIMITIVE: {
            const auto &name = static_cast<const Sem::PrimitiveType &>(*semType).getName();
            if (name == "i32" || name == "int")
                return Type::getInt32Type();
            if (name == "i64" || name == "long")
                return Type::getInt64Type();
            if (name == "string" || name == "str")
                return Type::getStringType();
            if (name == "bool")
                return Type::getBoolType();
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

        case Sem::TypeKind::ARRAY: {
            const auto &arrType = static_cast<const Sem::ArrayType &>(*semType);
            return std::make_shared<IR::ArrayType>(toIRType(arrType.getElementType()));
        }

        case Sem::TypeKind::REFERENCE: {
            const auto &refType = static_cast<const Sem::ReferenceType &>(*semType);
            return std::make_shared<IR::RefType>(toIRType(refType.getElementType()));
        }

        case Sem::TypeKind::POINTER: {
            const auto &ptrType = static_cast<const Sem::PointerType &>(*semType);
            return std::make_shared<IR::PtrType>(toIRType(ptrType.getElementType()));
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
        if (!irFunc)
            return;

        currentFunctionName_ = node.getName();
        ifCounter_ = 0;

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

    void IRGenerator::visit(Sem::TypedIfNode &node) {
        auto currentFunc = functionMap_[currentFunctionName_];
        if (!currentFunc)
            return;

        std::string suffix = std::to_string(ifCounter_++);

        node.getCondition()->accept(*this);
        auto condVal = lastValue_;
        if (!condVal) {
            lastValue_ = nullptr;
            return;
        }

        auto thenBlock = builder_.createBasicBlock("if.then." + suffix);
        auto elseBlock = builder_.createBasicBlock("if.else." + suffix);
        auto endBlock = builder_.createBasicBlock("if.end." + suffix);

        std::string trueTarget = thenBlock->getName();
        std::string falseTarget;

        if (node.getElseBranch()) {
            falseTarget = elseBlock->getName();
        } else {
            falseTarget = endBlock->getName();
        }

        builder_.createCondBr(condVal, trueTarget, falseTarget);
        currentFunc->addBasicBlock(thenBlock);
        builder_.setInsertPoint(thenBlock);

        node.getThenBlock()->accept(*this);

        // After visiting child statements, the current block may have changed
        // (e.g., inner ifs create new blocks). Use the actual current block.
        auto curBlock = builder_.getInsertPoint();
        if (curBlock) {
            auto &insts = curBlock->getInstructions();
            if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                builder_.createBr(endBlock->getName());
            }
        }

        if (node.getElseBranch()) {
            currentFunc->addBasicBlock(elseBlock);
            builder_.setInsertPoint(elseBlock);

            if (auto typedElseBlock = std::dynamic_pointer_cast<Sem::TypedBlockNode>(node.getElseBranch())) {
                typedElseBlock->accept(*this);
            } else if (auto typedElseIf = std::dynamic_pointer_cast<Sem::TypedIfNode>(node.getElseBranch())) {
                typedElseIf->accept(*this);
            }

            curBlock = builder_.getInsertPoint();
            if (curBlock) {
                auto &insts = curBlock->getInstructions();
                if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                    builder_.createBr(endBlock->getName());
                }
            }
        }

        currentFunc->addBasicBlock(endBlock);
        builder_.setInsertPoint(endBlock);
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedWhileNode &node) {
        auto currentFunc = functionMap_[currentFunctionName_];
        if (!currentFunc)
            return;

        std::string suffix = std::to_string(ifCounter_++);

        auto condBlock = builder_.createBasicBlock("while.cond." + suffix);
        auto bodyBlock = builder_.createBasicBlock("while.body." + suffix);
        auto endBlock = builder_.createBasicBlock("while.end." + suffix);

        builder_.createBr(condBlock->getName());
        currentFunc->addBasicBlock(condBlock);
        builder_.setInsertPoint(condBlock);

        node.getCondition()->accept(*this);
        auto condVal = lastValue_;
        if (!condVal) {
            lastValue_ = nullptr;
            return;
        }

        builder_.createCondBr(condVal, bodyBlock->getName(), endBlock->getName());
        currentFunc->addBasicBlock(bodyBlock);
        builder_.setInsertPoint(bodyBlock);

        loopStack_.push_back({condBlock->getName(), endBlock->getName()});
        node.getBody()->accept(*this);
        loopStack_.pop_back();

        auto curBlock = builder_.getInsertPoint();
        if (curBlock) {
            auto &insts = curBlock->getInstructions();
            if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                builder_.createBr(condBlock->getName());
            }
        }

        currentFunc->addBasicBlock(endBlock);
        builder_.setInsertPoint(endBlock);
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedForNode &node) {
        auto currentFunc = functionMap_[currentFunctionName_];
        if (!currentFunc)
            return;

        std::string suffix = std::to_string(ifCounter_++);

        if (node.getInit()) {
            node.getInit()->accept(*this);
        }

        auto condBlock = builder_.createBasicBlock("for.cond." + suffix);
        auto bodyBlock = builder_.createBasicBlock("for.body." + suffix);
        auto iterBlock = builder_.createBasicBlock("for.iter." + suffix);
        auto endBlock = builder_.createBasicBlock("for.end." + suffix);

        builder_.createBr(condBlock->getName());
        currentFunc->addBasicBlock(condBlock);
        builder_.setInsertPoint(condBlock);

        std::shared_ptr<Value> condVal;
        if (node.getCondition()) {
            node.getCondition()->accept(*this);
            condVal = lastValue_;
        } else {
            condVal = std::make_shared<ImmediateValue>(Type::getBoolType(), "1");
        }

        if (!condVal) {
            lastValue_ = nullptr;
            return;
        }

        builder_.createCondBr(condVal, bodyBlock->getName(), endBlock->getName());
        currentFunc->addBasicBlock(bodyBlock);
        builder_.setInsertPoint(bodyBlock);

        // Continue jumps to the iteration (operation) block
        loopStack_.push_back({iterBlock->getName(), endBlock->getName()});
        node.getBody()->accept(*this);
        loopStack_.pop_back();

        auto curBlock = builder_.getInsertPoint();
        if (curBlock) {
            auto &insts = curBlock->getInstructions();
            if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                builder_.createBr(iterBlock->getName());
            }
        }

        currentFunc->addBasicBlock(iterBlock);
        builder_.setInsertPoint(iterBlock);

        if (node.getOperation()) {
            node.getOperation()->accept(*this);
        }

        curBlock = builder_.getInsertPoint();
        if (curBlock) {
            auto &insts = curBlock->getInstructions();
            if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                builder_.createBr(condBlock->getName());
            }
        }

        currentFunc->addBasicBlock(endBlock);
        builder_.setInsertPoint(endBlock);
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedBreakNode &node) {
        if (loopStack_.empty())
            return;
        auto curBlock = builder_.getInsertPoint();
        if (curBlock) {
            auto &insts = curBlock->getInstructions();
            if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                builder_.createBr(loopStack_.back().endBlockName);
            }
        }
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedContinueNode &node) {
        if (loopStack_.empty())
            return;
        auto curBlock = builder_.getInsertPoint();
        if (curBlock) {
            auto &insts = curBlock->getInstructions();
            if (insts.empty() || !isTerminator(insts.back()->getOpcode())) {
                builder_.createBr(loopStack_.back().condBlockName);
            }
        }
        lastValue_ = nullptr;
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

        // Evaluate arguments first so we can infer parameter types for unknown callees
        std::vector<std::shared_ptr<Value>> argValues;
        for (const auto &arg : node.getArguments()) {
            arg->accept(*this);
            if (lastValue_)
                argValues.push_back(lastValue_);
        }

        // Mangle __builtin_ function names based on argument types (or return type for no-arg builtins)
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
                // No-arg builtins: mangle based on return type
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
        auto varName = node.getName();
        auto varIRType = toIRType(node.getType());

        // Allocate a local slot for the variable
        auto allocaInst = builder_.createAlloca(
            builder_.generateUniqueName(varName + "."), varIRType);
        allocaMap_[varName] = allocaInst;

        if (node.getInitializer()) {
            node.getInitializer()->accept(*this);
            if (lastValue_) {
                // Materialize ImmediateValue into a Constant instruction if needed
                std::shared_ptr<Value> storeVal = lastValue_;
                if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(lastValue_)) {
                    storeVal = builder_.createConstant(
                        builder_.generateUniqueName(""),
                        imm->getType(), imm);
                }
                builder_.createStore(storeVal, allocaInst);
                lastValue_ = nullptr;
            }
        }
    }

    void IRGenerator::visit(Compiler::Semantic::TypedArrayDeclarationNode &node) {
        auto varName = node.getName();
        auto elementIRType = toIRType(node.getElementType());

        // Visit size expression
        node.getSize()->accept(*this);
        auto sizeVal = lastValue_;
        if (!sizeVal) {
            lastValue_ = nullptr;
            return;
        }

        // Materialize size ImmediateValue if needed
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(sizeVal)) {
            sizeVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // Create NewArray instruction
        auto newArrayInst = builder_.createNewArray(
            builder_.generateUniqueName("arr." + varName + "."),
            elementIRType, sizeVal);

        // Allocate a local slot for the array reference
        auto arrIRType = std::make_shared<IR::ArrayType>(elementIRType);
        auto allocaInst = builder_.createAlloca(
            builder_.generateUniqueName(varName + "."), arrIRType);
        allocaMap_[varName] = allocaInst;

        // Store the new array into the alloca
        builder_.createStore(newArrayInst, allocaInst);
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedVariableNode &node) {
        auto it = allocaMap_.find(node.getName());
        if (it != allocaMap_.end()) {
            auto loadType = toIRType(node.getType());
            lastValue_ = builder_.createLoad(
                builder_.generateUniqueName(""),
                it->second,
                loadType);
        } else {
            // Variable not found in alloca map; fallback (shouldn't happen after semantic analysis)
            lastValue_ = nullptr;
        }
    }

    void IRGenerator::visit(Compiler::Semantic::TypedArrayIndexAccessNode &node) {
        auto it = allocaMap_.find(node.getArrayName());
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        // node.getType() is the element type (T), not ref<T>
        auto elemIRType = toIRType(node.getType());

        // Load the array reference from the alloca slot
        auto allocaInst = it->second;
        auto arrIRType = std::make_shared<IR::ArrayType>(elemIRType);
        auto arrayVal = builder_.createLoad(
            builder_.generateUniqueName(""), allocaInst, arrIRType);

        // Visit the index expression
        node.getIndex()->accept(*this);
        auto indexVal = lastValue_;
        if (!indexVal) {
            lastValue_ = nullptr;
            return;
        }

        // Materialize ImmediateValue if needed
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(indexVal)) {
            indexVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // Create ref to array element, then auto-dereference for value reading
        auto refType = std::make_shared<IR::RefType>(elemIRType);
        auto arrRef = builder_.createArrRef(
            builder_.generateUniqueName(""), arrayVal, indexVal, refType);
        lastValue_ = builder_.createRefLoad(
            builder_.generateUniqueName(""), arrRef, elemIRType);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedArrayIndexAssignmentNode &node) {
        auto it = allocaMap_.find(node.getArrayName());
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        // Extract element type - node.getType() is the element type (T), not ref<T>
        auto elemIRType = toIRType(node.getType());

        // Load the array reference from the alloca slot
        auto allocaInst = it->second;
        auto arrIRType = std::make_shared<IR::ArrayType>(elemIRType);
        auto arrayVal = builder_.createLoad(
            builder_.generateUniqueName(""), allocaInst, arrIRType);

        // Visit the index expression
        node.getIndex()->accept(*this);
        auto indexVal = lastValue_;
        if (!indexVal) {
            lastValue_ = nullptr;
            return;
        }

        // Materialize ImmediateValue if needed
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(indexVal)) {
            indexVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // Visit the value expression
        node.getValue()->accept(*this);
        auto valueVal = lastValue_;
        if (!valueVal) {
            lastValue_ = nullptr;
            return;
        }

        // Materialize ImmediateValue if needed
        std::shared_ptr<Value> storeVal = valueVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(valueVal)) {
            storeVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // Create ref to array element, then store through it
        auto refType = std::make_shared<IR::RefType>(elemIRType);
        auto arrRef = builder_.createArrRef(
            builder_.generateUniqueName(""), arrayVal, indexVal, refType);

        builder_.createRefStore(arrRef, storeVal);
        lastValue_ = storeVal;
    }

    //     // Load the array reference from the alloca slot
    //     auto allocaInst = it->second;
    //     auto arrIRType = std::make_shared<IR::ArrayType>(toIRType(node.getType()));
    //     auto arrayVal = builder_.createLoad(
    //         builder_.generateUniqueName(""), allocaInst, arrIRType);
    //
    //     // Visit the index expression
    //     node.getIndex()->accept(*this);
    //     auto indexVal = lastValue_;
    //     if (!indexVal) {
    //         lastValue_ = nullptr;
    //         return;
    //     }
    //
    //     // Materialize ImmediateValue if needed
    //     if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(indexVal)) {
    //         indexVal = builder_.createConstant(
    //             builder_.generateUniqueName(""), imm->getType(), imm);
    //     }
    //
    //     // ArrLoad
    //     auto elemIRType = toIRType(node.getType());
    //     lastValue_ = builder_.createArrLoad(
    //         builder_.generateUniqueName(""), arrayVal, indexVal, elemIRType);
    // }

    // void IRGenerator::visit(Compiler::Semantic::TypedArrayIndexAssignmentNode &node) {
    //     auto it = allocaMap_.find(node.getArrayName());
    //     if (it == allocaMap_.end()) {
    //         lastValue_ = nullptr;
    //         return;
    //     }
    //
    //     // Load the array reference
    //     auto allocaInst = it->second;
    //     auto elemIRType = toIRType(node.getType());
    //     auto arrIRType = std::make_shared<IR::ArrayType>(elemIRType);
    //     auto arrayVal = builder_.createLoad(
    //         builder_.generateUniqueName(""), allocaInst, arrIRType);
    //
    //     // Visit the index expression
    //     node.getIndex()->accept(*this);
    //     auto indexVal = lastValue_;
    //     if (!indexVal) {
    //         lastValue_ = nullptr;
    //         return;
    //     }
    //     if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(indexVal)) {
    //         indexVal = builder_.createConstant(
    //             builder_.generateUniqueName(""), imm->getType(), imm);
    //     }
    //
    //     // Visit the value expression
    //     node.getValue()->accept(*this);
    //     auto valueVal = lastValue_;
    //     if (!valueVal) {
    //         lastValue_ = nullptr;
    //         return;
    //     }
    //
    //     // Materialize ImmediateValue if needed
    //     std::shared_ptr<Value> storeVal = valueVal;
    //     if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(valueVal)) {
    //         storeVal = builder_.createConstant(
    //             builder_.generateUniqueName(""), imm->getType(), imm);
    //     }
    //
    //     // ArrStore
    //     builder_.createArrStore(arrayVal, indexVal, storeVal);
    //
    //     // Assignment expression yields the stored value
    //     lastValue_ = storeVal;
    // }

    void IRGenerator::visit(Compiler::Semantic::TypedUnaryOpNode &node) {
        node.getOperand()->accept(*this);
        auto operand = lastValue_;
        if (!operand) {
            lastValue_ = nullptr;
            return;
        }

        Instruction::Opcode irOp;
        switch (node.getOp()) {
        case Compiler::UnaryOpType::BitNot:
            irOp = Instruction::Opcode::BitNot;
            break;
        case Compiler::UnaryOpType::LogicalNot:
            irOp = Instruction::Opcode::LogicalNot;
            break;
        case Compiler::UnaryOpType::Negate: {
            auto zeroImm = std::make_shared<ImmediateValue>(operand->getType(), "0");
            auto zeroConst = builder_.createConstant(
                builder_.generateUniqueName(""), operand->getType(), zeroImm);
            auto result = builder_.createBinaryOp(
                Instruction::Opcode::Sub, builder_.generateUniqueName(""), zeroConst, operand);
            lastValue_ = result;
            return;
        }
        default:
            lastValue_ = nullptr;
            return;
        }

        auto result = builder_.createUnaryOp(irOp, builder_.generateUniqueName(""), operand);
        lastValue_ = result;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedBinaryOpNode &node) {
        node.getLeft()->accept(*this);
        auto lhs = lastValue_;

        node.getRight()->accept(*this);
        auto rhs = lastValue_;

        if (!lhs || !rhs) {
            lastValue_ = nullptr;
            return;
        }

        // Type promotion: if one operand is i64 and the other is i32,
        // promote the i32 to i64 so createBinaryOp's type check passes.
        // For ImmediateValue (literal) operands, create a new i64 ImmediateValue.
        // For non-immediate operands (variables), insert a SExt instruction.
        if (!lhs->getType()->isEqual(rhs->getType().get())) {
            if (lhs->getType()->isInt64() && rhs->getType()->isInt32()) {
                if (auto rhsImm = std::dynamic_pointer_cast<ImmediateValue>(rhs)) {
                    rhs = std::make_shared<ImmediateValue>(
                        Type::getInt64Type(), rhsImm->getLiteralValue());
                } else {
                    rhs = builder_.createSExt(
                        builder_.generateUniqueName(""), rhs, Type::getInt64Type());
                }
            } else if (lhs->getType()->isInt32() && rhs->getType()->isInt64()) {
                if (auto lhsImm = std::dynamic_pointer_cast<ImmediateValue>(lhs)) {
                    lhs = std::make_shared<ImmediateValue>(
                        Type::getInt64Type(), lhsImm->getLiteralValue());
                } else {
                    lhs = builder_.createSExt(
                        builder_.generateUniqueName(""), lhs, Type::getInt64Type());
                }
            }
        }

        Instruction::Opcode irOp;
        switch (node.getOp()) {
        case Compiler::BinaryOpType::Add:
            irOp = Instruction::Opcode::Add;
            break;
        case Compiler::BinaryOpType::Sub:
            irOp = Instruction::Opcode::Sub;
            break;
        case Compiler::BinaryOpType::Mul:
            irOp = Instruction::Opcode::Mul;
            break;
        case Compiler::BinaryOpType::Div:
            irOp = Instruction::Opcode::Div;
            break;
        case Compiler::BinaryOpType::Mod:
            irOp = Instruction::Opcode::Mod;
            break;
        case Compiler::BinaryOpType::BitAnd:
            irOp = Instruction::Opcode::BitAnd;
            break;
        case Compiler::BinaryOpType::BitOr:
            irOp = Instruction::Opcode::BitOr;
            break;
        case Compiler::BinaryOpType::BitXor:
            irOp = Instruction::Opcode::BitXor;
            break;
        case Compiler::BinaryOpType::Shl:
            irOp = Instruction::Opcode::Shl;
            break;
        case Compiler::BinaryOpType::Shr:
            irOp = Instruction::Opcode::Shr;
            break;
        }

        auto result = builder_.createBinaryOp(irOp, builder_.generateUniqueName(""), lhs, rhs);
        lastValue_ = result;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedCastNode &node) {
        node.getOperand()->accept(*this);
        auto operand = lastValue_;
        if (!operand) {
            lastValue_ = nullptr;
            return;
        }

        auto targetIRType = toIRType(node.getType());
        auto operandIRType = operand->getType();

        // Materialize ImmediateValue into a Constant instruction first if needed,
        // so we have a proper SSA value to cast
        std::shared_ptr<Value> castOperand = operand;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(operand)) {
            auto constInst = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
            castOperand = constInst;
        }

        if (operandIRType->isInt32() && targetIRType->isInt64()) {
            lastValue_ = builder_.createSExt(
                builder_.generateUniqueName(""), castOperand, targetIRType);
        } else if (operandIRType->isInt64() && targetIRType->isInt32()) {
            lastValue_ = builder_.createTrunc(
                builder_.generateUniqueName(""), castOperand, targetIRType);
        } else {
            // Same type — no-op, just forward
            lastValue_ = castOperand;
        }
    }

    void IRGenerator::visit(Compiler::Semantic::TypedComparisonNode &node) {
        node.getLeft()->accept(*this);
        auto lhs = lastValue_;

        node.getRight()->accept(*this);
        auto rhs = lastValue_;

        if (!lhs || !rhs) {
            lastValue_ = nullptr;
            return;
        }

        if (!lhs->getType()->isEqual(rhs->getType().get())) {
            if (lhs->getType()->isInt64() && rhs->getType()->isInt32()) {
                if (auto rhsImm = std::dynamic_pointer_cast<ImmediateValue>(rhs))
                    rhs = std::make_shared<ImmediateValue>(Type::getInt64Type(), rhsImm->getLiteralValue());
                else
                    rhs = builder_.createSExt(builder_.generateUniqueName(""), rhs, Type::getInt64Type());
            } else if (lhs->getType()->isInt32() && rhs->getType()->isInt64()) {
                if (auto lhsImm = std::dynamic_pointer_cast<ImmediateValue>(lhs))
                    lhs = std::make_shared<ImmediateValue>(Type::getInt64Type(), lhsImm->getLiteralValue());
                else
                    lhs = builder_.createSExt(builder_.generateUniqueName(""), lhs, Type::getInt64Type());
            }
        }

        Instruction::Opcode irOp;
        switch (node.getOp()) {
        case Compiler::ComparisonOpType::Eq: irOp = Instruction::Opcode::Eq; break;
        case Compiler::ComparisonOpType::Ne: irOp = Instruction::Opcode::Ne; break;
        case Compiler::ComparisonOpType::Lt: irOp = Instruction::Opcode::Lt; break;
        case Compiler::ComparisonOpType::Gt: irOp = Instruction::Opcode::Gt; break;
        case Compiler::ComparisonOpType::Le: irOp = Instruction::Opcode::Le; break;
        case Compiler::ComparisonOpType::Ge: irOp = Instruction::Opcode::Ge; break;
        }

        lastValue_ = builder_.createCompare(irOp, builder_.generateUniqueName(""), lhs, rhs);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPrefixOpNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto varIRType = toIRType(node.getType());

        // Load current value
        auto loadInst = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, varIRType);

        // Create immediate 1 of the appropriate type
        auto oneImm = std::make_shared<ImmediateValue>(varIRType, "1");
        auto oneConst = builder_.createConstant(
            builder_.generateUniqueName(""), varIRType, oneImm);

        // Add or subtract 1
        Instruction::Opcode arithOp = (node.getOp() == Compiler::IncDecOpType::Increment)
                                          ? Instruction::Opcode::Add
                                          : Instruction::Opcode::Sub;
        auto result = builder_.createBinaryOp(
            arithOp, builder_.generateUniqueName(""), loadInst, oneConst);

        // Store result back
        builder_.createStore(result, it->second);

        // Prefix expression yields the new value
        lastValue_ = result;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPostfixOpNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto varIRType = toIRType(node.getType());

        // Load current value (this is the old value, which is the result)
        auto loadInst = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, varIRType);

        // Create immediate 1 of the appropriate type
        auto oneImm = std::make_shared<ImmediateValue>(varIRType, "1");
        auto oneConst = builder_.createConstant(
            builder_.generateUniqueName(""), varIRType, oneImm);

        // Add or subtract 1
        Instruction::Opcode arithOp = (node.getOp() == Compiler::IncDecOpType::Increment)
                                          ? Instruction::Opcode::Add
                                          : Instruction::Opcode::Sub;
        auto newVal = builder_.createBinaryOp(
            arithOp, builder_.generateUniqueName(""), loadInst, oneConst);

        // Store new value back
        builder_.createStore(newVal, it->second);

        // Postfix expression yields the OLD value
        lastValue_ = loadInst;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedAssignmentNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        node.getRHS()->accept(*this);
        if (lastValue_) {
            // Materialize ImmediateValue if needed
            std::shared_ptr<Value> storeVal = lastValue_;
            if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(lastValue_)) {
                storeVal = builder_.createConstant(
                    builder_.generateUniqueName(""),
                    imm->getType(), imm);
            }
            builder_.createStore(storeVal, it->second);
            // Assignment expression yields the stored value (for potential chaining)
            lastValue_ = storeVal;
        }
    }

    void IRGenerator::visit(Compiler::Semantic::TypedRefCreateNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto refIRType = toIRType(node.getType());
        lastValue_ = builder_.createRefCreate(
            builder_.generateUniqueName(""), refIRType, it->second);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedRefLoadNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        // Load the ref value from the alloca
        auto refIRType = std::make_shared<IR::RefType>(toIRType(node.getType()));
        auto refVal = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, refIRType);

        // Dereference the ref to get the underlying value
        auto elemIRType = toIRType(node.getType());
        lastValue_ = builder_.createRefLoad(
            builder_.generateUniqueName(""), refVal, elemIRType);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedNullLiteralNode &node) {
        // null pointer is represented as slot index -1 (int32)
        lastValue_ = std::make_shared<ImmediateValue>(
            Type::getInt32Type(), "-1");
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPtrOffsetNode &node) {
        auto ptrVarName = node.getPtrVarName();
        auto it = allocaMap_.find(ptrVarName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        // Load the pointer value from the alloca
        auto ptrIRType = std::make_shared<IR::PtrType>(Type::getInt32Type());
        auto ptrVal = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, ptrIRType);

        // Materialize ptr load if needed
        std::shared_ptr<Value> ptrForArith = ptrVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(ptrVal)) {
            ptrForArith = builder_.createConstant(
                builder_.generateUniqueName(""), Type::getInt32Type(), imm);
        }

        // Evaluate the offset expression
        node.getOffset()->accept(*this);
        auto offsetVal = lastValue_;
        if (!offsetVal) {
            lastValue_ = nullptr;
            return;
        }
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(offsetVal)) {
            offsetVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // Add/subtract offset from ptr slot index
        auto arithOp = node.getIsAdd() ? Instruction::Opcode::Add : Instruction::Opcode::Sub;
        std::vector<std::shared_ptr<Value>> arithOperands = {ptrForArith, offsetVal};
        auto newSlotInst = std::make_shared<Instruction>(
            arithOp, Type::getInt32Type(), arithOperands,
            builder_.generateUniqueName(""));
        builder_.addInstruction(newSlotInst);

        // Create a pointer directly from the computed slot index.
        // Use PtrCreate with the computed slot as operand (not an alloca).
        auto ptrResultType = toIRType(node.getType());
        std::vector<std::shared_ptr<Value>> createOperands = {newSlotInst};
        auto ptrResult = std::make_shared<Instruction>(
            Instruction::Opcode::PtrCreate, ptrResultType, createOperands,
            builder_.generateUniqueName(""));
        builder_.addInstruction(ptrResult);
        lastValue_ = ptrResult;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPtrDiffNode &node) {
        auto leftIt = allocaMap_.find(node.getLeftPtrName());
        auto rightIt = allocaMap_.find(node.getRightPtrName());
        if (leftIt == allocaMap_.end() || rightIt == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        // Load left pointer value
        auto ptrIRType = std::make_shared<IR::PtrType>(Type::getInt32Type());
        auto leftPtrVal = builder_.createLoad(
            builder_.generateUniqueName(""), leftIt->second, ptrIRType);

        // Load right pointer value
        auto rightPtrVal = builder_.createLoad(
            builder_.generateUniqueName(""), rightIt->second, ptrIRType);

        // Materialize if needed
        std::shared_ptr<Value> leftForArith = leftPtrVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(leftPtrVal)) {
            leftForArith = builder_.createConstant(
                builder_.generateUniqueName(""), Type::getInt32Type(), imm);
        }
        std::shared_ptr<Value> rightForArith = rightPtrVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(rightPtrVal)) {
            rightForArith = builder_.createConstant(
                builder_.generateUniqueName(""), Type::getInt32Type(), imm);
        }

        // Subtract right from left, bypassing type checks
        std::vector<std::shared_ptr<Value>> operands = {leftForArith, rightForArith};
        auto result = std::make_shared<Instruction>(
            Instruction::Opcode::Sub, Type::getInt32Type(), operands,
            builder_.generateUniqueName(""));
        builder_.addInstruction(result);
        lastValue_ = result;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedRefAssignNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        // Load the ref value from the alloca
        auto refIRType = std::make_shared<IR::RefType>(toIRType(node.getType()));
        auto refVal = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, refIRType);

        // Visit the RHS
        node.getRHS()->accept(*this);
        if (!lastValue_) {
            lastValue_ = nullptr;
            return;
        }

        // Materialize ImmediateValue if needed
        std::shared_ptr<Value> storeVal = lastValue_;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(lastValue_)) {
            storeVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // Store through the ref
        builder_.createRefStore(refVal, storeVal);
        lastValue_ = storeVal;
    }

    void IRGenerator::visit(Compiler::Semantic::TypedUnsafeBlockNode &node) {
        node.getBody()->accept(*this);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPtrFromArrayNode &node) {
        auto varName = node.getArrayName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        // node.getType() is ptr<T> — extract T for the array element type
        auto &semPtrType = static_cast<const Sem::PointerType &>(*node.getType());
        auto elemIRType = toIRType(semPtrType.getElementType());

        // Load the array value from the alloca slot
        auto arrAlloca = it->second;
        auto arrIRType = std::make_shared<IR::ArrayType>(elemIRType);
        auto arrayVal = builder_.createLoad(
            builder_.generateUniqueName(""), arrAlloca, arrIRType);

        // Create a pointer from the array (points to element 0)
        auto ptrIRType = toIRType(node.getType());
        lastValue_ = builder_.createPtrFromArray(
            builder_.generateUniqueName(""), ptrIRType, arrayVal);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPtrCreateNode &node) {
        auto varName = node.getVariableName();
        auto it = allocaMap_.find(varName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        auto ptrIRType = toIRType(node.getType());
        lastValue_ = builder_.createPtrCreate(
            builder_.generateUniqueName(""), ptrIRType, it->second);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPtrLoadNode &node) {
        auto ptrVarName = node.getPtrVarName();
        auto it = allocaMap_.find(ptrVarName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        // Load the pointer value from the alloca
        auto ptrIRType = std::make_shared<IR::PtrType>(toIRType(node.getType()));
        auto ptrVal = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, ptrIRType);

        // Dereference the pointer to get the underlying value
        auto elemIRType = toIRType(node.getType());
        lastValue_ = builder_.createPtrLoad(
            builder_.generateUniqueName(""), ptrVal, elemIRType);
    }

    void IRGenerator::visit(Compiler::Semantic::TypedPtrStoreNode &node) {
        auto ptrVarName = node.getPtrVarName();
        auto it = allocaMap_.find(ptrVarName);
        if (it == allocaMap_.end()) {
            lastValue_ = nullptr;
            return;
        }

        // Load the pointer value from the alloca
        auto ptrIRType = std::make_shared<IR::PtrType>(toIRType(node.getType()));
        auto ptrVal = builder_.createLoad(
            builder_.generateUniqueName(""), it->second, ptrIRType);

        // Visit the RHS
        node.getRHS()->accept(*this);
        if (!lastValue_) {
            lastValue_ = nullptr;
            return;
        }

        // Materialize ImmediateValue if needed
        std::shared_ptr<Value> storeVal = lastValue_;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(lastValue_)) {
            storeVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // Store through the pointer
        builder_.createPtrStore(ptrVal, storeVal);
        lastValue_ = storeVal;
    }

    void IRGenerator::visit(Sem::TypedNewNode &node) {
        std::shared_ptr<Value> initVal;
        if (node.getInitializer()) {
            node.getInitializer()->accept(*this);
            initVal = lastValue_;
            if (!initVal) {
                lastValue_ = nullptr;
                return;
            }
        } else {
            auto elemIRType = toIRType(node.getElementType());
            if (elemIRType->isInt32()) {
                initVal = std::make_shared<ImmediateValue>(Type::getInt32Type(), "0");
            } else if (elemIRType->isInt64()) {
                initVal = std::make_shared<ImmediateValue>(Type::getInt64Type(), "0");
            } else if (elemIRType->isBool()) {
                initVal = std::make_shared<ImmediateValue>(Type::getBoolType(), "0");
            } else {
                lastValue_ = nullptr;
                return;
            }
        }

        // Materialize ImmediateValue if needed
        std::shared_ptr<Value> materialized = initVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(initVal)) {
            materialized = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        auto ptrType = toIRType(node.getType());
        lastValue_ = builder_.createNewHeap(
            builder_.generateUniqueName(""), ptrType, materialized);
    }

    void IRGenerator::visit(Sem::TypedDeleteNode &node) {
        node.getPtrExpr()->accept(*this);
        auto ptrVal = lastValue_;
        if (!ptrVal) {
            lastValue_ = nullptr;
            return;
        }

        // Materialize ImmediateValue if needed
        std::shared_ptr<Value> materialized = ptrVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(ptrVal)) {
            materialized = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        builder_.createDeleteHeap(materialized);
        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedFixedNode &node) {
        // Visit init expression to get the pointer value
        node.getInitExpr()->accept(*this);
        auto initVal = lastValue_;
        if (!initVal) {
            lastValue_ = nullptr;
            return;
        }

        // Materialize ImmediateValue if needed
        std::shared_ptr<Value> materialized = initVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(initVal)) {
            materialized = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // Emit PinArray
        builder_.createPinArray(materialized);

        // Alloca and store the pointer in the fixed variable
        auto ptrIRType = toIRType(node.getPtrType());
        auto allocaInst = builder_.createAlloca(node.getVarName(), ptrIRType);
        allocaMap_[node.getVarName()] = allocaInst;
        builder_.createStore(materialized, allocaInst);

        // Visit the body
        node.getBody()->accept(*this);

        // Emit UnpinArray
        auto loadedPtr = builder_.createLoad(
            builder_.generateUniqueName(""), allocaInst, ptrIRType);
        builder_.createUnpinArray(loadedPtr);

        lastValue_ = nullptr;
    }

    void IRGenerator::visit(Sem::TypedPtrIndexAccessNode &node) {
        // Visit the pointer expression
        node.getPtrExpr()->accept(*this);
        auto ptrVal = lastValue_;
        if (!ptrVal) {
            lastValue_ = nullptr;
            return;
        }

        // Materialize ImmediateValue if needed
        std::shared_ptr<Value> ptrMaterialized = ptrVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(ptrVal)) {
            ptrMaterialized = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // Visit the index expression
        node.getIndex()->accept(*this);
        auto indexVal = lastValue_;
        if (!indexVal) {
            lastValue_ = nullptr;
            return;
        }
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(indexVal)) {
            indexVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // node.getType() is the element type T
        auto elemIRType = toIRType(node.getType());
        auto refType = std::make_shared<IR::RefType>(elemIRType);

        auto ptrIndexRef = builder_.createPtrIndexRef(
            builder_.generateUniqueName(""), ptrMaterialized, indexVal, refType);

        // Auto-dereference the ref to get the element value
        lastValue_ = builder_.createRefLoad(
            builder_.generateUniqueName(""), ptrIndexRef, elemIRType);
    }

    void IRGenerator::visit(Sem::TypedPtrIndexAssignmentNode &node) {
        // Visit the pointer expression
        node.getPtrExpr()->accept(*this);
        auto ptrVal = lastValue_;
        if (!ptrVal) {
            lastValue_ = nullptr;
            return;
        }

        // Materialize ImmediateValue if needed
        std::shared_ptr<Value> ptrMaterialized = ptrVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(ptrVal)) {
            ptrMaterialized = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // Visit the index expression
        node.getIndex()->accept(*this);
        auto indexVal = lastValue_;
        if (!indexVal) {
            lastValue_ = nullptr;
            return;
        }
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(indexVal)) {
            indexVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // Visit the value expression
        node.getValue()->accept(*this);
        auto valueVal = lastValue_;
        if (!valueVal) {
            lastValue_ = nullptr;
            return;
        }
        std::shared_ptr<Value> storeVal = valueVal;
        if (auto imm = std::dynamic_pointer_cast<ImmediateValue>(valueVal)) {
            storeVal = builder_.createConstant(
                builder_.generateUniqueName(""), imm->getType(), imm);
        }

        // Create ref to ptr + index, then store through it
        auto refType = std::make_shared<IR::RefType>(Type::getInt32Type());
        auto ptrIndexRef = builder_.createPtrIndexRef(
            builder_.generateUniqueName(""), ptrMaterialized, indexVal, refType);

        builder_.createRefStore(ptrIndexRef, storeVal);
        lastValue_ = storeVal;
    }
} // namespace Ryntra::IR
