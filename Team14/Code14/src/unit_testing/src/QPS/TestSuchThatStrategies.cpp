#include "QPS/PQLParser.h"
#include "Pkb/Pkb.h"
#include "QPS/PQLParser.h"
#include "QPS/PQLEvaluator.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test UsesSuchThatStrategy") {
    // LHS is stmtRef
    SECTION("Uses(s,v)") {
        Pkb pkb = Pkb();
        shared_ptr<PkbWriter> writer = pkb.createPkbWriter();

        // TODO: to write into pkb

        PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
        PQLParser parser1("print p; variable v; Select p such that Uses(p, v)");
        Query queryObj1 = parser1.parse();
        Result resultObj1 = evaluator.evaluate(queryObj1);
        auto results1 = evaluator.formatResult(queryObj1, resultObj1);

        PQLParser parser2("if ifs; variable v; Select v such that Uses(ifs, v)");
        Query queryObj2 = parser2.parse();
        Result resultObj2 = evaluator.evaluate(queryObj2);
        auto results2 = evaluator.formatResult(queryObj2, resultObj2);

        // TODO: write require statements

    }

    SECTION("Uses(s,ident)") {
        Pkb pkb = Pkb();
        shared_ptr<PkbWriter> writer = pkb.createPkbWriter();

        // TODO: write into pkb

        PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
        PQLParser parser1("while w; Select w such that Uses(w, \"x\")");
        Query queryObj1 = parser1.parse();
        Result resultObj1 = evaluator.evaluate(queryObj1);
        auto results1 = evaluator.formatResult(queryObj1, resultObj1);

        PQLParser parser2("stmt s; Select s such that Uses(s, \"hello\")");
        Query queryObj2 = parser2.parse();
        Result resultObj2 = evaluator.evaluate(queryObj2);
        auto results2 = evaluator.formatResult(queryObj2, resultObj2);

        // TODO: write require statements
    }

    SECTION("Uses(integer, v)") {
        Pkb pkb = Pkb();
        shared_ptr<PkbWriter> writer = pkb.createPkbWriter();

        // TODO: write into pkb

        PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
        PQLParser parser1("variable v; Select v such that Uses(3, v)");
        Query queryObj1 = parser1.parse();
        Result resultObj1 = evaluator.evaluate(queryObj1);
        auto results1 = evaluator.formatResult(queryObj1, resultObj1);

        PQLParser parser2("variable v; Select v such that Uses(2, v)");
        Query queryObj2 = parser2.parse();
        Result resultObj2 = evaluator.evaluate(queryObj2);
        auto results2 = evaluator.formatResult(queryObj2, resultObj2);

        // TODO: write require statements
    }

    SECTION("Uses(integer, ident)") {
        Pkb pkb = Pkb();
        shared_ptr<PkbWriter> writer = pkb.createPkbWriter();

        // TODO: write into pkb

        PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
        PQLParser parser1("print p; Select p such that Uses(1, \"test\")");
        Query queryObj1 = parser1.parse();
        Result resultObj1 = evaluator.evaluate(queryObj1);
        auto results1 = evaluator.formatResult(queryObj1, resultObj1);

        PQLParser parser2("variable v; Select v such that Uses(4, \"x\")");
        Query queryObj2 = parser2.parse();
        Result resultObj2 = evaluator.evaluate(queryObj2);
        auto results2 = evaluator.formatResult(queryObj2, resultObj2);

        // TODO: write require statements
    }

    SECTION("Uses(s,_)") {
        Pkb pkb = Pkb();
        shared_ptr<PkbWriter> writer = pkb.createPkbWriter();

        // TODO: write into pkb

        PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
        PQLParser parser1("stmt s; Select s such that Uses(s, _)");
        Query queryObj1 = parser1.parse();
        Result resultObj1 = evaluator.evaluate(queryObj1);
        auto results1 = evaluator.formatResult(queryObj1, resultObj1);

        PQLParser parser2("assign v; Select v such that Uses(v,_)");
        Query queryObj2 = parser2.parse();
        Result resultObj2 = evaluator.evaluate(queryObj2);
        auto results2 = evaluator.formatResult(queryObj2, resultObj2);

        // TODO: write require statements
    }


}

