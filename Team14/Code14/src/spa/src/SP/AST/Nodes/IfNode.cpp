#include "IfNode.h"

IfNode::IfNode(StatementNumber statementNumber,
               std::shared_ptr<ConditionalExpressionNode> conditionalExpression,
               std::shared_ptr<StatementListNode> thenStatementList,
               std::shared_ptr<StatementListNode> elseStatementList)
    : StatementNode(statementNumber),
      conditionalExpression(std::move(conditionalExpression)),
      thenStatementList(std::move(thenStatementList)),
      elseStatementList(std::move(elseStatementList)) {}

std::shared_ptr<ConditionalExpressionNode> IfNode::getConditionalExpression() {
    return conditionalExpression;
}

std::shared_ptr<StatementListNode> IfNode::getThenStatementList() {
    return thenStatementList;
}

std::shared_ptr<StatementListNode> IfNode::getElseStatementList() {
    return elseStatementList;
}

std::vector<std::shared_ptr<ASTNode>> IfNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children{
            conditionalExpression, thenStatementList, elseStatementList};
    return children;
}

StatementNodeType IfNode::getStatementType() { return StatementNodeType::If; }

void IfNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor,
                    std::vector<std::shared_ptr<ASTNode>> parents,
                    std::shared_ptr<ASTNode> proc) {
    if (auto ifVisitor = std::dynamic_pointer_cast<IfNodeVisitor>(visitor)) {
        ifVisitor->visitIfNode(this, parents, proc);
    }
}
