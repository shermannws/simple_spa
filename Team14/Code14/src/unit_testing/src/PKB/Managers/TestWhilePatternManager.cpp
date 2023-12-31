#include "../../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "PKB/Managers/WhilePatternManager.h"
#include "catch.hpp"

using namespace std;

TEST_CASE_METHOD(UnitTestFixture, "Test While Pattern Storage Initialisation") {
    WhilePatternManager whilePatternManager = WhilePatternManager();
    Variable var = Variable("x");

    REQUIRE(whilePatternManager.getAllStmts().empty());
    REQUIRE(whilePatternManager.getStmtsByVar(var).empty());
    REQUIRE(whilePatternManager.getAllStmtVarPair().empty());
}

TEST_CASE_METHOD(UnitTestFixture, "Test While Pattern Storage") {
    WhilePatternManager whilePatternManager = WhilePatternManager();
    Statement whileStmt = Statement(1, StatementType::While);
    Variable var = Variable("x");

    REQUIRE_NOTHROW(whilePatternManager.storeWhilePattern(
            make_shared<Statement>(whileStmt),
            make_shared<vector<shared_ptr<Variable>>>(vector<shared_ptr<Variable>>{make_shared<Variable>(var)})));
}

TEST_CASE_METHOD(UnitTestFixture, "Test While Pattern Retrieval") {
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

    shared_ptr<Statement> testStmt1 = make_shared<Statement>(1, StatementType::While);
    shared_ptr<Statement> testStmt2 = make_shared<Statement>(2, StatementType::While);
    shared_ptr<Statement> testStmt3 = make_shared<Statement>(3, StatementType::While);
    Variable testX = Variable("x");
    Variable testY = Variable("y");
    Variable testZ = Variable("z");

    EntitySet getStmtByVar = whilePatternManager.getAllStmts();
    REQUIRE(getStmtByVar.size() == 3);
    REQUIRE(getStmtByVar.find(testStmt1) != getStmtByVar.end());
    REQUIRE(getStmtByVar.find(testStmt2) != getStmtByVar.end());
    REQUIRE(getStmtByVar.find(testStmt3) != getStmtByVar.end());

    REQUIRE(whilePatternManager.getAllStmtVarPair().size() == 6);

    EntitySet getStmtsByVarX = whilePatternManager.getStmtsByVar(testX);
    REQUIRE(getStmtsByVarX.size() == 2);
    REQUIRE(getStmtsByVarX.find(testStmt1) != getStmtsByVarX.end());
    REQUIRE(getStmtsByVarX.find(testStmt2) != getStmtsByVarX.end());

    EntitySet getStmtsByVarY = whilePatternManager.getStmtsByVar(testY);
    REQUIRE(getStmtsByVarY.size() == 2);
    REQUIRE(getStmtsByVarY.find(testStmt1) != getStmtsByVarY.end());
    REQUIRE(getStmtsByVarY.find(testStmt2) != getStmtsByVarY.end());

    EntitySet getStmtsByVarZ = whilePatternManager.getStmtsByVar(testZ);
    REQUIRE(getStmtsByVarZ.size() == 2);
    REQUIRE(getStmtsByVarZ.find(testStmt1) != getStmtsByVarZ.end());
    REQUIRE(getStmtsByVarZ.find(testStmt3) != getStmtsByVarZ.end());
}