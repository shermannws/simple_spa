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
     * Constructor for EntityExtractorVisitor
     */
    EntityExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits a ProcedureNode and adds Procedure to the PKB
     */
    void visitProcedureNode(ProcedureNode* node) const override;

    /*!
     * Visits an AssignNode and adds the assignment to the PKB and stores the assignment pattern to support pattern query
     */
    void visitAssignNode(AssignNode* node) const override;

    /*!
     * Visits a ReadNode and add Read statement into PKB
     */
    void visitReadNode(ReadNode* node) const override;

    /*!
     * Visits a PrintNode and add Print statement into PKB
     */
    void visitPrintNode(PrintNode* node) const override;

    /*!
     * Visits a VariableNode and add Variable into PKB
     */
    void visitVariableNode(VariableNode* node) const override;

    /*!
     * Visits a ConstantNode and add Constant into PKB
     */
    void visitConstantNode(ConstantNode* node) const override;

    /*!
     * Visits a CallNode and add Call statement into PKB
     */
    void visitCallNode(CallNode* node) const override;

    /*!
     * Visits a IfNode and add If statement into PKB
     */
    void visitIfNode(IfNode* node) const override;

    /*!
     * Visits a WhileNode and add While statement into PKB
     */
    void visitWhileNode(WhileNode* node) const override;
};
