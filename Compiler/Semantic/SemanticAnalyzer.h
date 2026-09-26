#pragma once

#include "../AST/ASTNodes.h"
#include "../AST/ASTVisitor.h"
#include "Compiler/GeneratedHeader/AllNodesVisitor.h"
#include "SymbolTable.h"
#include "TypedAST.h"
#include <unordered_map>

namespace Ryntra::Compiler::Semantic {
    class SemanticAnalyzer : public AllNodesVisitor {
    public:
        SemanticAnalyzer() = default;

        void analyze(const std::shared_ptr<IASTNode> &root);
        std::shared_ptr<TypedProgramNode> getTypedAST() const { return typedProgram; }

        // Visitor methods
        void visit(ProgramNode &node) override;
        void visit(FunctionDefinitionNode &node) override;
        void visit(FunctionCallNode &node) override;
        void visit(BlockNode &node) override;
        void visit(IfNode &node) override;
        void visit(WhileNode &node) override;
        void visit(ForNode &node) override;
        void visit(NullLiteralNode &node) override;
        void visit(BreakNode &node) override;
        void visit(ContinueNode &node) override;
        void visit(ExpressionStatementNode &node) override;
        void visit(StringLiteralNode &node) override;
        void visit(BoolLiteralNode &node) override;
        void visit(IntegerLiteralNode &node) override;
        void visit(LongLiteralNode &node) override;
        void visit(IdentifierNode &node) override;
        void visit(TypeSpecifierNode &node) override;
        void visit(FunctionTypeNode &node) override;
        void visit(ArrayTypeNode &node) override;
        void visit(ReferenceTypeNode &node) override;
        void visit(ReturnNode &node) override;
        void visit(VariableNode &node) override;
        void visit(VariableDeclarationNode &node) override;
        void visit(ArrayDeclarationNode &node) override;
        void visit(ArrayIndexAccessNode &node) override;
        void visit(ArrayIndexAssignmentNode &node) override;
        void visit(BinaryOpNode &node) override;
        void visit(UnaryOpNode &node) override;
        void visit(CastNode &node) override;
        void visit(ComparisonNode &node) override;
        void visit(ConditionalAndNode &node) override;
        void visit(ConditionalOrNode &node) override;
        void visit(AssignmentNode &node) override;
        void visit(PrefixOpNode &node) override;
        void visit(PostfixOpNode &node) override;
        void visit(RefExpressionNode &node) override;
        void visit(UnsafeBlockNode &node) override;
        void visit(PtrExpressionNode &node) override;
        void visit(MethodCallNode &node) override;
        void visit(NewExpressionNode &node) override;
        void visit(DeleteStatementNode &node) override;
        void visit(FixedNode &node) override;
        void visit(StructDeclarationNode &node) override;
        void visit(FieldDeclarationNode &node) override;
        void visit(ConstructorDeclarationNode &node) override;
        void visit(SelfExpressionNode &node) override;
        void visit(MemberAccessNode &node) override;
        void visit(MemberAssignmentNode &node) override;

    private:
        SymbolTable symbolTable;
        std::shared_ptr<TypedProgramNode> typedProgram;

        // Intermediate state for building the Typed AST
        std::shared_ptr<ITypedASTNode> lastNode;
        TypePtr lastType;                         // STType::Type result from TypeSpecifierNode
        TypePtr currentFunctionReturnType;        // STType::Type of the current function
        std::shared_ptr<Type> expectedReturnType; // Expected return type from context (for __builtin_scan)
        int loopDepth_ = 0;                       // Current loop nesting depth
        int unsafeDepth_ = 0;                     // Current unsafe block nesting depth
        std::shared_ptr<STType::StructType> currentStruct; // Enclosing struct being analyzed (for `self`)
        // Struct name -> its semantic type (fields + member symbol scope). Used to
        // resolve fields/methods from the `TypeSystem::StructType` stored in the
        // typed AST, which only carries the struct name.
        std::unordered_map<std::string, std::shared_ptr<STType::StructType>> structTypes;

        // Convert STType::Type -> TypeSystem::Type (for TypedAST nodes)
        static std::shared_ptr<Type> toTypedType(const TypePtr &stType);

        // Register a struct's field/method/constructor symbols into its member scope.
        // Duplicate fields / member signatures are diagnosed here.
        void registerStructMembers(const std::shared_ptr<STType::StructType> &structType,
                                   const std::shared_ptr<MemberListNode> &memberList);

        // Build a TypePtr from a type-name string
        static TypePtr makeSTType(const std::string &name);

        // Recursively check that every named type inside a type-name string is known
        void checkKnownTypeNames(const std::string &name, const SourceRange &range);

        // Extract variable name from a typed expression (for pointer operations)
        static std::string getPtrVarName(const std::shared_ptr<TypedExpressionNode> &expr,
                                          const SourceRange &range);

        // Build a TypedAST FunctionType from a FunctionSymbol
        static std::shared_ptr<FunctionType> functionTypeOf(const std::shared_ptr<FunctionSymbol> &fn);

        // Select the overload to take the address of, matching the expected type if available
        std::shared_ptr<FunctionSymbol> pickFunctionForAddress(const std::shared_ptr<OverloadSet> &ovSet,
                                                               const SourceRange &range);
    };

} // namespace Ryntra::Compiler::Semantic
