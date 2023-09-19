#pragma once

#include <memory>

#include "StatementNode.h"
#include "ConditionalExpressionNode.h"
#include "StatementListNode.h"

class WhileNode; // forward declaration
class WhileNodeVisitor {
public:
    virtual void visitWhileNode(WhileNode* node) const = 0;
};

class WhileNode: public StatementNode {
private:
    std::shared_ptr<ConditionalExpressionNode> conditionalExpression;
    std::shared_ptr<StatementListNode> statementList;
public:
    explicit WhileNode(int statementNumber,
                    std::shared_ptr<ConditionalExpressionNode> conditionalExpression,
                    std::shared_ptr<StatementListNode> statementList);
    std::shared_ptr<ConditionalExpressionNode> getConditionalExpression();
    std::shared_ptr<StatementListNode> getStatementList();
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
    StatementNodeType getStatementType() override;
};
