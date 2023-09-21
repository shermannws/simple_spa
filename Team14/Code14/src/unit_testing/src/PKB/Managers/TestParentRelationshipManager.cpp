#include <memory>

#include "catch.hpp"
#include "PKB/Managers/ParentRelationshipManager.h"
#include "PKB/Relationships/ParentRelationship.h"

using namespace std;

TEST_CASE("Test Parent Relationship Retrieval") {
    ParentRelationshipManager parentRelationshipManager = ParentRelationshipManager();

    REQUIRE(parentRelationshipManager.hasParent() == false);

    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::If));
    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::While));
    shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::Assign));

    parentRelationshipManager.storeParentRelationship(statement1, statement2, true);
    parentRelationshipManager.storeParentRelationship(statement2, statement3, true);
    parentRelationshipManager.storeParentRelationship(statement1, statement3, false);

    REQUIRE(parentRelationshipManager.getParentPair(StatementType::Stmt, StatementType::Stmt, true).size() == 2);
    REQUIRE(parentRelationshipManager.getParentPair(StatementType::Stmt, StatementType::Stmt, false).size() == 3);
    REQUIRE(parentRelationshipManager.getParentPair(StatementType::While, StatementType::Assign, true).size() == 1);
    REQUIRE(parentRelationshipManager.getParentPair(StatementType::If, StatementType::Assign, false).size() == 1);
    REQUIRE(parentRelationshipManager.getParentPair(StatementType::If, StatementType::Assign, true).empty());

    REQUIRE(parentRelationshipManager.getParentTypeStmt(StatementType::Stmt, *statement3, true).size() == 1);
    REQUIRE(parentRelationshipManager.getParentTypeStmt(StatementType::Stmt, *statement3, false).size() == 2);
    REQUIRE(parentRelationshipManager.getParentTypeStmt(StatementType::While, *statement3, false).size() == 1);
    REQUIRE(parentRelationshipManager.getParentTypeStmt(StatementType::If, *statement3, true).empty());

    REQUIRE(parentRelationshipManager.getParentWildcardType(StatementType::Stmt).size() == 2);
    REQUIRE(parentRelationshipManager.getParentWildcardType(StatementType::If).empty());
    REQUIRE(parentRelationshipManager.getParentWildcardType(StatementType::While).size() == 1);
    REQUIRE(parentRelationshipManager.getParentWildcardType(StatementType::Assign).size() == 1);

    REQUIRE(parentRelationshipManager.getParentStmtType(*statement1, StatementType::Stmt, true).size() == 1);
    REQUIRE(parentRelationshipManager.getParentStmtType(*statement1, StatementType::Stmt, false).size() == 2);
    REQUIRE(parentRelationshipManager.getParentStmtType(*statement1, StatementType::Assign, true).empty());
    REQUIRE(parentRelationshipManager.getParentStmtType(*statement1, StatementType::Assign, false).size() == 1);

    REQUIRE(parentRelationshipManager.getParentTypeWildcard(StatementType::Stmt).size() == 2);
    REQUIRE(parentRelationshipManager.getParentTypeWildcard(StatementType::If).size() == 1);
    REQUIRE(parentRelationshipManager.getParentTypeWildcard(StatementType::Assign).empty());
    REQUIRE(parentRelationshipManager.getParentTypeWildcard(StatementType::While).size() == 1);

    REQUIRE(parentRelationshipManager.isParent(*statement1, *statement2, true) == true);
    REQUIRE(parentRelationshipManager.isParent(*statement1, *statement2, false) == true);
    REQUIRE(parentRelationshipManager.isParent(*statement1, *statement3, true) == false);
    REQUIRE(parentRelationshipManager.isParent(*statement1, *statement3, false) == true);

    REQUIRE(parentRelationshipManager.hasParent() == true);
}