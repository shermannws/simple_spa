#include "FollowsExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"

FollowsExtractorVisitor::FollowsExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

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
		return StatementType::Assign;// should never enter here
	}
}

void FollowsExtractorVisitor::visitStatementListNode(StatementListNode* node) const {
	auto stmts = node->getStatements();
	//
	//for (auto it = stmts.begin(); it != stmts.end(); it++) {
	//	if (it + 1 == stmts.end()) {
	//		break;
	//	}
	//	StatementType s1Type = getStamentTypeFromStatementNodeType((*it).get()->getStatementType());
	//	StatementType s2Type = getStamentTypeFromStatementNodeType((*(it+1)).get()->getStatementType());
	//	this->pkbWriter->addFollowsRelationship(
	//		std::make_shared<Statement>((*it).get()->getStatementNumber(), s1Type),
	//		std::make_shared<Statement>((*(it + 1)).get()->getStatementNumber(), s2Type)
	//	);
	//}

	//Below is for Follow(*)
	for (auto it = stmts.begin(); it != stmts.end(); it++) {
		bool isDirect = true;
		for (auto it2 = it+1; it2 != stmts.end(); it2++) {
			StatementType s1Type = getStamentTypeFromStatementNodeType((*it).get()->getStatementType());
			StatementType s2Type = getStamentTypeFromStatementNodeType((*it2).get()->getStatementType());
			this->pkbWriter->addFollowsRelationship(
				std::make_shared<Statement>((*it).get()->getStatementNumber(), s1Type),
				std::make_shared<Statement>((*it2).get()->getStatementNumber(), s2Type),
				isDirect
			);
			isDirect = false;
		}
	}
}