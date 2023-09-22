#pragma once

#include "memory"

#include "ConditionalExpressionNode.h"
#include "BinaryConditionalExpressionType.h"

class BinaryConditionalExpressionNode; // forward declaration
class BinaryConditionalExpressionNodeVisitor {
public:
    virtual void visitBinaryConditionalExpressionNode(BinaryConditionalExpressionNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const = 0;
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
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) override;
    static BinaryConditionalExpressionType translateBinaryConditionalExpressionTypeString(std::string typeString);
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
