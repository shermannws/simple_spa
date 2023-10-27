#include <memory>

#include "../../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "PKB/Managers/UsesProcRelationshipManager.h"
#include "catch.hpp"

using namespace std;

TEST_CASE_METHOD(UnitTestFixture, "Test Uses Procedure-Variable Relationship Retrieval") {
    UsesProcRelationshipManager usesProcRelationshipManager = UsesProcRelationshipManager();

    Variable variableX = Variable("x");
    Variable variableY = Variable("y");
    Variable variableZ = Variable("z");

    Procedure procedure1 = Procedure("proc1");
    Procedure procedure2 = Procedure("proc2");
    Procedure procedure3 = Procedure("proc3");
    Procedure procedure4 = Procedure("proc4");
    Procedure procedure5 = Procedure("proc5");

    usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure1),
                                                  std::make_shared<Variable>(variableX));
    usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure2),
                                                  std::make_shared<Variable>(variableY));
    usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure3),
                                                  std::make_shared<Variable>(variableZ));
    usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4),
                                                  std::make_shared<Variable>(variableX));
    usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4),
                                                  std::make_shared<Variable>(variableY));
    usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4),
                                                  std::make_shared<Variable>(variableZ));

    REQUIRE(usesProcRelationshipManager.getRelationshipProcPair().size() == 6);

    REQUIRE(usesProcRelationshipManager.getRelationshipIdent(variableX).size() == 2);
    auto v = usesProcRelationshipManager.getRelationshipIdent(variableX);
    REQUIRE(find(v.begin(), v.end(), procedure1) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure4) != v.end());


    REQUIRE(usesProcRelationshipManager.getRelationshipProc().size() == 4);
    v = usesProcRelationshipManager.getRelationshipProc();
    REQUIRE(find(v.begin(), v.end(), procedure1) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure2) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure3) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure4) != v.end());

    REQUIRE(usesProcRelationshipManager.getRelationshipVar(procedure1).size() == 1);
    v = usesProcRelationshipManager.getRelationshipVar(procedure1);
    REQUIRE(find(v.begin(), v.end(), variableX) != v.end());
    REQUIRE(usesProcRelationshipManager.getRelationshipVar(procedure4).size() == 3);
    v = usesProcRelationshipManager.getRelationshipVar(procedure4);
    REQUIRE(find(v.begin(), v.end(), variableX) != v.end());
    REQUIRE(find(v.begin(), v.end(), variableY) != v.end());
    REQUIRE(find(v.begin(), v.end(), variableZ) != v.end());


    REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableX) == true);
    REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableY) == false);
    REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableZ) == false);
    REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableX) == false);
    REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableY) == true);
    REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableZ) == false);
    REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableX) == false);
    REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableY) == false);
    REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableZ) == true);
    REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableX) == true);
    REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableY) == true);
    REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableZ) == true);

    REQUIRE(usesProcRelationshipManager.hasRelationship(procedure1) == true);
    REQUIRE(usesProcRelationshipManager.hasRelationship(procedure2) == true);
    REQUIRE(usesProcRelationshipManager.hasRelationship(procedure3) == true);
    REQUIRE(usesProcRelationshipManager.hasRelationship(procedure4) == true);
    REQUIRE(usesProcRelationshipManager.hasRelationship(procedure5) == false);
}


TEST_CASE_METHOD(UnitTestFixture, "Test Uses Procedure-Variable Transitive Relationship Calculations") {

    SECTION("Test permutation 1") {
        UsesProcRelationshipManager usesProcRelationshipManager = UsesProcRelationshipManager();
        CallsRelationshipManager callRelationshipManager = CallsRelationshipManager();

        Procedure procedure1 = Procedure("proc1");
        Procedure procedure2 = Procedure("proc2");
        Procedure procedure3 = Procedure("proc3");
        Variable variableX = Variable("x");

        // 1-->2-->3
        callRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure1),
                                                  std::make_shared<Procedure>(procedure2), true);
        callRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure2),
                                                  std::make_shared<Procedure>(procedure3), true);
        callRelationshipManager.calculateTransitiveRelationship();

        usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure3),
                                                      std::make_shared<Variable>(variableX));

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableX) == true);

        usesProcRelationshipManager.calculateProcVarRelationshipForCallers(
                std::make_shared<CallsRelationshipManager>(callRelationshipManager));

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableX) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableX) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableX) == true);
    }

    SECTION("Test permutation 2") {
        UsesProcRelationshipManager usesProcRelationshipManager = UsesProcRelationshipManager();
        CallsRelationshipManager callRelationshipManager = CallsRelationshipManager();

        Procedure procedure1 = Procedure("proc1");
        Procedure procedure2 = Procedure("proc2");
        Procedure procedure3 = Procedure("proc3");
        Procedure procedure4 = Procedure("proc4");
        Procedure procedure5 = Procedure("proc5");
        Variable variableX = Variable("x");
        Variable variableY = Variable("y");
        Variable variableZ = Variable("z");
        Variable variableA = Variable("a");
        Variable variableB = Variable("b");

        // 1 --> 2
        // 3 --> 4
        // 5 --> 1
        callRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure1),
                                                  std::make_shared<Procedure>(procedure2), true);
        callRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure3),
                                                  std::make_shared<Procedure>(procedure4), true);
        callRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure5),
                                                  std::make_shared<Procedure>(procedure1), true);

        usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure1),
                                                      std::make_shared<Variable>(variableX));
        usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure2),
                                                      std::make_shared<Variable>(variableY));
        usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure3),
                                                      std::make_shared<Variable>(variableZ));
        usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4),
                                                      std::make_shared<Variable>(variableA));
        usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure5),
                                                      std::make_shared<Variable>(variableB));

        callRelationshipManager.calculateTransitiveRelationship();

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableX) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableY) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableZ) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableA) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure5, variableB) == true);

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableY) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableA) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableA) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableY) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableA) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableY) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure5, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure5, variableY) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure5, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure5, variableA) == false);

        usesProcRelationshipManager.calculateProcVarRelationshipForCallers(
                std::make_shared<CallsRelationshipManager>(callRelationshipManager));

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableX) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableY) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableZ) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableA) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure5, variableB) == true);

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableY) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableA) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure1, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableA) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure2, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableY) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableA) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure3, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableY) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure4, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isRelationship(procedure5, variableX) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure5, variableY) == true);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure5, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isRelationship(procedure5, variableA) == false);
    }
}