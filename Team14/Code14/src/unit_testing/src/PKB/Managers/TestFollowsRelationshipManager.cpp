#include <memory>

#include "catch.hpp"
#include "PKB/Managers/FollowsRelationshipManager.h"
#include "PKB/Relationships/FollowsRelationship.h"

using namespace std;

TEST_CASE("Test Follows Relationship Retrieval") {
    FollowsRelationshipManager followsRelationshipManager = FollowsRelationshipManager();

    REQUIRE(followsRelationshipManager.hasFollows() == false);

    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Call));
    shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::Print));

    followsRelationshipManager.storeFollowsRelationship(statement1, statement2, true);
    followsRelationshipManager.storeFollowsRelationship(statement2, statement3, true);
    followsRelationshipManager.storeFollowsRelationship(statement1, statement3, false);

    REQUIRE(followsRelationshipManager.getFollowsPair(StatementType::Stmt, StatementType::Stmt, true).size() == 2);
    REQUIRE(followsRelationshipManager.getFollowsPair(StatementType::Stmt, StatementType::Stmt, false).size() == 3);
    REQUIRE(followsRelationshipManager.getFollowsPair(StatementType::Assign, StatementType::Call, true).size() == 1);
    REQUIRE(followsRelationshipManager.getFollowsPair(StatementType::Assign, StatementType::Print, false).size() == 1);
    REQUIRE(followsRelationshipManager.getFollowsPair(StatementType::Assign, StatementType::Print, true).empty());

    REQUIRE(followsRelationshipManager.getFollowsTypeStmt(StatementType::Stmt, *statement3, true).size() == 1);
    REQUIRE(followsRelationshipManager.getFollowsTypeStmt(StatementType::Stmt, *statement3, false).size() == 2);
    REQUIRE(followsRelationshipManager.getFollowsTypeStmt(StatementType::Assign, *statement3, false).size() == 1);
    REQUIRE(followsRelationshipManager.getFollowsTypeStmt(StatementType::Assign, *statement3, true).empty());

    REQUIRE(followsRelationshipManager.getFollowsWildcardType(StatementType::Stmt).size() == 2);
    REQUIRE(followsRelationshipManager.getFollowsWildcardType(StatementType::Assign).empty());
    REQUIRE(followsRelationshipManager.getFollowsWildcardType(StatementType::Print).size() == 1);
    REQUIRE(followsRelationshipManager.getFollowsWildcardType(StatementType::Call).size() == 1);

    REQUIRE(followsRelationshipManager.getFollowsStmtType(*statement1, StatementType::Stmt, true).size() == 1);
    REQUIRE(followsRelationshipManager.getFollowsStmtType(*statement1, StatementType::Stmt, false).size() == 2);
    REQUIRE(followsRelationshipManager.getFollowsStmtType(*statement1, StatementType::Print, true).empty());
    REQUIRE(followsRelationshipManager.getFollowsStmtType(*statement1, StatementType::Print, false).size() == 1);

    REQUIRE(followsRelationshipManager.getFollowsTypeWildcard(StatementType::Stmt).size() == 2);
    REQUIRE(followsRelationshipManager.getFollowsTypeWildcard(StatementType::Assign).size() == 1);
    REQUIRE(followsRelationshipManager.getFollowsTypeWildcard(StatementType::Print).empty());
    REQUIRE(followsRelationshipManager.getFollowsTypeWildcard(StatementType::Call).size() == 1);

    REQUIRE(followsRelationshipManager.isFollows(*statement1, *statement2, true) == true);
    REQUIRE(followsRelationshipManager.isFollows(*statement1, *statement2, false) == true);
    REQUIRE(followsRelationshipManager.isFollows(*statement1, *statement3, true) == false);
    REQUIRE(followsRelationshipManager.isFollows(*statement1, *statement3, false) == true);

    REQUIRE(followsRelationshipManager.hasFollows() == true);
}