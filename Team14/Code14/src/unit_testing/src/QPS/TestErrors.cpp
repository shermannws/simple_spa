#include "PKB/Pkb.h"
#include "QPS/Parsers/PQLParser.h"
#include "QPS/QPS.h"
#include "catch.hpp"

using namespace std;

Pkb pkb = Pkb();
QPS qps = QPS(pkb.createPkbReader());

TEST_CASE("Syntax Errors") {
    SECTION("in declarations") {
        vector<string> queries = {
                "assignment a; Select a",
                "stmt s; Select ",
        };

        for (auto query: queries) {
            std::list<std::string> results;
            qps.evaluate(query, results);
            REQUIRE(results.size() == 1);
            REQUIRE(find(results.begin(), results.end(), "SyntaxError") != results.end());
        }
    }

    SECTION("in Such That Clause") {
        vector<string> queries = {
                "assign a; Select a such that Us",
                "assign a; Select a such that Follows(",
                "assign a; Select a such that Parent(a _)",
                "assign a; Select a such that Parent*(a, )",
                "assign a; Select a such that Parent*(a, 1",
                "stmt s; Select s such that Follows(\"hi\", 1)",
                "variable v; Select v such that Follows(v,\"x\")",// SemanticError of v is handled after SyntaxError
        };

        for (auto query: queries) {
            std::list<std::string> results;
            qps.evaluate(query, results);
            REQUIRE(results.size() == 1);
            REQUIRE(find(results.begin(), results.end(), "SyntaxError") != results.end());
        }
    }
}

TEST_CASE("Semantic Errors") {
    SECTION("in Such That Clause") {
        vector<string> queries = {
                "assign a; Select a such that Uses(_,_)",      "variable v; Select v such that Uses(v,v)",
                "stmt s; Select s such that Follows(1,a)",     "stmt s; Select s such that Follows*(b,1)",
                "variable v; Select v such that Follows(v,2)", "constant c; Select c such that Follows(2,c)",

        };
        for (auto query: queries) {
            std::list<std::string> results;
            qps.evaluate(query, results);
            REQUIRE(results.size() == 1);
            REQUIRE(find(results.begin(), results.end(), "SemanticError") != results.end());
        }
    }
}
