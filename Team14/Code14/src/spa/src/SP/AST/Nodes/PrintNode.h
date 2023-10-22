#pragma once

#include <memory>

#include "Commons/AppConstants.h"
#include "StatementNode.h"
#include "VariableNode.h"

class PrintNode;// forward declaration

/**
 * Visitor interface linked to PrintNode, used to implement the Acyclic Visitor pattern.
 */
class PrintNodeVisitor {
public:
    /**
     * Visits the PrintNode for design extraction.
     * @param node PrintNode to be visited
     * @param parents Parents of the PrintNode
     * @param proc The procedure that the PrintNode is in
     */
    virtual void visitPrintNode(PrintNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                std::shared_ptr<Procedure> proc) const = 0;
};

/**
 * ASTNode to represent a print statement.
 * Inherits from the StatementNode abstract class.
 */
class PrintNode : public StatementNode {
private:
    /**
     * The variable whose value is printed.
     */
    std::shared_ptr<VariableNode> var;

public:
    /**
     * Creates and initializes a PrintNode.
     * @param statementNumber The statement number of this statement
     * @param var The variable whose value is printed
     */
    explicit PrintNode(StatementNumber statementNumber, std::shared_ptr<VariableNode> var);

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
