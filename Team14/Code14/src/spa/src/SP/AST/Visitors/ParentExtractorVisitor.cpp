#include "ParentExtractorVisitor.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/StatementTypeFactory.h"
#include "Commons/StatementFactory.h"

ParentExtractorVisitor::ParentExtractorVisitor(std::shared_ptr<PkbWriter> writer) { this->pkbWriter = writer; }

void ParentExtractorVisitor::visitStatementListNode(StatementListNode *node,
                                                    std::vector<std::shared_ptr<ASTNode>> parents,
                                                    std::shared_ptr<ASTNode> proc) const {
    auto stmts = node->getStatements();

    bool isDirect = true;
    for (auto parent = parents.rbegin(); parent != parents.rend(); parent++) {
        auto parentPtr = std::static_pointer_cast<StatementNode>(*parent);
        assert(parentPtr != nullptr);
        std::shared_ptr<Statement> parentStatement = StatementFactory::createStatementFromStatementNode(parentPtr);

        for (auto stmt = stmts.begin(); stmt != stmts.end(); stmt++) {
            std::shared_ptr<Statement> childStatement = StatementFactory::createStatementFromStatementNode(*stmt);
            this->pkbWriter->addParentRelationship(parentStatement, childStatement, isDirect);
        }

        isDirect = false;
    }
}