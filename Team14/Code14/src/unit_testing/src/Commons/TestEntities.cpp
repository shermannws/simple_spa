#include <iostream>

#include "Commons/Entities/Constant.h"
#include "Commons/Entities/Procedure.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/Entity.h"

#include "catch.hpp"

using namespace std;

TEST_CASE("Test Entity - Constant") {
	int mockValue = 1;
	Constant c = Constant(mockValue);

	REQUIRE(to_string(mockValue) == *c.getEntityValue());
	REQUIRE(c.isEntityOfTypeInt() == true);
}

TEST_CASE("Test Entity - Procedure") {
	string mockName = "mockName";
	Procedure p = Procedure(mockName);

	REQUIRE(mockName == *p.getEntityValue());
	REQUIRE(p.isEntityOfTypeInt() == false);
}

TEST_CASE("Test Entity - Statement") {
	int mockLineNo = 1;
	Statement s = Statement(mockLineNo);

	REQUIRE(to_string(mockLineNo) == *s.getEntityValue());
	REQUIRE(s.isEntityOfTypeInt() == true);
}

TEST_CASE("Test Entity - Variable") {
	string mockName = "mockName";
	Variable v = Variable(mockName);

	REQUIRE(mockName == *v.getEntityValue());
	REQUIRE(v.isEntityOfTypeInt() == false);
}

TEST_CASE("Test Equality of Entities") {
	int mockValue = 1;
	string mockName = "1";
	int mockLineNo = 1;

	Constant c1 = Constant(mockValue);
	Entity c2 = Constant(mockValue);
	REQUIRE(c1 == c2);

	Procedure p1 = Procedure(mockName);
	Entity p2 = Procedure(mockName);
	REQUIRE(p1 == p2);

	Statement s1 = Statement(mockLineNo);
	Entity s2 = Statement(mockLineNo);
	REQUIRE(s1 == s2);

	Variable v1 = Variable(mockName);
	Entity v2 = Variable(mockName);
	REQUIRE(v1 == v2);
}

TEST_CASE("Test Hash Function of Entities") {
	int mockValue = 1;

	Constant c1 = Constant(mockValue);
	Constant c2 = Constant(1);
	Constant c3 = Constant(2);

	std::hash<Entity> entityHasher;
	std::size_t hashValue1 = entityHasher(c1);
	std::size_t hashValue2 = entityHasher(c2);
	std::size_t hashValue3 = entityHasher(c3);

	REQUIRE(hashValue1 == hashValue2);
	REQUIRE(hashValue1 != hashValue3);
}