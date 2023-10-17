#include <memory>

#include "PKB/Commons/Assignment.h"
#include "PKB/Managers/ModifiesRelationshipManager.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test Modifies Relationship Retrieval") {
    ModifiesRelationshipManager modifiesRelationshipManager =
            ModifiesRelationshipManager();

    shared_ptr<Variable> variableX = make_shared<Variable>(Variable("x"));
    shared_ptr<Variable> variableY = make_shared<Variable>(Variable("y"));
    shared_ptr<Variable> variableZ = make_shared<Variable>(Variable("z"));

    shared_ptr<Statement> statement1 =
            make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Statement> statement2 =
            make_shared<Statement>(Statement(2, StatementType::Read));
    shared_ptr<Statement> statement3 =
            make_shared<Statement>(Statement(3, StatementType::Assign));
    shared_ptr<Statement> statement4 =
            make_shared<Statement>(Statement(4, StatementType::Assign));

    modifiesRelationshipManager.storeRelationship(statement1, variableX);
    modifiesRelationshipManager.storeRelationship(statement2, variableX);
    modifiesRelationshipManager.storeRelationship(statement3, variableX);
    modifiesRelationshipManager.storeRelationship(statement3, variableY);

    REQUIRE(modifiesRelationshipManager
                    .getRelationshipStmtPair(StatementType::Assign)
                    .size() == 3);
    REQUIRE(modifiesRelationshipManager
                    .getRelationshipStmtPair(StatementType::Read)
                    .size() == 1);

    REQUIRE(modifiesRelationshipManager
                    .getRelationshipTypeIdent(StatementType::Assign, *variableX)
                    .size() == 2);
    REQUIRE(modifiesRelationshipManager
                    .getRelationshipTypeIdent(StatementType::Assign, *variableY)
                    .size() == 1);
    REQUIRE(modifiesRelationshipManager
                    .getRelationshipTypeIdent(StatementType::Read, *variableX)
                    .size() == 1);

    REQUIRE(modifiesRelationshipManager.getRelationshipStmt(StatementType::Stmt)
                    .size() == 3);
    REQUIRE(modifiesRelationshipManager
                    .getRelationshipStmt(StatementType::Assign)
                    .size() == 2);
    REQUIRE(modifiesRelationshipManager.getRelationshipStmt(StatementType::Read)
                    .size() == 1);

    REQUIRE(modifiesRelationshipManager.getRelationshipVar(*statement1)
                    .size() == 1);
    REQUIRE(modifiesRelationshipManager.getRelationshipVar(*statement2)
                    .size() == 1);
    REQUIRE(modifiesRelationshipManager.getRelationshipVar(*statement3)
                    .size() == 2);

    REQUIRE(modifiesRelationshipManager.isRelationship(*statement1,
                                                       *variableX) == true);
    REQUIRE(modifiesRelationshipManager.isRelationship(*statement1,
                                                       *variableY) == false);

    REQUIRE(modifiesRelationshipManager.hasRelationship(*statement1) == true);
    REQUIRE(modifiesRelationshipManager.hasRelationship(*statement4) == false);
}