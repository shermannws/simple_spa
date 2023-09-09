#include "QPS/Query.h"

#include "catch.hpp"

TEST_CASE("Query class tests") {
    std::shared_ptr<Entity> entity1 = std::make_shared<Entity>(EntityType::Variable, "v");
    std::shared_ptr<Entity> entity2 = std::make_shared<Entity>(EntityType::Assign, "a");
    Query query;

    SECTION("Test addDeclaration getDeclarations") {
        REQUIRE(query.hasDeclarations() == false);
        REQUIRE(query.getDeclarations().empty());

        query.addDeclaration(entity1);
        query.addDeclaration(entity2);

        REQUIRE(query.hasDeclarations() == true);

        std::unordered_map<std::string, std::shared_ptr<Entity>> declarations = query.getDeclarations();
        REQUIRE(declarations.size() == 2);

        REQUIRE(declarations["v"] == entity1);
        REQUIRE(declarations["a"] == entity2);
    }


    SECTION("Test addSelect") {
        REQUIRE(query.getSelect().empty());
        query.addSelect(entity1);

        std::vector<std::shared_ptr<Entity>> select = query.getSelect();
        REQUIRE(select.size() == 1);
        REQUIRE(select[0] == entity1);

    }

    SECTION("Test getEntity") {
        REQUIRE(query.getEntity("v") == nullptr);
        query.addDeclaration(entity1);
        query.addDeclaration(entity2);

        std::shared_ptr<Entity> entity = query.getEntity("v");

        REQUIRE(entity == entity1);
        REQUIRE(query.getEntity("unknownSynonym") == nullptr);
    }

}
