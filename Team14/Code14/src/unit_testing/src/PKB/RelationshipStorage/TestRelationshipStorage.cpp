#include "PKB/RelationshipStores/RelationshipStore.h"
#include "PKB/RelationshipStores/UsesRelationshipStore.h"
#include "PKB/Relationships/UsesRelationship.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

#include "catch.hpp"
#include <iostream>
using namespace std;

TEST_CASE("Test Relationship Storage and Retrieval") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Variable mockRightEntity = Variable("x");

	UsesRelationship uses = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	UsesRelationship usesCloned = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	UsesRelationship usesCloned2 = UsesRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Variable>(Variable("x")));

	RelationshipStore store = RelationshipStore();

	store.storeRelationship(std::make_shared<Relationship>(uses));
	auto r = store.getRelationship(std::make_shared<Relationship>(usesCloned));
	auto r2 = store.getRelationship(std::make_shared<Relationship>(usesCloned2));

	REQUIRE(r != nullptr);
	REQUIRE(*r == usesCloned);
	REQUIRE(*r == uses);
	REQUIRE(*r2 == uses);
	REQUIRE(*r2 == usesCloned);
}

TEST_CASE("Test Relationship Storage and Retrieval - Negative Test") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Variable mockRightEntity = Variable("x");

	UsesRelationship uses = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	UsesRelationship usesCloned = UsesRelationship(
		std::make_shared<Statement>(Statement(2, StatementType::Assign)),
		std::make_shared<Variable>(Variable("x")));

	RelationshipStore store = RelationshipStore();

	store.storeRelationship(std::make_shared<Relationship>(uses));
	auto r = store.getRelationship(std::make_shared<Relationship>(usesCloned));

	REQUIRE(r == nullptr);
}

TEST_CASE("Test UsesRelationshipStore") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Variable mockRightEntity = Variable("x");

	UsesRelationship uses = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	UsesRelationship usesCloned = UsesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	UsesRelationship usesCloned2 = UsesRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Variable>(Variable("x")));

	UsesRelationshipStore store = UsesRelationshipStore();

	store.storeRelationship(std::make_shared<Relationship>(uses));
	auto r = store.getRelationship(std::make_shared<Relationship>(usesCloned));
	auto r2 = store.getRelationship(std::make_shared<Relationship>(usesCloned2));

	REQUIRE(r != nullptr);
	REQUIRE(*r == usesCloned);
	REQUIRE(*r == uses);
	REQUIRE(*r2 == uses);
	REQUIRE(*r2 == usesCloned);
}
