#include <memory>

#include "../../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "PKB/Managers/EntitiesManager.h"
#include "catch.hpp"

using namespace std;

TEST_CASE_METHOD(UnitTestFixture, "Test Entities Retrieval") {
    EntitiesManager manager = EntitiesManager();

    Statement statement1 = Statement(1, StatementType::Assign);
    Statement statement2 = Statement(2, StatementType::While);

    Variable variable1 = Variable("x");

    Constant constant1 = Constant("1");

    Procedure procedure1 = Procedure("main");

    manager.storeStatement(std::make_shared<Statement>(statement1));
    manager.storeStatement(std::make_shared<Statement>(statement2));
    manager.storeVariable(std::make_shared<Variable>(variable1));
    manager.storeConstant(std::make_shared<Constant>(constant1));
    manager.storeProcedure(std::make_shared<Procedure>(procedure1));

    auto set1 = manager.getAllStatements();
    REQUIRE(set1.size() == 2);
    REQUIRE(set1.find(Entity(statement1)) != set1.end());
    REQUIRE(set1.find(Entity(statement2)) != set1.end());

    auto set2 = manager.getAllVariables();
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(Entity(variable1)) != set2.end());

    auto set3 = manager.getAllConstants();
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(Entity(constant1)) != set3.end());

    auto set4 = manager.getAllProcedures();
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(Entity(procedure1)) != set4.end());

    auto set5 = manager.getAllWhile();
    REQUIRE(set5.size() == 1);
    REQUIRE(set5.find(Entity(statement2)) != set5.end());

    REQUIRE(manager.getAllRead().empty());
    REQUIRE(manager.getAllPrint().empty());
    REQUIRE(manager.getAllWhile().size() == 1);
    REQUIRE(manager.getAllIf().empty());
}