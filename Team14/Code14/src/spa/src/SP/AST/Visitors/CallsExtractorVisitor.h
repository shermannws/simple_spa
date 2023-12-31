#pragma once

#include "../../AST/Nodes/CallNode.h"
#include "../../AST/Nodes/ProcedureNode.h"
#include "DesignExtractorVisitor.h"

class CallsExtractorVisitor : public DesignExtractorVisitor, public CallNodeVisitor {
public:
    /**
     * Constructor for CallsExtractorVisitor.
     * @param pkbWriter A shared ptr to a concrete implementation of PkbWriter class
     */
    explicit CallsExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /**
     * Visits a call node and adds the direct call relationship into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitCallNode(const std::shared_ptr<CallNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                       std::shared_ptr<Procedure> proc) const override;
};