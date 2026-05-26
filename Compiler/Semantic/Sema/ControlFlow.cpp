#include "../SemanticAnalyzer.h"
#include "ErrorHandler/ErrorHandler.h"

namespace Ryntra::Compiler::Semantic {
    void SemanticAnalyzer::visit(BlockNode &node) {
        std::vector<std::shared_ptr<TypedStatementNode>> typedStatements;
        for (const auto &stmt : node.getStatements()) {
            stmt->accept(*this);
            if (auto typedStmt = std::dynamic_pointer_cast<TypedStatementNode>(lastNode)) {
                typedStatements.push_back(typedStmt);
            }
        }
        auto typedBlock = std::make_shared<TypedBlockNode>(std::move(typedStatements));
        typedBlock->setLocation(node.getLocation());
        lastNode = typedBlock;
    }

    void SemanticAnalyzer::visit(IfNode &node) {
        node.getCondition()->accept(*this);
        auto typedCond = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (typedCond) {
            auto boolType = TypeFactory::getPrimitive("bool");
            if (!typedCond->getType()->equals(*boolType) && typedCond->getType()->toString() != "unknown") {
                ErrorHandler::getInstance().makeError(
                    "[RCE023]: If condition must be 'bool', but got '" +
                        typedCond->getType()->toString() + "'.",
                    node.getCondition()->getLocation());
            }
        }

        node.getThenBlock()->accept(*this);
        auto typedThen = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);

        std::shared_ptr<TypedStatementNode> typedElse = nullptr;
        if (node.getElseBranch()) {
            node.getElseBranch()->accept(*this);
            typedElse = std::dynamic_pointer_cast<TypedStatementNode>(lastNode);
        }

        auto typedIf = std::make_shared<TypedIfNode>(typedCond, typedThen, typedElse);
        typedIf->setLocation(node.getLocation());
        lastNode = typedIf;
    }

    void SemanticAnalyzer::visit(WhileNode &node) {
        node.getCondition()->accept(*this);
        auto typedCond = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

        if (typedCond) {
            auto boolType = TypeFactory::getPrimitive("bool");
            if (!typedCond->getType()->equals(*boolType) && typedCond->getType()->toString() != "unknown") {
                ErrorHandler::getInstance().makeError(
                    "[RCE024]: While condition must be 'bool', but got '" +
                        typedCond->getType()->toString() + "'.",
                    node.getCondition()->getLocation());
            }
        }

        ++loopDepth_;
        node.getBody()->accept(*this);
        --loopDepth_;
        auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);

        auto typedWhile = std::make_shared<TypedWhileNode>(typedCond, typedBody);
        typedWhile->setLocation(node.getLocation());
        lastNode = typedWhile;
    }

    void SemanticAnalyzer::visit(ForNode &node) {
        symbolTable.enterScope();

        std::shared_ptr<TypedStatementNode> typedInit = nullptr;
        if (node.getInit()) {
            node.getInit()->accept(*this);
            typedInit = std::dynamic_pointer_cast<TypedStatementNode>(lastNode);
        }

        std::shared_ptr<TypedExpressionNode> typedCond = nullptr;
        if (node.getCondition()) {
            node.getCondition()->accept(*this);
            typedCond = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);

            if (typedCond) {
                auto boolType = TypeFactory::getPrimitive("bool");
                if (!typedCond->getType()->equals(*boolType) && typedCond->getType()->toString() != "unknown") {
                    ErrorHandler::getInstance().makeError(
                        "[RCE031]: For-loop condition must be 'bool', but got '" +
                            typedCond->getType()->toString() + "'.",
                        node.getCondition()->getLocation());
                }
            }
        }

        std::shared_ptr<TypedExpressionNode> typedOp = nullptr;
        if (node.getOperation()) {
            node.getOperation()->accept(*this);
            typedOp = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode);
        }

        ++loopDepth_;
        node.getBody()->accept(*this);
        --loopDepth_;
        auto typedBody = std::dynamic_pointer_cast<TypedBlockNode>(lastNode);

        symbolTable.exitScope();

        auto typedFor = std::make_shared<TypedForNode>(typedInit, typedCond, typedOp, typedBody);
        typedFor->setLocation(node.getLocation());
        lastNode = typedFor;
    }

    void SemanticAnalyzer::visit(BreakNode &node) {
        if (loopDepth_ == 0) {
            ErrorHandler::getInstance().makeError(
                "[RCE025]: 'break' outside of loop.", node.getLocation());
            lastNode = nullptr;
            return;
        }
        auto typedBreak = std::make_shared<TypedBreakNode>();
        typedBreak->setLocation(node.getLocation());
        lastNode = typedBreak;
    }

    void SemanticAnalyzer::visit(ContinueNode &node) {
        if (loopDepth_ == 0) {
            ErrorHandler::getInstance().makeError(
                "[RCE026]: 'continue' outside of loop.", node.getLocation());
            lastNode = nullptr;
            return;
        }
        auto typedContinue = std::make_shared<TypedContinueNode>();
        typedContinue->setLocation(node.getLocation());
        lastNode = typedContinue;
    }

    void SemanticAnalyzer::visit(ExpressionStatementNode &node) {
        node.getExpression()->accept(*this);
        if (auto typedExpr = std::dynamic_pointer_cast<TypedExpressionNode>(lastNode)) {
            auto exprType = typedExpr->getType();
            if (exprType && exprType->getKind() != TypeKind::VOID && exprType->toString() != "unknown") {
                auto rawExpr = node.getExpression();
            if (!std::dynamic_pointer_cast<AssignmentNode>(rawExpr) &&
                !std::dynamic_pointer_cast<ArrayIndexAssignmentNode>(rawExpr) &&
                !std::dynamic_pointer_cast<PrefixOpNode>(rawExpr) &&
                !std::dynamic_pointer_cast<PostfixOpNode>(rawExpr) &&
                !std::dynamic_pointer_cast<ConditionalAndNode>(rawExpr) &&
                !std::dynamic_pointer_cast<ConditionalOrNode>(rawExpr) &&
                !std::dynamic_pointer_cast<PtrStoreNode>(rawExpr)) {
                    ErrorHandler::getInstance().makeWarning(
                        "[RCW001]: Result will be discarded.",
                        node.getLocation());
                }
            }

            auto typedStmt = std::make_shared<TypedExpressionStatementNode>(typedExpr);
            typedStmt->setLocation(node.getLocation());
            lastNode = typedStmt;
        } else {
            lastNode = nullptr;
        }
    }
} // namespace Ryntra::Compiler::Semantic
