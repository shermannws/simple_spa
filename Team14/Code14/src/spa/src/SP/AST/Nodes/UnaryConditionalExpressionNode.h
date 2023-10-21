#pragma once

#include "memory"

#include "ConditionalExpressionNode.h"

class UnaryConditionalExpressionNode;// forward declaration

/**
 * Visitor interface linked to UnaryConditionalExpressionNode,
 * used to implement the Acyclic Visitor pattern.
 */
class UnaryConditionalExpressionNodeVisitor {
public:
    /**
     * Visits the UnaryConditionalExpressionNode for design extraction.
     * @param node UnaryConditionalExpressionNode to be visited
     * @param parents Parents of the UnaryConditionalExpressionNode
     * @param proc Procedure containing the UnaryConditionalExpressionNode
     */
    virtual void visitUnaryConditionalExpressionNode(UnaryConditionalExpressionNode *node,
                                                     std::vector<std::shared_ptr<Statement>> parents,
                                                     std::shared_ptr<Procedure> proc) const = 0;
};

/**
 * ASTNode to represent a unary conditional expression.
 * Represents "! <cond_expr>" by default since there is only one type of
 * unary conditional expression.
 * Implements the ConditionalExpressionNode interface.
 */
class UnaryConditionalExpressionNode : public ConditionalExpressionNode {
private:
    /**
     * The nested conditional expression of the unary conditional expression.
     */
    std::shared_ptr<ConditionalExpressionNode> conditionalExpression;

public:
    /**
     * Creates and initializes a UnaryConditionalExpressionNode.
     * @param conditionalExpression The nested conditional expression
     */
    explicit UnaryConditionalExpressionNode(std::shared_ptr<ConditionalExpressionNode> conditionalExpression);

    /**
     * Returns the nested conditional expression of the unary conditional expression.
     * @return The nested conditional expression
     */
    std::shared_ptr<ConditionalExpressionNode> getConditionalExpression();

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<Statement>> parents,
                std::shared_ptr<Procedure> proc) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
