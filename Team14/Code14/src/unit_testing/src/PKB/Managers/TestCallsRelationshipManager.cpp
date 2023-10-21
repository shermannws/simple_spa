#include <memory>

#include "PKB/Managers/CallsRelationshipManager.h"
#include "catch.hpp"

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


TEST_CASE("Test Calls Transitivity Calculation") {
    SECTION("Calls* Test 1") {
        /**
        1 --> 2
        2 --> 3
        */
        CallsRelationshipManager callsRelationshipManager = CallsRelationshipManager();

        REQUIRE(callsRelationshipManager.hasRelationship() == false);

        shared_ptr<Procedure> procedure1 = make_shared<Procedure>(Procedure("First"));
        shared_ptr<Procedure> procedure2 = make_shared<Procedure>(Procedure("Second"));
        shared_ptr<Procedure> procedure3 = make_shared<Procedure>(Procedure("Third"));

        callsRelationshipManager.storeRelationship(procedure1, procedure2, true);
        callsRelationshipManager.storeRelationship(procedure2, procedure3, true);
        callsRelationshipManager.calculateTransitiveRelationship();

        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure3, false) == true);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure3, false) == true);

        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure2, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure3, false) == false);

        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure2, false) == false);
    }

    SECTION("Calls* Test 2") {
        /**
        1 --> 2
        1 --> 3
        */
        CallsRelationshipManager callsRelationshipManager = CallsRelationshipManager();

        REQUIRE(callsRelationshipManager.hasRelationship() == false);

        shared_ptr<Procedure> procedure1 = make_shared<Procedure>(Procedure("First"));
        shared_ptr<Procedure> procedure2 = make_shared<Procedure>(Procedure("Second"));
        shared_ptr<Procedure> procedure3 = make_shared<Procedure>(Procedure("Third"));

        callsRelationshipManager.storeRelationship(procedure1, procedure2, true);
        callsRelationshipManager.storeRelationship(procedure1, procedure3, true);
        callsRelationshipManager.calculateTransitiveRelationship();

        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure3, false) == true);

        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure3, false) == false);

        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure2, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure3, false) == false);

        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure2, false) == false);
    }

    SECTION("Calls* Test 3") {
        /**
        1 --> 2
        3 --> 4 --> 2
        */
        CallsRelationshipManager callsRelationshipManager = CallsRelationshipManager();

        REQUIRE(callsRelationshipManager.hasRelationship() == false);

        shared_ptr<Procedure> procedure1 = make_shared<Procedure>(Procedure("First"));
        shared_ptr<Procedure> procedure2 = make_shared<Procedure>(Procedure("Second"));
        shared_ptr<Procedure> procedure3 = make_shared<Procedure>(Procedure("Third"));
        shared_ptr<Procedure> procedure4 = make_shared<Procedure>(Procedure("Fourth"));

        callsRelationshipManager.storeRelationship(procedure1, procedure2, true);
        callsRelationshipManager.storeRelationship(procedure3, procedure4, true);
        callsRelationshipManager.storeRelationship(procedure4, procedure2, true);
        callsRelationshipManager.calculateTransitiveRelationship();

        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure4, false) == false);

        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure2, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure4, false) == false);

        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure4, false) == true);

        REQUIRE(callsRelationshipManager.isRelationship(*procedure4, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure4, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure4, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure4, *procedure4, false) == false);
    }

    SECTION("Calls* Test 4") {
        /**
        2 --> 1
        3 --> 4 --> 2
        */
        CallsRelationshipManager callsRelationshipManager = CallsRelationshipManager();

        REQUIRE(callsRelationshipManager.hasRelationship() == false);

        shared_ptr<Procedure> procedure1 = make_shared<Procedure>(Procedure("First"));
        shared_ptr<Procedure> procedure2 = make_shared<Procedure>(Procedure("Second"));
        shared_ptr<Procedure> procedure3 = make_shared<Procedure>(Procedure("Third"));
        shared_ptr<Procedure> procedure4 = make_shared<Procedure>(Procedure("Fourth"));

        callsRelationshipManager.storeRelationship(procedure2, procedure1, true);
        callsRelationshipManager.storeRelationship(procedure3, procedure4, true);
        callsRelationshipManager.storeRelationship(procedure4, procedure2, true);
        callsRelationshipManager.calculateTransitiveRelationship();

        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure1, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure2, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure4, false) == false);

        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure1, false) == true);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure2, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure2, *procedure4, false) == false);

        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure1, false) == true);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure3, *procedure4, false) == true);

        REQUIRE(callsRelationshipManager.isRelationship(*procedure4, *procedure1, false) == true);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure4, *procedure2, false) == true);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure4, *procedure3, false) == false);
        REQUIRE(callsRelationshipManager.isRelationship(*procedure4, *procedure4, false) == false);
    }

    SECTION("Calls* Test 5") {
        /**
        1 -> 2 -> 3 -> 4 -> ....... -> 10
        */
        CallsRelationshipManager callsRelationshipManager = CallsRelationshipManager();

        REQUIRE(callsRelationshipManager.hasRelationship() == false);

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

        callsRelationshipManager.storeRelationship(procedure1, procedure2, true);
        callsRelationshipManager.storeRelationship(procedure2, procedure3, true);
        callsRelationshipManager.storeRelationship(procedure3, procedure4, true);
        callsRelationshipManager.storeRelationship(procedure4, procedure5, true);
        callsRelationshipManager.storeRelationship(procedure5, procedure6, true);
        callsRelationshipManager.storeRelationship(procedure6, procedure7, true);
        callsRelationshipManager.storeRelationship(procedure7, procedure8, true);
        callsRelationshipManager.storeRelationship(procedure8, procedure9, true);
        callsRelationshipManager.storeRelationship(procedure9, procedure10, true);

        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure10, false) == false);

        callsRelationshipManager.calculateTransitiveRelationship();

        REQUIRE(callsRelationshipManager.isRelationship(*procedure1, *procedure10, false) == true);
    }
}