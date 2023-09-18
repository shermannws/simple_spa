#pragma once

#include "memory"

#include "ConditionalExpressionNode.h"
#include "BinaryConditionalExpressionType.h"

class BinaryConditionalExpressionNode; // forward declaration
class BinaryConditionalExpressionNodeVisitor {
public:
    virtual void visitBinaryConditionalExpressionNode(BinaryConditionalExpressionNode* node) const = 0;
};

class BinaryConditionalExpressionNode : public ConditionalExpressionNode {
private:
    BinaryConditionalExpressionType binaryConditionalExpressionType;
    std::shared_ptr<ConditionalExpressionNode> leftConditionalExpression;
    std::shared_ptr<ConditionalExpressionNode> rightConditionalExpression;
public:
    explicit BinaryConditionalExpressionNode(BinaryConditionalExpressionType binaryConditionalExpressionType,
                                             std::shared_ptr<ConditionalExpressionNode> leftConditionalExpression,
                                             std::shared_ptr<ConditionalExpressionNode> rightConditionalExpression);
    BinaryConditionalExpressionType getBinaryConditionalExpressionType();
    std::shared_ptr<ConditionalExpressionNode> getLeftConditionalExpression();
    std::shared_ptr<ConditionalExpressionNode> getRightConditionalExpression();
    BinaryConditionalExpressionType translateBinaryConditionalExpressionTypeString(std::string typeString);
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
