#include <iostream>

#include "PKB/EntityStores/EntityStore.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/Constant.h"
#include "Commons/Entities/Procedure.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("Test Entity Storage and Retrieval") {
	auto mockStatement = std::make_shared<Statement>(Statement(1, StatementType::Assign));
    auto mockVariable = std::make_shared<Variable>(Variable("x"));
    auto mockConstant = std::make_shared<Constant>(Constant(2));
    auto mockProcedure = std::make_shared<Procedure>(Procedure("y"));

    EntityStore store = EntityStore();

	store.storeEntity(mockStatement);
	store.storeEntity(mockVariable);
	store.storeEntity(mockConstant);
	store.storeEntity(mockProcedure);

	auto e1 = store.getEntity(std::make_shared<Entity>(Statement(1, StatementType::Assign)));
    auto e2 = store.getEntity(std::make_shared<Entity>(Variable("x")));
    auto e3 = store.getEntity(std::make_shared<Entity>(Constant(2)));
    auto e4 = store.getEntity(std::make_shared<Entity>(Procedure("y")));

    auto e5 = store.getEntity(std::make_shared<Entity>(Procedure("z")));

	REQUIRE(e5 == nullptr);
	REQUIRE(e1 == mockStatement);
	REQUIRE(e2 == mockVariable);
	REQUIRE(e3 == mockConstant);
	REQUIRE(e4 == mockProcedure);

    auto entities = store.getAllEntities();
    REQUIRE(entities->size() == 4);
    REQUIRE(find(entities->begin(), entities->end(), mockStatement) != entities->end());
    REQUIRE(find(entities->begin(), entities->end(), mockConstant) != entities->end());
    REQUIRE(find(entities->begin(), entities->end(), mockProcedure) != entities->end());
    REQUIRE(find(entities->begin(), entities->end(), mockVariable) != entities->end());
}