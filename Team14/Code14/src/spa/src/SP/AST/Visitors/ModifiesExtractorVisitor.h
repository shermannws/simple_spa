#pragma once

#include <functional>

#include "../../AST/Nodes/AssignNode.h"
#include "../../AST/Nodes/ReadNode.h"
#include "DesignExtractorVisitor.h"
#include "VisitorUtility.h"

class ModifiesExtractorVisitor : public DesignExtractorVisitor, public AssignNodeVisitor, public ReadNodeVisitor {
private:
    /*!
     * Utility class to help populate PKB with Uses relationships.
     */
    VisitorUtility mutable visitorUtils;

public:
    /*!
     * Constructor for ModifiesExtractorVisitor.
     * @param pkbWriter A shared ptr to a concrete implementation of PkbWriter class
     */
    explicit ModifiesExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits an AssignNode and add variables used by the Assignment into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitAssignNode(const std::shared_ptr<AssignNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                         std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits a ReadNode and add variable used into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitReadNode(const std::shared_ptr<ReadNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                       std::shared_ptr<Procedure> proc) const override;
};
