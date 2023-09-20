#include "ParentExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/StatementTypeFactory.h"

ParentExtractorVisitor::ParentExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

void ParentExtractorVisitor::visitStatementListNode(StatementListNode* node, std::vector<std::shared_ptr<ASTNode>> parents) const {
	auto stmts = node->getStatements();

	bool isDirect = true;
	for (auto parent = stmts.rbegin(); parent != stmts.rend(); ++parent) {
		StatementNode* parentPtr = dynamic_cast<StatementNode*>(parent.get());
		assert(parentPtr != nullptr);
		Statement parentStatement = Statement(
			parentPtr->getStatementNumber(),
			StatementTypeFactory::getStatementTypeFrom(parentPtr->getStatementType())
		);
		
		for (auto stmt = stmts.begin(); stmt != stmts.end(); stmt++) {
			Statement childStatement = Statement(
				(*stmt)->getStatementNumber(),
				StatementTypeFactory::getStatementTypeFrom((*stmt)->getStatementType());
			);
			this->pkbWriter->addParentRelationship(
				std::make_shared<Statement>(parentStatement),
				std::make_shared<Statement>(childStatement),
				isDirect
			);
		}

		isDirect = false;
	}
}