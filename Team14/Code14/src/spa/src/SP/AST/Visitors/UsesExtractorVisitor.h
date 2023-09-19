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

class UsesExtractorVisitor : public DesignExtractorVisitor,
    public AssignNodeVisitor,
    public PrintNodeVisitor {
public:
    /*!
     * Constructor for UsesExtractorVisitor
     */
    UsesExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits an AssignNide and add variables used by the Assignment into PKB
     */
    void visitAssignNode(AssignNode* node) const override;

    /*!
     * Visits a PrintNode and add variable used into PKB
     */
    void visitPrintNode(PrintNode* node) const override;
};
