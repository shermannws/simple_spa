#include "ASTComparer.h"
#include "SP/AST/Nodes/BinaryConditionalExpressionNode.h"
#include "SP/AST/Nodes/RelativeExpressionNode.h"
#include "SP/AST/Nodes/UnaryConditionalExpressionNode.h"

bool ASTComparer::isSameAST(const std::shared_ptr<ProgramNode> &firstAST,
                            const std::shared_ptr<ProgramNode> &secondAST) {
    auto firstASTProcedures = firstAST->getProcedures();
    auto secondASTProcedures = secondAST->getProcedures();

    if (firstASTProcedures.size() != secondASTProcedures.size()) { return false; }

    for (int i = 0; i < firstASTProcedures.size(); i++) {
        if (!isSameProcedure(firstASTProcedures[i], secondASTProcedures[i])) { return false; }
    }

    return true;
}

bool ASTComparer::isSameProcedure(const std::shared_ptr<ProcedureNode> &firstProc,
                                  const std::shared_ptr<ProcedureNode> &secondProc) {
    return firstProc->getProcedureName() == secondProc->getProcedureName() &&
           isSameStatementList(firstProc->getStatementList(), secondProc->getStatementList());
}

bool ASTComparer::isSameStatementList(const std::shared_ptr<StatementListNode> &firstStatementList,
                                      const std::shared_ptr<StatementListNode> &secondStatementList) {
    auto firstStatementListStatements = firstStatementList->getStatements();
    auto secondStatementListStatements = secondStatementList->getStatements();

    if (firstStatementListStatements.size() != secondStatementListStatements.size()) { return false; }

    for (int i = 0; i < firstStatementListStatements.size(); i++) {
        if (firstStatementListStatements[i]->getStatementType() !=
            secondStatementListStatements[i]->getStatementType()) {
            return false;
        }
        StatementNodeType statementNodeType = firstStatementListStatements[i]->getStatementType();
        auto func = statementNodeTypeToStatementComparer.at(statementNodeType);
        if (!func(firstStatementListStatements[i], secondStatementListStatements[i])) { return false; }
    }

    return true;
}

bool ASTComparer::isSameAssign(const std::shared_ptr<AssignNode> &firstAssign,
                               const std::shared_ptr<AssignNode> &secondAssign) {
    return isSameStatementNumber(firstAssign, secondAssign) &&
           firstAssign->getVar()->getVarName() == secondAssign->getVar()->getVarName() &&
           isSameExpression(firstAssign->getExpression(), secondAssign->getExpression());
}

bool ASTComparer::isSamePrint(const std::shared_ptr<PrintNode> &firstPrint,
                              const std::shared_ptr<PrintNode> &secondPrint) {
    return isSameStatementNumber(firstPrint, secondPrint) &&
           firstPrint->getVar()->getVarName() == secondPrint->getVar()->getVarName();
}

bool ASTComparer::isSameRead(const std::shared_ptr<ReadNode> &firstRead, const std::shared_ptr<ReadNode> &secondRead) {
    return isSameStatementNumber(firstRead, secondRead) &&
           firstRead->getVar()->getVarName() == secondRead->getVar()->getVarName();
}

bool ASTComparer::isSameIf(const std::shared_ptr<IfNode> &firstIf, const std::shared_ptr<IfNode> &secondIf) {
    return isSameStatementNumber(firstIf, secondIf) &&
           isSameCondExpression(firstIf->getConditionalExpression(), secondIf->getConditionalExpression()) &&
           isSameStatementList(firstIf->getThenStatementList(), secondIf->getThenStatementList()) &&
           isSameStatementList(firstIf->getElseStatementList(), secondIf->getElseStatementList());
}

bool ASTComparer::isSameWhile(const std::shared_ptr<WhileNode> &firstWhile,
                              const std::shared_ptr<WhileNode> &secondWhile) {
    return isSameStatementNumber(firstWhile, secondWhile) &&
           isSameCondExpression(firstWhile->getConditionalExpression(), secondWhile->getConditionalExpression()) &&
           isSameStatementList(firstWhile->getStatementList(), secondWhile->getStatementList());
}

bool ASTComparer::isSameCall(const std::shared_ptr<CallNode> &firstCall, const std::shared_ptr<CallNode> &secondCall) {
    return isSameStatementNumber(firstCall, secondCall) &&
           firstCall->getProcedureName() == secondCall->getProcedureName();
}

bool ASTComparer::isSameExpression(const std::shared_ptr<ExpressionNode> &firstExpr,
                                   const std::shared_ptr<ExpressionNode> &secondExpr) {
    return firstExpr->toString() == secondExpr->toString();
}

bool ASTComparer::isSameCondExpression(const std::shared_ptr<ConditionalExpressionNode> &firstExpr,
                                       const std::shared_ptr<ConditionalExpressionNode> &secondExpr) {
    // if both are Unary
    if (auto firstUnary = std::dynamic_pointer_cast<UnaryConditionalExpressionNode>(firstExpr)) {
        if (auto secondUnary = std::dynamic_pointer_cast<UnaryConditionalExpressionNode>(secondExpr)) {
            return isSameCondExpression(firstUnary->getConditionalExpression(),
                                        secondUnary->getConditionalExpression());
        }
    }

    // if both are Binary
    if (auto firstBinary = std::dynamic_pointer_cast<BinaryConditionalExpressionNode>(firstExpr)) {
        if (auto secondBinary = std::dynamic_pointer_cast<BinaryConditionalExpressionNode>(secondExpr)) {
            return firstBinary->getBinaryConditionalExpressionType() ==
                   secondBinary->getBinaryConditionalExpressionType() &&
                   isSameCondExpression(firstBinary->getLeftConditionalExpression(),
                                        secondBinary->getLeftConditionalExpression()) &&
                   isSameCondExpression(firstBinary->getRightConditionalExpression(),
                                        secondBinary->getRightConditionalExpression());
        }
    }

    // if both are RelativeExpr
    if (auto firstRelativeExpr = std::dynamic_pointer_cast<RelativeExpressionNode>(firstExpr)) {
        if (auto secondRelativeExpr = std::dynamic_pointer_cast<RelativeExpressionNode>(secondExpr)) {
            return firstRelativeExpr->getComparisonOperatorType() == secondRelativeExpr->getComparisonOperatorType() &&
                   isSameExpression(firstRelativeExpr->getLeftExpression(), secondRelativeExpr->getLeftExpression()) &&
                   isSameExpression(firstRelativeExpr->getRightExpression(), secondRelativeExpr->getRightExpression());
        }
    }

    return false;
}

bool ASTComparer::isSameStatementNumber(const std::shared_ptr<StatementNode> &firstStatement,
                                        const std::shared_ptr<StatementNode> &secondStatement) {
    return firstStatement->getStatementNumber() == secondStatement->getStatementNumber();
}