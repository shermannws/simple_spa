#pragma once

#include <memory>
#include <string>

#include "ExpressionNode.h"
#include "ArithmeticOperatorType.h"

class ArithmeticExpressionNode; // forward declaration
class ArithmeticExpressionNodeVisitor {
public:
    virtual void visitArithmeticExpressionNode(ArithmeticExpressionNode* node) const = 0;
};

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
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
