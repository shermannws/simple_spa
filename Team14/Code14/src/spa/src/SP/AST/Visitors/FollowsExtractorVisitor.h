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
    FollowsExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    void visitStatementListNode(std::shared_ptr<StatementListNode> node) const override;
};
