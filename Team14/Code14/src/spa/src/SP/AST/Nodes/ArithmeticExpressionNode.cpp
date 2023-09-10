#include <unordered_map>

#include "ArithmeticExpressionNode.h"

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
