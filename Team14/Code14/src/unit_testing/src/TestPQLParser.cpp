#include "QPS/PQLParser.h"

#include "catch.hpp"

// TODO refactor unit tests using SECTION()

TEST_CASE("single declaration, single Select") {
    std::string input = "stmt s; Select s";
    PQLParser parser(input);
    Query query = parser.parse();
    Entity expectedEntity = Entity(EntityType::Stmt, "s");
    std::shared_ptr<Entity> declarationEntity = query.getEntity("s");
    std::shared_ptr<Entity> selectEntity = query.getSelect()[0];

    REQUIRE(query.hasDeclarations());
    REQUIRE(query.getEntity("s"));
    REQUIRE(*declarationEntity == expectedEntity);
    REQUIRE(declarationEntity == selectEntity);
}

TEST_CASE("processDeclarations serial declaration") {
    std::string input = "variable v,v1,v2; Select v";
    PQLParser parser(input);
    Query query = parser.parse();
    auto declaration_map = query.getDeclarations();
    std::shared_ptr<Entity> declarationEntity = query.getEntity("v");
    std::shared_ptr<Entity> selectEntity = query.getSelect()[0];

    REQUIRE(query.hasDeclarations());
    REQUIRE(declaration_map.size()==3);
    REQUIRE(query.getEntity("v"));
    REQUIRE(query.getEntity("v1"));
    REQUIRE(query.getEntity("v2"));
    REQUIRE(declarationEntity == selectEntity);
}

TEST_CASE("processDeclarations multiple declaration") {
    std::string input = "procedure p; stmt s; read re; print pr; assign a; \n call c; while w; if i; variable v; constant k; \n Select c";
    PQLParser parser(input);
    Query query = parser.parse();
    auto declaration_map = query.getDeclarations();
    std::shared_ptr<Entity> declarationEntity = query.getEntity("c");
    std::shared_ptr<Entity> selectEntity = query.getSelect()[0];

    REQUIRE(query.hasDeclarations());
    REQUIRE(declaration_map.size()==10);
    REQUIRE(query.getEntity("p"));
    REQUIRE(query.getEntity("s"));
    REQUIRE(query.getEntity("re"));
    REQUIRE(query.getEntity("pr"));
    REQUIRE(query.getEntity("a"));
    REQUIRE(query.getEntity("c"));
    REQUIRE(query.getEntity("w"));
    REQUIRE(query.getEntity("i"));
    REQUIRE(query.getEntity("v"));
    REQUIRE(query.getEntity("k"));
    REQUIRE(declarationEntity == selectEntity);
}

TEST_CASE("processDeclarations Errors") {
    std::vector<std::pair<std::string, std::string>> testcases;
    testcases.emplace_back("Select s ", "Expected a declaration but found none");
    testcases.emplace_back("assignment a; ", "Expected a declaration but found none");
    testcases.emplace_back("assign a Select s", "Expected ; but found 'Select'");
    testcases.emplace_back("assign a a1;", "Expected ; but found 'a1'");
    testcases.emplace_back("assign a; print a;", "Trying to redeclare a synonym");
    testcases.emplace_back("assign 1; Select 1", "Invalid synonym '1'");
    testcases.emplace_back("assign -a ; Select -a", "Invalid synonym '-'");
    testcases.emplace_back("stmt", "Expected synonym but found none");
    testcases.emplace_back("stmt ; ",  "Invalid synonym ';'");

    for (const auto& testcase : testcases) {
        PQLParser parser(testcase.first);
        REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
    }
}

TEST_CASE("processSelect Errors") {
    std::vector<std::pair<std::string, std::string>> testcases;
    testcases.emplace_back("stmt s; where s", "Expected Select clause but found 'where'");
    testcases.emplace_back("assign a; Select s", "Undeclared synonym in Select clause");
    testcases.emplace_back("assign a; Select", "Expected synonym but found none");

    for (const auto& testcase : testcases) {
        PQLParser parser(testcase.first);
        REQUIRE_THROWS_WITH(parser.parse(), testcase.second);
    }
}

