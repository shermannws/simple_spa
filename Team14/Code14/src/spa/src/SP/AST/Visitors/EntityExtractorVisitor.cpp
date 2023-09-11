#include <string>

#include "EntityExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Constant.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/Procedure.h"

EntityExtractorVisitor::EntityExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

void EntityExtractorVisitor::visitProgramNode(std::shared_ptr<ProgramNode> node) const {}

void EntityExtractorVisitor::visitProcedureNode(std::shared_ptr<ProcedureNode> node) const {
	this->pkbWriter->addProcedure(std::make_shared<Procedure>(node->getProcedureName()));
}

void EntityExtractorVisitor::visitStatementListNode(std::shared_ptr<StatementListNode> node) const {}

void EntityExtractorVisitor::visitAssignNode(std::shared_ptr<AssignNode> node) const {
	this->pkbWriter->addAssignStatement(
		std::make_shared<Statement>(node->getStatementNumber(), StatementType::Assign),
		std::make_shared<Variable>(node->getVar()->getVarName()),
		std::make_shared<std::string>("")); //TODO: to get the string expression
}

void EntityExtractorVisitor::visitReadNode(std::shared_ptr<ReadNode> node) const {
	this->pkbWriter->addReadStatement(std::make_shared<Statement>(node->getStatementNumber()));
}

void EntityExtractorVisitor::visitPrintNode(std::shared_ptr<PrintNode> node) const {
	this->pkbWriter->addPrintStatement(std::make_shared<Statement>(node->getStatementNumber()));
}

void EntityExtractorVisitor::visitArithmeticExpressionNode(std::shared_ptr<ArithmeticExpressionNode> node) const {}

void EntityExtractorVisitor::visitVariableNode(std::shared_ptr<VariableNode> node) const {
	this->pkbWriter->addVariable(std::make_shared<Variable>(node->getVarName()));
}

void EntityExtractorVisitor::visitConstantNode(std::shared_ptr<ConstantNode> node) const {
	this->pkbWriter->addConstant(std::make_shared<Constant>(node->getValue()));
}