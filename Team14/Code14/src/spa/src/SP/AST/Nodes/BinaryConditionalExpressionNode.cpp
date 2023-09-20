#include "BinaryConditionalExpressionNode.h"

BinaryConditionalExpressionNode::BinaryConditionalExpressionNode(
        BinaryConditionalExpressionType binaryConditionalExpressionType,
        std::shared_ptr<ConditionalExpressionNode> leftConditionalExpression,
        std::shared_ptr<ConditionalExpressionNode> rightConditionalExpression)
        : binaryConditionalExpressionType(binaryConditionalExpressionType),
        leftConditionalExpression(std::move(leftConditionalExpression)),
        rightConditionalExpression(std::move(rightConditionalExpression)) {}

BinaryConditionalExpressionType BinaryConditionalExpressionNode::getBinaryConditionalExpressionType() {
    return binaryConditionalExpressionType;
}

std::shared_ptr<ConditionalExpressionNode> BinaryConditionalExpressionNode::getLeftConditionalExpression() {
    return leftConditionalExpression;
}

std::shared_ptr<ConditionalExpressionNode> BinaryConditionalExpressionNode::getRightConditionalExpression() {
    return rightConditionalExpression;
}

std::vector<std::shared_ptr<ASTNode>> BinaryConditionalExpressionNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children { leftConditionalExpression, rightConditionalExpression };
    return children;
}

void BinaryConditionalExpressionNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) {
    if (auto bceVisitor = std::dynamic_pointer_cast<BinaryConditionalExpressionNodeVisitor>(visitor)) {
        bceVisitor->visitBinaryConditionalExpressionNode(this, parents);
    }
}