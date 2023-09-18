#include "PKB/Relationships/ModifiesRelationship.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Relationships/RelationshipHash.h"

#include "catch.hpp"
#include <iostream>
#include <functional>

using namespace std;

TEST_CASE("Test ModifiesRelationship Constructor") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Variable mockRightEntity = Variable("x");

	ModifiesRelationship rs = ModifiesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	REQUIRE(*(rs.getLeftEntity()->getEntityValue()) == "1");
	REQUIRE(*(rs.getRightEntity()->getEntityValue()) == "x");
}

TEST_CASE("Test ModifiesRelationship Inequality") {
	Statement mockLeftEntity1 = Statement(1, StatementType::Assign);
	Variable mockRightEntity1 = Variable("x");

	ModifiesRelationship rs1 = ModifiesRelationship(
		std::make_shared<Statement>(mockLeftEntity1),
		std::make_shared<Variable>(mockRightEntity1));

	Statement mockLeftEntity2 = Statement(2, StatementType::Assign);
	Variable mockRightEntity2 = Variable("y");

	ModifiesRelationship rs2 = ModifiesRelationship(
		std::make_shared<Statement>(mockLeftEntity2),
		std::make_shared<Variable>(mockRightEntity2));

	REQUIRE(!(rs1 == rs2));
}

TEST_CASE("Test ModifiesRelationship Equality") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Variable mockRightEntity = Variable("x");

	ModifiesRelationship rs = ModifiesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	ModifiesRelationship rsWithSameSharedPtr = ModifiesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	ModifiesRelationship rsWithDiffSharedPtr = ModifiesRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Variable>(Variable("x")));

	REQUIRE(rs == rsWithSameSharedPtr);
	REQUIRE(rs == rsWithDiffSharedPtr);
}

TEST_CASE("Test ModifiesRelationship Static Field") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Variable mockRightEntity = Variable("x");

	ModifiesRelationship rs = ModifiesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	REQUIRE(rs.relationshipType == RelationshipType::Modifies);
}

TEST_CASE("Test ModifiesRelationship Hash") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Variable mockRightEntity = Variable("x");

	ModifiesRelationship rs = ModifiesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	ModifiesRelationship rsWithDiffPtr = ModifiesRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Variable>(Variable("x")));

	RelationshipHash<ModifiesRelationship> relationshipHasher;
	std::size_t hashValue = relationshipHasher(rs);
	std::size_t hashValueDiffPtr = relationshipHasher(rsWithDiffPtr);

	REQUIRE(hashValue == hashValueDiffPtr);
}

TEST_CASE("Test ModifiesRelationship Hasher") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Variable mockRightEntity = Variable("x");

	ModifiesRelationship rs = ModifiesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	ModifiesRelationship rsWithDiffPtr = ModifiesRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Variable>(Variable("x")));

	RelationshipPtrHash<ModifiesRelationship> relationshipPtrHasher;
	std::size_t hashValue = relationshipPtrHasher(std::make_shared<ModifiesRelationship>(rs));
	std::size_t hashValueDiffPtr = relationshipPtrHasher(std::make_shared<ModifiesRelationship>(rsWithDiffPtr));


	REQUIRE(hashValue == hashValueDiffPtr);
}