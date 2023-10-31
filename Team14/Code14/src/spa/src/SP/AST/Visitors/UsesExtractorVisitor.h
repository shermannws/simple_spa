#pragma once

#include <functional>

#include "../../AST/Nodes/AssignNode.h"
#include "../../AST/Nodes/IfNode.h"
#include "../../AST/Nodes/PrintNode.h"
#include "../../AST/Nodes/WhileNode.h"
#include "DesignExtractorVisitor.h"
#include "VisitorUtility.h"

class UsesExtractorVisitor : public DesignExtractorVisitor,
                             public AssignNodeVisitor,
                             public PrintNodeVisitor,
                             public IfNodeVisitor,
                             public WhileNodeVisitor {
private:
    /*!
     * Utility class to help populate PKB with Uses relationships.
     */
    VisitorUtility visitorUtils;

public:
    /*!
     * Constructor for UsesExtractorVisitor.
     * @param pkbWriter A shared ptr to a concrete implementation of PkbWriter class
     */
    explicit UsesExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits an AssignNode and add variables used by the Assignment into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitAssignNode(const std::shared_ptr<AssignNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                         std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits a PrintNode and add variable used into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitPrintNode(const std::shared_ptr<PrintNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                        std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits an IfNode and add variable used into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitIfNode(const std::shared_ptr<IfNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                     std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits a WhileNode and add variable used into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitWhileNode(const std::shared_ptr<WhileNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                        std::shared_ptr<Procedure> proc) const override;
};
