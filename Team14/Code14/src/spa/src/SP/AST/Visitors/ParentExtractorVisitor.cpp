#include "ParentExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/StatementTypeFactory.h"

ParentExtractorVisitor::ParentExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

void ParentExtractorVisitor::visitStatementListNode(StatementListNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	auto stmts = node->getStatements();

	bool isDirect = true;
	for (auto parent = parents.rbegin(); parent != parents.rend(); parent++) {
		auto parentPtr = std::dynamic_pointer_cast<StatementNode>(*parent);
		assert(parentPtr != nullptr);
		Statement parentStatement = Statement(
			parentPtr->getStatementNumber(),
			StatementTypeFactory::getStatementTypeFrom(parentPtr->getStatementType())
		);
		
		for (auto stmt = stmts.begin(); stmt != stmts.end(); stmt++) {
			Statement childStatement = Statement(
				(*stmt)->getStatementNumber(),
				StatementTypeFactory::getStatementTypeFrom((*stmt)->getStatementType())
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