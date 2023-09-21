#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "PKB/RelationshipStores/FollowsRelationshipStore.h"
#include "PKB/Relationships/FollowsRelationship.h"
#include "PKB/Managers/ManagerUtils.h"

template <typename S, typename R>
class StmtToStmtRelationshipManager {
private:
    std::shared_ptr<S> relationshipStore;
public:
    StmtToStmtRelationshipManager();

    void storeRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2, bool isDirect);

    std::vector<std::vector<Entity>> getRelationshipPair(StatementType formerType, StatementType latterType, bool requireDirect) const;

    std::vector<Entity> getRelationshipTypeStmt(StatementType type, Statement& statement, bool requireDirect) const;

    std::vector<Entity> getRelationshipTypeWildcard(StatementType type) const;

    std::vector<Entity> getRelationshipStmtType(Statement& statement, StatementType type, bool requireDirect) const;

    std::vector<Entity> getRelationshipWildcardType(StatementType type) const;

    bool isRelationship(Statement& statement1, Statement& statement2, bool requireDirect) const;

    bool hasRelationship() const;
};

#include "StmtToStmtRelationshipManager.hpp"