#pragma once

#include "../../AST/Nodes/StatementListNode.h"
#include "DesignExtractorVisitor.h"

class FollowsExtractorVisitor : public DesignExtractorVisitor, public StatementListNodeVisitor {
public:
    /*!
     * Constructor for FollowsExtractorVisitor.
     * @param pkbWriter A shared ptr to a concrete implementation of PkbWriter class
     */
    FollowsExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits a statement list node and add all follows/follows* relationship into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     * @param proc The procedure node which the node is in
     */
    void visitStatementListNode(const std::shared_ptr<StatementListNode> &node,
                                std::vector<std::shared_ptr<ASTNode>> parents,
                                std::shared_ptr<ASTNode> proc) const override;
};
