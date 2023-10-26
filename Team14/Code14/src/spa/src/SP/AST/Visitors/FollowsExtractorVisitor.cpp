#include "FollowsExtractorVisitor.h"
#include "Commons/Entities/Statement.h"
#include "Commons/EntityFactory.h"

FollowsExtractorVisitor::FollowsExtractorVisitor(std::shared_ptr<PkbWriter> writer) { this->pkbWriter = writer; }

void FollowsExtractorVisitor::visitStatementListNode(const std::shared_ptr<StatementListNode> &node,
                                                     std::vector<std::shared_ptr<Statement>> parents,
                                                     std::shared_ptr<Procedure> proc) const {
    auto stmts = node->getStatements();

    // Add all pairwise statements that obeys Follow* relationship
    for (auto it = stmts.begin(); it != stmts.end(); it++) {
        bool isDirect = true;
        for (auto it2 = it + 1; it2 != stmts.end(); it2++) {
            auto s1 = *it;
            auto s2 = *it2;
            this->pkbWriter->addFollowsRelationship(EntityFactory::createStatementFromStatementNode(s1),
                                                    EntityFactory::createStatementFromStatementNode(s2), isDirect);
            isDirect = false;
        }
    }
}