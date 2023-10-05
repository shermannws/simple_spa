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


TEST_CASE("Test Calls Transitivity Calculation") {
    SECTION("Calls* Test 1") {
        /**
        1 --> 2
        2 --> 3
        */
        CallsRelationshipManager callsRelationshipManager = CallsRelationshipManager();

        REQUIRE(callsRelationshipManager.hasCalls() == false);

        shared_ptr<Procedure> procedure1 = make_shared<Procedure>(Procedure("First"));
        shared_ptr<Procedure> procedure2 = make_shared<Procedure>(Procedure("Second"));
        shared_ptr<Procedure> procedure3 = make_shared<Procedure>(Procedure("Third"));

        callsRelationshipManager.storeCallsRelationship(procedure1, procedure2, true);
        callsRelationshipManager.storeCallsRelationship(procedure2, procedure3, true);
        callsRelationshipManager.calculateCallsStar();

        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure3, false) == true);
        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure3, false) == true);

        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure2, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure3, false) == false);

        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure2, false) == false);
    }

    SECTION("Calls* Test 2") {
        /**
        1 --> 2
        1 --> 3
        */
        CallsRelationshipManager callsRelationshipManager = CallsRelationshipManager();

        REQUIRE(callsRelationshipManager.hasCalls() == false);

        shared_ptr<Procedure> procedure1 = make_shared<Procedure>(Procedure("First"));
        shared_ptr<Procedure> procedure2 = make_shared<Procedure>(Procedure("Second"));
        shared_ptr<Procedure> procedure3 = make_shared<Procedure>(Procedure("Third"));

        callsRelationshipManager.storeCallsRelationship(procedure1, procedure2, true);
        callsRelationshipManager.storeCallsRelationship(procedure1, procedure3, true);
        callsRelationshipManager.calculateCallsStar();

        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure3, false) == true);

        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure3, false) == false);

        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure2, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure3, false) == false);

        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure2, false) == false);
    }

    SECTION("Calls* Test 3") {
        /**
        1 --> 2
        3 --> 4 --> 2
        */
        CallsRelationshipManager callsRelationshipManager = CallsRelationshipManager();

        REQUIRE(callsRelationshipManager.hasCalls() == false);

        shared_ptr<Procedure> procedure1 = make_shared<Procedure>(Procedure("First"));
        shared_ptr<Procedure> procedure2 = make_shared<Procedure>(Procedure("Second"));
        shared_ptr<Procedure> procedure3 = make_shared<Procedure>(Procedure("Third"));
        shared_ptr<Procedure> procedure4 = make_shared<Procedure>(Procedure("Fourth"));

        callsRelationshipManager.storeCallsRelationship(procedure1, procedure2, true);
        callsRelationshipManager.storeCallsRelationship(procedure3, procedure4, true);
        callsRelationshipManager.storeCallsRelationship(procedure4, procedure2, true);
        callsRelationshipManager.calculateCallsStar();

        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure4, false) == false);

        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure2, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure4, false) == false);

        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure4, false) == true);

        REQUIRE(callsRelationshipManager.isCalls(*procedure4, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure4, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isCalls(*procedure4, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure4, *procedure4, false) == false);
    }

    SECTION("Calls* Test 4") {
        /**
        2 --> 1
        3 --> 4 --> 2
        */
        CallsRelationshipManager callsRelationshipManager = CallsRelationshipManager();

        REQUIRE(callsRelationshipManager.hasCalls() == false);

        shared_ptr<Procedure> procedure1 = make_shared<Procedure>(Procedure("First"));
        shared_ptr<Procedure> procedure2 = make_shared<Procedure>(Procedure("Second"));
        shared_ptr<Procedure> procedure3 = make_shared<Procedure>(Procedure("Third"));
        shared_ptr<Procedure> procedure4 = make_shared<Procedure>(Procedure("Fourth"));

        callsRelationshipManager.storeCallsRelationship(procedure2, procedure1, true);
        callsRelationshipManager.storeCallsRelationship(procedure3, procedure4, true);
        callsRelationshipManager.storeCallsRelationship(procedure4, procedure2, true);
        callsRelationshipManager.calculateCallsStar();

        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure2, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure4, false) == false);

        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure1, false) == true);
        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure2, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure2, *procedure4, false) == false);

        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure1, false) == true);
        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure3, *procedure4, false) == true);

        REQUIRE(callsRelationshipManager.isCalls(*procedure4, *procedure1, false) == true);
        REQUIRE(callsRelationshipManager.isCalls(*procedure4, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isCalls(*procedure4, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isCalls(*procedure4, *procedure4, false) == false);
    }

    SECTION("Calls* Test 5") {
        /**
        1 -> 2 -> 3 -> 4 -> ....... -> 10
        */
        CallsRelationshipManager callsRelationshipManager = CallsRelationshipManager();

        REQUIRE(callsRelationshipManager.hasCalls() == false);

        shared_ptr<Procedure> procedure1 = make_shared<Procedure>(Procedure("First"));
        shared_ptr<Procedure> procedure2 = make_shared<Procedure>(Procedure("Second"));
        shared_ptr<Procedure> procedure3 = make_shared<Procedure>(Procedure("Third"));
        shared_ptr<Procedure> procedure4 = make_shared<Procedure>(Procedure("Fourth"));
        shared_ptr<Procedure> procedure5 = make_shared<Procedure>(Procedure("Fifth"));
        shared_ptr<Procedure> procedure6 = make_shared<Procedure>(Procedure("Sixth"));
        shared_ptr<Procedure> procedure7 = make_shared<Procedure>(Procedure("Seventh"));
        shared_ptr<Procedure> procedure8 = make_shared<Procedure>(Procedure("Eighth"));
        shared_ptr<Procedure> procedure9 = make_shared<Procedure>(Procedure("Ninth"));
        shared_ptr<Procedure> procedure10 = make_shared<Procedure>(Procedure("Tenth"));

        callsRelationshipManager.storeCallsRelationship(procedure1, procedure2, true);
        callsRelationshipManager.storeCallsRelationship(procedure2, procedure3, true);
        callsRelationshipManager.storeCallsRelationship(procedure3, procedure4, true);
        callsRelationshipManager.storeCallsRelationship(procedure4, procedure5, true);
        callsRelationshipManager.storeCallsRelationship(procedure5, procedure6, true);
        callsRelationshipManager.storeCallsRelationship(procedure6, procedure7, true);
        callsRelationshipManager.storeCallsRelationship(procedure7, procedure8, true);
        callsRelationshipManager.storeCallsRelationship(procedure8, procedure9, true);
        callsRelationshipManager.storeCallsRelationship(procedure9, procedure10, true);

        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure10, false) == false);

        callsRelationshipManager.calculateCallsStar();

        REQUIRE(callsRelationshipManager.isCalls(*procedure1, *procedure10, false) == true);
    }
}