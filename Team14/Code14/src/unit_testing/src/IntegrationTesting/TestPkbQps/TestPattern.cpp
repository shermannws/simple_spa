#include "catch.hpp"
#include "PKB/Pkb.h"
#include "QPS/PQLParser.h"
#include "QPS/PQLEvaluator.h"
#include "StubPkbReader.h"

using namespace std;

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

