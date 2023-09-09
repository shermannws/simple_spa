#include "PKB/Relationships/UsesRelationship.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

#include "catch.hpp"
#include <iostream>
#include <functional>

using namespace std;

TEST_CASE("Test UsesRelationship Constructor") {
	Statement mockLeftEntity = Statement(1);
	Variable mockRightEntity = Variable("x");

	UsesRelationship uses = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	REQUIRE(*(uses.getLeftEntity()->getEntityValue()) == "1");
	REQUIRE(*(uses.getRightEntity()->getEntityValue()) == "x");
}

TEST_CASE("Test UsesRelationship Inequality") {
	Statement mockLeftEntity1 = Statement(1);
	Variable mockRightEntity1 = Variable("x");

	UsesRelationship uses1 = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity1),
		std::make_shared<Variable>(mockRightEntity1));

	Statement mockLeftEntity2 = Statement(2);
	Variable mockRightEntity2 = Variable("y");

	UsesRelationship uses2 = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity2),
		std::make_shared<Variable>(mockRightEntity2));

	REQUIRE(!(uses1 == uses2));
}

TEST_CASE("Test UsesRelationship Equality") {
	Statement mockLeftEntity = Statement(1);
	Variable mockRightEntity = Variable("x");

	UsesRelationship uses = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	UsesRelationship usesWithSameSharedPtr = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	UsesRelationship usesWithDiffSharedPtr = UsesRelationship(
		std::make_shared<Statement>(Statement(1)),
		std::make_shared<Variable>(Variable("x")));

	REQUIRE(uses == usesWithSameSharedPtr);
	REQUIRE(uses == usesWithDiffSharedPtr);
}

TEST_CASE("Test UsesRelationship Static Field") {
	Statement mockLeftEntity = Statement(1);
	Variable mockRightEntity = Variable("x");

	UsesRelationship uses = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	REQUIRE(uses.relationshipType == RelationshipType::Uses);
}

TEST_CASE("Test UsesRelationship Hash") {
	Statement mockLeftEntity = Statement(1);
	Variable mockRightEntity = Variable("x");

	UsesRelationship uses = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	UsesRelationship usesWithDiffPtr = UsesRelationship(
		std::make_shared<Statement>(Statement(1)),
		std::make_shared<Variable>(Variable("x")));

	std::hash<Relationship> relationshipHasher;
	std::size_t hashValue = relationshipHasher(uses);
	std::size_t hashValueDiffPtr = relationshipHasher(usesWithDiffPtr);

	REQUIRE(hashValue == hashValueDiffPtr);
}

TEST_CASE("Test UsesRelationshipPtr Hasher") {
	Statement mockLeftEntity = Statement(1);
	Variable mockRightEntity = Variable("x");

	UsesRelationship uses = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	UsesRelationship usesWithDiffPtr = UsesRelationship(
		std::make_shared<Statement>(Statement(1)),
		std::make_shared<Variable>(Variable("x")));

	std::hash<std::shared_ptr<Relationship>> relationshipPtrHasher;
	std::size_t hashValue = relationshipPtrHasher(std::make_shared<Relationship>(uses));
	std::size_t hashValueDiffPtr = relationshipPtrHasher(std::make_shared<Relationship>(usesWithDiffPtr));


	REQUIRE(hashValue == hashValueDiffPtr);
}