#include <memory>

#include "catch.hpp"
#include "PKB/Managers/AssignmentManager.h"
#include "PKB/AssignmentPatternStore/Assignment.h"
#include "Commons/Entities/WildCard.h"

using namespace std;

TEST_CASE("Test Assignment Retrieval") {
    AssignmentManager assignmentManager = AssignmentManager();

    // Test a = w + (x + y) + z
    WildCard wildCard = WildCard();
    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Assign));
    shared_ptr<Variable> variableA = make_shared<Variable>(Variable("a"));
//    shared_ptr<Variable> variableW = make_shared<Variable>(Variable("w"));
//    shared_ptr<Variable> variableX = make_shared<Variable>(Variable("x"));
//    shared_ptr<Variable> variableY = make_shared<Variable>(Variable("y"));
//    shared_ptr<Variable> variableZ = make_shared<Variable>(Variable("z"));
    shared_ptr<string> expression1 = make_shared<string>("w+(x+y)+z");
    shared_ptr<string> expression2 = make_shared<string>("w+x+y+z");
    shared_ptr<Assignment> assignment1 = make_shared<Assignment>(Assignment(statement1, variableA, expression1));
    shared_ptr<Assignment> assignment2 = make_shared<Assignment>(Assignment(statement2, variableA, expression2));
    assignmentManager.addAssignment(assignment1);
    assignmentManager.addAssignment(assignment2);

    string empty;
    string query = "(x+y)";
    vector<Entity> assignLhsRhsWc = assignmentManager.getAssignStmtsByLhsRhs(*variableA, query, true); // pattern ("a", "_(x+y)_")
    REQUIRE(assignLhsRhsWc.size() == 1);
    REQUIRE(assignLhsRhsWc.at(0) == *statement1);
    vector<Entity> assignLhsRhsNoWc = assignmentManager.getAssignStmtsByLhsRhs(*variableA, query, false); // pattern ("a", "(x+y)")
    REQUIRE(assignLhsRhsNoWc.empty());
    REQUIRE(assignmentManager.getAssignStmtsByLhs(*variableA).size() == 2); // pattern ("a", "_")
    vector<Entity> assignRhsWc = assignmentManager.getAssignStmtsByRhs(query, true); // pattern ("_", "_(x+y)_")
    REQUIRE(assignRhsWc.size() == 1);
    REQUIRE(assignRhsWc.at(0) == *statement1);
    REQUIRE(assignmentManager.getAssignStmtsByRhs(query, false).empty()); // pattern ("_", "(x+y)")
    REQUIRE(assignmentManager.getAllAssignStmts().size() == 2); // pattern ("_", "_")

    //TODO: More unit tests, especially for synonyms

}