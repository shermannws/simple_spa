#pragma once

#include <memory>
#include <unordered_map>

#include "BinaryConditionalExpressionType.h"
#include "Commons/AppConstants.h"
#include "ConditionalExpressionNode.h"

class BinaryConditionalExpressionNode;// forward declaration

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
     * @param proc Procedure containing the BinaryConditionalExpressionNode
     */
    virtual void visitBinaryConditionalExpressionNode(const std::shared_ptr<BinaryConditionalExpressionNode> &node,
                                                      std::vector<std::shared_ptr<ASTNode>> parents,
                                                      std::shared_ptr<ASTNode> proc) const = 0;
};

/**
 * ASTNode to represent a binary conditional expression.
 * Implements the ConditionalExpressionNode interface.
 */
class BinaryConditionalExpressionNode : public ConditionalExpressionNode,
                                        public std::enable_shared_from_this<BinaryConditionalExpressionNode> {
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

    /**
     * Map of binary conditional operator type string to BinaryConditionalExpressionType.
     */
    inline static const std::unordered_map<std::string, BinaryConditionalExpressionType> stringToExpressionTypeMap = {
            {AppConstants::STRING_AND, BinaryConditionalExpressionType::And},
            {AppConstants::STRING_OR, BinaryConditionalExpressionType::Or}};

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
    static BinaryConditionalExpressionType
    translateBinaryConditionalExpressionTypeString(const std::string &typeString);

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents,
                std::shared_ptr<ASTNode> proc) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
