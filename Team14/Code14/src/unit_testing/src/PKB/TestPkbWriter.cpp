#include "catch.hpp"
#include "PKB/PkbWriter.h"
#include "PKB/Pkb.h"

using namespace std;

TEST_CASE("Test initialising PKB Writer") {
    Pkb pkb = Pkb();
    auto writer = pkb.createPkbWriter();

    REQUIRE(1 == 1);
}

TEST_CASE("Test set new map as CFGStore through Writer") {
    Pkb pkb = Pkb();
    auto writer = pkb.createPkbWriter();

    std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>> temp = std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>>();

    temp.insert({ "main" , std::make_shared<CFGNode>(1) });

    REQUIRE_NOTHROW(writer->setCFGMap(temp));
}
