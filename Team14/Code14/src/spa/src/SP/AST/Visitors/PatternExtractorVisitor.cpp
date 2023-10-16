#include "PatternExtractorVisitor.h"
#include "Commons/StatementTypeFactory.h"

PatternExtractorVisitor::PatternExtractorVisitor(
        std::shared_ptr<PkbWriter> pkbWriter) {
    this->pkbWriter = pkbWriter;
}

void PatternExtractorVisitor::visitAssignNode(
        AssignNode *node, std::vector<std::shared_ptr<ASTNode>> parents,
        std::shared_ptr<ASTNode> proc) const {
    auto currentStmt = std::make_shared<Statement>(node->getStatementNumber(),
                                                   StatementType::Assign);
    this->pkbWriter->addAssignPattern(
            currentStmt,
            std::make_shared<Variable>(node->getVar()->getVarName()),
            std::make_shared<FormattedExpression>(
                    node->getExpression()->toString()));
}

void PatternExtractorVisitor::visitIfNode(
        IfNode *node, std::vector<std::shared_ptr<ASTNode>> parents,
        std::shared_ptr<ASTNode> proc) const {
    auto currentStmt = std::make_shared<Statement>(
            node->getStatementNumber(),
            StatementTypeFactory::getStatementTypeFrom(
                    node->getStatementType()));
    std::shared_ptr<ConditionalExpressionNode> condExpr =
            std::dynamic_pointer_cast<ConditionalExpressionNode>(
                    node->getConditionalExpression());

    this->pkbWriter->addIfPattern(currentStmt,
                                  getVariablesFromCondExpr(condExpr));
}

void PatternExtractorVisitor::visitWhileNode(
        WhileNode *node, std::vector<std::shared_ptr<ASTNode>> parents,
        std::shared_ptr<ASTNode> proc) const {
    auto currentStmt = std::make_shared<Statement>(
            node->getStatementNumber(),
            StatementTypeFactory::getStatementTypeFrom(
                    node->getStatementType()));
    std::shared_ptr<ConditionalExpressionNode> condExpr =
            std::dynamic_pointer_cast<ConditionalExpressionNode>(
                    node->getConditionalExpression());

    this->pkbWriter->addWhilePattern(currentStmt,
                                     getVariablesFromCondExpr(condExpr));
}

std::shared_ptr<std::vector<std::shared_ptr<Variable>>>
PatternExtractorVisitor::getVariablesFromCondExpr(
        std::shared_ptr<ConditionalExpressionNode> condExpr) {
    std::vector<std::shared_ptr<Variable>> variableNodes;
    std::vector<std::shared_ptr<ASTNode>> childNodes =
            condExpr->getAllChildNodes();

    for (const auto &childNode: childNodes) {
        if (std::shared_ptr<Variable> variable =
                    std::dynamic_pointer_cast<Variable>(childNode)) {
            variableNodes.push_back(variable);
        }
    }
    return std::make_shared<std::vector<std::shared_ptr<Variable>>>(
            variableNodes);
}
