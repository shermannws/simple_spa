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

void EntityExtractorVisitor::visitProcedureNode(ProcedureNode *node) const {
	this->pkbWriter->addProcedure(std::make_shared<Procedure>(node->getProcedureName()));
}

void EntityExtractorVisitor::visitAssignNode(AssignNode *node) const {
	this->pkbWriter->addAssignStatement(
			std::make_shared<Statement>(node->getStatementNumber(), StatementType::Assign),
			std::make_shared<Variable>(node->getVar()->getVarName()),
			std::make_shared<std::string>(node->getExpression()->toString()));
}

void EntityExtractorVisitor::visitReadNode(ReadNode *node) const {
	this->pkbWriter->addReadStatement(std::make_shared<Statement>(node->getStatementNumber(), StatementType::Read));
}

void EntityExtractorVisitor::visitPrintNode(PrintNode *node) const {
	this->pkbWriter->addPrintStatement(std::make_shared<Statement>(node->getStatementNumber(), StatementType::Print));
}

void EntityExtractorVisitor::visitVariableNode(VariableNode *node) const {
	this->pkbWriter->addVariable(std::make_shared<Variable>(node->getVarName()));
}

void EntityExtractorVisitor::visitConstantNode(ConstantNode *node) const {
	this->pkbWriter->addConstant(std::make_shared<Constant>(node->getValue()));
}
