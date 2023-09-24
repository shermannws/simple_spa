#include <memory>

#include "catch.hpp"
#include "PKB/Managers/ModifiesRelationshipManager.h"
#include "PKB/AssignmentPatternStore/Assignment.h"
#include "PKB/Relationships/ModifiesRelationship.h"

using namespace std;

TEST_CASE("Test Modifies Relationship Retrieval") {
    ModifiesRelationshipManager modifiesRelationshipManager = ModifiesRelationshipManager();

    shared_ptr<Variable> variableX = make_shared<Variable>(Variable("x"));
    shared_ptr<Variable> variableY = make_shared<Variable>(Variable("y"));
    shared_ptr<Variable> variableZ = make_shared<Variable>(Variable("z"));

    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Read));
    shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::Assign));
    shared_ptr<Statement> statement4 = make_shared<Statement>(Statement(4, StatementType::Assign));

    modifiesRelationshipManager.storeModifiesRelationship(statement1, variableX);
    modifiesRelationshipManager.storeModifiesRelationship(statement2, variableX);
    modifiesRelationshipManager.storeModifiesRelationship(statement3, variableX);
    modifiesRelationshipManager.storeModifiesRelationship(statement3, variableY);

    REQUIRE(modifiesRelationshipManager.getModifiesStmtPair(StatementType::Assign).size() == 3);
    REQUIRE(modifiesRelationshipManager.getModifiesStmtPair(StatementType::Read).size() == 1);

    REQUIRE(modifiesRelationshipManager.getModifiesTypeIdent(StatementType::Assign, *variableX).size() == 2);
    REQUIRE(modifiesRelationshipManager.getModifiesTypeIdent(StatementType::Assign, *variableY).size() == 1);
    REQUIRE(modifiesRelationshipManager.getModifiesTypeIdent(StatementType::Read, *variableX).size() == 1);

    REQUIRE(modifiesRelationshipManager.getModifiesStmt(StatementType::Stmt).size() == 3);
    REQUIRE(modifiesRelationshipManager.getModifiesStmt(StatementType::Assign).size() == 2);
    REQUIRE(modifiesRelationshipManager.getModifiesStmt(StatementType::Read).size() == 1);

    REQUIRE(modifiesRelationshipManager.getModifiesVar(*statement1).size() == 1);
    REQUIRE(modifiesRelationshipManager.getModifiesVar(*statement2).size() == 1);
    REQUIRE(modifiesRelationshipManager.getModifiesVar(*statement3).size() == 2);

    REQUIRE(modifiesRelationshipManager.isStmtModifiesVar(*statement1, *variableX) == true);
    REQUIRE(modifiesRelationshipManager.isStmtModifiesVar(*statement1, *variableY) == false);

    REQUIRE(modifiesRelationshipManager.hasModifies(*statement1) == true);
    REQUIRE(modifiesRelationshipManager.hasModifies(*statement4) == false);
}