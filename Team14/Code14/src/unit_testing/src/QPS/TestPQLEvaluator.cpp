#include "../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "QPS/Evaluators/PQLEvaluator.h"
#include "QPS/Parsers/PQLParser.h"
#include "QPSTestUtil.h"


#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Variable.h"
#include "StubPkbReader.h"
#include "catch.hpp"
#include <unordered_map>


using namespace std;

std::shared_ptr<StubPkbReader> stubPkbReader = std::make_shared<StubPkbReader>();

TEST_CASE_METHOD(UnitTestFixture, "Test formatResult") {
    // TODO  test BOOLEAN, attrRef, tuplle with attrRef elem
    SECTION("Uses query multiple synonym tuple") {
        PQLParser parser("assign a; variable x; Select <x, a> such that Uses(a, x)");
        Query query = parser.parse();
        ResultType type = ResultType::Tuples;
        Result r = Result();
        r.setType(std::vector<Synonym>{"a", "x"});

        std::vector<Entity> v1{Statement(1, StatementType::Assign), Variable("my_variable")};
        std::vector<Entity> v2{Statement(5, StatementType::Stmt), Variable("another_variable")};

        std::vector<std::vector<Entity>> tuples{v1, v2};
        r.setTuples(tuples);

        PQLEvaluator evaluator = PQLEvaluator(stubPkbReader);

        std::list<std::string> formattedResults = evaluator.formatResult(query, r);

        std::list<std::string> expected{"my_variable", "another_variable"};

        REQUIRE(find(formattedResults.begin(), formattedResults.end(), "my_variable 1") != formattedResults.end());
        REQUIRE(find(formattedResults.begin(), formattedResults.end(), "another_variable 5") != formattedResults.end());
    }

    SECTION("Follows query single tuple") {
        PQLParser parser("stmt s; Select s such that Follows(2,s)");
        Query query = parser.parse();
        ResultType type = ResultType::Tuples;
        Result r = Result();
        r.setType(std::vector<Synonym>{"s"});

        std::vector<Entity> v1{Statement(1, StatementType::Stmt)};
        std::vector<Entity> v2{Statement(2, StatementType::Stmt)};


        std::vector<std::vector<Entity>> tuples{v1, v2};
        r.setTuples(tuples);

        PQLEvaluator evaluator = PQLEvaluator(stubPkbReader);

        std::list<std::string> formattedResults = evaluator.formatResult(query, r);

        std::list<std::string> expected{"1", "2"};
        REQUIRE(find(formattedResults.begin(), formattedResults.end(), "1") != formattedResults.end());
        REQUIRE(find(formattedResults.begin(), formattedResults.end(), "2") != formattedResults.end());
    }

    SECTION("Uses query multiple synonym tuple") {
        PQLParser parser("assign a; variable x; Select <x, a> such that Uses(a, x)");
        Query query = parser.parse();
        ResultType type = ResultType::Tuples;
        Result r = Result();
        r.setType(std::vector<Synonym>{"a", "x"});

        std::vector<Entity> v1{Statement(1, StatementType::Assign), Variable("my_variable")};
        std::vector<Entity> v2{Statement(5, StatementType::Stmt), Variable("another_variable")};

        std::vector<std::vector<Entity>> tuples{v1, v2};
        r.setTuples(tuples);

        PQLEvaluator evaluator = PQLEvaluator(stubPkbReader);

        std::list<std::string> formattedResults = evaluator.formatResult(query, r);

        std::list<std::string> expected{"my_variable", "another_variable"};

        REQUIRE(find(formattedResults.begin(), formattedResults.end(), "my_variable 1") != formattedResults.end());
        REQUIRE(find(formattedResults.begin(), formattedResults.end(), "another_variable 5") != formattedResults.end());
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Test UsesSuchThatStrategy") {
    // USES(STMTREF, ENTREF)
    SECTION("getUsesStmtPair") {
        PQLParser parser("assign a; variable v; Select a such that Uses(a, v)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    }

    SECTION("getUsesTypeIdent") {
        PQLParser parser("if ifs; Select ifs such that Uses(ifs, \"hello\")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "4") != results.end());
        REQUIRE(find(results.begin(), results.end(), "5") != results.end());
    }

    SECTION("getUsesStmt") {
        PQLParser parser("stmt s; Select s such that Uses(s,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
    }

    SECTION("getUsesVar(s)") {
        PQLParser parser("stmt s; variable v; Select v such that Uses(3,v)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "name") != results.end());
        REQUIRE(find(results.begin(), results.end(), "asdfghjkl") != results.end());
    }

    SECTION("isStmtUsesVar") {
        PQLParser parser("while w; Select w such that Uses(3,\"var\")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "10") != results.end());
        REQUIRE(find(results.begin(), results.end(), "13") != results.end());
        REQUIRE(find(results.begin(), results.end(), "15") != results.end());
    }

    SECTION("hasUses(s)") {
        PQLParser parser("assign a; Select a such that Uses(3,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    // USES(ENTREF, ENTREF)
    SECTION("getUsesProcPair") {
        PQLParser parser("procedure p; variable v; Select v such that Uses(p, v)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "hello123") != results.end());
        REQUIRE(find(results.begin(), results.end(), "hello321") != results.end());
    }

    SECTION("getUsesProcIdent") {
        PQLParser parser("procedure p; Select p such that Uses(p, \"hello\")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "ProcedureName") != results.end());
    }

    SECTION("getUsesProc") {
        PQLParser parser("procedure p; Select p such that Uses(p,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION("getUsesVar(p)") {
        PQLParser parser("stmt s; variable v; Select v such that Uses(\"proc\",v)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "proc") != results.end());
        REQUIRE(find(results.begin(), results.end(), "anotherVar") != results.end());
    }

    SECTION("isProcUsesVar") {
        PQLParser parser(R"(while w; Select w such that Uses("proc","var"))");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION("hasUses(p)") {
        PQLParser parser("assign a; Select a such that Uses(\"proc\",_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Test ModifiesSuchThatStrategy") {
    // MODIFIES(STMTREF, ENTREF)
    SECTION("getModifiesStmtPair") {
        PQLParser parser("stmt s; variable v; Select s such that Modifies(s, v)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    }

    SECTION("getModifiesTypeIdent") {
        PQLParser parser("read r; Select r such that Modifies(r, \"hello\")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "14") != results.end());
        REQUIRE(find(results.begin(), results.end(), "15") != results.end());
    }

    SECTION("getModifiesStmt") {
        PQLParser parser("while w; Select w such that Modifies(w,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "34") != results.end());
    }

    SECTION("getModifiesVar(s)") {
        PQLParser parser("variable v; Select v such that Modifies(34,v)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "myVar") != results.end());
        REQUIRE(find(results.begin(), results.end(), "anotherVar") != results.end());
    }

    SECTION("isStmtModifiesVar") {
        PQLParser parser("while w; Select w such that Modifies(3,\"var\")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION("hasModifies(s)") {
        PQLParser parser("assign a; Select a such that Modifies(3,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
    }

    // MODIFIES(ENTREF, ENTREF)
    SECTION("getModifiesProcPair") {
        PQLParser parser("procedure p; variable v; Select p such that Modifies(p, v)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 4);
        REQUIRE(find(results.begin(), results.end(), "first") != results.end());
        REQUIRE(find(results.begin(), results.end(), "second") != results.end());
        REQUIRE(find(results.begin(), results.end(), "third") != results.end());
        REQUIRE(find(results.begin(), results.end(), "fourth") != results.end());
    }

    SECTION("getModifiesProcIdent") {
        PQLParser parser("procedure p; Select p such that Modifies(p, \"test\")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "Procedure") != results.end());
    }

    SECTION("getModifiesProc") {
        PQLParser parser("procedure p; Select p such that Modifies(p,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "first") != results.end());
    }

    SECTION("getModifiesVar(p)") {
        PQLParser parser("stmt s; variable v; Select v such that Modifies(\"proc\",v)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION("isProcModifiesVar") {
        PQLParser parser(R"(stmt s; Select s such that Modifies("proc","var"))");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 5);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
        REQUIRE(find(results.begin(), results.end(), "4") != results.end());
        REQUIRE(find(results.begin(), results.end(), "5") != results.end());
    }

    SECTION("hasModifies(p)") {
        PQLParser parser("assign a; Select a such that Modifies(\"proc\",_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Test NextSuchThatStrategy") {
    // evaluateSynSyn
    SECTION("leftRef == rightRef") {// false
        PQLParser parser("stmt s; Select s such that Next(s,s)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.empty());
    }

    SECTION("getNextPair") {
        PQLParser parser("assign a; read r; Select r such that Next(a, r)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "4") != results.end());
        REQUIRE(find(results.begin(), results.end(), "6") != results.end());
    }

    // evaluateSynAny
    SECTION("getNextTypeStmt") {
        PQLParser parser("stmt s; Select s such that Next(s,14)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "13") != results.end());
    }

    SECTION("getNextTypeWildcard") {
        PQLParser parser("if if; Select if such that Next(if,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "11") != results.end());
    }

    // evaluateAnySyn
    SECTION("getNextStmtType") {
        PQLParser parser("call call; Select call such that Next(23, call)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "24") != results.end());
    }

    SECTION("getNextWildcardType") {
        PQLParser parser("assign assign; Select assign such that Next(_,assign)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "10") != results.end());
        REQUIRE(find(results.begin(), results.end(), "12") != results.end());
        REQUIRE(find(results.begin(), results.end(), "13") != results.end());
    }

    // evaluateBoolean
    SECTION("isNext") {
        PQLParser parser("if if; Select if such that Next(1,2)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "101") != results.end());
        REQUIRE(find(results.begin(), results.end(), "102") != results.end());
    }

    SECTION("hasAfterStmt") {
        PQLParser parser("stmt s; Select s such that Next(1,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION("hasBeforeStmt") {
        PQLParser parser("stmt s; Select s such that Next(_,1)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION("hasNext") {
        PQLParser parser("stmt s; Select s such that Next(_,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 5);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
        REQUIRE(find(results.begin(), results.end(), "4") != results.end());
        REQUIRE(find(results.begin(), results.end(), "5") != results.end());
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Test NextStarSuchThatStrategy") {
    // evaluateSynSyn
    SECTION("leftRef == rightRef, getNextStarSameStmt") {
        PQLParser parser("assign a; Select a such that Next*(a,a)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "102") != results.end());
    }

    SECTION("getNextStarPair") {
        PQLParser parser("read read; if if; Select read such that Next*(read, if)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "11") != results.end());
        REQUIRE(find(results.begin(), results.end(), "21") != results.end());
        REQUIRE(find(results.begin(), results.end(), "31") != results.end());
    }

    // evaluateSynAny
    SECTION("getNextStarTypeStmt") {
        PQLParser parser("stmt s; Select s such that Next*(s,15)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "5") != results.end());
    }

    SECTION("getNextStarTypeWildcard") {
        PQLParser parser("while w; Select w such that Next*(w,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "20") != results.end());
    }

    // evaluateAnySyn
    SECTION("getNextStarStmtType") {
        PQLParser parser("if ifs; Select ifs such that Next*(23, ifs)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "26") != results.end());
    }

    SECTION("getNextStarWildcardType") {
        PQLParser parser("read read; Select read such that Next*(_,read)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "10") != results.end());
        REQUIRE(find(results.begin(), results.end(), "12") != results.end());
        REQUIRE(find(results.begin(), results.end(), "15") != results.end());
    }

    // evaluateBoolean
    SECTION("isNextStar") {
        PQLParser parser("if if; Select if such that Next*(1,2)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION("hasAfterStarStmt") {
        PQLParser parser("stmt s; Select s such that Next*(1,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 5);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
        REQUIRE(find(results.begin(), results.end(), "4") != results.end());
        REQUIRE(find(results.begin(), results.end(), "5") != results.end());
    }

    SECTION("hasBeforeStarStmt") {
        PQLParser parser("stmt s; Select s such that Next*(_,1)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION("hasNextStar") {
        PQLParser parser("read r; Select r such that Next*(_,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 4);
        REQUIRE(find(results.begin(), results.end(), "88") != results.end());
        REQUIRE(find(results.begin(), results.end(), "24") != results.end());
        REQUIRE(find(results.begin(), results.end(), "36") != results.end());
        REQUIRE(find(results.begin(), results.end(), "14") != results.end());
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Test AffectsSuchThatStrategy") {
    // evaluateSynSyn
    SECTION("leftRef == rightRef, getAffectsStarSameStmt") {
        PQLParser parser("assign a; Select a such that Affects(a,a)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "61") != results.end());
    }

    SECTION("getAffectsPair") {
        PQLParser parser("assign a, a1; Select a such that Affects(a, a1)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
        REQUIRE(find(results.begin(), results.end(), "5") != results.end());
    }

    // evaluateSynAny
    SECTION("getAffectsTypeStmt") {
        PQLParser parser("stmt s; Select s such that Affects(s,14)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "7") != results.end());
    }

    SECTION("getAffectsTypeWildcard") {
        PQLParser parser("assign a; Select a such that Affects(a,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "8") != results.end());
    }

    // evaluateAnySyn
    SECTION("getAffectsStmtType") {
        PQLParser parser("assign a; Select a such that Affects(23, a)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "9") != results.end());
    }

    SECTION("getAffectsWildcardType") {
        PQLParser parser("assign assign; Select assign such that Affects(_,assign)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "10") != results.end());
    }

    // evaluateBoolean
    SECTION("isAffects") {
        PQLParser parser("if if; Select if such that Affects(11,12)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "101") != results.end());
        REQUIRE(find(results.begin(), results.end(), "102") != results.end());
    }

    SECTION("hasAfterStmt") {
        PQLParser parser("stmt s; Select s such that Affects(1,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION("hasAffectedStmt") {
        PQLParser parser("stmt s; Select s such that Affects(_,1)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION("hasAffectsStmt") {
        PQLParser parser("stmt s; Select s such that Affects(_,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 5);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
        REQUIRE(find(results.begin(), results.end(), "4") != results.end());
        REQUIRE(find(results.begin(), results.end(), "5") != results.end());
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Test WithStrategy") {
    // evaluateSynSyn
    SECTION("leftRef == rightRef") {
        PQLParser parser("read r; Select r with r.varName = r.varName");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 4);
        REQUIRE(find(results.begin(), results.end(), "88") != results.end());
        REQUIRE(find(results.begin(), results.end(), "24") != results.end());
        REQUIRE(find(results.begin(), results.end(), "36") != results.end());
        REQUIRE(find(results.begin(), results.end(), "14") != results.end());
    }

    SECTION("different synonyms name comparison") {
        PQLParser parser("read r; variable v; Select v with r.varName = v.varName");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 4);
        REQUIRE(find(results.begin(), results.end(), "var24") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var36") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var14") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var88") != results.end());
    }

    SECTION("different synonyms integer comparison") {
        PQLParser parser("call call; constant constant; Select call with call.stmt# = constant.value");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "7") != results.end());
        REQUIRE(find(results.begin(), results.end(), "21") != results.end());
    }

    // evaluateSynAny
    SECTION("SynAny name comparison") {
        PQLParser parser(R"(call call; Select call with call.procName = "Proc3")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "21") != results.end());
        REQUIRE(find(results.begin(), results.end(), "22") != results.end());
    }

    SECTION("SynAny integer comparison") {
        PQLParser parser("if if; Select if with if.stmt# = 100");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.empty());
    }

    // evaluateAnySyn
    SECTION("AnySyn name comparison") {
        PQLParser parser(R"(print print; Select print with "var7" = print.varName)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "7") != results.end());
    }

    SECTION("AnySyn integer comparison") {
        PQLParser parser("constant constant; Select constant with 21 = constant.value");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "21") != results.end());
    }

    // evaluateBoolean
    SECTION("BOOLEAN name comparison") {
        PQLParser parser(R"(procedure procedure; Select procedure with "hello" = "hello")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "proc1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "proc2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "proc3") != results.end());
    }

    SECTION("BOOLEAN integer comparison") {
        PQLParser parser("stmt s; Select s with 21 = 21");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 5);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
        REQUIRE(find(results.begin(), results.end(), "4") != results.end());
        REQUIRE(find(results.begin(), results.end(), "5") != results.end());
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Test QPS Flow - Assign With Pattern") {
    PQLEvaluator evaluator = PQLEvaluator(stubPkbReader);

    // build a query for the query "assign a; Select a pattern a(_, _)"
    Query queryObj = Query();
    Synonym assignSyn = "a";
    std::shared_ptr<QueryEntity> assignInQuery = std::make_shared<QueryEntity>(QueryEntityType::Assign, assignSyn);
    queryObj.addDeclaration(assignInQuery);
    queryObj.addSelect(assignInQuery->getSynonym());
    ExpressionSpec rhs = ExpressionSpec{ExpressionSpecType::Wildcard, ""};
    std::shared_ptr<PatternClause> patternClause = std::make_shared<PatternClause>();
    patternClause->setType(ClauseType::Assign);
    patternClause->setSyn(assignSyn);
    Ref wildcard;
    std::string rep = "_";
    RefType ent = RefType::EntRef;
    RootType root = RootType::Wildcard;
    wildcard.setRep(rep);
    wildcard.setRootType(root);
    wildcard.setType(ent);
    patternClause->setFirstParam(wildcard);
    patternClause->setSecondParam(rhs);
    queryObj.addClause(patternClause);

    Result resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);

    REQUIRE(results.size() == 3);
    REQUIRE(find(results.begin(), results.end(), "1") != results.end());
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    REQUIRE(find(results.begin(), results.end(), "3") != results.end());
}

TEST_CASE_METHOD(UnitTestFixture,
                 "assign pattern a(wildcard , expr-spec)") {// getAssignStmtsByRhs, hasRhsWildCard == false
    PQLParser parser("assign a; Select a pattern a(_, \"x   + y\")");
    Query queryObj = parser.parse();

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(results.size() == 2);
    REQUIRE(find(results.begin(), results.end(), "4") != results.end());
    REQUIRE(find(results.begin(), results.end(), "5") != results.end());
}

TEST_CASE_METHOD(UnitTestFixture,
                 "assign pattern a(wildcard , _expr-spec_)") {// getAssignStmtsByRhs, hasRhsWildCard == true
    PQLParser parser("assign a; Select a pattern a(_, _\"a/(b+c)\"_)");
    Query queryObj = parser.parse();

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(results.size() == 2);
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    REQUIRE(find(results.begin(), results.end(), "3") != results.end());
}

TEST_CASE_METHOD(UnitTestFixture, "assign pattern a(var_synonym, wildcard)") {// getAllAssignStmtVarPair()
    PQLParser parser("assign a; variable v; Select a pattern a(v, _)");
    Query queryObj = parser.parse();

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(results.size() == 2);
    REQUIRE(find(results.begin(), results.end(), "1") != results.end());
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
}

TEST_CASE_METHOD(UnitTestFixture,
                 "assign pattern a(var_synonym, _expr-spec_)") {// getAssignStmtsVarPairByRhs, hasWildCard == true
    PQLParser parser("assign a; variable v; Select a pattern a(v, _\"(a-b)+c\"_)");
    Query queryObj = parser.parse();

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(results.size() == 2);
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    REQUIRE(find(results.begin(), results.end(), "3") != results.end());
}

TEST_CASE_METHOD(UnitTestFixture,
                 "assign pattern a(var_synonym, expr-spec)") {// getAssignStmtsVarPairByRhs, hasWildcard == false
    PQLParser parser("assign a; variable v; Select v pattern a(v, \"a-b*c\")");
    Query queryObj = parser.parse();

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(results.size() == 3);
    REQUIRE(find(results.begin(), results.end(), "var1") != results.end());
    REQUIRE(find(results.begin(), results.end(), "var2") != results.end());
    REQUIRE(find(results.begin(), results.end(), "var3") != results.end());
}

TEST_CASE_METHOD(UnitTestFixture, "assign pattern a(char_string , wildcard)") {// getAssignStmtsByLhs
    PQLParser parser("assign a; Select a pattern a(\"x\", _)");
    Query queryObj = parser.parse();

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(results.size() == 1);
    REQUIRE(find(results.begin(), results.end(), "6") != results.end());
}

TEST_CASE_METHOD(UnitTestFixture,
                 "assign pattern a(char_string , expr-spec)") {// getAssignStmtsByLhsRhs, hasRhsWildcard = true
    PQLParser parser("assign a; Select a pattern a(\"x\", _\"(a-b)\"_)");
    Query queryObj = parser.parse();

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(results.size() == 2);
    REQUIRE(find(results.begin(), results.end(), "100") != results.end());
    REQUIRE(find(results.begin(), results.end(), "100000") != results.end());
}

TEST_CASE_METHOD(UnitTestFixture,
                 "assign pattern, select synonym not in clause ") {// getAssignStmtsByLhsRhs, hasRhsWildcard = false
    PQLParser parser("assign a; variable v; Select v pattern a(\"noneCase\", \"(a-b)\")");
    Query queryObj = parser.parse();

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(results.size() == 0);
}

TEST_CASE_METHOD(UnitTestFixture, "if pattern") {
    SECTION("getAllIf for pattern if(_,_,_)") {
        PQLParser parser("if if; Select if pattern if(_,_,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "101") != results.end());
        REQUIRE(find(results.begin(), results.end(), "102") != results.end());
        REQUIRE(find(results.begin(), results.end(), "103") != results.end());
    }

    SECTION("getAllIfStmtVarPair for pattern if(v,_,_)") {
        PQLParser parser("variable v; if if; Select v pattern if(v,_,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "var2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var3") != results.end());
    }

    SECTION("getAllIfStmtVarPair for pattern if(v,_,_) unrelated synonym in select") {
        PQLParser parser("if ifs; variable v, x; Select x pattern ifs(v, _, _)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 8);
        REQUIRE(find(results.begin(), results.end(), "var1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var5") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var14") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var24") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var36") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var38") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var88") != results.end());
    }


    SECTION("getIfStmtsByVar for pattern if(\"var\",_,_)") {
        PQLParser parser("if if; Select if pattern if(\"ifPatternVar\",_,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
        REQUIRE(find(results.begin(), results.end(), "59") != results.end());
        REQUIRE(find(results.begin(), results.end(), "100") != results.end());
    }
}

TEST_CASE_METHOD(UnitTestFixture, "while pattern") {
    SECTION("getAllWhile for pattern while (_,_)") {
        PQLParser parser("while w; Select w pattern w(_,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "847") != results.end());
    }

    SECTION("getAllWhileStmtVarPair for pattern while(v,_,_)") {
        PQLParser parser("while w; variable v; Select v pattern w(v,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 2);
        REQUIRE(find(results.begin(), results.end(), "var860") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var861") != results.end());
    }

    SECTION("getWhileStmtsByVar for pattern while(\"v\",_,_)") {
        PQLParser parser("while w; Select w pattern w(\"x\",_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "873") != results.end());
    }


    SECTION("getIfStmtsByVar for pattern if(\"var\",_,_)") {
        PQLParser parser("if if; Select if pattern if(\"ifPatternVar\",_,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
        REQUIRE(find(results.begin(), results.end(), "59") != results.end());
        REQUIRE(find(results.begin(), results.end(), "100") != results.end());
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Calls and Calls* clauses") {
    SECTION("boolean results, Calls (_,_)") {
        // Calls(_,_) - hasCalls()
        PQLParser parser("assign a; Select a such that Calls(_,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);// hasCalls return true
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 3);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
    }

    SECTION("boolean result, Calls (_,ident)") {
        // Calls (_, procName) - isCallee(procName)
        PQLParser parser("assign a; Select a such that Calls(_,\"testIdent\")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);// isCallee return false
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION("boolean result, Calls*(ident, _)") {
        // isCallerStar(procName)
        PQLParser parser("constant c; Select c such that Calls*(\"testIdent\",_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);// isCallerStar(procName) return true
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION("boolean result, Calls*(ident, ident)") {
        //  isCallsStar(procName, procName)
        PQLParser parser("stmt s; Select s such that  Calls*(\"testIdent\", \"testIdent2\")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);// isCallsStar(procName, procName) return true
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 5);
        REQUIRE(find(results.begin(), results.end(), "1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "3") != results.end());
        REQUIRE(find(results.begin(), results.end(), "4") != results.end());
        REQUIRE(find(results.begin(), results.end(), "5") != results.end());
    }

    SECTION("Calls(*) pair results") {
        // Calls(p,q) - getCallsPair()
        SECTION("pair results, Calls (p,q)") {
            PQLParser parser("procedure p, q; Select p such that Calls(p,q)");
            Query queryObj = parser.parse();

            auto stubReader = make_shared<StubPkbReader>();
            PQLEvaluator evaluator = PQLEvaluator(stubReader);
            auto resultObj = evaluator.evaluate(queryObj);
            auto results = evaluator.formatResult(queryObj, resultObj);
            REQUIRE(results.size() == 1);
            REQUIRE(find(results.begin(), results.end(), "procedureLHS") != results.end());
        }

        SECTION("pair results, Calls (p,p)") {
            PQLParser parser("procedure p; Select p such that Calls(p,p)");
            Query queryObj = parser.parse();

            auto stubReader = make_shared<StubPkbReader>();
            PQLEvaluator evaluator = PQLEvaluator(stubReader);
            auto resultObj = evaluator.evaluate(queryObj);
            auto results = evaluator.formatResult(queryObj, resultObj);
            REQUIRE(results.size() == 0);
        }

        SECTION("pair results, Calls* (p,p)") {
            PQLParser parser("procedure p; assign a; Select a such that Calls*(p,p)");
            Query queryObj = parser.parse();

            auto stubReader = make_shared<StubPkbReader>();
            PQLEvaluator evaluator = PQLEvaluator(stubReader);
            auto resultObj = evaluator.evaluate(queryObj);
            auto results = evaluator.formatResult(queryObj, resultObj);
            REQUIRE(results.size() == 0);
        }
    }

    SECTION("Calls(*) procedure singles results") {
        // Calls(_, syn) - getCallees() returns non-empty
        SECTION("single results, Calls (_,syn)") {
            PQLParser parser("procedure procedure; Select procedure such that Calls(_,procedure)");
            Query queryObj = parser.parse();

            auto stubReader = make_shared<StubPkbReader>();
            PQLEvaluator evaluator = PQLEvaluator(stubReader);
            auto resultObj = evaluator.evaluate(queryObj);
            auto results = evaluator.formatResult(queryObj, resultObj);
            REQUIRE(results.size() == 2);
            REQUIRE(find(results.begin(), results.end(), "procedure1") != results.end());
            REQUIRE(find(results.begin(), results.end(), "procedure2") != results.end());
        }

        // Calls(syn, procName) -  - getCallers(procName) returns empty
        SECTION("single results, Calls (syn, ident)") {
            PQLParser parser("procedure procedure; stmt s; Select s such that Calls(procedure, \"procName\")");
            Query queryObj = parser.parse();

            auto stubReader = make_shared<StubPkbReader>();
            PQLEvaluator evaluator = PQLEvaluator(stubReader);
            auto resultObj = evaluator.evaluate(queryObj);
            auto results = evaluator.formatResult(queryObj, resultObj);
            REQUIRE(results.size() == 0);
        }

        // Calls*(procName, syn) - getCalleesStar(procName) returns empty
        SECTION("single results, Calls* (ident, syn)") {
            PQLParser parser("procedure procedure; Select procedure such that Calls*(\"procName\",procedure)");
            Query queryObj = parser.parse();

            auto stubReader = make_shared<StubPkbReader>();
            PQLEvaluator evaluator = PQLEvaluator(stubReader);
            auto resultObj = evaluator.evaluate(queryObj);
            auto results = evaluator.formatResult(queryObj, resultObj);
            REQUIRE(results.size() == 0);
        }

        // Calls*(syn, _)  - getCallersStar() returns non-empty
        SECTION("single results, Calls* (syn,_)") {
            PQLParser parser("procedure p; assign a; Select a such that Calls*(p,_)");
            Query queryObj = parser.parse();

            auto stubReader = make_shared<StubPkbReader>();
            PQLEvaluator evaluator = PQLEvaluator(stubReader);
            auto resultObj = evaluator.evaluate(queryObj);
            auto results = evaluator.formatResult(queryObj, resultObj);
            REQUIRE(results.size() == 3);
            REQUIRE(find(results.begin(), results.end(), "1") != results.end());
            REQUIRE(find(results.begin(), results.end(), "2") != results.end());
            REQUIRE(find(results.begin(), results.end(), "3") != results.end());
        }
    }
}

TEST_CASE_METHOD(UnitTestFixture, "multiclause, pattern only - synonym in empty result table") {
    // assign a, a1; variable v; Select a pattern a (v,_"multiclauseTest+patternOnly"_) and a(v1,_)

    auto pc1 = QPSTestUtil::createPatternClause(ClauseType::Assign, "a", RootType::Synonym, "v",
                                                ExpressionSpecType::ExactMatch, "((multiclauseTest)+(patternOnly))");
    auto pc2 = QPSTestUtil::createPatternClause(ClauseType::Assign, "a", RootType::Synonym, "v1",
                                                ExpressionSpecType::Wildcard, "");

    Query queryObj;
    queryObj.addSelect("a");
    queryObj.addClause(pc1);// returns a,v of 1 var1, 1 var2, 2 var3, 3 var4, 4 var3
    queryObj.addClause(pc2);// returns a,v1 of 6 var6
    std::vector<std::shared_ptr<QueryEntity>> decl = {std::make_shared<QueryEntity>(QueryEntityType::Assign, "a"),
                                                      std::make_shared<QueryEntity>(QueryEntityType::Assign, "a1"),
                                                      std::make_shared<QueryEntity>(QueryEntityType::Variable, "v")};
    queryObj.addDeclaration(decl[0]);
    queryObj.addDeclaration(decl[1]);
    queryObj.addDeclaration(decl[2]);

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);// no intersection of v, no a returned
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(resultObj.getType() == ResultType::Boolean);
    REQUIRE(resultObj.getBoolResult() == false);
    REQUIRE(results.size() == 0);
}

TEST_CASE_METHOD(UnitTestFixture, "multiclause, suchThat only - False Result table ") {// syn not involved in clauses
    // assign a, a1; variable v; Select a1 such that Follows*(a,20) and  Parent(1,10) and Uses(1, "x")

    auto sc1 = QPSTestUtil::createSuchThatClause(ClauseType::FollowsStar, RefType::StmtRef, RootType::Synonym,
                                                 QueryEntityType::Assign, "a", RefType::StmtRef, RootType::Integer,
                                                 QueryEntityType::Invalid, "700");
    auto sc2 = QPSTestUtil::createSuchThatClause(ClauseType::Parent, RefType::StmtRef, RootType::Integer,
                                                 QueryEntityType::Invalid, "1", RefType::StmtRef, RootType::Integer,
                                                 QueryEntityType::Invalid, "10");
    auto sc3 = QPSTestUtil::createSuchThatClause(ClauseType::Uses, RefType::StmtRef, RootType::Integer,
                                                 QueryEntityType::Invalid, "1", RefType::EntRef, RootType::Ident,
                                                 QueryEntityType::Variable, "multiClauseSTonly");

    Query queryObj;
    queryObj.addSelect("a1");
    queryObj.addClause(sc1);// returns non-empty
    queryObj.addClause(sc2);// returns  true
    queryObj.addClause(sc3);// returns false
    std::vector<std::shared_ptr<QueryEntity>> decl = {std::make_shared<QueryEntity>(QueryEntityType::Assign, "a"),
                                                      std::make_shared<QueryEntity>(QueryEntityType::Assign, "a1"),
                                                      std::make_shared<QueryEntity>(QueryEntityType::Variable, "v")};
    queryObj.addDeclaration(decl[0]);
    queryObj.addDeclaration(decl[1]);
    queryObj.addDeclaration(decl[2]);

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(resultObj.getType() == ResultType::Boolean);
    REQUIRE(!resultObj.getBoolResult());
    REQUIRE(results.size() == 0);
}

TEST_CASE_METHOD(UnitTestFixture, "multiclause, pattern and suchThat - True Result table ") {
    // assign a1; Select a1 such that Parent(1,10) and Uses(1, "multiclauseTrue")

    auto sc2 = QPSTestUtil::createSuchThatClause(ClauseType::Parent, RefType::StmtRef, RootType::Integer,
                                                 QueryEntityType::Invalid, "1", RefType::StmtRef, RootType::Integer,
                                                 QueryEntityType::Invalid, "10");
    auto sc3 = QPSTestUtil::createSuchThatClause(ClauseType::Uses, RefType::StmtRef, RootType::Integer,
                                                 QueryEntityType::Invalid, "1", RefType::EntRef, RootType::Ident,
                                                 QueryEntityType::Variable, "multiClauseTrue");

    Query queryObj;
    queryObj.addSelect("a1");
    queryObj.addClause(sc2);// returns  true
    queryObj.addClause(sc3);// returns true
    std::vector<std::shared_ptr<QueryEntity>> decl = {
            std::make_shared<QueryEntity>(QueryEntityType::Assign, "a1"),
    };
    queryObj.addDeclaration(decl[0]);
    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(resultObj.getType() == ResultType::Tuples);
    REQUIRE(resultObj.getSynIndices()["a1"] == 0);
    REQUIRE(resultObj.getTuples().size() == 3);
    REQUIRE(results.size() == 3);
    REQUIRE(find(results.begin(), results.end(), "1") != results.end());
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    REQUIRE(find(results.begin(), results.end(), "3") != results.end());
}

TEST_CASE_METHOD(UnitTestFixture, "multiclause, pattern and suchThat - synonym in tuple result table") {
    // assign a, a1; variable v; Select a such that Follows*(a,20) pattern a (v,_"1+multiclauseTest"_) and a1(v,_) such
    // that Parent(1,10)

    auto pc1 = QPSTestUtil::createPatternClause(ClauseType::Assign, "a", RootType::Synonym, "v",
                                                ExpressionSpecType::PartialMatch, "((1)+(multiclauseTest))");
    auto pc2 = QPSTestUtil::createPatternClause(ClauseType::Assign, "a1", RootType::Synonym, "v",
                                                ExpressionSpecType::Wildcard, "");
    auto sc2 = QPSTestUtil::createSuchThatClause(ClauseType::Parent, RefType::StmtRef, RootType::Integer,
                                                 QueryEntityType::Invalid, "1", RefType::StmtRef, RootType::Integer,
                                                 QueryEntityType::Invalid, "10");

    Query queryObj;
    queryObj.addSelect("a");
    queryObj.addClause(pc1);// returns a,v of 1 var1, 1 var2, 2 var3, 3 var4, 4 var3
    queryObj.addClause(pc2);// returns a1,v of 1 var1, 1 var2, 2 var3
    queryObj.addClause(sc2);// returns  true
    std::vector<std::shared_ptr<QueryEntity>> decl = {std::make_shared<QueryEntity>(QueryEntityType::Assign, "a"),
                                                      std::make_shared<QueryEntity>(QueryEntityType::Assign, "a1"),
                                                      std::make_shared<QueryEntity>(QueryEntityType::Variable, "v")};
    queryObj.addDeclaration(decl[0]);
    queryObj.addDeclaration(decl[1]);
    queryObj.addDeclaration(decl[2]);

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(results.size() == 3);
    REQUIRE(find(results.begin(), results.end(), "1") != results.end());
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    REQUIRE(find(results.begin(), results.end(), "4") != results.end());
}

TEST_CASE_METHOD(UnitTestFixture, "multiclause, pattern and suchThat - synonym not in tuple result table") {
    // assign a, a1; variable v; constant c; Select c such that pattern a (v,_"1+multiclauseTest"_) and
    // a(v,_) such that Parent(1,10)

    auto pc1 = QPSTestUtil::createPatternClause(ClauseType::Assign, "a", RootType::Synonym, "v",
                                                ExpressionSpecType::PartialMatch, "((1)+(multiclauseTest))");
    auto pc2 = QPSTestUtil::createPatternClause(ClauseType::Assign, "a1", RootType::Synonym, "v",
                                                ExpressionSpecType::Wildcard, "");
    auto sc2 = QPSTestUtil::createSuchThatClause(ClauseType::Parent, RefType::StmtRef, RootType::Integer,
                                                 QueryEntityType::Invalid, "1", RefType::StmtRef, RootType::Integer,
                                                 QueryEntityType::Invalid, "10");

    Query queryObj;
    queryObj.addSelect("c");
    queryObj.addClause(pc1);// returns a,v of 1 var1, 1 var2, 2 var3, 3 var4, 4 var3
    queryObj.addClause(pc2);// returns a1,v of 1 var1, 1 var2, 2 var3
    queryObj.addClause(sc2);// returns  true
    std::vector<std::shared_ptr<QueryEntity>> decl = {std::make_shared<QueryEntity>(QueryEntityType::Assign, "a"),
                                                      std::make_shared<QueryEntity>(QueryEntityType::Assign, "a1"),
                                                      std::make_shared<QueryEntity>(QueryEntityType::Variable, "v"),
                                                      std::make_shared<QueryEntity>(QueryEntityType::Constant, "c")};
    queryObj.addDeclaration(decl[0]);
    queryObj.addDeclaration(decl[1]);
    queryObj.addDeclaration(decl[2]);
    queryObj.addDeclaration(decl[3]);

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(resultObj.getType() == ResultType::Tuples);
    REQUIRE(results.size() == 4);
}

TEST_CASE_METHOD(UnitTestFixture, "boolean result clause query") {
    SECTION("no constraint clauses") {
        PQLParser parser("Select BOOLEAN");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(resultObj.getBoolResult() == true);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "TRUE") != results.end());
    }

    SECTION("false constraint clauses") {
        PQLParser parser("stmt s1, s2; Select BOOLEAN such that Parent*(s1,s2)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(resultObj.getBoolResult() == false);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "FALSE") != results.end());
    }

    SECTION("non empty result of constraint clauses") {
        PQLParser parser("assign a; Select BOOLEAN pattern a(_,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(resultObj.getTuples().empty());
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "TRUE") != results.end());
    }
}

TEST_CASE_METHOD(UnitTestFixture, "tuple result-clause query") {
    SECTION("no constraint clauses") {
        PQLParser parser("read re; if i; Select <i, re>");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(resultObj.getTuples().size() == 8);
        REQUIRE(find(results.begin(), results.end(), "101 88") != results.end());
        REQUIRE(find(results.begin(), results.end(), "101 24") != results.end());
        REQUIRE(find(results.begin(), results.end(), "101 36") != results.end());
        REQUIRE(find(results.begin(), results.end(), "101 14") != results.end());
        REQUIRE(find(results.begin(), results.end(), "102 88") != results.end());
        REQUIRE(find(results.begin(), results.end(), "102 24") != results.end());
        REQUIRE(find(results.begin(), results.end(), "102 36") != results.end());
        REQUIRE(find(results.begin(), results.end(), "102 14") != results.end());
    }

    SECTION("empty result table (false)") {
        PQLParser parser("read re; if i; constant c; Select <i, re, c.value> with c.value = 1");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.empty());
    }

    SECTION("duplicate synonym in tuple") {
        PQLParser parser("read re; Select <re, re>");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 4);
        REQUIRE(find(results.begin(), results.end(), "88 88") != results.end());
        REQUIRE(find(results.begin(), results.end(), "24 24") != results.end());
        REQUIRE(find(results.begin(), results.end(), "36 36") != results.end());
        REQUIRE(find(results.begin(), results.end(), "14 14") != results.end());
    }
}


TEST_CASE_METHOD(UnitTestFixture, "attrRef result-clause query") {
    SECTION("single attrRef,no constraint clauses") {
        PQLParser parser("read re; Select re.varName");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(resultObj.getTuples().size() == 4);
        REQUIRE(find(results.begin(), results.end(), "var88") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var24") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var36") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var14") != results.end());
    }

    SECTION("multiple attrRef in tuple with 1 clause") {
        PQLParser parser("read re; call c; variable v; Select <re.varName, c.procName> such that Uses(c, v)");// or c,v
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 8);
        REQUIRE(find(results.begin(), results.end(), "var88 proc1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var24 proc1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var36 proc1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var14 proc1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var88 proc2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var24 proc2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var36 proc2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var14 proc2") != results.end());
    }

    SECTION("multiple attrRef and synonym in tuple, with constraint clause") {
        PQLParser parser("read re; call c; variable v; Select <re.varName, c.procName,v> such that Uses(c, v)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 8);
        REQUIRE(find(results.begin(), results.end(), "var88 proc1 var1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var24 proc1 var1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var36 proc1 var1") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var14 proc1 var1") != results.end());

        REQUIRE(find(results.begin(), results.end(), "var88 proc2 var2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var24 proc2 var2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var36 proc2 var2") != results.end());
        REQUIRE(find(results.begin(), results.end(), "var14 proc2 var2") != results.end());
    }

    SECTION("duplicate attr ref in tuple") {
        PQLParser parser("read re; Select <re, re.varName, re.varName>");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 4);
        REQUIRE(find(results.begin(), results.end(), "88 var88 var88") != results.end());
        REQUIRE(find(results.begin(), results.end(), "24 var24 var24") != results.end());
        REQUIRE(find(results.begin(), results.end(), "36 var36 var36") != results.end());
        REQUIRE(find(results.begin(), results.end(), "14 var14 var14") != results.end());
    }
}
