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

class EntityExtractorVisitor : public DesignExtractorVisitor,
    public ProgramNodeVisitor,
    public ProcedureNodeVisitor,
    public StatementListNodeVisitor,
    public AssignNodeVisitor,
    public ReadNodeVisitor,
    public PrintNodeVisitor,
    public ArithmeticExpressionNodeVisitor,
    public VariableNodeVisitor,
    public ConstantNodeVisitor {
public:
    EntityExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter);

    void visitProgramNode(ProgramNode* node) const override;

    void visitProcedureNode(ProcedureNode* node) const override;

    void visitStatementListNode(StatementListNode* node) const override;

    void visitAssignNode(AssignNode* node) const override;

    void visitReadNode(ReadNode* node) const override;

    void visitPrintNode(PrintNode* node) const override;

    void visitArithmeticExpressionNode(ArithmeticExpressionNode* node) const override;

    void visitVariableNode(VariableNode* node) const override;

    void visitConstantNode(ConstantNode* node) const override;
};
