#include <memory>

#include "catch.hpp"
#include "PKB/Managers/EntitiesManager.h"

using namespace std;

TEST_CASE("Test Entities Retrieval") {
    EntitiesManager manager = EntitiesManager();

    Statement statement1 = Statement(1, StatementType::Assign);
    Statement statement2 = Statement(2, StatementType::While);

    Variable variable1 = Variable("x");

    Constant constant1 = Constant(1);

    Procedure procedure1 = Procedure("main");

    manager.storeStatement(std::make_shared<Statement>(statement1));
    manager.storeStatement(std::make_shared<Statement>(statement2));
    manager.storeVariable(std::make_shared<Variable>(variable1));
    manager.storeConstant(std::make_shared<Constant>(constant1));
    manager.storeProcedure(std::make_shared<Procedure>(procedure1));

    REQUIRE(manager.getAllStatements().size() == 2);
    REQUIRE(manager.getAllVariables().size() == 1);
    REQUIRE(manager.getAllVariables().at(0) == Entity(variable1));
    REQUIRE(manager.getAllConstants().size() == 1);
    REQUIRE(manager.getAllConstants().at(0) == Entity(constant1));
    REQUIRE(manager.getAllProcedures().size() == 1);
    REQUIRE(manager.getAllProcedures().at(0) == Entity(procedure1));
    REQUIRE(manager.getAllRead().empty());
    REQUIRE(manager.getAllPrint().empty());
    REQUIRE(manager.getAllWhile().size() == 1);
    REQUIRE(manager.getAllWhile().at(0) == Entity(statement2));
    REQUIRE(manager.getAllIf().empty());


}