#pragma once

#include "memory"

#include "ConditionalExpressionNode.h"
#include "ComparisonOperatorType.h"
#include "ExpressionNode.h"

class RelativeExpressionNode; // forward declaration

/**
 * Visitor interface linked to RelativeExpressionNode,
 * used to implement the Acyclic Visitor pattern.
 */
class RelativeExpressionNodeVisitor {
public:
    /**
     * Visits the RelativeExpressionNode for design extraction.
     * @param node RelativeExpressionNode to be visited
     * @param parents Parents of the RelativeExpressionNode
     */
    virtual void visitRelativeExpressionNode(RelativeExpressionNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const = 0;
};

/**
 * ASTNode to represent a relative expression.
 * Implements the ConditionalExpressionNode interface.
 */
class RelativeExpressionNode : public ConditionalExpressionNode {
private:
    /**
     * The type of comparison operators for the relative expression.
     */
    ComparisonOperatorType comparisonOperatorType;

    /**
     * The expression (arithmetic, variable, constant) on the LHS.
     */
    std::shared_ptr<ExpressionNode> leftExpression;

    /**
     * The expression (arithmetic, variable, constant) on the RHS.
     * */
    std::shared_ptr<ExpressionNode> rightExpression;

public:
    /**
     * Creates and initializes a RelativeExpressionNode.
     * @param comparisonOperatorType The type of comparison operator
     * @param leftExpression The LHS expression (arithmetic, variable, constant)
     * @param rightExpression The RHS expression (arithmetic, variable, constant)
     */
    explicit RelativeExpressionNode(ComparisonOperatorType comparisonOperatorType,
                                             std::shared_ptr<ExpressionNode> leftExpression,
                                             std::shared_ptr<ExpressionNode> rightExpression);

    /**
     * Returns the comparison operator.
     * @return The comparison operator
     */
    ComparisonOperatorType getComparisonOperatorType();

    /**
     * Returns the expression (arithmetic, variable, constant) on the LHS.
     * @return The expression on the LHS
     */
    std::shared_ptr<ExpressionNode> getLeftExpression();

    /**
     * Returns the expression (arithmetic, variable, constant) on the RHS.
     * @return The expression on the RHS
     */
    std::shared_ptr<ExpressionNode> getRightExpression();

    /**
     * Converts the given string representing a binary conditional operator to the
     * corresponding ComparisonOperatorType value.
     * @param operatorTypeString The string representing a comparison operator
     * @return The ComparisonOperatorType value corresponding to the string
     */
    static ComparisonOperatorType translateComparisonOperatorType(std::string operatorTypeString);

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};