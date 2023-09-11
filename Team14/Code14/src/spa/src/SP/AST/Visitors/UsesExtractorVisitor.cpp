#include "UsesExtractorVisitor.h"

// TODO: Implement relevant visit methods

void UsesExtractorVisitor::visitProgramNode(std::shared_ptr<ProgramNode> node) {}

void UsesExtractorVisitor::visitProcedureNode(std::shared_ptr<ProcedureNode> node) {}

void UsesExtractorVisitor::visitStatementListNode(std::shared_ptr<StatementListNode> node) {}

void UsesExtractorVisitor::visitAssignNode(std::shared_ptr<AssignNode> node) {}

void UsesExtractorVisitor::visitReadNode(std::shared_ptr<ReadNode> node) {}

void UsesExtractorVisitor::visitPrintNode(std::shared_ptr<PrintNode> node) {}

void UsesExtractorVisitor::visitArithmeticExpressionNode(std::shared_ptr<ArithmeticExpressionNode> node) {}

void UsesExtractorVisitor::visitVariableNode(std::shared_ptr<VariableNode> node) {}

void UsesExtractorVisitor::visitConstantNode(std::shared_ptr<ConstantNode> node) {}