#include <memory>

#include "catch.hpp"
#include "PKB/Managers/ParentRelationshipManager.h"

using namespace std;

TEST_CASE("Test Parent Relationship Retrieval") {
    ParentRelationshipManager parentRelationshipManager = ParentRelationshipManager();

    REQUIRE(parentRelationshipManager.hasRelationship() == false);

    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::If));
    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::While));
    shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::Assign));

    parentRelationshipManager.storeRelationship(statement1, statement2, true);
    parentRelationshipManager.storeRelationship(statement2, statement3, true);
    parentRelationshipManager.storeRelationship(statement1, statement3, false);

    REQUIRE(parentRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Stmt, true).size() == 2);
    REQUIRE(parentRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Stmt, false).size() == 3);
    REQUIRE(parentRelationshipManager.getRelationshipPair(StatementType::While, StatementType::Assign, true).size() == 1);
    REQUIRE(parentRelationshipManager.getRelationshipPair(StatementType::If, StatementType::Assign, false).size() == 1);
    REQUIRE(parentRelationshipManager.getRelationshipPair(StatementType::If, StatementType::Assign, true).empty());

    REQUIRE(parentRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement3, true).size() == 1);
    REQUIRE(parentRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement3, false).size() == 2);
    REQUIRE(parentRelationshipManager.getRelationshipTypeStmt(StatementType::While, *statement3, false).size() == 1);
    REQUIRE(parentRelationshipManager.getRelationshipTypeStmt(StatementType::If, *statement3, true).empty());

    REQUIRE(parentRelationshipManager.getRelationshipWildcardType(StatementType::Stmt).size() == 2);
    REQUIRE(parentRelationshipManager.getRelationshipWildcardType(StatementType::If).empty());
    REQUIRE(parentRelationshipManager.getRelationshipWildcardType(StatementType::While).size() == 1);
    REQUIRE(parentRelationshipManager.getRelationshipWildcardType(StatementType::Assign).size() == 1);

    REQUIRE(parentRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Stmt, true).size() == 1);
    REQUIRE(parentRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Stmt, false).size() == 2);
    REQUIRE(parentRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Assign, true).empty());
    REQUIRE(parentRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Assign, false).size() == 1);

    REQUIRE(parentRelationshipManager.getRelationshipTypeWildcard(StatementType::Stmt).size() == 2);
    REQUIRE(parentRelationshipManager.getRelationshipTypeWildcard(StatementType::If).size() == 1);
    REQUIRE(parentRelationshipManager.getRelationshipTypeWildcard(StatementType::Assign).empty());
    REQUIRE(parentRelationshipManager.getRelationshipTypeWildcard(StatementType::While).size() == 1);

    REQUIRE(parentRelationshipManager.isRelationship(*statement1, *statement2, true) == true);
    REQUIRE(parentRelationshipManager.isRelationship(*statement1, *statement2, false) == true);
    REQUIRE(parentRelationshipManager.isRelationship(*statement1, *statement3, true) == false);
    REQUIRE(parentRelationshipManager.isRelationship(*statement1, *statement3, false) == true);

    REQUIRE(parentRelationshipManager.hasRelationship() == true);
}