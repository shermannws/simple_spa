#include "../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "PKB/Pkb.h"
#include "PKB/PkbWriter.h"
#include "catch.hpp"

using namespace std;

TEST_CASE_METHOD(UnitTestFixture, "Test initialising PKB Writer") {
    Pkb pkb = Pkb();

    REQUIRE_NOTHROW(pkb.createPkbWriter());
}

TEST_CASE_METHOD(UnitTestFixture, "Test PKBConcreteWriter Methods - Assert no throw") {
    Pkb pkb = Pkb();
    auto writer = pkb.createPkbWriter();

    REQUIRE(1 == 1);
}

TEST_CASE_METHOD(UnitTestFixture, "Test set new map as CFGStore through Writer") {
    Pkb pkb = Pkb();
    auto writer = pkb.createPkbWriter();

    REQUIRE_NOTHROW(writer->addConstant(make_shared<Constant>("1")));
    REQUIRE_NOTHROW(writer->addVariable(make_shared<Variable>("x")));
    REQUIRE_NOTHROW(writer->addProcedure(make_shared<Procedure>("main")));
    REQUIRE_NOTHROW(writer->addPrintStatement(make_shared<Statement>(1, StatementType::Print)));
    REQUIRE_NOTHROW(writer->addReadStatement(make_shared<Statement>(2, StatementType::Read)));
    REQUIRE_NOTHROW(writer->addAssignStatement(make_shared<Statement>(3, StatementType::Assign)));
    REQUIRE_NOTHROW(writer->addAssignPattern(make_shared<Statement>(3, StatementType::Assign),
                                             make_shared<Variable>("x"), make_shared<Expression>("1")));
    REQUIRE_NOTHROW(writer->addFollowsRelationship(make_shared<Statement>(1, StatementType::Print),
                                                   make_shared<Statement>(2, StatementType::Read), true));
    REQUIRE_NOTHROW(writer->addFollowsRelationship(make_shared<Statement>(1, StatementType::Print),
                                                   make_shared<Statement>(3, StatementType::Assign), false));
    REQUIRE_NOTHROW(
            writer->addUsesRelationship(make_shared<Statement>(1, StatementType::Print), make_shared<Variable>("x")));
    REQUIRE_NOTHROW(writer->addCallStatement(make_shared<Statement>(4, StatementType::Call)));
    REQUIRE_NOTHROW(writer->addIfStatement(make_shared<Statement>(5, StatementType::If)));
    REQUIRE_NOTHROW(writer->addIfPattern(make_shared<Statement>(5, StatementType::If),
                                         make_shared<vector<shared_ptr<Variable>>>(1, make_shared<Variable>("x"))));
    REQUIRE_NOTHROW(writer->addWhileStatement(make_shared<Statement>(6, StatementType::While)));
    REQUIRE_NOTHROW(writer->addWhilePattern(make_shared<Statement>(6, StatementType::While),
                                            make_shared<vector<shared_ptr<Variable>>>(1, make_shared<Variable>("x"))));
    REQUIRE_NOTHROW(writer->addModifiesRelationship(make_shared<Statement>(2, StatementType::Read),
                                                    make_shared<Variable>("x")));
    REQUIRE_NOTHROW(writer->addParentRelationship(make_shared<Statement>(5, StatementType::If),
                                                  make_shared<Statement>(6, StatementType::While), true));
    REQUIRE_NOTHROW(writer->addParentRelationship(make_shared<Statement>(5, StatementType::If),
                                                  make_shared<Statement>(7, StatementType::While), false));
    REQUIRE_NOTHROW(writer->addCallsRelationship(make_shared<Procedure>("main"), make_shared<Procedure>("proc1")));
    REQUIRE_NOTHROW(writer->addProcedureToStatementsMap(make_shared<Procedure>("main"),
                                                        {make_shared<Statement>(1, StatementType::Print)}));
    REQUIRE_NOTHROW(writer->triggerTransitiveCalc());
    REQUIRE_NOTHROW(writer->addModifiesProcRelationship(make_shared<Procedure>("main"), make_shared<Variable>("x")));
    REQUIRE_NOTHROW(writer->addUsesProcRelationship(make_shared<Procedure>("main"), make_shared<Variable>("x")));
}
