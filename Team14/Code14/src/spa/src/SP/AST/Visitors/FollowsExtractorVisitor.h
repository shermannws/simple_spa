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

class FollowsExtractorVisitor : public DesignExtractorVisitor,
    public StatementListNodeVisitor {
public:
    /*!
     * Constructor for FollowsExtractorVisitor
     */
    FollowsExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    /*!
     * Visits a statement list node and add all follows/follows* relationship into PKB
     */
    void visitStatementListNode(StatementListNode* node) const override;
};
