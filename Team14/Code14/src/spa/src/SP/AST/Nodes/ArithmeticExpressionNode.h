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
    ArithmeticOperatorType getOperatorType();
    std::shared_ptr<ExpressionNode> getLeftExpression();
    std::shared_ptr<ExpressionNode> getRightExpression();
    static ArithmeticOperatorType translateOperatorTypeString(std::string operatorTypeString);
    void accept(DesignExtractorVisitor& visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
