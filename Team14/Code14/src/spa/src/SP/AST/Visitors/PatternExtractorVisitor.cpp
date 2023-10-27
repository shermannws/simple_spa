#include <stack>

#include "Commons/EntityFactory.h"
#include "Commons/StatementTypeFactory.h"
#include "PatternExtractorVisitor.h"

PatternExtractorVisitor::PatternExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter) { this->pkbWriter = pkbWriter; }

void PatternExtractorVisitor::visitAssignNode(const std::shared_ptr<AssignNode> &node,
                                              std::vector<std::shared_ptr<Statement>> parents,
                                              std::shared_ptr<Procedure> proc) const {
    auto currentStmt = EntityFactory::createStatementFromStatementNode(node);
    this->pkbWriter->addAssignPattern(currentStmt, EntityFactory::createVariable(node->getVar()->getVarName()),
                                      std::make_shared<FormattedExpression>(node->getExpression()->toString()));
}

void PatternExtractorVisitor::visitIfNode(const std::shared_ptr<IfNode> &node,
                                          std::vector<std::shared_ptr<Statement>> parents,
                                          std::shared_ptr<Procedure> proc) const {
    auto currentStmt = EntityFactory::createStatementFromStatementNode(node);
    auto variablesUsedByIf = getVariablesFromCondExpr(node->getConditionalExpression());

    if (variablesUsedByIf->empty()) { return; }
    this->pkbWriter->addIfPattern(currentStmt, variablesUsedByIf);
}

void PatternExtractorVisitor::visitWhileNode(const std::shared_ptr<WhileNode> &node,
                                             std::vector<std::shared_ptr<Statement>> parents,
                                             std::shared_ptr<Procedure> proc) const {
    auto currentStmt = EntityFactory::createStatementFromStatementNode(node);
    auto variablesUsedByWhile = getVariablesFromCondExpr(node->getConditionalExpression());

    if (variablesUsedByWhile->empty()) { return; }
    this->pkbWriter->addWhilePattern(currentStmt, variablesUsedByWhile);
}

std::shared_ptr<std::vector<std::shared_ptr<Variable>>>
PatternExtractorVisitor::getVariablesFromCondExpr(const std::shared_ptr<ConditionalExpressionNode> &condExpr) {
    auto variables = std::make_shared<std::vector<std::shared_ptr<Variable>>>();
    std::stack<std::shared_ptr<ASTNode>> frontier;
    frontier.push(condExpr);

    while (!frontier.empty()) {
        std::shared_ptr<ASTNode> current = frontier.top();
        frontier.pop();

        std::shared_ptr<VariableNode> ptr = std::dynamic_pointer_cast<VariableNode>(current);
        if (ptr) { variables->push_back(EntityFactory::createVariable(ptr->getVarName())); }

        std::vector<std::shared_ptr<ASTNode>> childrenOfCurrent = current->getAllChildNodes();
        for (auto it = childrenOfCurrent.rbegin(); it != childrenOfCurrent.rend(); it++) { frontier.push(*it); }
    }
    return variables;
}
