#include <unordered_map>
#include <utility>

#include "Commons/AppConstants.h"
#include "ArithmeticExpressionNode.h"

ArithmeticExpressionNode::ArithmeticExpressionNode(ArithmeticOperatorType operatorType,
                                                   std::shared_ptr<ExpressionNode> leftExpression,
                                                   std::shared_ptr<ExpressionNode> rightExpression)
                                                   : operatorType(operatorType),
                                                   leftExpression(std::move(leftExpression)),
                                                   rightExpression(std::move(rightExpression)) {}

ArithmeticOperatorType ArithmeticExpressionNode::getOperatorType() {
    return operatorType;
}

std::shared_ptr<ExpressionNode> ArithmeticExpressionNode::getLeftExpression() {
    return leftExpression;
}

std::shared_ptr<ExpressionNode> ArithmeticExpressionNode::getRightExpression() {
    return rightExpression;
}

ArithmeticOperatorType ArithmeticExpressionNode::translateOperatorTypeString(std::string operatorTypeString) {
    std::unordered_map<std::string, ArithmeticOperatorType> operatorTypeMap = {
            { AppConstants::STRING_PLUS, ArithmeticOperatorType::Plus },
            { AppConstants::STRING_MINUS, ArithmeticOperatorType::Minus },
            { AppConstants::STRING_TIMES, ArithmeticOperatorType::Times },
            { AppConstants::STRING_DIVIDE, ArithmeticOperatorType::Divide },
            { AppConstants::STRING_MODULO, ArithmeticOperatorType::Modulo }
    };
    assert(operatorTypeMap.find(operatorTypeString) != operatorTypeMap.end());
    return operatorTypeMap[operatorTypeString];
}
std::vector<std::shared_ptr<ASTNode>> ArithmeticExpressionNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children { leftExpression, rightExpression };
    return children;
}

void ArithmeticExpressionNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) {
    if (auto aenVisitor = std::dynamic_pointer_cast<ArithmeticExpressionNodeVisitor>(visitor)) {
        aenVisitor->visitArithmeticExpressionNode(this, parents);
    }
}

std::string ArithmeticExpressionNode::toString() {
    std::unordered_map<ArithmeticOperatorType, std::string> operatorTypeToStringMap = {
            { ArithmeticOperatorType::Plus, AppConstants::STRING_PLUS },
            { ArithmeticOperatorType::Minus, AppConstants::STRING_MINUS },
            { ArithmeticOperatorType::Times, AppConstants::STRING_TIMES },
            { ArithmeticOperatorType::Divide, AppConstants::STRING_DIVIDE },
            { ArithmeticOperatorType::Modulo, AppConstants::STRING_MODULO }
    };

    return "(" +
        this->getLeftExpression()->toString() +
        operatorTypeToStringMap[operatorType] +
        this->getRightExpression()->toString() +
        ")";
}