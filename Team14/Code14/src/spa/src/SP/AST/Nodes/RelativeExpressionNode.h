#pragma once

#include "memory"

#include "ConditionalExpressionNode.h"
#include "ComparisonOperatorType.h"
#include "ExpressionNode.h"

class RelativeExpressionNode; // forward declaration
class RelativeExpressionNodeVisitor {
public:
    virtual void visitRelativeExpressionNode(RelativeExpressionNode* node) const = 0;
};

class RelativeExpressionNode : public ConditionalExpressionNode {
private:
    ComparisonOperatorType comparisonOperatorType;
    std::shared_ptr<ExpressionNode> leftExpression;
    std::shared_ptr<ExpressionNode> rightExpression;
public:
    explicit RelativeExpressionNode(ComparisonOperatorType comparisonOperatorType,
                                             std::shared_ptr<ExpressionNode> leftExpression,
                                             std::shared_ptr<ExpressionNode> rightExpression);
    ComparisonOperatorType getComparisonOperatorType();
    std::shared_ptr<ExpressionNode> getLeftExpression();
    std::shared_ptr<ExpressionNode> getRightExpression();
    static ComparisonOperatorType translateComparisonOperatorType(std::string operatorTypeString);
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
