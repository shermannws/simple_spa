#include "catch.hpp"
#include "PKB/PkbWriter.h"
#include "PKB/Pkb.h"

using namespace std;

TEST_CASE("Test initialising PKB Writer") {
    Pkb pkb = Pkb();
    auto writer = pkb.createPkbWriter();

    REQUIRE(1 == 1);
}