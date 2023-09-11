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

    void visitProgramNode(std::shared_ptr<ProgramNode> node) const override;

    void visitProcedureNode(std::shared_ptr<ProcedureNode> node) const override;

    void visitStatementListNode(std::shared_ptr<StatementListNode> node) const override;

    void visitAssignNode(std::shared_ptr<AssignNode> node) const override;

    void visitReadNode(std::shared_ptr<ReadNode> node) const override;

    void visitPrintNode(std::shared_ptr<PrintNode> node) const override;

    void visitArithmeticExpressionNode(std::shared_ptr<ArithmeticExpressionNode> node) const override;

    void visitVariableNode(std::shared_ptr<VariableNode> node) const override;

    void visitConstantNode(std::shared_ptr<ConstantNode> node) const override;
};
