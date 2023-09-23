#include "catch.hpp"
#include "PKB/PkbWriter.h"
#include "PKB/Relationships/FollowsRelationship.h"
#include "PKB/Relationships/UsesRelationship.h"
#include "PKB/Pkb.h"

using namespace std;

TEST_CASE("Test initialising PKB Writer") {
    Pkb pkb = Pkb();
    auto writer = pkb.createPkbWriter();

    REQUIRE(1 == 1);
}

//TEST_CASE("Test PKB Writer Facade") {
//    auto assignManager = std::make_shared<AssignmentManager>(std::make_shared<AssignmentPatternStore>());
//    auto constantStore = std::make_shared<ConstantStore>();
//    auto procedureStore = std::make_shared<ProcedureStore>();
//    auto statementStore = std::make_shared<StatementStore>();
//    auto variableStore = std::make_shared<VariableStore>();
//    auto followsStore = std::make_shared<FollowsRelationshipStore>();
//    auto usesStore = std::make_shared<UsesRelationshipStore>();
//    auto readStmtStore = std::make_shared<ReadStatementStore>();
//    auto printStmtStore = std::make_shared<PrintStatementStore>();
//
//    PkbWriter writer = PkbWriter(
//        assignManager,
//        constantStore,
//        procedureStore,
//        statementStore,
//        variableStore,
//        followsStore,
//        usesStore,
//        readStmtStore,
//        printStmtStore
//    );
//
//    writer.addConstant(std::make_shared<Constant>(1));
//    REQUIRE(*(constantStore->getEntity(std::make_shared<Constant>(1))) == Constant(1));
//
//    writer.addVariable(std::make_shared<Variable>("x"));
//    REQUIRE(*(variableStore->getEntity(std::make_shared<Variable>("x"))) == Variable("x"));
//
//    writer.addProcedure(std::make_shared<Procedure>("p"));
//    REQUIRE(*(procedureStore->getEntity(std::make_shared<Procedure>("p"))) == Variable("p"));
//
//    writer.addPrintStatement(std::make_shared<Statement>(2));
//    REQUIRE(*(printStmtStore->getEntity(std::make_shared<Statement>(2))) == Statement(2));
//    REQUIRE(*(statementStore->getEntity(std::make_shared<Statement>(2))) == Statement(2));
//
//    writer.addReadStatement(std::make_shared<Statement>(3));
//    REQUIRE(*(readStmtStore->getEntity(std::make_shared<Statement>(3))) == Statement(3));
//    REQUIRE(*(statementStore->getEntity(std::make_shared<Statement>(3))) == Statement(3));
//
//    writer.addAssignStatement(std::make_shared<Statement>(4), std::make_shared<Variable>("y"), std::make_shared<std::string>("((a+b)+c)"));
//    //TODO: test assignment pattern store after regex matching is completed
//    REQUIRE(*(statementStore->getEntity(std::make_shared<Statement>(4))) == Statement(4));
//
//
//    writer.addFollowsRelationship(std::make_shared<Statement>(5), std::make_shared<Statement>(6));
//    REQUIRE(*(followsStore->getRelationship(std::make_shared<FollowsRelationship>(std::make_shared<Statement>(5), std::make_shared<Statement>(6))))
//        == FollowsRelationship(std::make_shared<Statement>(5), std::make_shared<Statement>(6)));
//
//    writer.addUsesRelationship(std::make_shared<Statement>(7), std::make_shared<Variable>("z"));
//    REQUIRE(*(usesStore->getRelationship(std::make_shared<UsesRelationship>(std::make_shared<Statement>(7), std::make_shared<Variable>("z"))))
//        == UsesRelationship(std::make_shared<Statement>(7), std::make_shared<Variable>("z")));
//}