#include <memory>

#include "PKB/Commons/Assignment.h"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test Uses Relationship Retrieval") {
    UsesRelationshipManager usesRelationshipManager = UsesRelationshipManager();

    // Test x = y + z
    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Variable> variableX = make_shared<Variable>(Variable("x"));
    shared_ptr<Variable> variableY = make_shared<Variable>(Variable("y"));
    shared_ptr<Variable> variableZ = make_shared<Variable>(Variable("z"));

    usesRelationshipManager.storeRelationship(statement1, variableY);
    usesRelationshipManager.storeRelationship(statement1, variableZ);

    // Test a = x + y + a
    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Assign));
    shared_ptr<Variable> variableA = make_shared<Variable>(Variable("a"));
    shared_ptr<Variable> variableC = make_shared<Variable>(Variable("c"));

    usesRelationshipManager.storeRelationship(statement2, variableA);
    usesRelationshipManager.storeRelationship(statement2, variableX);
    usesRelationshipManager.storeRelationship(statement2, variableY);

    // Print "test"
    shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::Print));
    shared_ptr<Variable> variableTest = make_shared<Variable>(Variable("test"));

    usesRelationshipManager.storeRelationship(statement3, variableTest);

    REQUIRE(usesRelationshipManager.getRelationshipStmtPair(StatementType::Print).size() == 1);
    REQUIRE(usesRelationshipManager.getRelationshipStmtPair(StatementType::Assign).size() == 5);
    REQUIRE(usesRelationshipManager.getRelationshipStmtPair(StatementType::Stmt).size() == 6);

    REQUIRE(usesRelationshipManager.getRelationshipTypeIdent(StatementType::Print, *variableTest).size() == 1);
    REQUIRE(usesRelationshipManager.getRelationshipTypeIdent(StatementType::Assign, *variableX).size() == 1);
    REQUIRE(usesRelationshipManager.getRelationshipTypeIdent(StatementType::Assign, *variableY).size() == 2);
    REQUIRE(usesRelationshipManager.getRelationshipTypeIdent(StatementType::Assign, *variableA).size() == 1);

    REQUIRE(usesRelationshipManager.getRelationshipStmt(StatementType::Print).size() == 1);
    REQUIRE(usesRelationshipManager.getRelationshipStmt(StatementType::Assign).size() == 2);

    REQUIRE(usesRelationshipManager.getRelationshipVar(*statement1).size() == 2);
    REQUIRE(usesRelationshipManager.getRelationshipVar(*statement2).size() == 3);
    REQUIRE(usesRelationshipManager.getRelationshipVar(*statement3).size() == 1);

    REQUIRE(usesRelationshipManager.isRelationship(*statement1, *variableY) == true);
    REQUIRE(usesRelationshipManager.isRelationship(*statement1, *variableA) == false);

    REQUIRE(usesRelationshipManager.hasRelationship(*statement1) == true);
    REQUIRE(usesRelationshipManager.hasRelationship(*statement2) == true);
    REQUIRE(usesRelationshipManager.hasRelationship(*statement3) == true);
}