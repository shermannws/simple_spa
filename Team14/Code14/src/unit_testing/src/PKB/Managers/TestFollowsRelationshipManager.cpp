#include <memory>

#include "catch.hpp"
#include "PKB/Managers/FollowsRelationshipManager.h"
#include "PKB/Relationships/FollowsRelationship.h"

using namespace std;

TEST_CASE("Test Follows Relationship Retrieval") {
    FollowsRelationshipManager followsRelationshipManager = FollowsRelationshipManager();

    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Call));
    shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::Print));

    followsRelationshipManager.storeFollowsRelationship(statement1, statement2);
    followsRelationshipManager.storeFollowsRelationship(statement2, statement3);

    REQUIRE(followsRelationshipManager.getFollowsByStatement(*statement1).empty());
    auto followsStatement2 = followsRelationshipManager.getFollowsByStatement(*statement2);
    REQUIRE(followsStatement2.size() == 1);
    REQUIRE(followsStatement2.at(0) == *statement1);
    auto followsStatement3 = followsRelationshipManager.getFollowsByStatement(*statement3);
    REQUIRE(followsStatement3.size() == 1);
    REQUIRE(followsStatement3.at(0) == *statement2);

    auto followingStatement1 = followsRelationshipManager.getFollowingStatement(*statement1);
    REQUIRE(followingStatement1.size() == 1);
    REQUIRE(followingStatement1.at(0) == *statement2);
    auto followingStatement2 = followsRelationshipManager.getFollowingStatement(*statement2);
    REQUIRE(followingStatement2.size() == 1);
    REQUIRE(followingStatement2.at(0) == *statement3);
    REQUIRE(followsRelationshipManager.getFollowingStatement(*statement3).empty());

    REQUIRE(followsRelationshipManager.getIsFollows(*statement1, *statement2) == true);
    REQUIRE(followsRelationshipManager.getIsFollows(*statement2, *statement3) == true);
    REQUIRE(followsRelationshipManager.getIsFollows(*statement1, *statement3) == false);

    auto allFollowsStatementPair = followsRelationshipManager.getAllFollowsStatementPair();
    REQUIRE(allFollowsStatementPair.size() == 2);
}