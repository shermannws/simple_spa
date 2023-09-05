#include "Commons/Constant.h"
#include "Commons/Procedure.h"
#include "Commons/Statement.h"
#include "Commons/Variable.h"

#include "catch.hpp"
using namespace std;

TEST_CASE("Test Entity - Constant") {
	int mockValue = 1;
	Constant c = Constant(mockValue);

	REQUIRE(mockValue == c.getValue());
}

TEST_CASE("Test Entity - Procedure") {
	string mockName = "mockName";
	Procedure p = Procedure(mockName);

	REQUIRE(mockName == p.getName());
}

TEST_CASE("Test Entity - Statement") {
	int mockLineNo = 1;
	Statement s = Statement(mockLineNo);

	REQUIRE(mockLineNo == s.getLineNo());
}

TEST_CASE("Test Entity - Variable") {
	string mockName = "mockName";
	Variable v = Variable(mockName);

	REQUIRE(mockName == v.getName());
}