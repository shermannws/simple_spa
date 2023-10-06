#include <unordered_map>

#include "Commons/AppConstants.h"
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

BinaryConditionalExpressionType
BinaryConditionalExpressionNode::translateBinaryConditionalExpressionTypeString(std::string typeString) {
    std::unordered_map<std::string, BinaryConditionalExpressionType> typeMap = {
            { AppConstants::STRING_AND, BinaryConditionalExpressionType::And },
            { AppConstants::STRING_OR, BinaryConditionalExpressionType::Or }
    };
    assert(typeMap.find(typeString) != typeMap.end());
    return typeMap[typeString];
}

void BinaryConditionalExpressionNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) {
    if (auto bceVisitor = std::dynamic_pointer_cast<BinaryConditionalExpressionNodeVisitor>(visitor)) {
        bceVisitor->visitBinaryConditionalExpressionNode(this, parents, proc);
    }
}