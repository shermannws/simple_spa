#include <memory>

#include "catch.hpp"
#include "PKB/Managers/FollowsRelationshipManager.h"

using namespace std;

TEST_CASE("Test Follows Relationship Retrieval") {
    FollowsRelationshipManager followsRelationshipManager = FollowsRelationshipManager();

    REQUIRE(followsRelationshipManager.hasRelationship() == false);

    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Call));
    shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::Print));

    followsRelationshipManager.storeRelationship(statement1, statement2, true);
    followsRelationshipManager.storeRelationship(statement2, statement3, true);
    followsRelationshipManager.storeRelationship(statement1, statement3, false);

    REQUIRE(followsRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Stmt, true).size() == 2);
    REQUIRE(followsRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Stmt, false).size() == 3);
    REQUIRE(followsRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Call, true).size() == 1);
    REQUIRE(followsRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Print, false).size() == 1);
    REQUIRE(followsRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Print, true).empty());

    REQUIRE(followsRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement3, true).size() == 1);
    REQUIRE(followsRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement3, false).size() == 2);
    REQUIRE(followsRelationshipManager.getRelationshipTypeStmt(StatementType::Assign, *statement3, false).size() == 1);
    REQUIRE(followsRelationshipManager.getRelationshipTypeStmt(StatementType::Assign, *statement3, true).empty());

    REQUIRE(followsRelationshipManager.getRelationshipWildcardType(StatementType::Stmt).size() == 2);
    REQUIRE(followsRelationshipManager.getRelationshipWildcardType(StatementType::Assign).empty());
    REQUIRE(followsRelationshipManager.getRelationshipWildcardType(StatementType::Print).size() == 1);
    REQUIRE(followsRelationshipManager.getRelationshipWildcardType(StatementType::Call).size() == 1);

    REQUIRE(followsRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Stmt, true).size() == 1);
    REQUIRE(followsRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Stmt, false).size() == 2);
    REQUIRE(followsRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Print, true).empty());
    REQUIRE(followsRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Print, false).size() == 1);

    REQUIRE(followsRelationshipManager.getRelationshipTypeWildcard(StatementType::Stmt).size() == 2);
    REQUIRE(followsRelationshipManager.getRelationshipTypeWildcard(StatementType::Assign).size() == 1);
    REQUIRE(followsRelationshipManager.getRelationshipTypeWildcard(StatementType::Print).empty());
    REQUIRE(followsRelationshipManager.getRelationshipTypeWildcard(StatementType::Call).size() == 1);

    REQUIRE(followsRelationshipManager.isRelationship(*statement1, *statement2, true) == true);
    REQUIRE(followsRelationshipManager.isRelationship(*statement1, *statement2, false) == true);
    REQUIRE(followsRelationshipManager.isRelationship(*statement1, *statement3, true) == false);
    REQUIRE(followsRelationshipManager.isRelationship(*statement1, *statement3, false) == true);

    REQUIRE(followsRelationshipManager.hasRelationship() == true);
}