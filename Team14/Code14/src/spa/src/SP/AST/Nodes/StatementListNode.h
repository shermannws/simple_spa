#pragma once

#include <vector>

#include "ASTNode.h"
#include "StatementNode.h"

class StatementListNode;// forward declaration

/**
 * Visitor interface linked to StatementListNode, used to implement the Acyclic Visitor pattern.
 */
class StatementListNodeVisitor {
public:
    /**
     * Visits the StatementListNode for design extraction.
     * @param node StatementListNode to be visited
     * @param parents Parents of the StatementListNode
     * @param proc Procedure containing the StatementListNode
     */
    virtual void visitStatementListNode(const std::shared_ptr<StatementListNode> &node,
                                        std::vector<std::shared_ptr<Statement>> parents,
                                        std::shared_ptr<Procedure> proc) const = 0;
};

/**
 * ASTNode to represent a statement list.
 */
class StatementListNode : public ASTNode, public std::enable_shared_from_this<StatementListNode> {
private:
    /**
     * The vector of statements in the statement list.
     */
    std::vector<std::shared_ptr<StatementNode>> statements;

public:
    /**
     * Creates and initializes a StatementListNode.
     * @param statements The vector of statements in the statement list
     */
    explicit StatementListNode(std::vector<std::shared_ptr<StatementNode>> statements);

    /**
     * Returns the vector of statements in the statement list.
     * @return The vector of statements in the statement list
     */
    std::vector<std::shared_ptr<StatementNode>> getStatements();

    void accept(std::shared_ptr<DesignExtractorVisitor> visitor, std::vector<std::shared_ptr<Statement>> parents,
                std::shared_ptr<Procedure> proc) override;

    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
