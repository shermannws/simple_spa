#include "catch.hpp"
#include "PKB/Pkb.h"
#include "QPS/Parsers/PQLParser.h"
#include "QPS/Evaluators/PQLEvaluator.h"

using namespace std;

TEST_CASE("Test integration of PKB with QPS - Variables") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    shared_ptr<Variable> variableX = make_shared<Variable>(Variable("x"));
    shared_ptr<Variable> variableY = make_shared<Variable>(Variable("y"));
    shared_ptr<Variable> variableZ = make_shared<Variable>(Variable("z"));

    pkbWriter->addVariable(variableX);
    pkbWriter->addVariable(variableY);
    pkbWriter->addVariable(variableZ);

    PQLParser parser("variable v; Select v");
    Query queryObj = parser.parse();
    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
    Result resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);

    REQUIRE(results.size() == 3);
    REQUIRE(find(results.begin(), results.end(), "x") != results.end());
    REQUIRE(find(results.begin(), results.end(), "y") != results.end());
    REQUIRE(find(results.begin(), results.end(), "z") != results.end());
}

TEST_CASE("Test integration of PKB with QPS - Get all Constants") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    shared_ptr<Constant> constant1 = make_shared<Constant>(Constant("1"));
    shared_ptr<Constant> constant2 = make_shared<Constant>(Constant("2"));
    shared_ptr<Constant> constant3 = make_shared<Constant>(Constant("3"));

    pkbWriter->addConstant(constant1);
    pkbWriter->addConstant(constant2);
    pkbWriter->addConstant(constant3);

    PQLParser parser("constant c; Select c");
    Query queryObj = parser.parse();
    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
    Result resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);

    REQUIRE(results.size() == 3);
    REQUIRE(find(results.begin(), results.end(), "1") != results.end());
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    REQUIRE(find(results.begin(), results.end(), "3") != results.end());
}

TEST_CASE("Test integration of PKB with QPS - Get all Procedure") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    shared_ptr<Procedure> procedureA = make_shared<Procedure>(Procedure("ProcedureA"));
    shared_ptr<Procedure> procedureB = make_shared<Procedure>(Procedure("ProcedureB"));
    shared_ptr<Procedure> procedureC = make_shared<Procedure>(Procedure("ProcedureC"));

    pkbWriter->addProcedure(procedureA);
    pkbWriter->addProcedure(procedureB);
    pkbWriter->addProcedure(procedureC);

    PQLParser parser("procedure p; Select p");
    Query queryObj = parser.parse();
    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
    Result resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);

    REQUIRE(results.size() == 3);
    REQUIRE(find(results.begin(), results.end(), "ProcedureA") != results.end());
    REQUIRE(find(results.begin(), results.end(), "ProcedureB") != results.end());
    REQUIRE(find(results.begin(), results.end(), "ProcedureC") != results.end());
}

TEST_CASE("Test integration of PKB with QPS - Get all Stmt") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    shared_ptr<Statement> printStatement = make_shared<Statement>(Statement(1, StatementType::Print));
    shared_ptr<Statement> readStatement = make_shared<Statement>(Statement(2, StatementType::Read));
    shared_ptr<Statement> assignStatement = make_shared<Statement>(Statement(3, StatementType::Assign));

    pkbWriter->addPrintStatement(printStatement);
    pkbWriter->addReadStatement(readStatement);
    pkbWriter->addAssignStatement(assignStatement, nullptr, nullptr);

    PQLParser parser("stmt s; Select s");
    Query queryObj = parser.parse();
    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
    Result resultObj = evaluator.evaluate(queryObj);
    auto results = evaluator.formatResult(queryObj, resultObj);

    REQUIRE(results.size() == 3);
    REQUIRE(find(results.begin(), results.end(), "1") != results.end());
    REQUIRE(find(results.begin(), results.end(), "2") != results.end());
    REQUIRE(find(results.begin(), results.end(), "3") != results.end());
}

