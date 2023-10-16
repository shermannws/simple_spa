#include "catch.hpp"
#include "PKB/Managers/CFGManager.h"

using namespace std;

TEST_CASE("Test initialising CFGManager") {
    REQUIRE_NOTHROW(CFGManager());
}

TEST_CASE("Test CFGManager Methods") {
    SECTION("Storing new map as the store") {
        CFGManager cfgManager = CFGManager();
        std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>> temp = std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>>();
        temp.insert({ "main" , std::make_shared<CFGNode>(1) });

        REQUIRE_NOTHROW(cfgManager.setCFG(temp));
    }
}
