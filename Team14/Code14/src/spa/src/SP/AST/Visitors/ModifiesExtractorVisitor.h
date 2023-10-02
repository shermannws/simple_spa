#pragma once

#include <functional>

#include "DesignExtractorVisitor.h"
#include "../../AST/Nodes/AssignNode.h"
#include "../../AST/Nodes/ReadNode.h"

class ModifiesExtractorVisitor : public DesignExtractorVisitor,
    public AssignNodeVisitor,
    public ReadNodeVisitor
{
private:
    /*!
     * func is a lambda function used to abstract the call to PKB to add Modifies relationship.
     */
    std::function<void(std::shared_ptr<Statement>, std::shared_ptr<Variable>)> func;
public:
    /*!
     * Constructor for ModifiesExtractorVisitor.
     * @param pkbWriter A shared ptr to a concrete implementation of PkbWriter class
     */
    ModifiesExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits an AssignNode and add variables used by the Assignment into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     */
    void visitAssignNode(AssignNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    /*!
     * Visits a ReadNode and add variable used into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     */
    void visitReadNode(ReadNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;
};
