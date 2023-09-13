#pragma once

#include <memory>
#include <vector>

#include "PKB/RelationshipStorage/FollowsRelationshipStore.h"
#include "Commons/Entities/Statement.h"
#include "PKB/Relationships/FollowsRelationship.h"

class FollowsRelationshipManager {
private:
    std::shared_ptr<FollowsRelationshipStore> followsRelationshipStore;
public:
    FollowsRelationshipManager();

    void storeFollowsRelationship(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2);

    std::vector<std::vector<Entity>> getAllFollowsStatementPair() const;

    std::vector<Entity> getFollowsByStatement(Statement& statement) const; // Returns statement followed by (ahead) given statement

    std::vector<Entity> getFollowingStatement(Statement& statement) const; // Returns statement following (behind) given statement

    bool getIsFollows(Statement& statement1, Statement& statement2) const; // Returns true if statement1 follows statement2


};
