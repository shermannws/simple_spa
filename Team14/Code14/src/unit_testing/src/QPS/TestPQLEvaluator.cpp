#include "QPS/Evaluators/PQLEvaluator.h"
#include "QPS/Parsers/PQLParser.h"

#include <unordered_map>

#include "catch.hpp"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Variable.h"
#include "PKB/Pkb.h"
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

TEST_CASE("Test integration of PKB with QPS - Get all Assign") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    shared_ptr<Statement> assignStatement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Statement> assignStatement2 = make_shared<Statement>(Statement(2, StatementType::Assign));
    shared_ptr<Statement> assignStatement3 = make_shared<Statement>(Statement(3, StatementType::Assign));

    pkbWriter->addAssignStatement(assignStatement1, nullptr, nullptr);
    pkbWriter->addAssignStatement(assignStatement2, nullptr, nullptr);
    pkbWriter->addAssignStatement(assignStatement3, nullptr, nullptr);

    PQLParser parser("assign a; Select a");
    Query queryObj = parser.parse();
    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
    Result resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);

    REQUIRE(results.size() == 3);
    REQUIRE(find(results.begin(), results.end(), "1") != results.end());
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    REQUIRE(find(results.begin(), results.end(), "3") != results.end());
}

TEST_CASE("Test integration of PKB with QPS - Get all Assign - No Assign") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    PQLParser parser("assign a; Select a");
    Query queryObj = parser.parse();
    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
    Result resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);

    REQUIRE(results.size() == 0);
}

TEST_CASE("Test integration of PKB with QPS - Assign With Pattern") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    shared_ptr<Statement> assignStatement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Statement> assignStatement2 = make_shared<Statement>(Statement(2, StatementType::Assign));
    shared_ptr<Statement> assignStatement3 = make_shared<Statement>(Statement(3, StatementType::Assign));

    pkbWriter->addAssignStatement(assignStatement1, nullptr, nullptr);
    pkbWriter->addAssignStatement(assignStatement2, nullptr, nullptr);
    pkbWriter->addAssignStatement(assignStatement3, nullptr, nullptr);

    PQLParser parser("assign a; Select a pattern a(_, _)");
    Query queryObj = parser.parse();
    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
    Result resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);

    REQUIRE(results.size() == 3);
    REQUIRE(find(results.begin(), results.end(), "1") != results.end());
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    REQUIRE(find(results.begin(), results.end(), "3") != results.end());
}

TEST_CASE("Test integration of PKB with QPS - Assign With Pattern, returns no result") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    shared_ptr<Statement> printStatement1 = make_shared<Statement>(Statement(1, StatementType::Print));
    shared_ptr<Statement> printStatement2 = make_shared<Statement>(Statement(2, StatementType::Print));
    shared_ptr<Statement> printStatement3 = make_shared<Statement>(Statement(3, StatementType::Print));

    pkbWriter->addPrintStatement(printStatement1);
    pkbWriter->addPrintStatement(printStatement2);
    pkbWriter->addPrintStatement(printStatement3);

    PQLParser parser("assign a; Select a pattern a(_, _)");
    Query queryObj = parser.parse();
    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
    Result resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);

    REQUIRE(results.size() == 0);
}

TEST_CASE("Test integration of PKB with QPS - Assign With Pattern, returns no result, no stmts in pkb") {
    Pkb pkb = Pkb();

    PQLParser parser("assign a; Select a pattern a(_, _)");
    Query queryObj = parser.parse();
    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
    Result resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);

    REQUIRE(results.size() == 0);
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


