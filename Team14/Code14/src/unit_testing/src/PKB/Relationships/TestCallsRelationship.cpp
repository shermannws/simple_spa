#include "PKB/Relationships/CallsRelationship.h"
#include "Commons/Entities/Procedure.h"
#include "PKB/Relationships/RelationshipHash.h"

#include "catch.hpp"
#include <iostream>
#include <functional>

using namespace std;

TEST_CASE("Test CallsRelationship Constructor") {
	Procedure mockLeftEntity = Procedure("one");
	Procedure mockRightEntity = Procedure("two");

	CallsRelationship follows = CallsRelationship(
		std::make_shared<Procedure>(mockLeftEntity),
		std::make_shared<Procedure>(mockRightEntity),
		true);

	REQUIRE(*(follows.getLeftEntity()->getEntityValue()) == "one");
	REQUIRE(*(follows.getRightEntity()->getEntityValue()) == "two");
}

TEST_CASE("Test CallsRelationship Inequality") {
	Procedure mockLeftEntity1 = Procedure("one");
	Procedure mockRightEntity1 = Procedure("two");

	CallsRelationship calls1 = CallsRelationship(
		std::make_shared<Procedure>(mockLeftEntity1),
		std::make_shared<Procedure>(mockRightEntity1),
		true);

	Procedure mockLeftEntity2 = Procedure("one");
	Procedure mockRightEntity2 = Procedure("four");

	CallsRelationship calls2 = CallsRelationship(
		std::make_shared<Procedure>(mockLeftEntity2),
		std::make_shared<Procedure>(mockRightEntity2),
		true);

	REQUIRE(!(calls1 == calls2));
}

TEST_CASE("Test CallsRelationship Equality") {
	Procedure mockLeftEntity = Procedure("one");
	Procedure mockRightEntity = Procedure("two");

	CallsRelationship calls = CallsRelationship(
		std::make_shared<Procedure>(mockLeftEntity),
		std::make_shared<Procedure>(mockRightEntity),
		true);

	CallsRelationship callsWithSameSharedPtr = CallsRelationship(
		std::make_shared<Procedure>(mockLeftEntity),
		std::make_shared<Procedure>(mockRightEntity),
		true);

	CallsRelationship callsWithDiffSharedPtr = CallsRelationship(
		std::make_shared<Procedure>(Procedure("one")),
		std::make_shared<Procedure>(Procedure("two")),
		true);

	REQUIRE(calls == callsWithSameSharedPtr);
	REQUIRE(calls == callsWithDiffSharedPtr);
}

TEST_CASE("Test CallsRelationship Static Field") {
	Procedure mockLeftEntity = Procedure("one");
	Procedure mockRightEntity = Procedure("two");

	CallsRelationship calls = CallsRelationship(
		std::make_shared<Procedure>(mockLeftEntity),
		std::make_shared<Procedure>(mockRightEntity),
		true);

	REQUIRE(calls.relationshipType == RelationshipType::Calls);
}

TEST_CASE("Test CallsRelationship Hash") {
	Procedure mockLeftEntity = Procedure("one");
	Procedure mockRightEntity = Procedure("four");

	CallsRelationship calls = CallsRelationship(
		std::make_shared<Procedure>(mockLeftEntity),
		std::make_shared<Procedure>(mockRightEntity),
		true);

	CallsRelationship callsWithDiffPtr = CallsRelationship(
		std::make_shared<Procedure>(Procedure("one")),
		std::make_shared<Procedure>(Procedure("four")),
		true);

	RelationshipHash<CallsRelationship> relationshipHasher;
	std::size_t hashValue = relationshipHasher(calls);
	std::size_t hashValueDiffPtr = relationshipHasher(callsWithDiffPtr);

	REQUIRE(hashValue == hashValueDiffPtr);
}

TEST_CASE("Test CallsRelationshipPtr Hasher") {
	Procedure mockLeftEntity = Procedure("one");
	Procedure mockRightEntity = Procedure("four");

	CallsRelationship calls = CallsRelationship(
		std::make_shared<Procedure>(mockLeftEntity),
		std::make_shared<Procedure>(mockRightEntity),
		true);

	CallsRelationship callsWithDiffPtr = CallsRelationship(
		std::make_shared<Procedure>(Procedure("one")),
		std::make_shared<Procedure>(Procedure("four")),
		true);

	RelationshipPtrHash<CallsRelationship> relationshipPtrHasher;
	std::size_t hashValue = relationshipPtrHasher(std::make_shared<CallsRelationship>(calls));
	std::size_t hashValueDiffPtr = relationshipPtrHasher(std::make_shared<CallsRelationship>(callsWithDiffPtr));


	REQUIRE(hashValue == hashValueDiffPtr);
}