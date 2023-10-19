#include "ParentExtractorVisitor.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/StatementFactory.h"
#include "Commons/StatementTypeFactory.h"

ParentExtractorVisitor::ParentExtractorVisitor(std::shared_ptr<PkbWriter> writer) { this->pkbWriter = writer; }

void ParentExtractorVisitor::visitStatementListNode(StatementListNode *node,
                                                    std::vector<std::shared_ptr<Statement>> parents,
                                                    std::shared_ptr<ASTNode> proc) const {
    auto stmts = node->getStatements();

    bool isDirect = true;
    for (auto parent = parents.rbegin(); parent != parents.rend(); parent++) {
        for (auto stmt = stmts.begin(); stmt != stmts.end(); stmt++) {
            std::shared_ptr<Statement> childStatement = StatementFactory::createStatementFromStatementNode(*stmt);
            this->pkbWriter->addParentRelationship(*parent, childStatement, isDirect);
        }

        isDirect = false;
    }
}