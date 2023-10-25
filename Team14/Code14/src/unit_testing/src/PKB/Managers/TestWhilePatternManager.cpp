#include "PKB/Managers/WhilePatternManager.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test While Pattern Storage Initialisation") {
    WhilePatternManager whilePatternManager = WhilePatternManager();
    Variable var = Variable("x");

    REQUIRE(whilePatternManager.getAllStmts().empty());
    REQUIRE(whilePatternManager.getStmtsByVar(var).empty());
    REQUIRE(whilePatternManager.getAllStmtVarPair().empty());
}

TEST_CASE("Test While Pattern Storage") {
    WhilePatternManager whilePatternManager = WhilePatternManager();
    Statement whileStmt = Statement(1, StatementType::While);
    Variable var = Variable("x");

    REQUIRE_NOTHROW(whilePatternManager.storeWhilePattern(
            make_shared<Statement>(whileStmt),
            make_shared<vector<shared_ptr<Variable>>>(vector<shared_ptr<Variable>>{make_shared<Variable>(var)})));
}

TEST_CASE("Test While Pattern Retrieval") {
    WhilePatternManager whilePatternManager = WhilePatternManager();
    shared_ptr<Statement> whileStmt1 = make_shared<Statement>(Statement(1, StatementType::While));
    shared_ptr<Statement> whileStmt2 = make_shared<Statement>(Statement(2, StatementType::While));
    shared_ptr<Statement> whileStmt3 = make_shared<Statement>(Statement(3, StatementType::While));

    shared_ptr<Variable> varX = make_shared<Variable>(Variable("x"));
    shared_ptr<Variable> varY = make_shared<Variable>(Variable("y"));
    shared_ptr<Variable> varZ = make_shared<Variable>(Variable("z"));

    shared_ptr<vector<shared_ptr<Variable>>> vars1 =
            make_shared<vector<shared_ptr<Variable>>>(vector<shared_ptr<Variable>>{varX, varY, varZ});
    shared_ptr<vector<shared_ptr<Variable>>> vars2 =
            make_shared<vector<shared_ptr<Variable>>>(vector<shared_ptr<Variable>>{varX, varY});
    shared_ptr<vector<shared_ptr<Variable>>> vars3 =
            make_shared<vector<shared_ptr<Variable>>>(vector<shared_ptr<Variable>>{varZ});

    whilePatternManager.storeWhilePattern(whileStmt1, vars1);
    whilePatternManager.storeWhilePattern(whileStmt2, vars2);
    whilePatternManager.storeWhilePattern(whileStmt3, vars3);

    Statement testStmt1 = Statement(1, StatementType::While);
    Statement testStmt2 = Statement(2, StatementType::While);
    Statement testStmt3 = Statement(3, StatementType::While);
    Variable testX = Variable("x");
    Variable testY = Variable("y");
    Variable testZ = Variable("z");

    unordered_set<Entity> getStmtByVar = whilePatternManager.getAllStmts();
    REQUIRE(getStmtByVar.size() == 3);
    REQUIRE(find(getStmtByVar.begin(), getStmtByVar.end(), testStmt1) != getStmtByVar.end());
    REQUIRE(find(getStmtByVar.begin(), getStmtByVar.end(), testStmt2) != getStmtByVar.end());
    REQUIRE(find(getStmtByVar.begin(), getStmtByVar.end(), testStmt3) != getStmtByVar.end());

    REQUIRE(whilePatternManager.getAllStmtVarPair().size() == 6);

    unordered_set<Entity> getStmtsByVarX = whilePatternManager.getStmtsByVar(testX);
    REQUIRE(getStmtsByVarX.size() == 2);
    REQUIRE(find(getStmtsByVarX.begin(), getStmtsByVarX.end(), testStmt1) != getStmtsByVarX.end());
    REQUIRE(find(getStmtsByVarX.begin(), getStmtsByVarX.end(), testStmt2) != getStmtsByVarX.end());

    unordered_set<Entity> getStmtsByVarY = whilePatternManager.getStmtsByVar(testY);
    REQUIRE(getStmtsByVarY.size() == 2);
    REQUIRE(find(getStmtsByVarY.begin(), getStmtsByVarY.end(), testStmt1) != getStmtsByVarY.end());
    REQUIRE(find(getStmtsByVarY.begin(), getStmtsByVarY.end(), testStmt2) != getStmtsByVarY.end());

    unordered_set<Entity> getStmtsByVarZ = whilePatternManager.getStmtsByVar(testZ);
    REQUIRE(getStmtsByVarZ.size() == 2);
    REQUIRE(find(getStmtsByVarZ.begin(), getStmtsByVarZ.end(), testStmt1) != getStmtsByVarZ.end());
    REQUIRE(find(getStmtsByVarZ.begin(), getStmtsByVarZ.end(), testStmt3) != getStmtsByVarZ.end());
}