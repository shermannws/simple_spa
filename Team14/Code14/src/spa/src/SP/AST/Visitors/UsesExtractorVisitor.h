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
    UsesExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    void visitAssignNode(std::shared_ptr<AssignNode> node) const override;

    void visitPrintNode(std::shared_ptr<PrintNode> node) const override;
};
