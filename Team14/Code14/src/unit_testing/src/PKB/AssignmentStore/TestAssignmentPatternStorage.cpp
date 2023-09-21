#include <memory>

#include "catch.hpp"
#include "PKB/Managers/AssignmentManager.h"
#include "PKB/AssignmentPatternStore/Assignment.h"
#include "Commons/Entities/WildCard.h"

using namespace std;

TEST_CASE("Test Assignment Pattern Storage and Retrieval") {
//    AssignmentManager manager = AssignmentManager();
//
//    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
//    shared_ptr<Variable> variable1 = make_shared<Variable>(Variable("x"));
//    shared_ptr<string> pattern1 = make_shared<string>("1");
//    shared_ptr<Assignment> assignment1 = make_shared<Assignment>(Assignment(statement1, variable1, pattern1));
//
//    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Assign));
//    shared_ptr<Variable> variable2 = make_shared<Variable>(Variable("y"));
//    shared_ptr<string> pattern2 = make_shared<string>("2");
//    shared_ptr<Assignment> assignment2 = make_shared<Assignment>(Assignment(statement2, variable2, pattern2));
//
//    manager.addAssignment(assignment1);
//    REQUIRE(1 == 1);
//    manager.addAssignment(assignment2);
//
//    vector<Entity> statements1 = manager.getAssignStatements(*variable1, "1");
//    REQUIRE(statements1.size() == 1);
//    REQUIRE(statements1.at(0) == *statement1);
//
//    vector<Entity> statements2 = manager.getAssignStatements(*variable2, "2");
//    REQUIRE(statements2.size() == 1);
//    REQUIRE(statements2.at(0) == *statement2);
//
//    WildCard variableWild = WildCard();
//    vector<Entity> statementsAll = manager.getAssignStatements(variableWild, "2");
//    REQUIRE(statementsAll.size() == 2);
//    REQUIRE(find(statementsAll.begin(), statementsAll.end(), *statement1) != statementsAll.end());
//    REQUIRE(find(statementsAll.begin(), statementsAll.end(), *statement2) != statementsAll.end());
}