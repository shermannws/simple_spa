#pragma once

#include <functional>

#include "../../AST/Nodes/AssignNode.h"
#include "../../AST/Nodes/ReadNode.h"
#include "DesignExtractorVisitor.h"

class ModifiesExtractorVisitor : public DesignExtractorVisitor, public AssignNodeVisitor, public ReadNodeVisitor {
private:
    /*!
     * funcStmt is a lambda function used to abstract the call to PKB to add Modifies (stmt-var) relationship.
     */
    std::function<void(std::shared_ptr<Statement>, std::shared_ptr<Variable>)> funcStmt;

    /*!
     * funcProc is a lambda function used to abstract the call to PKB to add Modifies (proc-var) relationship.
     */
    std::function<void(std::shared_ptr<Procedure>, std::shared_ptr<Variable>)> funcProc;

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
     * @param proc The procedure node which the node is in
     */
    void visitAssignNode(const std::shared_ptr<AssignNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                         std::shared_ptr<ASTNode> proc) const override;

    /*!
     * Visits a ReadNode and add variable used into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     * @param proc The procedure node which the node is in
     */
    void visitReadNode(const std::shared_ptr<ReadNode> &node, std::vector<std::shared_ptr<ASTNode>> parents,
                       std::shared_ptr<ASTNode> proc) const override;
};
