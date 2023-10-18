#pragma once

#include <memory>
#include <unordered_map>

#include "Commons/AppConstants.h"
#include "ComparisonOperatorType.h"
#include "ConditionalExpressionNode.h"
#include "ExpressionNode.h"

class RelativeExpressionNode;// forward declaration

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
     * @param proc Procedure containing the RelativeExpressionNode
     */
    virtual void visitRelativeExpressionNode(RelativeExpressionNode *node,
                                             std::vector<std::shared_ptr<ASTNode>> parents,
                                             std::shared_ptr<ASTNode> proc) const = 0;
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

    /**
     * Map of comparison operator string to ComparisonOperatorType.
     */
    inline static const std::unordered_map<std::string, ComparisonOperatorType> stringToOperatorTypeMap = {
            {AppConstants::STRING_GREATER_THAN, ComparisonOperatorType::GreaterThan},
            {AppConstants::STRING_GREATER_EQUAL, ComparisonOperatorType::GreaterThanEqual},
            {AppConstants::STRING_LESS_THAN, ComparisonOperatorType::LessThan},
            {AppConstants::STRING_LESS_EQUAL, ComparisonOperatorType::LessThanEqual},
            {AppConstants::STRING_DOUBLE_EQUAL, ComparisonOperatorType::Equal},
            {AppConstants::STRING_NOT_EQUAL, ComparisonOperatorType::NotEqual}};

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
    static ComparisonOperatorType translateComparisonOperatorType(const std::string &operatorTypeString);

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents,
                std::shared_ptr<ASTNode> proc) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
