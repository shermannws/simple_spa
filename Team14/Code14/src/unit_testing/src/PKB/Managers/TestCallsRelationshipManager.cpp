#include <memory>

#include "catch.hpp"
#include "PKB/Managers/CallsRelationshipManager.h"

using namespace std;

TEST_CASE("Test Calls Relationship Retrieval") {
    CallsRelationshipManager callsRelationshipManager = CallsRelationshipManager();

    REQUIRE(callsRelationshipManager.hasCalls() == false);

    shared_ptr<Procedure> procedure1 = make_shared<Procedure>(Procedure("First"));
    shared_ptr<Procedure> procedure2 = make_shared<Procedure>(Procedure("Second"));
    shared_ptr<Procedure> procedure3 = make_shared<Procedure>(Procedure("Third"));
    shared_ptr<Procedure> procedure4 = make_shared<Procedure>(Procedure("Four"));

    callsRelationshipManager.storeCallsRelationship(procedure1, procedure2, true);
    callsRelationshipManager.storeCallsRelationship(procedure2, procedure3, true);
    callsRelationshipManager.storeCallsRelationship(procedure1, procedure3, false);
    callsRelationshipManager.storeCallsRelationship(procedure1, procedure4, true);

    REQUIRE(callsRelationshipManager.getCallsPair(true).size() == 3);
    REQUIRE(callsRelationshipManager.getCallsPair(false).size() == 4);
    REQUIRE(callsRelationshipManager.getCallsFormer(*procedure3, true).size() == 1);
    REQUIRE(callsRelationshipManager.getCallsFormer(*procedure3, false).size() == 2);
    REQUIRE(callsRelationshipManager.getCallsFormer().size() == 2);
    REQUIRE(callsRelationshipManager.getCallsLatter(*procedure1, true).size() == 2);
    REQUIRE(callsRelationshipManager.getCallsLatter(*procedure1, false).size() == 3);
    REQUIRE(callsRelationshipManager.getCallsLatter().size() == 3);

    REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure2, true) == true);
    REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure2, false) == true);
    REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure3, true) == false);
    REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure3, false) == true);
    REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure3, false) == true);
    REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure3, true) == true);
    REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure3, false) == false);
    REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure4, true) == true);
    REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure4, false) == true);
    REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure4, false) == false);
    REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure4, false) == false);
    
    REQUIRE(callsRelationshipManager.hasCalls() == true);

    REQUIRE(callsRelationshipManager.hasLatterProc(*procedure1) == true);
    REQUIRE(callsRelationshipManager.hasLatterProc(*procedure2) == true);
    REQUIRE(callsRelationshipManager.hasLatterProc(*procedure3) == false);
    REQUIRE(callsRelationshipManager.hasLatterProc(*procedure4) == false);

    REQUIRE(callsRelationshipManager.hasFormerProc(*procedure1) == false);
    REQUIRE(callsRelationshipManager.hasFormerProc(*procedure2) == true);
    REQUIRE(callsRelationshipManager.hasFormerProc(*procedure3) == true);
    REQUIRE(callsRelationshipManager.hasFormerProc(*procedure4) == true);
}