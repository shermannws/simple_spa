#include <memory>

#include "catch.hpp"
#include "PKB/Managers/CallsRelationshipManager.h"

using namespace std;

TEST_CASE("Test Calls Relationship Retrieval") {
    CallsRelationshipManager callsRelationshipManager = CallsRelationshipManager();

    REQUIRE(callsRelationshipManager.hasRelationship() == false);

    shared_ptr<Procedure> procedure1 = make_shared<Procedure>(Procedure("First"));
    shared_ptr<Procedure> procedure2 = make_shared<Procedure>(Procedure("Second"));
    shared_ptr<Procedure> procedure3 = make_shared<Procedure>(Procedure("Third"));
    shared_ptr<Procedure> procedure4 = make_shared<Procedure>(Procedure("Four"));

    callsRelationshipManager.storeRelationship(procedure1, procedure2, true);
    callsRelationshipManager.storeRelationship(procedure2, procedure3, true);
    callsRelationshipManager.storeRelationship(procedure1, procedure3, false);
    callsRelationshipManager.storeRelationship(procedure1, procedure4, true);

    REQUIRE(callsRelationshipManager.getRelationshipPair(true).size() == 3);
    REQUIRE(callsRelationshipManager.getRelationshipPair(false).size() == 4);
    REQUIRE(callsRelationshipManager.getRelationshipFormer(*procedure3, true).size() == 1);
    REQUIRE(callsRelationshipManager.getRelationshipFormer(*procedure3, false).size() == 2);
    REQUIRE(callsRelationshipManager.getRelationshipFormer().size() == 2);
    REQUIRE(callsRelationshipManager.getRelationshipLatter(*procedure1, true).size() == 2);
    REQUIRE(callsRelationshipManager.getRelationshipLatter(*procedure1, false).size() == 3);
    REQUIRE(callsRelationshipManager.getRelationshipLatter().size() == 3);

    REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure2, true) == true);
    REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure2, false) == true);
    REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure3, true) == false);
    REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure3, false) == true);
    REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure3, false) == true);
    REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure3, true) == true);
    REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure3, false) == false);
    REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure4, true) == true);
    REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure4, false) == true);
    REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure4, false) == false);
    REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure4, false) == false);
    
    REQUIRE(callsRelationshipManager.hasRelationship() == true);

    REQUIRE(callsRelationshipManager.isFormer(*procedure1) == true);
    REQUIRE(callsRelationshipManager.isFormer(*procedure2) == true);
    REQUIRE(callsRelationshipManager.isFormer(*procedure3) == false);
    REQUIRE(callsRelationshipManager.isFormer(*procedure4) == false);

    REQUIRE(callsRelationshipManager.isLatter(*procedure1) == false);
    REQUIRE(callsRelationshipManager.isLatter(*procedure2) == true);
    REQUIRE(callsRelationshipManager.isLatter(*procedure3) == true);
    REQUIRE(callsRelationshipManager.isLatter(*procedure4) == true);
}