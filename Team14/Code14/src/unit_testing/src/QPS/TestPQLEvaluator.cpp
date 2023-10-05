#include "QPS/Evaluators/PQLEvaluator.h"
#include "QPS/Parsers/PQLParser.h"

#include <unordered_map>

#include "catch.hpp"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Variable.h"
#include "StubPkbReader.h"


using namespace std;

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

TEST_CASE("Test UsesSuchThatStrategy") {
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

    SECTION ("getUsesTypeIdent") {
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

    SECTION ("getUsesStmt") {
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

    SECTION ("getUsesVar(s)") {
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

    SECTION ("isStmtUsesVar") {
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

    SECTION ("hasUses(s)") {
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

    SECTION ("getUsesProcIdent") {
        PQLParser parser("procedure p; Select p such that Uses(p, \"hello\")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "ProcedureName") != results.end());
    }

    SECTION ("getUsesProc") {
        PQLParser parser("procedure p; Select p such that Uses(p,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION ("getUsesVar(p)") {
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

    SECTION ("isProcUsesVar") {
        PQLParser parser(R"(while w; Select w such that Uses("proc","var"))");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION ("hasUses(p)") {
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

TEST_CASE("Test ModifiesSuchThatStrategy") {
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

    SECTION ("getModifiesTypeIdent") {
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

    SECTION ("getModifiesStmt") {
        PQLParser parser("while w; Select w such that Modifies(w,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "34") != results.end());
    }

    SECTION ("getModifiesVar(s)") {
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

    SECTION ("isStmtModifiesVar") {
        PQLParser parser("while w; Select w such that Modifies(3,\"var\")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION ("hasModifies(s)") {
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

    SECTION ("getModifiesProcIdent") {
        PQLParser parser("procedure p; Select p such that Modifies(p, \"test\")");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "Procedure") != results.end());
    }

    SECTION ("getModifiesProc") {
        PQLParser parser("procedure p; Select p such that Modifies(p,_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 1);
        REQUIRE(find(results.begin(), results.end(), "first") != results.end());
    }

    SECTION ("getModifiesVar(p)") {
        PQLParser parser("stmt s; variable v; Select v such that Modifies(\"proc\",v)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }

    SECTION ("isProcModifiesVar") {
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

    SECTION ("hasModifies(p)") {
        PQLParser parser("assign a; Select a such that Modifies(\"proc\",_)");
        Query queryObj = parser.parse();

        auto stubReader = make_shared<StubPkbReader>();
        PQLEvaluator evaluator = PQLEvaluator(stubReader);
        auto resultObj = evaluator.evaluate(queryObj);
        auto results = evaluator.formatResult(queryObj, resultObj);
        REQUIRE(results.size() == 0);
    }
}

TEST_CASE("Test QPS Flow - Assign With Pattern") {
    PQLEvaluator evaluator = PQLEvaluator(stubPkbReader);

    // build a query for the query "assign a; Select a pattern a(_, _)"
    Query queryObj = Query();
    Synonym assignSyn = "a";
    std::shared_ptr<QueryEntity> assignInQuery = std::make_shared<QueryEntity>(QueryEntityType::Assign, assignSyn);
    queryObj.addDeclaration(assignInQuery);
    queryObj.addSelect(assignInQuery);
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
    queryObj.addPattern(patternClause);

    Result resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);

    REQUIRE(results.size() == 3);
    REQUIRE(find(results.begin(), results.end(), "1") != results.end());
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    REQUIRE(find(results.begin(), results.end(), "3") != results.end());
}

TEST_CASE("pattern a(wildcard , expr-spec)") { //getAssignStmtsByRhs
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

TEST_CASE("pattern a(var_synonym, wildcard)") { //getAllAssignStmtVarPair()
    PQLParser parser("assign a; variable v; Select a pattern a(v, _\"(a-b)+c\"_)");
    Query queryObj = parser.parse();

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(results.size() == 2);
    REQUIRE(find(results.begin(), results.end(), "1") != results.end());
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
}

TEST_CASE("pattern a(var_synonym, expr-spec)") { //getAssignStmtsVarPairByRhs
    PQLParser parser("assign a; variable v; Select v pattern a(v, _\"(a-b)+c\"_)");
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

TEST_CASE("pattern a(char_string , wildcard)") { //getAssignStmtsByLhs
    PQLParser parser("assign a; Select a pattern a(\"x\", _)");
    Query queryObj = parser.parse();

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(results.size() == 1);
    REQUIRE(find(results.begin(), results.end(), "6") != results.end());
}

TEST_CASE("pattern a(char_string , expr-spec)") { //getAssignStmtsByLhsRhs
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

TEST_CASE("pattern, select synonym not in clause ") { //getAssignStmtsByLhsRhs
    PQLParser parser("assign a; variable v; Select v pattern a(\"noneCase\", \"(a-b)\")");
    Query queryObj = parser.parse();

    auto stubReader = make_shared<StubPkbReader>();
    PQLEvaluator evaluator = PQLEvaluator(stubReader);
    auto resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);
    REQUIRE(results.size() == 0);
}


