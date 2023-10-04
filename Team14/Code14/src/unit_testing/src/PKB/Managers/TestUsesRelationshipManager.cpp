#include <memory>

#include "catch.hpp"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "PKB/AssignmentPatternStore/Assignment.h"

using namespace std;

TEST_CASE("Test Uses Relationship Retrieval") {
    UsesRelationshipManager usesRelationshipManager = UsesRelationshipManager();

    // Test x = y + z
    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Variable> variableX = make_shared<Variable>(Variable("x"));
    shared_ptr<Variable> variableY = make_shared<Variable>(Variable("y"));
    shared_ptr<Variable> variableZ = make_shared<Variable>(Variable("z"));

    usesRelationshipManager.storeUsesRelationship(statement1, variableY);
    usesRelationshipManager.storeUsesRelationship(statement1, variableZ);

    // Test a = x + y + a
    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Assign));
    shared_ptr<Variable> variableA = make_shared<Variable>(Variable("a"));
    shared_ptr<Variable> variableC = make_shared<Variable>(Variable("c"));

    usesRelationshipManager.storeUsesRelationship(statement2, variableA);
    usesRelationshipManager.storeUsesRelationship(statement2, variableX);
    usesRelationshipManager.storeUsesRelationship(statement2, variableY);

    // Print "test"
    shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::Print));
    shared_ptr<Variable> variableTest = make_shared<Variable>(Variable("test"));

    usesRelationshipManager.storeUsesRelationship(statement3, variableTest);

    REQUIRE(usesRelationshipManager.getUsesStmtPair(StatementType::Print).size() == 1);
    REQUIRE(usesRelationshipManager.getUsesStmtPair(StatementType::Assign).size() == 5);
    REQUIRE(usesRelationshipManager.getUsesStmtPair(StatementType::Stmt).size() == 6);

    REQUIRE(usesRelationshipManager.getUsesTypeIdent(StatementType::Print, *variableTest).size() == 1);
    REQUIRE(usesRelationshipManager.getUsesTypeIdent(StatementType::Assign, *variableX).size() == 1);
    REQUIRE(usesRelationshipManager.getUsesTypeIdent(StatementType::Assign, *variableY).size() == 2);
    REQUIRE(usesRelationshipManager.getUsesTypeIdent(StatementType::Assign, *variableA).size() == 1);

    REQUIRE(usesRelationshipManager.getUsesStmt(StatementType::Print).size() == 1);
    REQUIRE(usesRelationshipManager.getUsesStmt(StatementType::Assign).size() == 2);

    REQUIRE(usesRelationshipManager.getUsesVar(*statement1).size() == 2);
    REQUIRE(usesRelationshipManager.getUsesVar(*statement2).size() == 3);
    REQUIRE(usesRelationshipManager.getUsesVar(*statement3).size() == 1);

    REQUIRE(usesRelationshipManager.isStmtUsesVar(*statement1, *variableY) == true);
    REQUIRE(usesRelationshipManager.isStmtUsesVar(*statement1, *variableA) == false);

    REQUIRE(usesRelationshipManager.hasUses(*statement1) == true);
    REQUIRE(usesRelationshipManager.hasUses(*statement2) == true);
    REQUIRE(usesRelationshipManager.hasUses(*statement3) == true);
}