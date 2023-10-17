#include <iostream>

#include "Commons/Entities/Constant.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/Entity.h"
#include "Commons/Entities//EntityType.h"

#include "catch.hpp"

TEST_CASE("Test Entity - Constant") {
	ConstantValue mockValue = "1";
	Constant c = Constant(mockValue);

	REQUIRE(mockValue == c.getEntityValue());
    REQUIRE(c.getEntityType() == EntityType::Constant);
}

TEST_CASE("Test Entity - Procedure") {
	ProcedureName mockName = "mockName";
	Procedure p = Procedure(mockName);

	REQUIRE(mockName == p.getEntityValue());
    REQUIRE(p.getEntityType() == EntityType::Procedure);
}

TEST_CASE("Test Entity - Statement") {
	StatementNumber mockLineNo = 1;
	Statement s = Statement(mockLineNo, StatementType::Assign);

	REQUIRE(std::to_string(mockLineNo) == s.getEntityValue());
    REQUIRE(s.getEntityType() == EntityType::Statement);
}

TEST_CASE("Test Entity - Variable") {
	VariableName mockName = "mockName";
	Variable v = Variable(mockName);

	REQUIRE(mockName == v.getEntityValue());
    REQUIRE(v.getEntityType() == EntityType::Variable);
}

TEST_CASE("Test Equality of Entities") {
	ConstantValue mockValue = "1";
	VariableName mockName = "1";
	StatementNumber mockLineNo = 1;

	Constant c1 = Constant(mockValue);
	Entity c2 = Constant(mockValue);
	REQUIRE(c1 == c2);

	Procedure p1 = Procedure(mockName);
	Entity p2 = Procedure(mockName);
	REQUIRE(p1 == p2);

	Statement s1 = Statement(mockLineNo, StatementType::Assign);
	Entity s2 = Statement(mockLineNo, StatementType::Assign);
	REQUIRE(s1 == s2);

	Variable v1 = Variable(mockName);
	Entity v2 = Variable(mockName);
	REQUIRE(v1 == v2);
}

TEST_CASE("Test Hash Function of Entities") {
	ConstantValue mockValue = "1";

	Constant c1 = Constant(mockValue);
	Constant c2 = Constant("1");
	Constant c3 = Constant("2");

	std::hash<Entity> entityHasher;
	std::size_t hashValue1 = entityHasher(c1);
	std::size_t hashValue2 = entityHasher(c2);
	std::size_t hashValue3 = entityHasher(c3);

	REQUIRE(hashValue1 == hashValue2);
	REQUIRE(hashValue1 != hashValue3);
}