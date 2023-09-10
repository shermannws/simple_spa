#include <unordered_map>
#include <utility>

#include "ArithmeticExpressionNode.h"

ArithmeticExpressionNode::ArithmeticExpressionNode(ArithmeticOperatorType operatorType,
                                                   std::shared_ptr<ExpressionNode> leftExpression,
                                                   std::shared_ptr<ExpressionNode> rightExpression)
                                                   : operatorType(operatorType),
                                                   leftExpression(std::move(leftExpression)),
                                                   rightExpression(std::move(rightExpression)) {}

ArithmeticOperatorType ArithmeticExpressionNode::translateOperatorTypeString(std::string operatorTypeString) {
    std::unordered_map<std::string, ArithmeticOperatorType> operatorTypeMap = {
            // TODO: move raw operator strings to common enum
            { "+", ArithmeticOperatorType::PLUS },
            { "-", ArithmeticOperatorType::MINUS },
            { "*", ArithmeticOperatorType::TIMES },
            { "/", ArithmeticOperatorType::DIVIDE },
            { "%", ArithmeticOperatorType::MODULO }
    };
    assert(operatorTypeMap.find(operatorTypeString) != operatorTypeMap.end());
    return operatorTypeMap[operatorTypeString];
}

void ArithmeticExpressionNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitArithmeticExpressionNode();
}
