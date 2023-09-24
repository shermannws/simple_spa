#include "PKB/Relationships/FollowsRelationship.h"
#include "Commons/Entities/Statement.h"
#include "PKB/Relationships/RelationshipHash.h"

#include "catch.hpp"
#include <iostream>
#include <functional>

using namespace std;

TEST_CASE("Test FollowsRelationship Constructor") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Statement mockRightEntity = Statement(2, StatementType::Assign);

	FollowsRelationship follows = FollowsRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	REQUIRE(*(follows.getLeftEntity()->getEntityValue()) == "1");
	REQUIRE(*(follows.getRightEntity()->getEntityValue()) == "2");
}

TEST_CASE("Test FollowsRelationship Inequality") {
	Statement mockLeftEntity1 = Statement(1, StatementType::Assign);
	Statement mockRightEntity1 = Statement(2, StatementType::Assign);

	FollowsRelationship follows1 = FollowsRelationship(
		std::make_shared<Statement>(mockLeftEntity1),
		std::make_shared<Statement>(mockRightEntity1),
        true);

	Statement mockLeftEntity2 = Statement(2, StatementType::Assign);
	Statement mockRightEntity2 = Statement(1, StatementType::Assign);

	FollowsRelationship follows2 = FollowsRelationship(
		std::make_shared<Statement>(mockLeftEntity2),
		std::make_shared<Statement>(mockRightEntity2),
        true);

	REQUIRE(!(follows1 == follows2));
}

TEST_CASE("Test FollowsRelationship Equality") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Statement mockRightEntity = Statement(2, StatementType::Assign);

	FollowsRelationship follows = FollowsRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	FollowsRelationship followsWithSameSharedPtr = FollowsRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	FollowsRelationship followsWithDiffSharedPtr = FollowsRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Statement>(Statement(2, StatementType::Assign)),
        true);

	REQUIRE(follows == followsWithSameSharedPtr);
	REQUIRE(follows == followsWithDiffSharedPtr);
}

TEST_CASE("Test FollowsRelationship Static Field") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Statement mockRightEntity = Statement(1, StatementType::Assign);

	FollowsRelationship follows = FollowsRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	REQUIRE(follows.relationshipType == RelationshipType::Follows);
}

TEST_CASE("Test FollowsRelationship Hash") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Statement mockRightEntity = Statement(4, StatementType::Assign);

	FollowsRelationship follows = FollowsRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	FollowsRelationship followsWithDiffPtr = FollowsRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Statement>(Statement(4, StatementType::Assign)),
        true);

	RelationshipHash<FollowsRelationship> relationshipHasher;
	std::size_t hashValue = relationshipHasher(follows);
	std::size_t hashValueDiffPtr = relationshipHasher(followsWithDiffPtr);

	REQUIRE(hashValue == hashValueDiffPtr);
}

TEST_CASE("Test FollowsRelationshipPtr Hasher") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Statement mockRightEntity = Statement(4, StatementType::Assign);

	FollowsRelationship follows = FollowsRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	FollowsRelationship followsWithDiffPtr = FollowsRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Statement>(Statement(4, StatementType::Assign)),
        true);

	RelationshipPtrHash<FollowsRelationship> relationshipPtrHasher;
	std::size_t hashValue = relationshipPtrHasher(std::make_shared<FollowsRelationship>(follows));
	std::size_t hashValueDiffPtr = relationshipPtrHasher(std::make_shared<FollowsRelationship>(followsWithDiffPtr));


	REQUIRE(hashValue == hashValueDiffPtr);
}