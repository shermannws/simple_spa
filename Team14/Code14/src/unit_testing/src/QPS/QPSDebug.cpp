#include "QPS/Evaluators/PQLEvaluator.h"
#include "QPS/Parsers/PQLParser.h"

#include "catch.hpp"
#include "Commons/Entities/Variable.h"
#include "../IntegrationTesting/TestPkbQps/StubPkbReader.h"


TEST_CASE("Debug PQLParser") {
    std::string input = "assign a; variable v; Select v pattern a (_, _\"x\"_)"; //ENTER YOUR QUERY HERE
    PQLParser parser(input);
    Query query = parser.parse();

    //BREAKPOINT HERE TO EXAMINE query
    REQUIRE(true);
}

TEST_CASE("Debug PQLEvaluator") {
    std::shared_ptr<StubPkbReader> stubPkbReader = std::make_shared<StubPkbReader>();

    std::string input = "assign a; variable v; Select v pattern a (_, _\"x\"_)"; //ENTER YOUR QUERY HERE
    PQLParser parser(input);
    Query query = parser.parse();
    //BREAKPOINT HERE TO EXAMINE query

    PQLEvaluator evaluator = PQLEvaluator(stubPkbReader); //HARDCODE THE REQUIRED PKBReader APIs in stubPkbReader.cpp
    Result resultObj = evaluator.evaluate(query);
    //BREAKPOINT HERE TO EXAMINE resultTable

    auto results = evaluator.formatResult(query, resultObj);

    REQUIRE(true);
    // TO VERIFY CONTENTS OF results, UNCOMMENT BELOW
    //REQUIRE(find(results.begin(), results.end(), "<EXPECTED ELEMENT IN RESULT HERE>") != results.end());
}

