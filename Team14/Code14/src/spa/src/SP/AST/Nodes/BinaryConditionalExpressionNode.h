#pragma once

#include "memory"

#include "ConditionalExpressionNode.h"
#include "BinaryConditionalExpressionType.h"

class BinaryConditionalExpressionNode; // forward declaration

/**
 * Visitor interface linked to BinaryConditionalExpressionNode,
 * used to implement the Acyclic Visitor pattern.
 */
class BinaryConditionalExpressionNodeVisitor {
public:
    /**
     * Visits the BinaryConditionalExpressionNode for design extraction.
     * @param node BinaryConditionalExpressionNode to be visited
     * @param parents Parents of the BinaryConditionalExpressionNode
     */
    virtual void visitBinaryConditionalExpressionNode(BinaryConditionalExpressionNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const = 0;
};

/**
 * ASTNode to represent a binary conditional expression.
 * Implements the ConditionalExpressionNode interface.
 */
class BinaryConditionalExpressionNode : public ConditionalExpressionNode {
private:
    /**
     * The type of conditional operator for the binary conditional expression.
     */
    BinaryConditionalExpressionType binaryConditionalExpressionType;

    /**
     * The conditional expression on the LHS.
     */
    std::shared_ptr<ConditionalExpressionNode> leftConditionalExpression;

    /**
     * The conditional expression on the RHS.
     */
    std::shared_ptr<ConditionalExpressionNode> rightConditionalExpression;

public:
    /**
     * Creates and initializes a BinaryConditionalExpressionNode.
     * @param binaryConditionalExpressionType The type of binary conditional operator
     * @param leftConditionalExpression The LHS conditional expression
     * @param rightConditionalExpression The RHS conditional expression
     */
    explicit BinaryConditionalExpressionNode(BinaryConditionalExpressionType binaryConditionalExpressionType,
                                             std::shared_ptr<ConditionalExpressionNode> leftConditionalExpression,
                                             std::shared_ptr<ConditionalExpressionNode> rightConditionalExpression);

    /**
     * Returns the binary conditional operator.
     * @return The binary conditional operator
     */
    BinaryConditionalExpressionType getBinaryConditionalExpressionType();

    /**
     * Returns the conditional expression on the LHS.
     * @return The LHS conditional expression
     */
    std::shared_ptr<ConditionalExpressionNode> getLeftConditionalExpression();

    /**
     * Returns the conditional expression on the RHS.
     * @return The RHS conditional expression
     */
    std::shared_ptr<ConditionalExpressionNode> getRightConditionalExpression();

    /**
     * Converts the given string representing a binary conditional operator to the
     * corresponding BinaryConditionalExpressionType value.
     * @param typeString The string representing a binary conditional operator
     * @return The BinaryConditionalExpressionType value corresponding to the string
     */
    static BinaryConditionalExpressionType translateBinaryConditionalExpressionTypeString(std::string typeString);

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};