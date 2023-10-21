#pragma once

#include <functional>

#include "../../AST/Nodes/AssignNode.h"
#include "../../AST/Nodes/IfNode.h"
#include "../../AST/Nodes/PrintNode.h"
#include "../../AST/Nodes/WhileNode.h"
#include "DesignExtractorVisitor.h"

class UsesExtractorVisitor : public DesignExtractorVisitor,
                             public AssignNodeVisitor,
                             public PrintNodeVisitor,
                             public IfNodeVisitor,
                             public WhileNodeVisitor {
private:
    /*!
     * funcStmt is a lambda function used to abstract the call to PKB to add Uses relationship.
     */
    std::function<void(std::shared_ptr<Statement>, std::shared_ptr<Variable>)> funcStmt;

    /*!
     * funcProc is a lambda function used to abstract the call to PKB to add Uses (proc-var) relationship.
     */
    std::function<void(std::shared_ptr<Procedure>, std::shared_ptr<Variable>)> funcProc;

public:
    /*!
     * Constructor for UsesExtractorVisitor.
     * @param pkbWriter A shared ptr to a concrete implementation of PkbWriter class
     */
    UsesExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits an AssignNode and add variables used by the Assignment into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitAssignNode(AssignNode *node, std::vector<std::shared_ptr<Statement>> parents,
                         std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits a PrintNode and add variable used into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitPrintNode(PrintNode *node, std::vector<std::shared_ptr<Statement>> parents,
                        std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits an IfNode and add variable used into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitIfNode(IfNode *node, std::vector<std::shared_ptr<Statement>> parents,
                     std::shared_ptr<Procedure> proc) const override;


    /*!
     * Visits a WhileNode and add variable used into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitWhileNode(WhileNode *node, std::vector<std::shared_ptr<Statement>> parents,
                        std::shared_ptr<Procedure> proc) const override;
};
