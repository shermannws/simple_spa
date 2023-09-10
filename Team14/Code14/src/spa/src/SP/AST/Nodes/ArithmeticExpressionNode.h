#pragma once

#include <memory>
#include <string>

#include "ExpressionNode.h"
#include "ArithmeticOperatorType.h"

class ArithmeticExpressionNode : public ExpressionNode {
private:
    ArithmeticOperatorType operatorType;
    std::shared_ptr<ExpressionNode> leftExpression;
    std::shared_ptr<ExpressionNode> rightExpression;
public:
    explicit ArithmeticExpressionNode(ArithmeticOperatorType operatorType,
                             std::shared_ptr<ExpressionNode> leftExpression,
                             std::shared_ptr<ExpressionNode> rightExpression);
    static ArithmeticOperatorType translateOperatorTypeString(std::string operatorTypeString);
    void accept(DesignExtractorVisitor& visitor) override;
};
