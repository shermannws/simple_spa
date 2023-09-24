#include "PKB/Relationships/ParentRelationship.h"
#include "Commons/Entities/Statement.h"
#include "PKB/Relationships/RelationshipHash.h"

#include "catch.hpp"
#include <iostream>
#include <functional>

using namespace std;

TEST_CASE("Test ParentRelationship Constructor") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Statement mockRightEntity = Statement(2, StatementType::Assign);

	ParentRelationship rs = ParentRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	REQUIRE(*(rs.getLeftEntity()->getEntityValue()) == "1");
	REQUIRE(*(rs.getRightEntity()->getEntityValue()) == "2");
}

TEST_CASE("Test ParentRelationship Inequality") {
	Statement mockLeftEntity1 = Statement(1, StatementType::Assign);
	Statement mockRightEntity1 = Statement(2, StatementType::Assign);

	ParentRelationship rs1 = ParentRelationship(
		std::make_shared<Statement>(mockLeftEntity1),
		std::make_shared<Statement>(mockRightEntity1),
        true);

	Statement mockLeftEntity2 = Statement(2, StatementType::Assign);
	Statement mockRightEntity2 = Statement(1, StatementType::Assign);

	ParentRelationship rs2 = ParentRelationship(
		std::make_shared<Statement>(mockLeftEntity2),
		std::make_shared<Statement>(mockRightEntity2),
        true);

	REQUIRE(!(rs1 == rs2));
}

TEST_CASE("Test ParentRelationship Equality") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Statement mockRightEntity = Statement(2, StatementType::Assign);

	ParentRelationship rs = ParentRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	ParentRelationship rsWithSameSharedPtr = ParentRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	ParentRelationship rsWithDiffSharedPtr = ParentRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Statement>(Statement(2, StatementType::Assign)),
        true);

	REQUIRE(rs == rsWithSameSharedPtr);
	REQUIRE(rs == rsWithDiffSharedPtr);
}

TEST_CASE("Test ParentRelationship Static Field") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Statement mockRightEntity = Statement(1, StatementType::Assign);

	ParentRelationship rs = ParentRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	REQUIRE(rs.relationshipType == RelationshipType::Parent);
}

TEST_CASE("Test ParentRelationship Hash") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Statement mockRightEntity = Statement(4, StatementType::Assign);

	ParentRelationship rs = ParentRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	ParentRelationship rsWithDiffPtr = ParentRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Statement>(Statement(4, StatementType::Assign)),
        true);

	RelationshipHash<ParentRelationship> relationshipHasher;
	std::size_t hashValue = relationshipHasher(rs);
	std::size_t hashValueDiffPtr = relationshipHasher(rsWithDiffPtr);

	REQUIRE(hashValue == hashValueDiffPtr);
}

TEST_CASE("Test ParentRelationship Hasher") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Statement mockRightEntity = Statement(4, StatementType::Assign);

	ParentRelationship rs = ParentRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	ParentRelationship rsWithDiffPtr = ParentRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Statement>(Statement(4, StatementType::Assign)),
        true);

	RelationshipPtrHash<ParentRelationship> relationshipPtrHasher;
	std::size_t hashValue = relationshipPtrHasher(std::make_shared<ParentRelationship>(rs));
	std::size_t hashValueDiffPtr = relationshipPtrHasher(std::make_shared<ParentRelationship>(rsWithDiffPtr));


	REQUIRE(hashValue == hashValueDiffPtr);
}