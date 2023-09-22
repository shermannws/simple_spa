#pragma once

#include <memory>
#include <vector>

#include "PKB/RelationshipStores/ParentRelationshipStore.h"
#include "Commons/Entities/Statement.h"
#include "PKB/Relationships/ParentRelationship.h"
#include "PKB/Managers/StmtToStmtRelationshipManager.h"

class ParentRelationshipManager : public StmtToStmtRelationshipManager<ParentRelationshipStore, ParentRelationship> {
public:
    ParentRelationshipManager();

    void storeParentRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2, bool isDirect);

    std::vector<std::vector<Entity>> getParentPair(StatementType formerType, StatementType latterType, bool requireDirect) const;

    std::vector<Entity> getParentTypeStmt(StatementType type, Statement& statement, bool requireDirect) const;

    std::vector<Entity> getParentTypeWildcard(StatementType type) const;

    std::vector<Entity> getParentStmtType(Statement& statement, StatementType type, bool requireDirect) const;

    std::vector<Entity> getParentWildcardType(StatementType type) const;

    bool isParent(Statement& statement1, Statement& statement2, bool requireDirect) const;

    bool hasParent() const;

    bool hasParentStmt(Statement& statement) const;

    bool hasParentStarStmt(Statement& statement) const;

    bool hasChildStmt(Statement& statement) const;

    bool hasChildStarStmt(Statement& statement) const;
};
