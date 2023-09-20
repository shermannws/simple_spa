#include <functional>

#include "ModifiesExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

ModifiesExtractorVisitor::ModifiesExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

void ModifiesExtractorVisitor::visitAssignNode(AssignNode* node) const {
	this->pkbWriter->addModifiesRelationship(
		std::make_shared<Statement>(node->getStatementNumber(), StatementType::Assign),
		std::make_shared<Variable>(node->getVar()->getVarName())
	);
}

void ModifiesExtractorVisitor::visitReadNode(ReadNode* node) const {
	this->pkbWriter->addModifiesRelationship(
		std::make_shared<Statement>(node->getStatementNumber(), StatementType::Read),
		std::make_shared<Variable>(node->getVar()->getVarName())
	);
}
