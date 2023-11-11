#include "../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "QPS/Evaluators/PQLEvaluator.h"
#include "QPS/Evaluators/ResultHandler.h"

#include <unordered_map>

#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Variable.h"
#include "catch.hpp"

using namespace std;

TEST_CASE_METHOD(UnitTestFixture, "Test Result combiner") {

    SECTION("Test both tuples, should return tuple result") {
        ResultTuple v1{make_shared<Entity>(Statement(1, StatementType::Assign)),
                       make_shared<Entity>(Variable("my_variable"))};
        ResultTuple v2{make_shared<Entity>(Statement(5, StatementType::Stmt)),
                       make_shared<Entity>(Variable("another_variable"))};
        ResultTuple v3{make_shared<Entity>(Statement(7, StatementType::Stmt)),
                       make_shared<Entity>(Variable("third_variable"))};
        ResultType type = ResultType::Tuples;

        std::shared_ptr<Result> r = std::make_shared<Result>();
        r->setType(std::vector<Synonym>{"a", "x"});
        std::unordered_set<ResultTuple> tuples{v1, v2};
        r->setTuples(tuples);

        std::shared_ptr<Result> r1 = std::make_shared<Result>();
        r1->setType(std::vector<Synonym>{"a", "x"});
        std::unordered_set<ResultTuple> tuples1{v1, v2, v3};
        r1->setTuples(tuples1);

        ResultHandler evaluator = ResultHandler();
        std::shared_ptr<Result> final = evaluator.getCombined(r, r1);
        auto finalTuples = final->getTuples();

        REQUIRE(final->getTuples().size() == 2);
        REQUIRE(find(finalTuples.begin(), finalTuples.end(), v1) != finalTuples.end());
        REQUIRE(find(finalTuples.begin(), finalTuples.end(), v2) != finalTuples.end());
    }

    SECTION("Test both tuples with 1 empty Tuples Result, should return false Result") {
        ResultTuple v1{make_shared<Entity>(Statement(1, StatementType::Assign)),
                       make_shared<Entity>(Variable("my_variable"))};
        ResultTuple v2{make_shared<Entity>(Statement(5, StatementType::Assign)),
                       make_shared<Entity>(Variable("another_variable"))};
        ResultTuple v3{make_shared<Entity>(Statement(7, StatementType::Assign)),
                       make_shared<Entity>(Variable("third_variable"))};
        ResultType type = ResultType::Tuples;

        std::shared_ptr<Result> r = std::make_shared<Result>();
        r->setType(std::vector<Synonym>{"a", "x"});
        std::unordered_set<ResultTuple> tuples{v1, v2};
        r->setTuples(tuples);

        std::shared_ptr<Result> r1 = std::make_shared<Result>();
        r1->setType(std::vector<Synonym>{"v"});

        std::shared_ptr<Result> final = ResultHandler::getCombined(r, r1);
        auto finalTuples = final->getTuples();

        REQUIRE(final->getType() == ResultType::Boolean);
        REQUIRE(final->getBoolResult() == false);
    }

    SECTION("FALSE boolean result x tuple result") {
        shared_ptr<Entity> a1 = make_shared<Entity>(Statement(1, StatementType::Assign));
        shared_ptr<Entity> a2 = make_shared<Entity>(Statement(2, StatementType::Assign));
        shared_ptr<Entity> a3 = make_shared<Entity>(Statement(3, StatementType::Assign));

        std::shared_ptr<Result> r = std::make_shared<Result>();
        r->setType(std::vector<Synonym>{});
        r->setBoolResult(false);

        std::shared_ptr<Result> r1 = std::make_shared<Result>();
        r1->setType(std::vector<Synonym>{"b"});
        std::unordered_set<ResultTuple> tuples1{{a1}, {a2}, {a3}};
        r1->setTuples(tuples1);

        std::shared_ptr<Result> final = ResultHandler::getCombined(r, r1);
        auto finalTuples = final->getTuples();

        REQUIRE(final->getTuples().size() == 0);
        REQUIRE(final->getBoolResult() == false);
        REQUIRE(final->getType() == ResultType::Boolean);

        std::shared_ptr<Result> finalAssociative = ResultHandler::getCombined(r1, r);
        REQUIRE(finalAssociative->getBoolResult() == false);
        REQUIRE(finalAssociative->getType() == ResultType::Boolean);
    }

    SECTION("TRUE boolean result x tuple result") {
        shared_ptr<Entity> a1 = make_shared<Entity>(Statement(1, StatementType::Assign));

        std::shared_ptr<Result> r = std::make_shared<Result>();
        r->setType(std::vector<Synonym>{});
        r->setBoolResult(true);

        std::shared_ptr<Result> r1 = std::make_shared<Result>();
        r1->setType(std::vector<Synonym>{"b"});
        std::unordered_set<ResultTuple> tuples1{{a1}};
        r1->setTuples(tuples1);

        std::shared_ptr<Result> final = ResultHandler::getCombined(r, r1);
        auto finalTuples = final->getTuples();

        REQUIRE(final->getTuples().size() == 1);
        REQUIRE(final->getType() == ResultType::Tuples);
        REQUIRE(find(finalTuples.begin(), finalTuples.end(), ResultTuple{a1}) != finalTuples.end());

        std::shared_ptr<Result> finalAssociative = ResultHandler::getCombined(r1, r);
        auto finalAssociativeTuples = final->getTuples();

        REQUIRE(finalAssociative->getTuples().size() == 1);
        REQUIRE(finalAssociative->getType() == ResultType::Tuples);
        REQUIRE(find(finalAssociativeTuples.begin(), finalAssociativeTuples.end(), ResultTuple{a1}) !=
                finalAssociativeTuples.end());
    }

    SECTION("both boolean result") {
        std::shared_ptr<Result> rTrue = std::make_shared<Result>();
        rTrue->setType(std::vector<Synonym>{});
        rTrue->setBoolResult(true);

        std::shared_ptr<Result> rFalse = std::make_shared<Result>();
        rFalse->setType(std::vector<Synonym>{});
        rFalse->setBoolResult(false);

        // TRUE X TRUE
        auto tt = ResultHandler::getCombined(rTrue, rTrue);
        REQUIRE(tt->getBoolResult() == true);
        REQUIRE(tt->getType() == ResultType::Boolean);

        // T x F
        auto tf = ResultHandler::getCombined(rTrue, rFalse);
        REQUIRE(tf->getBoolResult() == false);
        REQUIRE(tf->getType() == ResultType::Boolean);

        // F x F
        auto ff = ResultHandler::getCombined(rFalse, rFalse);
        REQUIRE(ff->getBoolResult() == false);
        REQUIRE(ff->getType() == ResultType::Boolean);

        // F x T
        auto ft = ResultHandler::getCombined(rFalse, rTrue);
        REQUIRE(ft->getBoolResult() == false);
        REQUIRE(ft->getType() == ResultType::Boolean);
    }

    SECTION("one invalid result") {
        ResultType boolType = ResultType::Boolean;
        std::shared_ptr<Result> rTrue = std::make_shared<Result>();
        rTrue->setType(std::vector<Synonym>{});
        rTrue->setBoolResult(true);

        std::shared_ptr<Result> rFalse = std::make_shared<Result>();
        rFalse->setType(std::vector<Synonym>{});
        rFalse->setBoolResult(false);

        ResultTuple v1{make_shared<Entity>(Statement(1, StatementType::Assign)),
                       make_shared<Entity>(Variable("my_variable"))};
        ResultTuple v2{make_shared<Entity>(Statement(5, StatementType::Stmt)),
                       make_shared<Entity>(Variable("another_variable"))};

        std::shared_ptr<Result> rTuple = std::make_shared<Result>();
        rTuple->setType(std::vector<Synonym>{"a", "x"});
        std::unordered_set<ResultTuple> tuples{v1, v2};
        rTuple->setTuples(tuples);

        std::shared_ptr<Result> rInvalid = std::make_shared<Result>();

        // TRUE X INVALID
        auto t = ResultHandler::getCombined(rTrue, rInvalid);
        REQUIRE(t->getBoolResult() == true);
        REQUIRE(t->getType() == ResultType::Boolean);

        // FALSE x INVALID
        auto f = ResultHandler::getCombined(rInvalid, rFalse);
        REQUIRE(f->getBoolResult() == false);
        REQUIRE(f->getType() == ResultType::Boolean);

        // Tuple x INVALID
        auto tup = ResultHandler::getCombined(rInvalid, rTuple);
        REQUIRE(tup->getType() == ResultType::Tuples);
        REQUIRE(tup->getTuples().size() == 2);
        auto finalTuples = tup->getTuples();
        REQUIRE(find(finalTuples.begin(), finalTuples.end(), v1) != finalTuples.end());
        REQUIRE(find(finalTuples.begin(), finalTuples.end(), v2) != finalTuples.end());

        // INVALID x INVALID
        auto i = ResultHandler::getCombined(rInvalid, rInvalid);
        REQUIRE(i->getBoolResult() == false);
        REQUIRE(i->getType() == ResultType::Invalid);
    }
}

TEST_CASE_METHOD(UnitTestFixture, "Test Result::getHeader") {
    SECTION("boolean result") {
        auto results = std::make_shared<Result>(false);
        std::vector<Synonym> header = results->getHeader();
        REQUIRE(header.empty());
    }

    SECTION("tuple result") {
        vector<Synonym> synonyms = {"a", "s", "c"};
        auto results = std::make_shared<Result>(synonyms);
        std::vector<Synonym> header = results->getHeader();
        REQUIRE(header.size() == 3);
        for (const auto &syn: synonyms) { REQUIRE(find(header.begin(), header.end(), syn) != header.end()); }
    }
}