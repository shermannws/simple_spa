#include "QPS/Query.h"

#include "catch.hpp"

TEST_CASE("Query class tests") {
    std::shared_ptr<QueryEntity> entity1 = std::make_shared<QueryEntity>(QueryEntityType::Variable, "v");
    std::shared_ptr<QueryEntity> entity2 = std::make_shared<QueryEntity>(QueryEntityType::Assign, "a");
    Query query;

    SECTION("Test addDeclaration getDeclarations") {
        REQUIRE(query.hasDeclarations() == false);
        REQUIRE(query.getDeclarations().empty());

        query.addDeclaration(entity1);
        query.addDeclaration(entity2);

        REQUIRE(query.hasDeclarations() == true);

        std::unordered_map<std::string, std::shared_ptr<QueryEntity>> declarations = query.getDeclarations();
        REQUIRE(declarations.size() == 2);

        REQUIRE(declarations["v"] == entity1);
        REQUIRE(declarations["a"] == entity2);
    }


    SECTION("Test addSelect") {
        REQUIRE(query.getSelect().empty());
        query.addSelect("v");

        std::vector<Synonym> select = query.getSelect();
        REQUIRE(select.size() == 1);
        REQUIRE(select[0] == "v");
    }

    SECTION("Test getEntity") {
        REQUIRE(query.getEntity("v") == nullptr);
        query.addDeclaration(entity1);
        query.addDeclaration(entity2);

        std::shared_ptr<QueryEntity> entity = query.getEntity("v");

        REQUIRE(entity == entity1);
        REQUIRE(query.getEntity("unknownSynonym") == nullptr);
    }
}