#include <functional>

#include "UsesExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "VisitorUtility.h"

UsesExtractorVisitor::UsesExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

void UsesExtractorVisitor::visitAssignNode(AssignNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const {
	std::function<void(std::shared_ptr<Statement>, std::shared_ptr<Variable>)> func = [this](std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) -> void {
		this->pkbWriter->addUsesRelationship(s, v);
		};

	VisitorUtility::addAllStatementVariableRelationshipFrom(
		node->getExpression(),
		Statement(node->getStatementNumber(), StatementType::Assign),
		func
	);
}

void UsesExtractorVisitor::visitPrintNode(PrintNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const {
	this->pkbWriter->addUsesRelationship(
		std::make_shared<Statement>(node->getStatementNumber(), StatementType::Print),
		std::make_shared<Variable>(node->getVar()->getVarName())
	);
}

void UsesExtractorVisitor::visitIfNode(IfNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const {
	std::function<void(std::shared_ptr<Statement>, std::shared_ptr<Variable>)> func = [this](std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) -> void {
		this->pkbWriter->addUsesRelationship(s, v);
		};

	VisitorUtility::addAllStatementVariableRelationshipFrom(
		node->getConditionalExpression(),
		Statement(node->getStatementNumber(), StatementType::If),
		func
	);
}

void UsesExtractorVisitor::visitWhileNode(WhileNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const {
	std::function<void(std::shared_ptr<Statement>, std::shared_ptr<Variable>)> func = [this](std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) -> void {
		this->pkbWriter->addUsesRelationship(s, v);
		};

	VisitorUtility::addAllStatementVariableRelationshipFrom(
		node->getConditionalExpression(),
		Statement(node->getStatementNumber(), StatementType::While),
		func
	);
}