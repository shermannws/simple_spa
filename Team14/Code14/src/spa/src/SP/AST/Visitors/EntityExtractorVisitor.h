#pragma once

#include "../../AST/Nodes/ArithmeticExpressionNode.h"
#include "../../AST/Nodes/AssignNode.h"
#include "../../AST/Nodes/CallNode.h"
#include "../../AST/Nodes/ConstantNode.h"
#include "../../AST/Nodes/IfNode.h"
#include "../../AST/Nodes/PrintNode.h"
#include "../../AST/Nodes/ProcedureNode.h"
#include "../../AST/Nodes/ProgramNode.h"
#include "../../AST/Nodes/ReadNode.h"
#include "../../AST/Nodes/StatementListNode.h"
#include "../../AST/Nodes/VariableNode.h"
#include "../../AST/Nodes/WhileNode.h"
#include "DesignExtractorVisitor.h"

class EntityExtractorVisitor : public DesignExtractorVisitor,
                               public ProcedureNodeVisitor,
                               public AssignNodeVisitor,
                               public ReadNodeVisitor,
                               public PrintNodeVisitor,
                               public VariableNodeVisitor,
                               public ConstantNodeVisitor,
                               public CallNodeVisitor,
                               public IfNodeVisitor,
                               public WhileNodeVisitor {
public:
    /*!
     * Constructor for EntityExtractorVisitor.
     * @param pkbWriter A shared ptr to a concrete implementation of PkbWriter class
     */
    EntityExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits a ProcedureNode and adds Procedure to the PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitProcedureNode(const std::shared_ptr<ProcedureNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                            std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits an AssignNode and adds the assignment to the PKB and stores the assignment pattern to support pattern
     * query.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitAssignNode(const std::shared_ptr<AssignNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                         std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits a ReadNode and add Read statement into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitReadNode(const std::shared_ptr<ReadNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                       std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits a PrintNode and add Print statement into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitPrintNode(const std::shared_ptr<PrintNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                        std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits a VariableNode and add Variable into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitVariableNode(const std::shared_ptr<VariableNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                           std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits a ConstantNode and add Constant into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitConstantNode(const std::shared_ptr<ConstantNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                           std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits a CallNode and add Call statement into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitCallNode(const std::shared_ptr<CallNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                       std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits an IfNode and add If statement into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitIfNode(const std::shared_ptr<IfNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                     std::shared_ptr<Procedure> proc) const override;

    /*!
     * Visits a WhileNode and add While statement into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent statements for this node
     * @param proc The procedure which the node is in
     */
    void visitWhileNode(const std::shared_ptr<WhileNode> &node, std::vector<std::shared_ptr<Statement>> parents,
                        std::shared_ptr<Procedure> proc) const override;
};
