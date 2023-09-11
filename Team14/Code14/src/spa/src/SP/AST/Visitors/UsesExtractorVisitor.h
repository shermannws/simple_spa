#pragma once

#include "DesignExtractorVisitor.h"

class UsesExtractorVisitor : public DesignExtractorVisitor {
public:
    void visitProgramNode(std::shared_ptr<ProgramNode> node) override;

    void visitProcedureNode(std::shared_ptr<ProcedureNode> node) override;

    void visitStatementListNode(std::shared_ptr<StatementListNode> node) override;

    void visitAssignNode(std::shared_ptr<AssignNode> node) override;

    void visitReadNode(std::shared_ptr<ReadNode> node) override;

    void visitPrintNode(std::shared_ptr<PrintNode> node) override;

    void visitArithmeticExpressionNode(std::shared_ptr<ArithmeticExpressionNode> node) override;

    void visitVariableNode(std::shared_ptr<VariableNode> node) override;

    void visitConstantNode(std::shared_ptr<ConstantNode> node) override;
};