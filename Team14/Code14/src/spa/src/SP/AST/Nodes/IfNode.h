#pragma once

#include <memory>

#include "StatementNode.h"
#include "ConditionalExpressionNode.h"
#include "StatementListNode.h"

class IfNode; // forward declaration
class IfNodeVisitor {
public:
    virtual void visitIfNode(IfNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const = 0;
};

class IfNode: public StatementNode {
private:
    std::shared_ptr<ConditionalExpressionNode> conditionalExpression;
    std::shared_ptr<StatementListNode> thenStatementList;
    std::shared_ptr<StatementListNode> elseStatementList;
public:
    explicit IfNode(int statementNumber,
                    std::shared_ptr<ConditionalExpressionNode> conditionalExpression,
                    std::shared_ptr<StatementListNode> thenStatementList,
                    std::shared_ptr<StatementListNode> elseStatementList);
    std::shared_ptr<ConditionalExpressionNode> getConditionalExpression();
    std::shared_ptr<StatementListNode> getThenStatementList();
    std::shared_ptr<StatementListNode> getElseStatementList();
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
    StatementNodeType getStatementType() override;
};
