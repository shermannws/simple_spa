#include "QPS/PQLEvaluator.h"
#include "QPS/PQLParser.h"

#include <unordered_map>

#include "catch.hpp"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Variable.h"
#include "StubPkbReader.h"

std::shared_ptr<StubPkbReader> stubPkbReader = std::make_shared<StubPkbReader>();

TEST_CASE("Test formatResult") {

    SECTION("Uses query single tuple") {
        PQLParser parser("assign a; variable x; Select x such that Uses(a, x)");
        Query query = parser.parse();
        ResultType type = ResultType::Tuples;
        Result r = Result();
        r.setType(type);

        std::vector<Entity> v1 {Statement(1, StatementType::Assign), Variable("my_variable")};
        std::vector<Entity> v2 {Statement(5, StatementType::Stmt), Variable("another_variable")};

        std::unordered_map<std::string, int> map {{"a", 0}, {"x", 1}};
        r.setSynIndices(map);

        std::vector<std::vector<Entity>> tuples {v1, v2};
        r.setTuples(tuples);

        PQLEvaluator evaluator = PQLEvaluator(stubPkbReader);

        std::list<std::string> formattedResults = evaluator.formatResult(query, r);

        std::list<std::string> expected {"my_variable", "another_variable"};
        REQUIRE(find(formattedResults.begin(), formattedResults.end(), "my_variable") != formattedResults.end());
        REQUIRE(find(formattedResults.begin(), formattedResults.end(), "another_variable") != formattedResults.end());
    }
    // TODO: CHANGE THIS
    SECTION("Follows query single tuple") {
        PQLParser parser("stmt s; Select s such that Follows(2,s)");
        Query query = parser.parse();
        ResultType type = ResultType::Tuples;
        Result r = Result();
        r.setType(type);

        std::vector<Entity> v1 {Statement(1, StatementType::Stmt)};
        std::vector<Entity> v2 {Statement(2, StatementType::Stmt)};


        std::unordered_map<std::string, int> map {{"s", 0}};
        r.setSynIndices(map);

        std::vector<std::vector<Entity>> tuples{v1, v2};
        r.setTuples(tuples);

        PQLEvaluator evaluator = PQLEvaluator(stubPkbReader);

        std::list<std::string> formattedResults = evaluator.formatResult(query, r);

        std::list<std::string> expected {"1", "2"};
        REQUIRE(find(formattedResults.begin(), formattedResults.end(), "1") != formattedResults.end());
        REQUIRE(find(formattedResults.begin(), formattedResults.end(), "2") != formattedResults.end());
    }
}

TEST_CASE("Test QPS Flow - Assign With Pattern") {
    PQLEvaluator evaluator = PQLEvaluator(stubPkbReader);

    // build a query for the query "assign a; Select a pattern a(_, _)"
    Query queryObj = Query();
    std::shared_ptr<QueryEntity> assignInQuery = std::make_shared<QueryEntity>(QueryEntityType::Assign, "a");
    queryObj.addDeclaration(assignInQuery);
    queryObj.addSelect(assignInQuery);
    PatternClause patternClause = PatternClause();
    patternClause.setEntity(assignInQuery);
    Ref wildcard;
    std::string rep = "_";
    RefType ent = RefType::EntRef;
    RootType root = RootType::Wildcard;
    wildcard.setRep(rep);
    wildcard.setRootType(root);
    wildcard.setType(ent);
    patternClause.setFirstParam(wildcard);
    patternClause.setSecondParam(wildcard);
    queryObj.addPattern(patternClause);

    Result resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);

    REQUIRE(results.size() == 3);
    REQUIRE(find(results.begin(), results.end(), "1") != results.end());
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    REQUIRE(find(results.begin(), results.end(), "3") != results.end());
}

