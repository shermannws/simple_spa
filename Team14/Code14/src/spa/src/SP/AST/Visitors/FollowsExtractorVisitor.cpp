#include "FollowsExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"

FollowsExtractorVisitor::FollowsExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

// Helper method to translate from AST StatementNodeType into PKB StatementType
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
	case StatementNodeType::Call:
		return StatementType::Call;
		break;
	case StatementNodeType::While:
		return StatementType::While;
		break;
	case StatementNodeType::If:
		return StatementType::If;
		break;
	}
	//Should never reach here as all statements must be one of the above types
	throw std::runtime_error("Invalid StatementNodeType");
}

void FollowsExtractorVisitor::visitStatementListNode(StatementListNode* node) const {
	auto stmts = node->getStatements();

	// Add all pairwise statements that obeys Follow* relationship
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