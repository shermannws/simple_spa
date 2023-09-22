#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "PKB/RelationshipStores/FollowsRelationshipStore.h"
#include "Commons/Entities/Statement.h"
#include "PKB/Relationships/FollowsRelationship.h"
#include "PKB/Managers/StmtToStmtRelationshipManager.h"

class FollowsRelationshipManager : StmtToStmtRelationshipManager<FollowsRelationshipStore, FollowsRelationship> {
public:
    FollowsRelationshipManager();

    void storeFollowsRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2, bool isDirect);

    std::vector<std::vector<Entity>> getFollowsPair(StatementType formerType, StatementType latterType, bool requireDirect) const;

    std::vector<Entity> getFollowsTypeStmt(StatementType type, Statement& statement, bool requireDirect) const;

    std::vector<Entity> getFollowsTypeWildcard(StatementType type) const;

    std::vector<Entity> getFollowsStmtType(Statement& statement, StatementType type, bool requireDirect) const;

    std::vector<Entity> getFollowsWildcardType(StatementType type) const;

    bool isFollows(Statement& statement1, Statement& statement2, bool requireDirect) const;

    bool hasFollows() const;

    bool hasFollowingStmt(Statement& statement) const;

    bool hasFollowedStmt(Statement& statement) const;

    bool hasFollowingStarStmt(Statement& statement) const;

    bool hasFollowedStarStmt(Statement& statement) const;
};