TEST_CASE("Test integration of PKB with QPS - Follows (1, s)") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    shared_ptr<Statement> assignStatement1 = make_shared<Statement>(Statement(1, StatementType::Stmt));
    shared_ptr<Statement> assignStatement2 = make_shared<Statement>(Statement(2, StatementType::Stmt));
    shared_ptr<Statement> assignStatement3 = make_shared<Statement>(Statement(3, StatementType::Stmt));

    pkbWriter->addFollowsRelationship(assignStatement1, assignStatement2, true);
    pkbWriter->addFollowsRelationship(assignStatement2, assignStatement3, true);

    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());

    PQLParser parser1("stmt s; Select s such that Follows (1, s)");
    Query queryObj1 = parser1.parse();
    Result resultObj1 = evaluator.evaluate(queryObj1);
    auto results1 = evaluator.formatResult(queryObj1, resultObj1);

    PQLParser parser2("stmt s; Select s such that Follows (2, s)");
    Query queryObj2 = parser2.parse();
    Result resultObj2 = evaluator.evaluate(queryObj2);
    auto results2 = evaluator.formatResult(queryObj2, resultObj2);

    PQLParser parser3("stmt s; Select s such that Follows (3, s)");
    Query queryObj3 = parser3.parse();
    Result resultObj3 = evaluator.evaluate(queryObj3);
    auto results3 = evaluator.formatResult(queryObj3, resultObj3);

    REQUIRE(results1.size() == 1);
    REQUIRE(*(results1.begin()) == "2");

    REQUIRE(results2.size() == 1);
    REQUIRE(*(results2.begin()) == "3");

    REQUIRE(results3.empty());
    REQUIRE(results3.begin() == results3.end());
}

TEST_CASE("Test integration of PKB with QPS - Follows (s, 1)") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    shared_ptr<Statement> assignStatement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Statement> assignStatement2 = make_shared<Statement>(Statement(2, StatementType::Assign));
    shared_ptr<Statement> assignStatement3 = make_shared<Statement>(Statement(3, StatementType::Assign));

    pkbWriter->addFollowsRelationship(assignStatement1, assignStatement2, true);
    pkbWriter->addFollowsRelationship(assignStatement2, assignStatement3, true);

    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());

    PQLParser parser1("stmt s; Select s such that Follows (s, 1)");
    Query queryObj1 = parser1.parse();
    Result resultObj1 = evaluator.evaluate(queryObj1);
    auto results1 = evaluator.formatResult(queryObj1, resultObj1);

    PQLParser parser2("stmt s; Select s such that Follows (s, 2)");
    Query queryObj2 = parser2.parse();
    Result resultObj2 = evaluator.evaluate(queryObj2);
    auto results2 = evaluator.formatResult(queryObj2, resultObj2);

    PQLParser parser3("stmt s; Select s such that Follows (s, 3)");
    Query queryObj3 = parser3.parse();
    Result resultObj3 = evaluator.evaluate(queryObj3);
    auto results3 = evaluator.formatResult(queryObj3, resultObj3);

    REQUIRE(results1.empty());
    REQUIRE(results1.begin() == results1.end());

    REQUIRE(results2.size() == 1);
    REQUIRE(*(results2.begin()) == "1");

    REQUIRE(results3.size() == 1);
    REQUIRE(*(results3.begin()) == "2");
}

TEST_CASE("Test integration of PKB with QPS - Follows (1, 2)") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    shared_ptr<Statement> assignStatement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Statement> assignStatement2 = make_shared<Statement>(Statement(2, StatementType::Assign));

    pkbWriter->addAssignStatement(assignStatement1, nullptr, nullptr);
    pkbWriter->addAssignStatement(assignStatement2, nullptr, nullptr);
    pkbWriter->addFollowsRelationship(assignStatement1, assignStatement2, true);
    pkbWriter->addFollowsRelationship(assignStatement1, assignStatement2, true);

    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());

    PQLParser parser1("stmt s; Select s such that Follows (1, 2)");
    Query queryObj1 = parser1.parse();
    Result resultObj1 = evaluator.evaluate(queryObj1);
    auto results1 = evaluator.formatResult(queryObj1, resultObj1);

    PQLParser parser2("stmt s; Select s such that Follows (2, 1)");
    Query queryObj2 = parser2.parse();
    Result resultObj2 = evaluator.evaluate(queryObj2);
    auto results2 = evaluator.formatResult(queryObj2, resultObj2);

    REQUIRE(results1.size() == 2);
    REQUIRE(find(results1.begin(), results1.end(), "1") != results1.end());
    REQUIRE(find(results1.begin(), results1.end(), "2") != results1.end());

    REQUIRE(results2.empty());
}

TEST_CASE("Test integration of PKB with QPS - Uses (a, 'x')") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    shared_ptr<Statement> assignStatement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Variable> variableX = make_shared<Variable>(Variable("x"));
    shared_ptr<Variable> variableY = make_shared<Variable>(Variable("y"));
    shared_ptr<Variable> variableZ = make_shared<Variable>(Variable("z"));
    shared_ptr<string> expression1 = make_shared<string>("y + z");

    shared_ptr<Statement> assignStatement2 = make_shared<Statement>(Statement(2, StatementType::Assign));
    shared_ptr<Variable> variableA = make_shared<Variable>(Variable("a"));
    shared_ptr<Variable> variableB = make_shared<Variable>(Variable("b"));
    shared_ptr<string> expression2 = make_shared<string>("b * y");

    pkbWriter->addUsesRelationship(assignStatement1, variableY);
    pkbWriter->addUsesRelationship(assignStatement1, variableZ);
    pkbWriter->addUsesRelationship(assignStatement2, variableB);
    pkbWriter->addUsesRelationship(assignStatement2, variableY);

    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());

