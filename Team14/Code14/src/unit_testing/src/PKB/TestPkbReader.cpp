#include "catch.hpp"
#include "Pkb/Pkb.h"

using namespace std;

TEST_CASE("Test initialising PKB Reader") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();

    REQUIRE(1 == 1);
}
