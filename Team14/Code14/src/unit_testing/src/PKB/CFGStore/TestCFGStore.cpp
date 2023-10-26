#include "../../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "PKB/CFGStore/CFGStore.h"
#include "catch.hpp"

using namespace std;

TEST_CASE_METHOD(UnitTestFixture, "Test initialising CFGStore") { REQUIRE_NOTHROW(CFGStore()); }

TEST_CASE_METHOD(UnitTestFixture, "Test CFGStore Methods") {
    SECTION("Constructor initializes an empty store") {
        CFGStore cfgStore = CFGStore();
        REQUIRE(cfgStore.getBeginIterator() == cfgStore.getEndIterator());
    }

    SECTION("Storing new map as the store") {
        CFGStore cfgStore = CFGStore();
        std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>> temp =
                std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>>();
        temp.insert({"main", std::make_shared<CFGNode>(1)});

        REQUIRE(cfgStore.getBeginIterator() == cfgStore.getEndIterator());

        cfgStore.storeCFGMap(temp);

        REQUIRE(++cfgStore.getBeginIterator() == cfgStore.getEndIterator());
        REQUIRE(cfgStore.getBeginIterator()->first == "main");
        REQUIRE(cfgStore.getBeginIterator()->second->getStatementNumber() == 1);
    }
}