//    PQLParser parser1("assign a; variable v; Select v such that Uses (a, v)");
    PQLParser parser1("assign a; Select a such that Uses (a, \"x\")");
    Query queryObj1 = parser1.parse();
    Result resultObj1 = evaluator.evaluate(queryObj1);
    auto results1 = evaluator.formatResult(queryObj1, resultObj1);

    PQLParser parser2("stmt a; Select a such that Uses (a, \"y\")");
    Query queryObj2 = parser2.parse();
    Result resultObj2 = evaluator.evaluate(queryObj2);
    auto results2 = evaluator.formatResult(queryObj2, resultObj2);

    PQLParser parser3("assign a; Select a such that Uses (a, \"b\")");
    Query queryObj3 = parser3.parse();
    Result resultObj3 = evaluator.evaluate(queryObj3);
    auto results3 = evaluator.formatResult(queryObj3, resultObj3);

    REQUIRE(results1.empty());

    REQUIRE(results2.size() == 2);
    REQUIRE(find(results2.begin(), results2.end(), "1") != results2.end());
    REQUIRE(find(results2.begin(), results2.end(), "2") != results2.end());

    REQUIRE(results3.size() == 1);
    REQUIRE(find(results3.begin(), results3.end(), "2") != results3.end());
}

TEST_CASE("Test integration of PKB with QPS - Uses (a, x)") {
    Pkb pkb = Pkb();
    shared_ptr<PkbWriter> pkbWriter = pkb.createPkbWriter();

    shared_ptr<Statement> assignStatement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Variable> variableX = make_shared<Variable>(Variable("x"));
    shared_ptr<Variable> variableY = make_shared<Variable>(Variable("y"));
    shared_ptr<Variable> variableZ = make_shared<Variable>(Variable("z"));
    shared_ptr<string> expression1 = make_shared<string>("y + z");

    shared_ptr<Statement> assignStatement2 = make_shared<Statement>(Statement(2, StatementType::Assign));
    shared_ptr<Variable> variableA = make_shared<Variable>(Variable("a"));
    shared_ptr<Variable> variableB = make_shared<Variable>(Variable("b"));
    shared_ptr<string> expression2 = make_shared<string>("b * y");

    pkbWriter->addUsesRelationship(assignStatement1, variableY);
    pkbWriter->addUsesRelationship(assignStatement1, variableZ);
    pkbWriter->addUsesRelationship(assignStatement2, variableB);
    pkbWriter->addUsesRelationship(assignStatement2, variableY);

    PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());

    PQLParser parser1("assign a; variable v; Select v such that Uses (a, v)");
    Query queryObj1 = parser1.parse();
    Result resultObj1 = evaluator.evaluate(queryObj1);
    auto results1 = evaluator.formatResult(queryObj1, resultObj1);

    PQLParser parser2("stmt a; variable x; Select a such that Uses (a, x)");
    Query queryObj2 = parser2.parse();
    Result resultObj2 = evaluator.evaluate(queryObj2);
    auto results2 = evaluator.formatResult(queryObj2, resultObj2);

    PQLParser parser3("assign a; variable v; Select a such that Uses (a, v)");
    Query queryObj3 = parser3.parse();
    Result resultObj3 = evaluator.evaluate(queryObj3);
    auto results3 = evaluator.formatResult(queryObj3, resultObj3);

    REQUIRE(results1.size() == 3);
    REQUIRE(results2.size() == 2);
    REQUIRE(results2.size() == 2);

    REQUIRE(find(results1.begin(), results1.end(), "y") != results1.end());
    REQUIRE(find(results1.begin(), results1.end(), "z") != results1.end());
    REQUIRE(find(results1.begin(), results1.end(), "b") != results1.end());

    REQUIRE(find(results2.begin(), results2.end(), "1") != results2.end());
    REQUIRE(find(results2.begin(), results2.end(), "2") != results2.end());

    REQUIRE(find(results3.begin(), results3.end(), "1") != results3.end());
    REQUIRE(find(results3.begin(), results3.end(), "2") != results3.end());
}