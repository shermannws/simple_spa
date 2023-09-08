#include "QPS/PQLParser.h"

#include "catch.hpp"

TEST_CASE("Select Only Query") {
    std::string input = "stmt s;\nSelect s; ";
    PQLParser parser(input);
    Query query = parser.parse();
    std::shared_ptr<Entity> expectedEntity = std::make_shared<Entity>(EntityType::STMT, "a");

    REQUIRE(query.hasDeclarations());
}

TEST_CASE("Missing Declaration Query") {
    std::string input = "Select s; ";
    PQLParser parser(input);
    REQUIRE_THROWS_WITH(parser.parse(), "Missing declarations");
}

TEST_CASE("Missing Select Query") {
    std::string input = "assign a; unexpectedString ";
    PQLParser parser(input);
    REQUIRE_THROWS_WITH(parser.parse(), "Expected Select clause but found ...");
}

TEST_CASE("No Query") {
    std::string input = "stmt ";
    PQLParser parser(input);
    REQUIRE_THROWS_WITH(parser.parse(), "No more char");
}
TEST_CASE("No Query2") {
    std::string input = "stmt";
    PQLParser parser(input);
    REQUIRE_THROWS_WITH(parser.parse(), "No more token");
}

