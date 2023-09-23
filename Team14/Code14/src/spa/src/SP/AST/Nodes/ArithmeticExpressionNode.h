#pragma once

#include <memory>
#include <string>

#include "ExpressionNode.h"
#include "ArithmeticOperatorType.h"

class ArithmeticExpressionNode; // forward declaration

/**
 * Visitor interface linked to ArithmeticExpressionNode, used to implement the Acyclic Visitor pattern.
 */
class ArithmeticExpressionNodeVisitor {
public:
    /**
     * Visits the ArithmeticExpressionNode for design extraction.
     * @param node ArithmeticExpressionNode to be visited
     * @param parents Parents of the ArithmeticExpressionNode
     */
    virtual void visitArithmeticExpressionNode(ArithmeticExpressionNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const = 0;
};

/**
 * ASTNode to represent an arithmetic expression.
 * Implements the ExpressionNode interface.
 */
class ArithmeticExpressionNode : public ExpressionNode {
private:
    /**
     * The type of arithmetic operator for the arithmetic expression.
     */
    ArithmeticOperatorType operatorType;

    /**
     * The LHS expression in the arithmetic expression.
     */
    std::shared_ptr<ExpressionNode> leftExpression;

    /**
     * The RHS expression in the arithmetic expression.
     */
    std::shared_ptr<ExpressionNode> rightExpression;

public:
    /**
     * Creates and initializes an ArithmeticExpressionNode.
     * @param operatorType The arithmetic operator type
     * @param leftExpression The expression on the LHS
     * @param rightExpression The expression on the RHS
     */
    explicit ArithmeticExpressionNode(ArithmeticOperatorType operatorType,
                             std::shared_ptr<ExpressionNode> leftExpression,
                             std::shared_ptr<ExpressionNode> rightExpression);

    /**
     * Returns the arithmetic operator type of the arithmetic expression.
     * @return The arithmetic operator type
     */
    ArithmeticOperatorType getOperatorType();

    /**
     * Returns the expression on the LHS of the arithmetic expression.
     * @return The expression on the LHS
     */
    std::shared_ptr<ExpressionNode> getLeftExpression();

    /**
     * Returns the expression on the RHS of the arithmetic expression.
     * @return The expression on the RHS
     */
    std::shared_ptr<ExpressionNode> getRightExpression();

    /**
     * Converts the given string representing an arithmetic operator to the corresponding ArithmeticOperatorType value.
     * @param operatorTypeString The string representing an arithmetic operator
     * @return The ArithmeticOperatorType value corresponding to the string
     */
    static ArithmeticOperatorType translateOperatorTypeString(std::string operatorTypeString);

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;

    std::string toString() override;
};
