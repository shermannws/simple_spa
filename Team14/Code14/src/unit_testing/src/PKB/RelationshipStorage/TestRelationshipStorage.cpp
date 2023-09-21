#include "PKB/RelationshipStores/RelationshipStore.h"
#include "PKB/RelationshipStores/UsesRelationshipStore.h"
#include "PKB/Relationships/UsesRelationship.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Relationships/ModifiesRelationship.h"
#include "PKB/RelationshipStores/ModifiesRelationshipStore.h"
#include "PKB/Relationships/ParentRelationship.h"
#include "PKB/RelationshipStores/ParentRelationshipStore.h"

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

	RelationshipStore store = RelationshipStore<UsesRelationship>();

	store.storeRelationship(std::make_shared<UsesRelationship>(uses));

	auto r = store.getRelationship(std::make_shared<UsesRelationship>(usesCloned));
	auto r2 = store.getRelationship(std::make_shared<UsesRelationship>(usesCloned2));

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

	RelationshipStore store = RelationshipStore<UsesRelationship>();

	store.storeRelationship(std::make_shared<UsesRelationship>(uses));
	auto r = store.getRelationship(std::make_shared<UsesRelationship>(usesCloned));

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

	store.storeRelationship(std::make_shared<UsesRelationship>(uses));
	auto r = store.getRelationship(std::make_shared<UsesRelationship>(usesCloned));
	auto r2 = store.getRelationship(std::make_shared<UsesRelationship>(usesCloned2));

	REQUIRE(r != nullptr);
	REQUIRE(*r == usesCloned);
	REQUIRE(*r == uses);
	REQUIRE(*r2 == uses);
	REQUIRE(*r2 == usesCloned);
}

TEST_CASE("Test ModifiesRelationshipStore") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Variable mockRightEntity = Variable("x");

	ModifiesRelationship rs = ModifiesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	ModifiesRelationship rsCloned = ModifiesRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Variable>(mockRightEntity));

	ModifiesRelationship rsCloned2 = ModifiesRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Variable>(Variable("x")));

	ModifiesRelationshipStore store = ModifiesRelationshipStore();

	store.storeRelationship(std::make_shared<ModifiesRelationship>(rs));
	auto r = store.getRelationship(std::make_shared<ModifiesRelationship>(rsCloned));
	auto r2 = store.getRelationship(std::make_shared<ModifiesRelationship>(rsCloned2));

	REQUIRE(r != nullptr);
	REQUIRE(*r == rsCloned);
	REQUIRE(*r == rs);
	REQUIRE(*r2 == rs);
	REQUIRE(*r2 == rsCloned);
}

TEST_CASE("Test ParentRelationshipStore") {
	Statement mockLeftEntity = Statement(1, StatementType::Assign);
	Statement mockRightEntity = Statement(2, StatementType::Assign);

	ParentRelationship rs = ParentRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	ParentRelationship rsCloned = ParentRelationship(
		std::make_shared<Statement>(mockLeftEntity),
		std::make_shared<Statement>(mockRightEntity),
        true);

	ParentRelationship rsCloned2 = ParentRelationship(
		std::make_shared<Statement>(Statement(1, StatementType::Assign)),
		std::make_shared<Statement>(Statement(2, StatementType::Assign)),
        true);

	ParentRelationshipStore store = ParentRelationshipStore();

	store.storeRelationship(std::make_shared<ParentRelationship>(rs));
	auto r = store.getRelationship(std::make_shared<ParentRelationship>(rsCloned));
	auto r2 = store.getRelationship(std::make_shared<ParentRelationship>(rsCloned2));

	REQUIRE(r != nullptr);
	REQUIRE(*r == rsCloned);
	REQUIRE(*r == rs);
	REQUIRE(*r2 == rs);
	REQUIRE(*r2 == rsCloned);
}