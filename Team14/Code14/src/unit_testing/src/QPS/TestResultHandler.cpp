#include "QPS/Evaluators/PQLEvaluator.h"

#include <unordered_map>

#include "catch.hpp"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Variable.h"

TEST_CASE("Test Result combiner") {

    SECTION("Test both tuples") {
        std::vector<Entity> v1{Statement(1, StatementType::Assign), Variable("my_variable")};
        std::vector<Entity> v2{Statement(5, StatementType::Stmt), Variable("another_variable")};
        std::vector<Entity> v3{Statement(7, StatementType::Stmt), Variable("third_variable")};
        ResultType type = ResultType::Tuples;

        std::shared_ptr<Result> r = std::make_shared<Result>();
        r->setType(std::vector<Synonym>{});
        std::unordered_map<std::string, int> map{{"a", 0},
                                                 {"x", 1}};
        r->setSynIndices(map);
        std::vector<std::vector<Entity>> tuples{v1, v2};
        r->setTuples(tuples);

        std::shared_ptr<Result> r1 =  std::make_shared<Result>();
        r1->setType(std::vector<Synonym> {});
        std::unordered_map<std::string, int> map1{{"a", 0},
                                                  {"x", 1}};
        r1->setSynIndices(map1);
        std::vector<std::vector<Entity>> tuples1{v1, v2, v3};
        r1->setTuples(tuples1);

        ResultHandler evaluator = ResultHandler();
        std::shared_ptr<Result> final = evaluator.getCombined(r, r1);
        auto finalTuples = final->getTuples();

        REQUIRE(final->getTuples().size() == 2);
        REQUIRE(find(finalTuples.begin(), finalTuples.end(), v1) != finalTuples.end());
        REQUIRE(find(finalTuples.begin(), finalTuples.end(), v2) != finalTuples.end());
    }

    SECTION("Test both tuples with 1 empty Tuples Result") {
        std::vector<Entity> v1{Statement(1, StatementType::Assign), Variable("my_variable")};
        std::vector<Entity> v2{Statement(5, StatementType::Stmt), Variable("another_variable")};
        std::vector<Entity> v3{Statement(7, StatementType::Stmt), Variable("third_variable")};
        ResultType type = ResultType::Tuples;

        std::shared_ptr<Result> r = std::make_shared<Result>();
        r->setType(std::vector<Synonym> {"a", "x"});
        std::vector<std::vector<Entity>> tuples{v1, v2};
        r->setTuples(tuples);

        std::shared_ptr<Result> r1 = std::make_shared<Result>();
        r1->setType(std::vector<Synonym> {"v"});

        ResultHandler evaluator = ResultHandler();
        std::shared_ptr<Result> final = evaluator.getCombined(r, r1);
        auto finalTuples = final->getTuples();

        REQUIRE(final->getTuples().empty());
        REQUIRE(final->getSynIndices().size()==3);

    }

    SECTION("FALSE boolean result x tuple result") {
        Entity a1 = Statement(1, StatementType::Assign);
        Entity a2 = Statement(2, StatementType::Assign);
        Entity a3 = Statement(3, StatementType::Assign);

        std::shared_ptr<Result> r = std::make_shared<Result>();
        r->setType(std::vector<Synonym> {});
        r->setBoolResult(false);

        std::shared_ptr<Result> r1 = std::make_shared<Result>();
        r1->setType(std::vector<Synonym> {"b"});
        std::vector<std::vector<Entity>> tuples1{{a1},
                                                 {a2},
                                                 {a3}};
        r1->setTuples(tuples1);

        ResultHandler evaluator = ResultHandler();
        std::shared_ptr<Result> final = evaluator.getCombined(r, r1);
        auto finalTuples = final->getTuples();

        REQUIRE(final->getTuples().size() == 0);
        REQUIRE(final->getBoolResult() == false);
        REQUIRE(final->getType() == ResultType::Boolean);

        std::shared_ptr<Result> finalAssociative = evaluator.getCombined(r1, r);
        REQUIRE(finalAssociative->getBoolResult() == false);
        REQUIRE(finalAssociative->getType() == ResultType::Boolean);
    }

    SECTION("TRUE boolean result x tuple result") {
        Entity a1 = Statement(1, StatementType::Assign);

        std::shared_ptr<Result> r = std::make_shared<Result>();
        r->setType(std::vector<Synonym> {});
        r->setBoolResult(true);

        std::shared_ptr<Result> r1 = std::make_shared<Result>();
        r1->setType(std::vector<Synonym> {"b"});
        std::vector<std::vector<Entity>> tuples1{{a1}};
        r1->setTuples(tuples1);

        ResultHandler evaluator = ResultHandler();
        std::shared_ptr<Result> final = evaluator.getCombined(r, r1);
        auto finalTuples = final->getTuples();

        REQUIRE(final->getTuples().size() == 1);
        REQUIRE(final->getType() == ResultType::Tuples);
        REQUIRE(find(finalTuples.begin(), finalTuples.end(), std::vector<Entity>{a1}) != finalTuples.end());

        std::shared_ptr<Result> finalAssociative = evaluator.getCombined(r1, r);
        auto finalAssociativeTuples = final->getTuples();

        REQUIRE(finalAssociative->getTuples().size() == 1);
        REQUIRE(finalAssociative->getType() == ResultType::Tuples);
        REQUIRE(find(finalAssociativeTuples.begin(), finalAssociativeTuples.end(), std::vector<Entity>{a1}) != finalAssociativeTuples.end());
    }

    SECTION("both boolean result") {
        std::shared_ptr<Result> rTrue = std::make_shared<Result>();
        rTrue->setType(std::vector<Synonym> {});
        rTrue->setBoolResult(true);

        std::shared_ptr<Result> rFalse = std::make_shared<Result>();
        rFalse->setType(std::vector<Synonym> {});
        rFalse->setBoolResult(false);

        ResultHandler evaluator = ResultHandler();

        // TRUE X TRUE
        auto tt = evaluator.getCombined(rTrue, rTrue);
        REQUIRE(tt->getBoolResult() == true);
        REQUIRE(tt->getType() == ResultType::Boolean);

        // T x F
        auto tf = evaluator.getCombined(rTrue, rFalse);
        REQUIRE(tf->getBoolResult() == false);
        REQUIRE(tf->getType() == ResultType::Boolean);

        // F x F
        auto ff = evaluator.getCombined(rFalse, rFalse);
        REQUIRE(ff->getBoolResult() == false);
        REQUIRE(ff->getType() == ResultType::Boolean);

        // F x T
        auto ft = evaluator.getCombined(rFalse, rTrue);
        REQUIRE(ft->getBoolResult() == false);
        REQUIRE(ft->getType() == ResultType::Boolean);
    }

    SECTION("one invalid result") {
        ResultType boolType = ResultType::Boolean;
        std::shared_ptr<Result> rTrue = std::make_shared<Result>();
        rTrue->setType(std::vector<Synonym> {});
        rTrue->setBoolResult(true);

        std::shared_ptr<Result> rFalse = std::make_shared<Result>();
        rFalse->setType(std::vector<Synonym> {});
        rFalse->setBoolResult(false);

        std::vector<Entity> v1{Statement(1, StatementType::Assign), Variable("my_variable")};
        std::vector<Entity> v2{Statement(5, StatementType::Stmt), Variable("another_variable")};
        ResultType tupleType = ResultType::Tuples;

        std::shared_ptr<Result> rTuple = std::make_shared<Result>();
        rTuple->setType(std::vector<Synonym> {});
        std::unordered_map<std::string, int> map{{"a", 0},
                                                 {"x", 1}};
        rTuple->setSynIndices(map);
        std::vector<std::vector<Entity>> tuples{v1, v2};
        rTuple->setTuples(tuples);

        std::shared_ptr<Result> rInvalid = std::make_shared<Result>();

        ResultHandler evaluator = ResultHandler();

        // TRUE X INVALID
        auto t = evaluator.getCombined(rTrue, rInvalid);
        REQUIRE(t->getBoolResult() == true);
        REQUIRE(t->getType() == ResultType::Boolean);

        // FALSE x INVALID
        auto f = evaluator.getCombined(rInvalid, rFalse);
        REQUIRE(f->getBoolResult() == false);
        REQUIRE(f->getType() == ResultType::Boolean);

        // Tuple x INVALID
        auto tup = evaluator.getCombined(rInvalid, rTuple);
        REQUIRE(tup->getType() == ResultType::Tuples);
        REQUIRE(tup->getTuples().size()==2);
        auto finalTuples = tup->getTuples();
        REQUIRE(find(finalTuples.begin(), finalTuples.end(), v1) != finalTuples.end());
        REQUIRE(find(finalTuples.begin(), finalTuples.end(), v2) != finalTuples.end());

        // INVALID x INVALID
        auto i = evaluator.getCombined(rInvalid, rInvalid);
        REQUIRE(i->getBoolResult() == false);
        REQUIRE(i->getType() == ResultType::Invalid);
    }

}
