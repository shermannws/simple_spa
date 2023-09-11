#include <memory>

#include "catch.hpp"
#include "PKB/Managers/FollowsRelationshipManager.h"
#include "PKB/Relationships/FollowsRelationship.h"

using namespace std;

TEST_CASE("Test Follows Relationship Retrieval") {
    shared_ptr<FollowsRelationshipManager> followsRelationshipManager = make_shared<FollowsRelationshipManager>();

    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Call));
    shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::Print));

    followsRelationshipManager->storeFollowsRelationship(statement1, statement2);
    followsRelationshipManager->storeFollowsRelationship(statement2, statement3);

    REQUIRE(followsRelationshipManager->getFollowsByStatement(statement1) == nullptr);
    REQUIRE(followsRelationshipManager->getFollowsByStatement(statement2) == statement1);
    REQUIRE(followsRelationshipManager->getFollowsByStatement(statement3) == statement2);

    REQUIRE(followsRelationshipManager->getFollowingStatement(statement1) == statement2);
    REQUIRE(followsRelationshipManager->getFollowingStatement(statement2) == statement3);
    REQUIRE(followsRelationshipManager->getFollowingStatement(statement3) == nullptr);

    REQUIRE(followsRelationshipManager->getIsFollows(statement1, statement2) == true);
    REQUIRE(followsRelationshipManager->getIsFollows(statement2, statement3) == true);
    REQUIRE(followsRelationshipManager->getIsFollows(statement1, statement3) == false);

    auto allFollowsStatementPair = followsRelationshipManager->getAllFollowsStatementPair();
    REQUIRE(allFollowsStatementPair->size() == 2);
}