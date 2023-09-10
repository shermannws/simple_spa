#include "QPS/PQLEvaluator.h"
#include "QPS/PQLParser.h"

#include <unordered_map>

#include "catch.hpp"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

TEST_CASE("Test formatResult") {
    SECTION("Uses query single tuple") {
        PQLParser parser("assign a; variable x; Select x such that Uses(a, x)");
        Query query = parser.parse();
        ResultType type = ResultType::Tuples;
        Result r = Result();
        r.setType(type);

        std::shared_ptr<Statement> e1 = std::make_shared<Statement>(1);
        std::shared_ptr<Variable> e11 = std::make_shared<Variable>("my_variable");
        std::unordered_map<std::string, std::shared_ptr<Entity>> map1 {{"a", e1}, {"x", e11}};
        std::shared_ptr<Statement> e2 = std::make_shared<Statement>(5);
        std::shared_ptr<Variable> e21 = std::make_shared<Variable>("another_variable");
        std::unordered_map<std::string, std::shared_ptr<Entity>> map2 {{"a", e2}, {"x", e21}};

        std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>> tuples {map1, map2};
        r.setTuples(tuples);

        PQLEvaluator evaluator;
        std::list<std::string> formattedResults = evaluator.formatResult(query, r);

        std::list<std::string> expected {"my_variable", "another_variable"};
        REQUIRE(formattedResults == expected);
    }

    SECTION("Follows query single tuple") {
        PQLParser parser("stmt s; Select s such that Follows(2,s)");
        Query query = parser.parse();
        ResultType type = ResultType::Tuples;
        Result r = Result();
        r.setType(type);

        std::shared_ptr<Statement> e1 = std::make_shared<Statement>(1);
        std::shared_ptr<Statement> e11 = std::make_shared<Statement>(3);
        std::unordered_map<std::string, std::shared_ptr<Entity>> map1 {{"s", e1}, {"r", e11}};

        std::shared_ptr<Statement> e2 = std::make_shared<Statement>(2);
        std::unordered_map<std::string, std::shared_ptr<Entity>> map2 {{"s", e2}};

        std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>> tuples {map1, map2};
        r.setTuples(tuples);

        PQLEvaluator evaluator;
        std::list<std::string> formattedResults = evaluator.formatResult(query, r);

        std::list<std::string> expected {"1", "2"};
        REQUIRE(formattedResults == expected);
    }
}