#pragma once

#include "Compiler/Semantic/TypedAST.h"
#include "IRBuilder.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace Ryntra::IR {
    class IRGenerator : public Compiler::Semantic::ITypedVisitor {
    public:
        IRGenerator();

        std::shared_ptr<Module> generate(Compiler::Semantic::TypedProgramNode &program,
                                         const std::string &moduleName = "module");

        void visit(Compiler::Semantic::TypedProgramNode &node) override;
        void visit(Compiler::Semantic::TypedFunctionDefinitionNode &node) override;
        void visit(Compiler::Semantic::TypedBlockNode &node) override;
        void visit(Compiler::Semantic::TypedIfNode &node) override;
        void visit(Compiler::Semantic::TypedWhileNode &node) override;
        void visit(Compiler::Semantic::TypedForNode &node) override;
        void visit(Compiler::Semantic::TypedBreakNode &node) override;
        void visit(Compiler::Semantic::TypedContinueNode &node) override;
        void visit(Compiler::Semantic::TypedExpressionStatementNode &node) override;
        void visit(Compiler::Semantic::TypedReturnNode &node) override;
        void visit(Compiler::Semantic::TypedStringLiteralNode &node) override;
        void visit(Compiler::Semantic::TypedBoolLiteralNode &node) override;
        void visit(Compiler::Semantic::TypedIntegerLiteralNode &node) override;
        void visit(Compiler::Semantic::TypedLongLiteralNode &node) override;
        void visit(Compiler::Semantic::TypedIdentifierNode &node) override;
        void visit(Compiler::Semantic::TypedFunctionCallNode &node) override;
        void visit(Compiler::Semantic::TypedVariableNode &node) override;
        void visit(Compiler::Semantic::TypedVariableDeclarationNode &node) override;
        void visit(Compiler::Semantic::TypedArrayDeclarationNode &node) override;
        void visit(Compiler::Semantic::TypedArrayIndexAccessNode &node) override;
        void visit(Compiler::Semantic::TypedArrayIndexAssignmentNode &node) override;
        void visit(Compiler::Semantic::TypedUnaryOpNode &node) override;
        void visit(Compiler::Semantic::TypedBinaryOpNode &node) override;
        void visit(Compiler::Semantic::TypedCastNode &node) override;
        void visit(Compiler::Semantic::TypedComparisonNode &node) override;
        void visit(Compiler::Semantic::TypedConditionalAndNode &node) override;
        void visit(Compiler::Semantic::TypedConditionalOrNode &node) override;
        void visit(Compiler::Semantic::TypedAssignmentNode &node) override;
        void visit(Compiler::Semantic::TypedPrefixOpNode &node) override;
        void visit(Compiler::Semantic::TypedPostfixOpNode &node) override;
        void visit(Compiler::Semantic::TypedRefCreateNode &node) override;
        void visit(Compiler::Semantic::TypedRefLoadNode &node) override;
        void visit(Compiler::Semantic::TypedRefAssignNode &node) override;
        void visit(Compiler::Semantic::TypedUnsafeBlockNode &node) override;
        void visit(Compiler::Semantic::TypedPtrCreateNode &node) override;
        void visit(Compiler::Semantic::TypedPtrLoadNode &node) override;
        void visit(Compiler::Semantic::TypedPtrStoreNode &node) override;
        void visit(Compiler::Semantic::TypedNullLiteralNode &node) override;
        void visit(Compiler::Semantic::TypedPtrOffsetNode &node) override;
        void visit(Compiler::Semantic::TypedPtrDiffNode &node) override;
        void visit(Compiler::Semantic::TypedNewNode &node) override;
        void visit(Compiler::Semantic::TypedDeleteNode &node) override;
        void visit(Compiler::Semantic::TypedFixedNode &node) override;
        void visit(Compiler::Semantic::TypedPtrIndexAccessNode &node) override;
        void visit(Compiler::Semantic::TypedPtrIndexAssignmentNode &node) override;
        void visit(Compiler::Semantic::TypedPtrFromArrayNode &node) override;
        void visit(Compiler::Semantic::TypedFunctionAddressNode &node) override;
        void visit(Compiler::Semantic::TypedFunctionPointerCallNode &node) override;
        void visit(Compiler::Semantic::TypedStructDeclarationNode &node) override;
        void visit(Compiler::Semantic::TypedSelfExpressionNode &node) override;
        void visit(Compiler::Semantic::TypedMemberAccessNode &node) override;
        void visit(Compiler::Semantic::TypedMemberAssignmentNode &node) override;
        void visit(Compiler::Semantic::TypedMethodCallNode &node) override;

    private:
        IRBuilder builder_;

        // Last expression value produced by visiting an expression node
        std::shared_ptr<Value> lastValue_;

        // Map from function name -> IR Function (for call resolution)
        std::unordered_map<std::string, std::shared_ptr<Function>> functionMap_;

        // Current function name being generated (for adding basic blocks)
        std::string currentFunctionName_;

        // Counter for unique if-block names
        int ifCounter_ = 0;

        // Check if an opcode is a terminator (ends a basic block)
        bool isTerminator(Instruction::Opcode opcode) const {
            return opcode == Instruction::Opcode::Return ||
                   opcode == Instruction::Opcode::Br ||
                   opcode == Instruction::Opcode::CondBr;
        }

        struct LoopInfo {
            std::string condBlockName;
            std::string endBlockName;
        };
        std::vector<LoopInfo> loopStack_;

        // Map from variable name -> Alloca instruction (for load/store)
        std::unordered_map<std::string, std::shared_ptr<Instruction>> allocaMap_;

        // Struct support -------------------------------------------------------
        // Canonical IR struct type per struct name (shared so field layout is stable).
        std::unordered_map<std::string, std::shared_ptr<StructType>> structTypeMap_;
        // The receiver (`this`) of the method/constructor currently being generated.
        // It is the incoming argument value itself, so `self` needs no alloca.
        std::shared_ptr<Value> currentSelfValue_;

        // Wrap an ImmediateValue in a materialized Constant instruction.
        std::shared_ptr<Value> materialize(const std::shared_ptr<Value> &value);
        // Compute the address (pointer) of an lvalue expression, or nullptr.
        std::shared_ptr<Value> addressOf(const std::shared_ptr<Compiler::Semantic::TypedExpressionNode> &expr);
        // Compute a pointer to a struct field via FieldPtr.
        std::shared_ptr<Value> createFieldPtr(const std::shared_ptr<Value> &base,
                                              const std::shared_ptr<Compiler::Semantic::Type> &ownerType,
                                              const std::string &fieldName);
        // Mangle a method/constructor into a unique IR function name.
        std::string mangleMethod(const std::string &structName, const std::string &methodName,
                                 const std::vector<std::shared_ptr<Compiler::Semantic::Type>> &paramTypes);
        // Register IR functions for every struct method/constructor.
        void registerStructFunctions(
            const std::vector<std::shared_ptr<Compiler::Semantic::TypedStructDeclarationNode>> &structs);
        // Emit the body of a function/method/constructor.
        void generateCallableBody(const std::shared_ptr<Function> &irFunc,
                                  const std::shared_ptr<Compiler::Semantic::TypedParameterListNode> &params,
                                  Compiler::Semantic::TypedBlockNode &body,
                                  bool hasSelf);

        // Convert a Semantic::Type to an IR::Type
        std::shared_ptr<Type> toIRType(const std::shared_ptr<Compiler::Semantic::Type> &semType);
    };
} // namespace Ryntra::IR