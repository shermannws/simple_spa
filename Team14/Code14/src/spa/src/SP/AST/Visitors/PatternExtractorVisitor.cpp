#include <stack>

#include "Commons/StatementTypeFactory.h"
#include "PatternExtractorVisitor.h"

PatternExtractorVisitor::PatternExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter) { this->pkbWriter = pkbWriter; }

void PatternExtractorVisitor::visitAssignNode(const std::shared_ptr<AssignNode> &node,
                                              std::vector<std::shared_ptr<ASTNode>> parents,
                                              std::shared_ptr<ASTNode> proc) const {
    auto currentStmt = std::make_shared<Statement>(node->getStatementNumber(), StatementType::Assign);
    this->pkbWriter->addAssignPattern(currentStmt, std::make_shared<Variable>(node->getVar()->getVarName()),
                                      std::make_shared<FormattedExpression>(node->getExpression()->toString()));
}

void PatternExtractorVisitor::visitIfNode(const std::shared_ptr<IfNode> &node,
                                          std::vector<std::shared_ptr<ASTNode>> parents,
                                          std::shared_ptr<ASTNode> proc) const {
    auto currentStmt = std::make_shared<Statement>(
            node->getStatementNumber(), StatementTypeFactory::getStatementTypeFrom(node->getStatementType()));
    auto variablesUsedByIf = getVariablesFromCondExpr(node->getConditionalExpression());

    if (variablesUsedByIf->empty()) { return; }
    this->pkbWriter->addIfPattern(currentStmt, variablesUsedByIf);
}

void PatternExtractorVisitor::visitWhileNode(const std::shared_ptr<WhileNode> &node,
                                             std::vector<std::shared_ptr<ASTNode>> parents,
                                             std::shared_ptr<ASTNode> proc) const {
    auto currentStmt = std::make_shared<Statement>(
            node->getStatementNumber(), StatementTypeFactory::getStatementTypeFrom(node->getStatementType()));
    auto variablesUsedByWhile = getVariablesFromCondExpr(node->getConditionalExpression());

    if (variablesUsedByWhile->empty()) { return; }
    this->pkbWriter->addWhilePattern(currentStmt, variablesUsedByWhile);
}

std::shared_ptr<std::vector<std::shared_ptr<Variable>>>
PatternExtractorVisitor::getVariablesFromCondExpr(std::shared_ptr<ConditionalExpressionNode> condExpr) {
    std::vector<std::shared_ptr<Variable>> variables;
    std::stack<std::shared_ptr<ASTNode>> frontier;
    frontier.push(condExpr);

    while (!frontier.empty()) {
        std::shared_ptr<ASTNode> current = frontier.top();
        frontier.pop();

        std::shared_ptr<VariableNode> ptr = std::dynamic_pointer_cast<VariableNode>(current);
        if (ptr) { variables.push_back(std::make_shared<Variable>(ptr->getVarName())); }

        std::vector<std::shared_ptr<ASTNode>> childrenOfCurrent = current->getAllChildNodes();
        for (auto it = childrenOfCurrent.rbegin(); it != childrenOfCurrent.rend(); it++) { frontier.push(*it); }
    }
    return std::make_shared<std::vector<std::shared_ptr<Variable>>>(variables);
}
