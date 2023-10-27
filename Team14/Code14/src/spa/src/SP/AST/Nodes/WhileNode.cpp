#include "WhileNode.h"

WhileNode::WhileNode(StatementNumber statementNumber, std::shared_ptr<ConditionalExpressionNode> conditionalExpression,
                     std::shared_ptr<StatementListNode> statementList)
    : StatementNode(statementNumber), conditionalExpression(std::move(conditionalExpression)),
      statementList(std::move(statementList)) {}

std::shared_ptr<ConditionalExpressionNode> WhileNode::getConditionalExpression() { return conditionalExpression; }

std::shared_ptr<StatementListNode> WhileNode::getStatementList() { return statementList; }

std::vector<std::shared_ptr<ASTNode>> WhileNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children{conditionalExpression, statementList};
    return children;
}

StatementNodeType WhileNode::getStatementType() { return StatementNodeType::While; }

void WhileNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<Statement>> parents,
                       std::shared_ptr<Procedure> proc) {
    if (auto whileVisitor = std::dynamic_pointer_cast<WhileNodeVisitor>(visitor)) {
        whileVisitor->visitWhileNode(std::enable_shared_from_this<WhileNode>::shared_from_this(), parents, proc);
    }
}