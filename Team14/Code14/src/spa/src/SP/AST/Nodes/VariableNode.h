#pragma once

#include <string>

#include "Commons/AppConstants.h"
#include "ExpressionNode.h"

class VariableNode;// forward declaration

/**
 * Visitor interface linked to VariableNode, used to implement the Acyclic Visitor pattern.
 */
class VariableNodeVisitor {
public:
    /**
     * Visits the VariableNode for design extraction.
     * @param node VariableNode to be visited
     * @param parents Parents of the VariableNode
     * @param proc The procedure that the VariableNode is in
     */
    virtual void visitVariableNode(const std::shared_ptr<VariableNode> &node,
                                   std::vector<std::shared_ptr<Statement>> parents,
                                   std::shared_ptr<Procedure> proc) const = 0;
};

/**
 * ASTNode to represent a variable.
 * Implements the ExpressionNode interface.
 */
class VariableNode : public ExpressionNode, public std::enable_shared_from_this<VariableNode> {
private:
    /**
     * The name of the variable.
     */
    VariableName varName;

public:
    /**
     * Creates and initializes an VariableNode.
     * @param varName The name of the variable
     */
    explicit VariableNode(VariableName varName);

    /**
     * Returns the name of the variable.
     * @return The name of the variable
     */
    VariableName getVarName();

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<Statement>> parents,
                std::shared_ptr<Procedure> proc) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;

    std::string toString() override;
};
