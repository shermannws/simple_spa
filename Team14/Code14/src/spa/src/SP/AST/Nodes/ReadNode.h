#pragma once

#include <memory>

#include "Commons/AppConstants.h"
#include "StatementNode.h"
#include "VariableNode.h"

class ReadNode;// forward declaration

/**
 * Visitor interface linked to ReadNode, used to implement the Acyclic Visitor pattern.
 */
class ReadNodeVisitor {
public:
    /**
     * Visits the ReadNode for design extraction.
     * @param node ReadNode to be visited
     * @param parents Parents of the ReadNode
     * @param proc The procedure that the ReadNode is contained within
     */
    virtual void visitReadNode(ReadNode *node, std::vector<std::shared_ptr<Statement>> parents,
                               std::shared_ptr<Procedure> proc) const = 0;
};

/**
 * ASTNode to represent a read statement.
 * Inherits from the StatementNode abstract class.
 */
class ReadNode : public StatementNode {
private:
    /**
     * The variable that a value is read into.
     */
    std::shared_ptr<VariableNode> var;

public:
    /**
     * Creates and initializes a ReadNode.
     * @param statementNumber The statement number of this statement
     * @param var The variable that a value is read into
     */
    explicit ReadNode(StatementNumber statementNumber, std::shared_ptr<VariableNode> var);

    /**
     * Returns the variable that the value is read into.
     * @return The variable that is read into
     */
    std::shared_ptr<VariableNode> getVar();

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<Statement>> parents,
                std::shared_ptr<Procedure> proc) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;

    StatementNodeType getStatementType() override;
};
