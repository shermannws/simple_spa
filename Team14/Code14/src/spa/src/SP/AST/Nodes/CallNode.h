#pragma once

#include <memory>

#include "Commons/AppConstants.h"
#include "StatementNode.h"

class CallNode;// forward declaration

/**
 * Visitor interface linked to CallNode, used to implement the Acyclic Visitor pattern.
 */
class CallNodeVisitor {
public:
    /**
     * Visits the CallNode for design extraction.
     * @param node CallNode to be visited
     * @param parents Parents of the CallNode
     * @param proc Procedure containing the CallNode
     */
    virtual void visitCallNode(const std::shared_ptr<CallNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                               std::shared_ptr<ASTNode> proc) const = 0;
};

/**
 * ASTNode to represent a call statement.
 * Inherits from the StatementNode abstract class.
 */
class CallNode : public StatementNode, public std::enable_shared_from_this<CallNode> {
private:
    /**
     * The name of the procedure called.
     */
    ProcedureName procedureName;

public:
    /**
     * Creates and initializes a CallNode.
     * @param statementNumber The statement number of this statement
     * @param procedureName The name of the procedure called
     */
    explicit CallNode(StatementNumber statementNumber, ProcedureName procedureName);

    /**
     * Returns the name of the procedure called.
     * @return The name of the procedure called
     */
    ProcedureName getProcedureName();

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<ASTNode>> parents,
                std::shared_ptr<ASTNode> proc) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;

    StatementNodeType getStatementType() override;
};
