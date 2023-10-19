#pragma once

#include "../../AST/Nodes/StatementListNode.h"
#include "DesignExtractorVisitor.h"

class ParentExtractorVisitor : public DesignExtractorVisitor, public StatementListNodeVisitor {
public:
    /*!
     * Constructor for ParentExtractorVisitor.
     * @param pkbWriter A shared ptr to a concrete implementation of PkbWriter class
     */
    ParentExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits a statement list node and add all parent / parent* relationship into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     * @param proc The procedure node which the node is in
     */
    void visitStatementListNode(StatementListNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                std::shared_ptr<ASTNode> proc) const override;
};
