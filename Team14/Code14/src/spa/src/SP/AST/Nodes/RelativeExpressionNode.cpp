#include <unordered_map>

#include "Commons/AppConstants.h"
#include "RelativeExpressionNode.h"

RelativeExpressionNode::RelativeExpressionNode(
        ComparisonOperatorType comparisonOperatorType,
        std::shared_ptr<ExpressionNode> leftExpression,
        std::shared_ptr<ExpressionNode> rightExpression)
        : comparisonOperatorType(comparisonOperatorType),
        leftExpression(std::move(leftExpression)),
        rightExpression(std::move(rightExpression)) {}

ComparisonOperatorType RelativeExpressionNode::getComparisonOperatorType() {
    return comparisonOperatorType;
}

std::shared_ptr<ExpressionNode> RelativeExpressionNode::getLeftExpression() {
    return leftExpression;
}

std::shared_ptr<ExpressionNode> RelativeExpressionNode::getRightExpression() {
    return rightExpression;
}

std::vector<std::shared_ptr<ASTNode>> RelativeExpressionNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children { leftExpression, rightExpression };
    return children;
}

ComparisonOperatorType RelativeExpressionNode::translateComparisonOperatorType(std::string operatorTypeString) {
    std::unordered_map<std::string, ComparisonOperatorType> operatorTypeMap = {
            { AppConstants::STRING_GREATER_THAN, ComparisonOperatorType::GreaterThan },
            { AppConstants::STRING_GREATER_EQUAL, ComparisonOperatorType::GreaterThanEqual },
            { AppConstants::STRING_LESS_THAN, ComparisonOperatorType::LessThan },
            { AppConstants::STRING_LESS_EQUAL, ComparisonOperatorType::LessThanEqual },
            { AppConstants::STRING_EQUAL, ComparisonOperatorType::Equal },
            { AppConstants::STRING_NOT_EQUAL, ComparisonOperatorType::NotEqual }
    };
    assert(operatorTypeMap.find(operatorTypeString) != operatorTypeMap.end());
    return operatorTypeMap[operatorTypeString];
}

void RelativeExpressionNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor) {
    if (auto relativeExpressionVisitor = std::dynamic_pointer_cast<RelativeExpressionNodeVisitor>(visitor)) {
        relativeExpressionVisitor->visitRelativeExpressionNode(this);
    }
}