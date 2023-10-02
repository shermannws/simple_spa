#include <functional>

#include "ModifiesExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "VisitorUtility.h"

ModifiesExtractorVisitor::ModifiesExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
	this->func =
		[this](std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) -> void {
		this->pkbWriter->addModifiesRelationship(s, v);
		};
}

void ModifiesExtractorVisitor::visitAssignNode(AssignNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	return VisitorUtility::addAllStatementVariableRelationshipFrom(
		node->getVar(),
		Statement(node->getStatementNumber(), StatementType::Assign),
		parents,
		this->func
	);
}

void ModifiesExtractorVisitor::visitReadNode(ReadNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	return VisitorUtility::addAllStatementVariableRelationshipFrom(
		node->getVar(),
		Statement(node->getStatementNumber(), StatementType::Read),
		parents,
		this->func
	);
}
