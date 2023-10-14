#include "PatternExtractorVisitor.h"
#include "Commons/StatementTypeFactory.h"

PatternExtractorVisitor::PatternExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter) {
    this->pkbWriter = pkbWriter;
}

void PatternExtractorVisitor::visitAssignNode(AssignNode *node, std::vector<std::shared_ptr<ASTNode>> parents,
                                              std::shared_ptr<ASTNode> proc) const {
    auto currentStmt = std::make_shared<Statement>(node->getStatementNumber(), StatementType::Assign);
    this->pkbWriter->addAssignPattern(
            currentStmt,
            std::make_shared<Variable>(node->getVar()->getVarName()),
            std::make_shared<FormattedExpression>(node->getExpression()->toString())
    );
}

void PatternExtractorVisitor::visitIfNode(IfNode *node, std::vector<std::shared_ptr<ASTNode>> parents,
                                          std::shared_ptr<ASTNode> proc) const {
    auto currentStmt = std::make_shared<Statement>(node->getStatementNumber(),
                                                   StatementTypeFactory::getStatementTypeFrom(node->getStatementType()));
    std::shared_ptr<RelativeExpressionNode> relExpr = std::dynamic_pointer_cast<RelativeExpressionNode>(node->getConditionalExpression());

    this->pkbWriter->addIfPattern(currentStmt, getVariablesFromRelExpr(relExpr));
}

void PatternExtractorVisitor::visitWhileNode(WhileNode *node, std::vector<std::shared_ptr<ASTNode>> parents,
                                             std::shared_ptr<ASTNode> proc) const {
    auto currentStmt = std::make_shared<Statement>(node->getStatementNumber(),
                                                   StatementTypeFactory::getStatementTypeFrom(node->getStatementType()));
    std::shared_ptr<RelativeExpressionNode> relExpr = std::dynamic_pointer_cast<RelativeExpressionNode>(node->getConditionalExpression());

    this->pkbWriter->addWhilePattern(currentStmt, getVariablesFromRelExpr(relExpr));
}

std::vector<std::shared_ptr<Variable>> PatternExtractorVisitor::getVariablesFromRelExpr(std::shared_ptr<RelativeExpressionNode> relExpr) {
    std::vector<std::shared_ptr<Variable>> variableNodes;
    std::vector<std::shared_ptr<ASTNode>> childNodes = relExpr->getAllChildNodes();

    for (const auto& childNode : childNodes) {
        if (std::shared_ptr<Variable> variable = std::dynamic_pointer_cast<Variable>(childNode)) {
            variableNodes.push_back(variable);
        }
    }
    return variableNodes;
}

