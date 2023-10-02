#pragma once

#include "DesignExtractorVisitor.h"
#include "../../AST/Nodes/ProgramNode.h"
#include "../../AST/Nodes/ProcedureNode.h"
#include "../../AST/Nodes/StatementListNode.h"
#include "../../AST/Nodes/AssignNode.h"
#include "../../AST/Nodes/ReadNode.h"
#include "../../AST/Nodes/PrintNode.h"
#include "../../AST/Nodes/ArithmeticExpressionNode.h"
#include "../../AST/Nodes/VariableNode.h"
#include "../../AST/Nodes/ConstantNode.h"
#include "../../AST/Nodes/CallNode.h"
#include "../../AST/Nodes/IfNode.h"
#include "../../AST/Nodes/WhileNode.h"

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
     * @param parents A vector of parent nodes for this node
     */
    void visitProcedureNode(ProcedureNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    /*!
     * Visits an AssignNode and adds the assignment to the PKB and stores the assignment pattern to support pattern query.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     */
    void visitAssignNode(AssignNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    /*!
     * Visits a ReadNode and add Read statement into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     */
    void visitReadNode(ReadNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    /*!
     * Visits a PrintNode and add Print statement into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     */
    void visitPrintNode(PrintNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    /*!
     * Visits a VariableNode and add Variable into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     */
    void visitVariableNode(VariableNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    /*!
     * Visits a ConstantNode and add Constant into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     */
    void visitConstantNode(ConstantNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    /*!
     * Visits a CallNode and add Call statement into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     */
    void visitCallNode(CallNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    /*!
     * Visits an IfNode and add If statement into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     */
    void visitIfNode(IfNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;

    /*!
     * Visits a WhileNode and add While statement into PKB.
     * @param node The node to be visited
     * @param parents A vector of parent nodes for this node
     */
    void visitWhileNode(WhileNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const override;
};
