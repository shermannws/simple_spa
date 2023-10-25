#pragma once

#include "Commons/AppConstants.h"
#include "ExpressionNode.h"

class ConstantNode;// forward declaration

/**
 * Visitor interface linked to ConstantNode, used to implement the Acyclic Visitor pattern.
 */
class ConstantNodeVisitor {
public:
    /**
     * Visits the ConstantNode for design extraction.
     * @param node ConstantNode to be visited
     * @param parents Parents of the ConstantNode
     * @param proc The procedure that the ConstantNode is in
     */
    virtual void visitConstantNode(const std::shared_ptr<ConstantNode> &node,
                                   std::vector<std::shared_ptr<Statement>> parents,
                                   std::shared_ptr<Procedure> proc) const = 0;
};

/**
 * ASTNode to represent a constant.
 * Implements the ExpressionNode interface.
 */
class ConstantNode : public ExpressionNode, public std::enable_shared_from_this<ConstantNode> {
private:
    /**
     * The value of the constant.
     */
    ConstantValue value;

public:
    /**
     * Creates and initializes an ConstantNode.
     * @param value The value of the constant
     */
    explicit ConstantNode(ConstantValue value);

    /**
     * Returns the value of the constant.
     * @return The value of the constant
     */
    ConstantValue getValue();

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<Statement>> parents,
                std::shared_ptr<Procedure> proc) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;

    std::string toString() override;
};
