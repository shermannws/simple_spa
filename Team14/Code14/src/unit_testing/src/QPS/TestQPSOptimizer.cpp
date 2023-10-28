#include "../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "QPS/Evaluators/PQLEvaluator.h"
#include "QPS/Parsers/PQLParser.h"

#include <unordered_map>

#include "QPS/Clauses/Clause.h"
#include "StubPkbReader.h"
#include "catch.hpp"

using namespace std;

TEST_CASE_METHOD(UnitTestFixture, "Test getGroupScorePairs") {
    SECTION("All boolean clauses -- one group") {
        PQLParser parser(R"(Select BOOLEAN such that Follows(1, 2) and Modifies("proc", "var") with 1 = 3)");
        Query queryObj = parser.parse();
        auto stubReader = make_shared<StubPkbReader>();
        auto pairs = QPSOptimizer::getGroupScorePairs(queryObj);
        pair<unordered_set<shared_ptr<Clause>>, GroupScore> expectedPair(
                {queryObj.getSuchThat()[0], queryObj.getSuchThat()[1], queryObj.getWith()[0]}, tuple(0, 0, 3));
        REQUIRE(pairs.size() == 1);
        REQUIRE(pairs[0] == expectedPair);
    }

    SECTION("All irrelevant clauses to selects, but unconnected -- separate groups") {
        PQLParser parser(
                R"(stmt s1, s2, s3; variable v1, v2; procedure p1, p2; assign a; Select <s1, s2, v1.varName> such that Follows(s3, 2) and Modifies(p1, "var") with v2.varName = p2.procName)");
        Query queryObj = parser.parse();
        auto stubReader = make_shared<StubPkbReader>();
        auto pairs = QPSOptimizer::getGroupScorePairs(queryObj);
        REQUIRE(pairs.size() == 3);
        vector<pair<unordered_set<shared_ptr<Clause>>, GroupScore>> expectedPairs{
                {{queryObj.getSuchThat()[0]}, tuple(0, 1, 1)},
                {{queryObj.getSuchThat()[1]}, tuple(0, 1, 1)},
                {{queryObj.getWith()[0]}, tuple(0, 2, 1)},
        };
        for (auto &expectedPair: expectedPairs) {
            REQUIRE(find(pairs.begin(), pairs.end(), expectedPair) != pairs.end());
        }
    }

    SECTION("Boolean clauses, irrelevant clauses to selects, relevant clauses") {
        PQLParser parser(
                "assign a1, a2, a3; stmt s1, s2, s3; variable v1, v2, v3; Select <s1, s2, v2> such that "
                "Uses(s3,v1) and Modifies(s3, \"x\") and Follows(s1,s2) and Parent(s3,s1) and Uses(s2,v1) such that "
                "Uses(5, \"y\") and Follows(3,4) pattern a1(v2, _\"x+y\"_) such that Parent(a1, a2) with a2.stmt# = "
                "20 such that Modifies (a3,v3) pattern a3(\"z\",_)");
        Query queryObj = parser.parse();
        auto stubReader = make_shared<StubPkbReader>();
        auto pairs = QPSOptimizer::getGroupScorePairs(queryObj);
        REQUIRE(pairs.size() == 4);
        vector<pair<unordered_set<shared_ptr<Clause>>, GroupScore>> expectedPairs{
                {{queryObj.getSuchThat()[5], queryObj.getSuchThat()[6]}, tuple(0, 0, 2)},// Uses(5, "y"), Follows(3,4)
                {{queryObj.getSuchThat()[8], queryObj.getPattern()[1]},
                 tuple(0, 2, 2)},// Modifies(a3,v3), pattern a3("z",_)
                {{queryObj.getSuchThat()[7], queryObj.getPattern()[0], queryObj.getWith()[0]},
                 tuple(1, 3, 3)},// Parent(a1,a2), pattern a1(v2, _"x+y"_), with a2.stmt# = 20
                {{queryObj.getSuchThat()[0], queryObj.getSuchThat()[1], queryObj.getSuchThat()[2],
                  queryObj.getSuchThat()[3], queryObj.getSuchThat()[4]},
                 tuple(2, 4, 5)},// Uses(s3,v1), Modifies(s3, "x"), Follows(s1,s2), Parent(s3,s1), Uses(s2,v1)
        };

        for (auto &expectedPair: expectedPairs) {
            REQUIRE(find(pairs.begin(), pairs.end(), expectedPair) != pairs.end());
        }
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Test sortByScore") {
    PQLParser parser(
            "assign a1, a2, a3; stmt s1, s2, s3; variable v1, v2, v3; Select <s1, s2, v2> such that "
            "Uses(s3,v1) and Modifies(s3, \"x\") and Follows(s1,s2) and Parent(s3,s1) and Uses(s2,v1) such that "
            "Uses(5, \"y\") and Follows(3,4) pattern a1(v2, _\"x+y\"_) such that Parent(a1, a2) with a2.stmt# = "
            "20 such that Modifies (a3,v3) pattern a3(\"z\",_)");
    Query queryObj = parser.parse();
    auto stubReader = make_shared<StubPkbReader>();
    auto pairs = QPSOptimizer::getGroupScorePairs(queryObj);
    priority_queue pq(pairs.begin(), pairs.end(), QPSOptimizer::sortByScore);
    vector<GroupScore> expected{
            std::tuple(0, 0, 2),
            std::tuple(0, 2, 2),
            std::tuple(1, 3, 3),
            std::tuple(2, 4, 5),
    };
    int i = 0;
    while (!pq.empty()) {
        auto pair = pq.top();
        pq.pop();
        REQUIRE(pair.second == expected[i]);
        i++;
    }
}