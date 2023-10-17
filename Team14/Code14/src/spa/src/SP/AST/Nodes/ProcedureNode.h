#pragma once

#include <string>

#include "ASTNode.h"
#include "Commons/AppConstants.h"
#include "StatementListNode.h"

class ProcedureNode;// forward declaration

/**
 * Visitor interface linked to ProcedureNode, used to implement the Acyclic
 * Visitor pattern.
 */
class ProcedureNodeVisitor {
public:
    /**
     * Visits the ProcedureNode for design extraction.
     * @param node ProcedureNode to be visited
     * @param parents Parents of the ProcedureNode
     * @param proc The procedure that the ProcedureNode (aka itself)
     */
    virtual void
    visitProcedureNode(ProcedureNode *node,
                       std::vector<std::shared_ptr<ASTNode>> parents,
                       std::shared_ptr<ASTNode> proc) const = 0;
};

/**
 * ASTNode to represent a procedure.
 */
class ProcedureNode : public ASTNode {
private:
    /**
     * The name of the procedure.
     */
    std::string procedureName;

    /**
     * The statement list for the procedure.
     */
    std::shared_ptr<StatementListNode> statementList;

public:
    /**
     * Creates and initializes a ProcedureNode.
     * @param procedureName The name of the procedure
     * @param statementList The statement list for the procedure
     */
    explicit ProcedureNode(ProcedureName procedureName,
                           std::shared_ptr<StatementListNode> statementList);

    /**
     * Returns the name of the procedure.
     * @return The name of the procedure
     */
    ProcedureName getProcedureName();

    /**
     * Returns the statement list of the procedure.
     * @return The statement list of the procedure
     */
    std::shared_ptr<StatementListNode> getStatementList();

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor,
                std::vector<std::shared_ptr<ASTNode>> parents,
                std::shared_ptr<ASTNode> proc) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
