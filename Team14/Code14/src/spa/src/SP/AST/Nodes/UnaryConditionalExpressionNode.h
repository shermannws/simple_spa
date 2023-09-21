#pragma once

#include "memory"

#include "ConditionalExpressionNode.h"

class UnaryConditionalExpressionNode; // forward declaration
class UnaryConditionalExpressionNodeVisitor {
public:
    virtual void visitUnaryConditionalExpressionNode(UnaryConditionalExpressionNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const = 0;
};

class UnaryConditionalExpressionNode : public ConditionalExpressionNode {
private:
    std::shared_ptr<ConditionalExpressionNode> conditionalExpression;
public:
    explicit UnaryConditionalExpressionNode(std::shared_ptr<ConditionalExpressionNode> conditionalExpression);
    std::shared_ptr<ConditionalExpressionNode> getConditionalExpression();
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
