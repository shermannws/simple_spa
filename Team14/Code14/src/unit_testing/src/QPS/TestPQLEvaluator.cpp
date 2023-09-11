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
        std::vector<std::shared_ptr<Entity>> v1 {e1, e11};

        std::shared_ptr<Statement> e2 = std::make_shared<Statement>(5);
        std::shared_ptr<Variable> e21 = std::make_shared<Variable>("another_variable");
        std::vector<std::shared_ptr<Entity>> v2 {e2, e21};

        std::unordered_map<std::string, int> map {{"a", 0}, {"x", 1}};
        r.setSynIndices(map);

        std::shared_ptr<std::vector<std::shared_ptr<Entity>>> ptr1 = std::make_shared<std::vector<std::shared_ptr<Entity>>>(v1);
        std::shared_ptr<std::vector<std::shared_ptr<Entity>>> ptr2 = std::make_shared<std::vector<std::shared_ptr<Entity>>>(v2);

        std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>> tuples {ptr1, ptr2};
        r.setTuples(tuples);

        PQLEvaluator evaluator;
        std::list<std::string> formattedResults = evaluator.formatResult(query, r);

        std::list<std::string> expected {"my_variable", "another_variable"};
        REQUIRE(formattedResults == expected);
    }
    // TODO: CHANGE THIS
    SECTION("Follows query single tuple") {
        PQLParser parser("stmt s; Select s such that Follows(2,s)");
        Query query = parser.parse();
        ResultType type = ResultType::Tuples;
        Result r = Result();
        r.setType(type);

        std::shared_ptr<Statement> e1 = std::make_shared<Statement>(1);
        std::vector<std::shared_ptr<Entity>> v1 {e1};

        std::shared_ptr<Statement> e2 = std::make_shared<Statement>(2);
        std::vector<std::shared_ptr<Entity>> v2 {e2};


        std::unordered_map<std::string, int> map {{"s", 0}};
        r.setSynIndices(map);

        std::shared_ptr<std::vector<std::shared_ptr<Entity>>> ptr1 = std::make_shared<std::vector<std::shared_ptr<Entity>>>(v1);
        std::shared_ptr<std::vector<std::shared_ptr<Entity>>> ptr2 = std::make_shared<std::vector<std::shared_ptr<Entity>>>(v2);

        std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>> tuples {ptr1, ptr2};
        r.setTuples(tuples);

        PQLEvaluator evaluator;
        std::list<std::string> formattedResults = evaluator.formatResult(query, r);

        std::list<std::string> expected {"1", "2"};
        REQUIRE(formattedResults == expected);
    }
}