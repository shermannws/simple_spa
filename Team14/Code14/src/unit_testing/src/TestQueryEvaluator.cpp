#include "QPS/QueryEvaluator.h"
#include "QPS/PQLParser.h"

#include <unordered_map>
#include <iostream>

#include "catch.hpp"
#include "Commons/Entities/Statement.h"

TEST_CASE("Test formatResult") {
    SECTION("hello") {
        PQLParser parser("stmt s; Select s such that Follows(2,s)");
        Query query = parser.parse();
        ResultType type = ResultType::Tuples;
        Result r = Result();
        r.setType(type);
        std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>> tuples;
        std::unordered_map<std::string, std::shared_ptr<Entity>> map1;
        std::unordered_map<std::string, std::shared_ptr<Entity>> map2;
        std::shared_ptr<Statement> e1 = std::make_shared<Statement>(1);
        map1.insert({"s", e1});
        std::shared_ptr<Statement> e1_1 = std::make_shared<Statement>(3);
        map1.insert({"r", e1_1});
        std::shared_ptr<Statement> e2 = std::make_shared<Statement>(2);
        map2.insert({"s", e2});
        tuples.push_back(map1);
        tuples.push_back(map2);
        r.setTuples(tuples);
        QueryEvaluator evaluator;
        std::list<std::string> formatted_results = evaluator.formatResult(query, r);

//        for (auto const &i: formatted_results) {
//            std::cout << i << std::endl;
//        }
    }

    SECTION("ANOTHER") {
        PQLParser parser("assign a; variable x; Select x such that Uses(a, x)");
        Query query = parser.parse();
        ResultType type = ResultType::Tuples;
        Result r = Result();
        r.setType(type);
        std::vector<std::unordered_map<std::string, std::shared_ptr<Entity>>> tuples;
        std::unordered_map<std::string, std::shared_ptr<Entity>> map1;
        std::unordered_map<std::string, std::shared_ptr<Entity>> map2;
        std::shared_ptr<Statement> e1 = std::make_shared<Statement>(1);
        map1.insert({"a", e1});
        std::shared_ptr<Statement> e1_1 = std::make_shared<Statement>(3);
        map1.insert({"x", e1_1});
        std::shared_ptr<Statement> e2 = std::make_shared<Statement>(2);
        map2.insert({"a", e2});
        tuples.push_back(map1);
        tuples.push_back(map2);
        r.setTuples(tuples);
        QueryEvaluator evaluator;
        std::list<std::string> formatted_results = evaluator.formatResult(query, r);

        for (auto const &i: formatted_results) {
            std::cout << i << std::endl;
        }
    }

}