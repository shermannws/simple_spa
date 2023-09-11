#include <unordered_map>
#include <utility>

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
            // TODO: move raw operator strings to common enum
            { "+", ArithmeticOperatorType::Plus },
            { "-", ArithmeticOperatorType::Minus },
            { "*", ArithmeticOperatorType::Times },
            { "/", ArithmeticOperatorType::Divide },
            { "%", ArithmeticOperatorType::Modulo }
    };
    assert(operatorTypeMap.find(operatorTypeString) != operatorTypeMap.end());
    return operatorTypeMap[operatorTypeString];
}

void ArithmeticExpressionNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitArithmeticExpressionNode();
}