TEST_CASE("Test FollowsSuchThatStrategy") {
    // LHS is stmtRef
    SECTION("Follows(s1,s2)") {
        Pkb pkb = Pkb();
        shared_ptr<PkbWriter> writer = pkb.createPkbWriter();

        // TODO: to write into pkb

        PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
        PQLParser parser1("assign a; print p; Select p such that Follows(a, p)");
        Query queryObj1 = parser1.parse();
        Result resultObj1 = evaluator.evaluate(queryObj1);
        auto results1 = evaluator.formatResult(queryObj1, resultObj1);

        PQLParser parser2("read r; if ifs; Select r such that Follows(r, ifs)");
        Query queryObj2 = parser2.parse();
        Result resultObj2 = evaluator.evaluate(queryObj2);
        auto results2 = evaluator.formatResult(queryObj2, resultObj2);

        // TODO: write require statements

    }

    SECTION("Follows(s,integer)") {
        Pkb pkb = Pkb();
        shared_ptr<PkbWriter> writer = pkb.createPkbWriter();

        // TODO: write into pkb

        PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
        PQLParser parser1("while w; Select w such that Follows(w, 2)");
        Query queryObj1 = parser1.parse();
        Result resultObj1 = evaluator.evaluate(queryObj1);
        auto results1 = evaluator.formatResult(queryObj1, resultObj1);

        PQLParser parser2("call c; Select c such that Follows(c, 3)");
        Query queryObj2 = parser2.parse();
        Result resultObj2 = evaluator.evaluate(queryObj2);
        auto results2 = evaluator.formatResult(queryObj2, resultObj2);

        // TODO: write require statements
    }

    SECTION("Follows(s,_)") {
        Pkb pkb = Pkb();
        shared_ptr<PkbWriter> writer = pkb.createPkbWriter();

        // TODO: write into pkb

        PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
        PQLParser parser1("stmt s; Select s such that Follows(s, _)");
        Query queryObj1 = parser1.parse();
        Result resultObj1 = evaluator.evaluate(queryObj1);
        auto results1 = evaluator.formatResult(queryObj1, resultObj1);

        PQLParser parser2("print p; Select p such that Follows(p,_)");
        Query queryObj2 = parser2.parse();
        Result resultObj2 = evaluator.evaluate(queryObj2);
        auto results2 = evaluator.formatResult(queryObj2, resultObj2);

        // TODO: write require statements
    }

    SECTION("Follows(integer,s)") {
        Pkb pkb = Pkb();
        shared_ptr<PkbWriter> writer = pkb.createPkbWriter();

        // TODO: write into pkb

        PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
        PQLParser parser1("read r; Select r such that Follows(1,r)");
        Query queryObj1 = parser1.parse();
        Result resultObj1 = evaluator.evaluate(queryObj1);
        auto results1 = evaluator.formatResult(queryObj1, resultObj1);

        PQLParser parser2("if ifs; Select ifs such that Follows(3, ifs)");
        Query queryObj2 = parser2.parse();
        Result resultObj2 = evaluator.evaluate(queryObj2);
        auto results2 = evaluator.formatResult(queryObj2, resultObj2);

        // TODO: write require statements
    }

    SECTION("Follows(_,s)") {
        Pkb pkb = Pkb();
        shared_ptr<PkbWriter> writer = pkb.createPkbWriter();

        // TODO: write into pkb

        PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
        PQLParser parser1("while w; Select w such that Follows(_,w)");
        Query queryObj1 = parser1.parse();
        Result resultObj1 = evaluator.evaluate(queryObj1);
        auto results1 = evaluator.formatResult(queryObj1, resultObj1);

        PQLParser parser2("call c; Select c such that Follows(_,c)");
        Query queryObj2 = parser2.parse();
        Result resultObj2 = evaluator.evaluate(queryObj2);
        auto results2 = evaluator.formatResult(queryObj2, resultObj2);

        // TODO: write require statements
    }

    SECTION("Follows(integer, integer)") {
        Pkb pkb = Pkb();
        shared_ptr<PkbWriter> writer = pkb.createPkbWriter();

        // TODO: write into pkb

        PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
        PQLParser parser1("stmt s; Select s such that Follows(1,3)");
        Query queryObj1 = parser1.parse();
        Result resultObj1 = evaluator.evaluate(queryObj1);
        auto results1 = evaluator.formatResult(queryObj1, resultObj1);

        PQLParser parser2("constant c; Select c such that Follows(3,4)");
        Query queryObj2 = parser2.parse();
        Result resultObj2 = evaluator.evaluate(queryObj2);
        auto results2 = evaluator.formatResult(queryObj2, resultObj2);

        // TODO: write require statements
    }

    SECTION("Follows(_,_)") {
        Pkb pkb = Pkb();
        shared_ptr<PkbWriter> writer = pkb.createPkbWriter();

        // TODO: write into pkb

        PQLEvaluator evaluator = PQLEvaluator(pkb.createPkbReader());
        PQLParser parser1("assign s; Select s such that Follows(_, _)");
        Query queryObj1 = parser1.parse();
        Result resultObj1 = evaluator.evaluate(queryObj1);
        auto results1 = evaluator.formatResult(queryObj1, resultObj1);

        PQLParser parser2("print v; Select v such that Follows(_,_)");
        Query queryObj2 = parser2.parse();
        Result resultObj2 = evaluator.evaluate(queryObj2);
        auto results2 = evaluator.formatResult(queryObj2, resultObj2);

        // TODO: write require statements
    }
}

