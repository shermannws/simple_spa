#include "catch.hpp"
#include "QPS/QPS.h"
#include "PKB/Pkb.h"
#include "QPS/PQLParser.h"

using namespace std;

TEST_CASE("Syntax Errors") {
    SECTION("in declarations") {
        vector<string> queries = {
//        "call c; Select c" // TODO: to uncomment when call is commented
                "assignment a; Select a",
                "stmt s; Select ",
        };

        Pkb pkb = Pkb();
        for (auto query : queries) {
            std::list<std::string> results;
            QPS::evaluate(pkb.createPkbReader(), query, results);
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
            "print p; Select p such that Uses(\"test\",_)", // TODO: TO DELETE ONCE PROCEDURE IS SUPPORTED
            "stmt s; Select s such that Follows(\"hi\", 1)",
            "variable v; Select v such that Follows(v,\"x\")", // SemanticError of v is handled after SyntaxError
        };

        Pkb pkb = Pkb();
        for (auto query : queries) {
            std::list<std::string> results;
            QPS::evaluate(pkb.createPkbReader(), query, results);
            REQUIRE(results.size() == 1);
            REQUIRE(find(results.begin(), results.end(), "SyntaxError") != results.end());
        }
    }

}

TEST_CASE("Semantic Errors") {
    SECTION("in Such That Clause") {
        vector<string> queries = {
                "assign a; Select a such that Uses(_,_)",
                "read r; Select r such that Uses(r,_)",
                "variable v; Select v such that Uses(v,v)",
                "stmt s; Select s such that Follows(1,a)",
                "stmt s; Select s such that Follows*(b,1)",
                "variable v; Select v such that Follows(v,2)",
                "constant c; Select c such that Follows(2,c)",

//        "print p, variable v; Select p such that Modifies(p, v)" // TODO: to uncomment once Modifies is implemented
        };
        Pkb pkb = Pkb();
        for (auto query : queries) {
            std::list<std::string> results;
            QPS::evaluate(pkb.createPkbReader(), query, results);
            REQUIRE(results.size() == 1);
            REQUIRE(find(results.begin(), results.end(), "SemanticError") != results.end());
        }
    }
}
