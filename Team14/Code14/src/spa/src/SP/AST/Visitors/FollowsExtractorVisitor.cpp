#include "FollowsExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"

FollowsExtractorVisitor::FollowsExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

void FollowsExtractorVisitor::visitProgramNode(std::shared_ptr<ProgramNode> node) {}

void FollowsExtractorVisitor::visitProcedureNode(std::shared_ptr<ProcedureNode> node) {}

void FollowsExtractorVisitor::visitStatementListNode(std::shared_ptr<StatementListNode> node) {
	auto stmts = node->getStatements();
	for (auto it = stmts.begin(); it != stmts.end(); it++) {
		for (auto it2 = it+1; it2 != stmts.end(); it2++) {
			StatementType s1Type = getStamentTypeFromStatementNodeType((*it).get()->getStatementType());
			StatementType s2Type = getStamentTypeFromStatementNodeType((*it2).get()->getStatementType());
			this->pkbWriter->addFollowsRelationship(
				std::make_shared<Statement>((*it).get()->getStatementNumber(), s1Type),
				std::make_shared<Statement>((*it2).get()->getStatementNumber(), s2Type)
			);
		}
	}
}

void FollowsExtractorVisitor::visitAssignNode(std::shared_ptr<AssignNode> node) {}

void FollowsExtractorVisitor::visitReadNode(std::shared_ptr<ReadNode> node) {}

void FollowsExtractorVisitor::visitPrintNode(std::shared_ptr<PrintNode> node) {}

void FollowsExtractorVisitor::visitArithmeticExpressionNode(std::shared_ptr<ArithmeticExpressionNode> node) {}

void FollowsExtractorVisitor::visitVariableNode(std::shared_ptr<VariableNode> node) {}

void FollowsExtractorVisitor::visitConstantNode(std::shared_ptr<ConstantNode> node) {}


// Helper method to translate from AST StatementType into PKB StatementType
StatementType getStamentTypeFromStatementNodeType(StatementNodeType type) {
	switch (type) {
	case StatementNodeType::Assign:
		return StatementType::Assign;
		break;
	case StatementNodeType::Print:
		return StatementType::Print;
		break;
	case StatementNodeType::Read:
		return StatementType::Read;
		break;
	//TODO: handle all other statement types
	default:
		// should never enter here
	}
}