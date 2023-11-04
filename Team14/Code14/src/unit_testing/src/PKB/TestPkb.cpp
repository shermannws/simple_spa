#include "../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "PKB/Pkb.h"
#include "catch.hpp"

using namespace std;

TEST_CASE_METHOD(UnitTestFixture, "Test initialising PKB") {
    Pkb pkb = Pkb();

    REQUIRE(1 == 1);
}

TEST_CASE_METHOD(UnitTestFixture, "Test PKB end-to-end using Facades") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    writer->addFollowsRelationship(std::make_shared<Statement>(2, StatementType::Read),
                                   std::make_shared<Statement>(3, StatementType::Print), true);

    Statement statement2(2, StatementType::Read);
    Statement statement3(3, StatementType::Print);

    auto isFollows = reader->isFollows(statement2, statement3);
    REQUIRE(isFollows);
    auto followingStmts = reader->getFollowsStmtType(statement2, StatementType::Print);
    REQUIRE(followingStmts.find(make_shared<Statement>(3, StatementType::Print)) != followingStmts.end());

    writer->addConstant(std::make_shared<Constant>("2"));
    auto c = reader->getAllConstants();
    REQUIRE(c.find(make_shared<Constant>("2")) != c.end());

    writer->addPrintStatement(std::make_shared<Statement>(5, StatementType::Print));
    auto pn = reader->getAllStatements();
    REQUIRE(pn.find(make_shared<Statement>(5, StatementType::Print)) != pn.end());

    writer->addVariable(std::make_shared<Variable>("x"));
    auto v = reader->getAllVariables();
    REQUIRE(v.find(make_shared<Variable>("x")) != v.end());
}
