#include "UsesExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Variable.h"
#include "VisitorUtility.h"

UsesExtractorVisitor::UsesExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
	this->funcStmt =
		[this](std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) -> void {
		this->pkbWriter->addUsesRelationship(s, v);
		};
	this->funcProc =
		[this](std::shared_ptr<Procedure> p, std::shared_ptr<Variable> v) -> void {
		this->pkbWriter->addUsesProcRelationship(p, v);
		};
}

void UsesExtractorVisitor::visitAssignNode(AssignNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	return VisitorUtility::addAllVariableRelationshipFrom(
		node->getExpression(),
		Statement(node->getStatementNumber(), StatementType::Assign),
		parents,
		this->funcStmt,
		proc,
		this->funcProc
	);
}

void UsesExtractorVisitor::visitPrintNode(PrintNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	return VisitorUtility::addAllVariableRelationshipFrom(
		node->getVar(),
		Statement(node->getStatementNumber(), StatementType::Print),
		parents,
		this->funcStmt,
		proc,
		this->funcProc
	);
}

void UsesExtractorVisitor::visitIfNode(IfNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	return VisitorUtility::addAllVariableRelationshipFrom(
		node->getConditionalExpression(),
		Statement(node->getStatementNumber(), StatementType::If),
		parents,
		this->funcStmt,
		proc,
		this->funcProc
	);
}

void UsesExtractorVisitor::visitWhileNode(WhileNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	return VisitorUtility::addAllVariableRelationshipFrom(
		node->getConditionalExpression(),
		Statement(node->getStatementNumber(), StatementType::While),
		parents,
		this->funcStmt,
		proc,
		this->funcProc
	);
}