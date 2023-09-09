#include <iostream>

#include "PKB/EntityStorage/EntityStorage.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/Constant.h"
#include "Commons/Entities/Procedure.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("Test Entity Storage and Retrieval") {
	Statement mockStatement = Statement(1);
	Variable mockVariable = Variable("x");
	Constant mockConstant = Constant(2);
	Procedure mockProcedure = Procedure("y");

	EntityStorage store = EntityStorage();

	store.storeEntity(std::make_shared<Entity>(mockStatement));
	store.storeEntity(std::make_shared<Entity>(mockVariable));
	store.storeEntity(std::make_shared<Entity>(mockConstant));
	store.storeEntity(std::make_shared<Entity>(mockProcedure));

	Entity* e1 = store.getEntity(std::make_shared<Entity>(Statement(1)));
	Entity* e2 = store.getEntity(std::make_shared<Entity>(Variable("x")));
	Entity* e3 = store.getEntity(std::make_shared<Entity>(Constant(2)));
	Entity* e4 = store.getEntity(std::make_shared<Entity>(Procedure("y")));

	Entity* e5 = store.getEntity(std::make_shared<Entity>(Procedure("z")));

	REQUIRE(e5 == nullptr);
	REQUIRE(*e1 == mockStatement);
	REQUIRE(*e2 == mockVariable);
	REQUIRE(*e3 == mockConstant);
	REQUIRE(*e4 == mockProcedure);
}