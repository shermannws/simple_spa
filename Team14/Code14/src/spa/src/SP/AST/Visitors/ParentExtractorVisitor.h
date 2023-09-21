#pragma once

#include "DesignExtractorVisitor.h"
#include "../../AST/Nodes/StatementListNode.h"

class ParentExtractorVisitor : public DesignExtractorVisitor,
    public StatementListNodeVisitor {
public:
    /*!
     * Constructor for FollowsExtractorVisitor
     */
    ParentExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits a statement list node and add all parent / parent* relationship into PKB
     */
    void visitStatementListNode(StatementListNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const override;
};
