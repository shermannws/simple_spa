#pragma once

#include <memory>
#include <string>

#include "ExpressionNode.h"
#include "ArithmeticOperatorType.h"

class ArithmeticExpressionNode : public ExpressionNode {
public:
    ArithmeticOperatorType operatorType;
    std::shared_ptr<ExpressionNode> leftExpression;
    std::shared_ptr<ExpressionNode> rightExpression;

    ArithmeticOperatorType translateOperatorTypeString(std::string operatorTypeString);

    void accept(DesignExtractorVisitor& visitor) override;
};
