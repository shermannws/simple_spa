#include "PKB/Managers/IfPatternManager.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test If Pattern Storage Initialisation") {
    IfPatternManager ifPatternManager = IfPatternManager();
    Variable var = Variable("x");

    REQUIRE(ifPatternManager.getAllStmts().empty());
    REQUIRE(ifPatternManager.getStmtsByVar(var).empty());
    REQUIRE(ifPatternManager.getAllStmtVarPair().empty());
}

TEST_CASE("Test If Pattern Storage") {
    IfPatternManager ifPatternManager = IfPatternManager();
    Statement ifStmt = Statement(1, StatementType::If);
    Variable var = Variable("x");

    REQUIRE_NOTHROW(ifPatternManager.storeIfPattern(
            make_shared<Statement>(ifStmt),
            make_shared<vector<shared_ptr<Variable>>>(vector<shared_ptr<Variable>>{make_shared<Variable>(var)})));
}

TEST_CASE("Test If Pattern Retrieval") {
    IfPatternManager ifPatternManager = IfPatternManager();
    shared_ptr<Statement> ifStmt1 = make_shared<Statement>(Statement(1, StatementType::If));
    shared_ptr<Statement> ifStmt2 = make_shared<Statement>(Statement(2, StatementType::If));
    shared_ptr<Statement> ifStmt3 = make_shared<Statement>(Statement(3, StatementType::If));

    shared_ptr<Variable> varX = make_shared<Variable>(Variable("x"));
    shared_ptr<Variable> varY = make_shared<Variable>(Variable("y"));
    shared_ptr<Variable> varZ = make_shared<Variable>(Variable("z"));

    shared_ptr<vector<shared_ptr<Variable>>> vars1 =
            make_shared<vector<shared_ptr<Variable>>>(vector<shared_ptr<Variable>>{varX, varY, varZ});
    shared_ptr<vector<shared_ptr<Variable>>> vars2 =
            make_shared<vector<shared_ptr<Variable>>>(vector<shared_ptr<Variable>>{varX, varY});
    shared_ptr<vector<shared_ptr<Variable>>> vars3 =
            make_shared<vector<shared_ptr<Variable>>>(vector<shared_ptr<Variable>>{varZ});

    ifPatternManager.storeIfPattern(ifStmt1, vars1);
    ifPatternManager.storeIfPattern(ifStmt2, vars2);
    ifPatternManager.storeIfPattern(ifStmt3, vars3);

    Statement testStmt1 = Statement(1, StatementType::If);
    Statement testStmt2 = Statement(2, StatementType::If);
    Statement testStmt3 = Statement(3, StatementType::If);
    Variable testX = Variable("x");
    Variable testY = Variable("y");
    Variable testZ = Variable("z");

    vector<Entity> getStmtByVar = ifPatternManager.getAllStmts();
    REQUIRE(getStmtByVar.size() == 3);
    REQUIRE(find(getStmtByVar.begin(), getStmtByVar.end(), testStmt1) != getStmtByVar.end());
    REQUIRE(find(getStmtByVar.begin(), getStmtByVar.end(), testStmt2) != getStmtByVar.end());
    REQUIRE(find(getStmtByVar.begin(), getStmtByVar.end(), testStmt3) != getStmtByVar.end());

    REQUIRE(ifPatternManager.getAllStmtVarPair().size() == 6);

    vector<Entity> getStmtsByVarX = ifPatternManager.getStmtsByVar(testX);
    REQUIRE(getStmtsByVarX.size() == 2);
    REQUIRE(find(getStmtsByVarX.begin(), getStmtsByVarX.end(), testStmt1) != getStmtsByVarX.end());
    REQUIRE(find(getStmtsByVarX.begin(), getStmtsByVarX.end(), testStmt2) != getStmtsByVarX.end());

    vector<Entity> getStmtsByVarY = ifPatternManager.getStmtsByVar(testY);
    REQUIRE(getStmtsByVarY.size() == 2);
    REQUIRE(find(getStmtsByVarY.begin(), getStmtsByVarY.end(), testStmt1) != getStmtsByVarY.end());
    REQUIRE(find(getStmtsByVarY.begin(), getStmtsByVarY.end(), testStmt2) != getStmtsByVarY.end());

    vector<Entity> getStmtsByVarZ = ifPatternManager.getStmtsByVar(testZ);
    REQUIRE(getStmtsByVarZ.size() == 2);
    REQUIRE(find(getStmtsByVarZ.begin(), getStmtsByVarZ.end(), testStmt1) != getStmtsByVarZ.end());
    REQUIRE(find(getStmtsByVarZ.begin(), getStmtsByVarZ.end(), testStmt3) != getStmtsByVarZ.end());
}