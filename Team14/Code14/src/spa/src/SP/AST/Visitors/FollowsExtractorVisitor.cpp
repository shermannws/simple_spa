#include "FollowsExtractorVisitor.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Statement.h"
#include "Commons/StatementTypeFactory.h"

FollowsExtractorVisitor::FollowsExtractorVisitor(std::shared_ptr<PkbWriter> writer) {
	this->pkbWriter = writer;
}

void FollowsExtractorVisitor::visitStatementListNode(StatementListNode* node, std::vector<std::shared_ptr<ASTNode>> parents, std::shared_ptr<ASTNode> proc) const {
	auto stmts = node->getStatements();

	// Add all pairwise statements that obeys Follow* relationship
	for (auto it = stmts.begin(); it != stmts.end(); it++) {
        bool isDirect = true;
		for (auto it2 = it+1; it2 != stmts.end(); it2++) {
			StatementType s1Type = StatementTypeFactory::getStatementTypeFrom((*it)->getStatementType());
			StatementType s2Type = StatementTypeFactory::getStatementTypeFrom((*it2)->getStatementType());
			this->pkbWriter->addFollowsRelationship(
				std::make_shared<Statement>((*it)->getStatementNumber(), s1Type),
				std::make_shared<Statement>((*it2)->getStatementNumber(), s2Type),
                isDirect
			);
            isDirect = false;
		}
	}
}