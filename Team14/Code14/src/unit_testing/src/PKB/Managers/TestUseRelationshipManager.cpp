#include <memory>

#include "catch.hpp"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "PKB/AssignmentPatternStore/Assignment.h"
#include "PKB/Relationships/UsesRelationship.h"

using namespace std;

TEST_CASE("Test Uses Relationship Retrieval") {
    shared_ptr<UsesRelationshipStore> usesRelationshipStore =  make_shared<UsesRelationshipStore>(UsesRelationshipStore());

    shared_ptr<UsesRelationshipManager> usesRelationshipManager = make_shared<UsesRelationshipManager>(UsesRelationshipManager(usesRelationshipStore));

    // Test x = y + z
    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Variable> variableX = make_shared<Variable>(Variable("x"));
    shared_ptr<Variable> variableY = make_shared<Variable>(Variable("y"));
    shared_ptr<Variable> variableZ = make_shared<Variable>(Variable("z"));

    usesRelationshipStore->storeRelationship(make_shared<UsesRelationship>(UsesRelationship(statement1, variableY)));
    usesRelationshipStore->storeRelationship(make_shared<UsesRelationship>(UsesRelationship(statement1, variableZ)));

    // Test a = b + c
    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Assign));
    shared_ptr<Variable> variableA = make_shared<Variable>(Variable("a"));
    shared_ptr<Variable> variableB = make_shared<Variable>(Variable("b"));
    shared_ptr<Variable> variableC = make_shared<Variable>(Variable("c"));

    usesRelationshipStore->storeRelationship(make_shared<UsesRelationship>(UsesRelationship(statement2, variableB)));
    usesRelationshipStore->storeRelationship(make_shared<UsesRelationship>(UsesRelationship(statement2, variableC)));

    // Results
    auto pairY = make_shared<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>>(make_pair(statement1, variableY));
    auto pairZ = make_shared<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>>(make_pair(statement1, variableZ));
    auto pairB = make_shared<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>>(make_pair(statement2, variableB));
    auto pairC = make_shared<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>>(make_pair(statement2, variableC));

    auto allAssignmentVariables = usesRelationshipManager->getAllAssignVariable();
    REQUIRE(allAssignmentVariables->size() == 4);
//    REQUIRE(find(allAssignmentVariables->begin(), allAssignmentVariables->end(), pairY) != allAssignmentVariables->end());
//    REQUIRE(find(allAssignmentVariables->begin(), allAssignmentVariables->end(), pairZ) != allAssignmentVariables->end());
//    REQUIRE(find(allAssignmentVariables->begin(), allAssignmentVariables->end(), pairB) != allAssignmentVariables->end());
//    REQUIRE(find(allAssignmentVariables->begin(), allAssignmentVariables->end(), pairC) != allAssignmentVariables->end());

    auto statement1Variables = usesRelationshipManager->getVariableAssignment(variableB);
    REQUIRE(statement1Variables->size() == 1);
    REQUIRE(statement1Variables->at(0)->first == statement2);
    REQUIRE(statement1Variables->at(0)->second == variableB);
}