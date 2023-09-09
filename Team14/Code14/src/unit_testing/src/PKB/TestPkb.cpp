#include "catch.hpp"
#include "Pkb/Pkb.h"

using namespace std;

TEST_CASE("Test initialising PKB") {
    Pkb pkb = Pkb();

    REQUIRE(1 == 1);
}