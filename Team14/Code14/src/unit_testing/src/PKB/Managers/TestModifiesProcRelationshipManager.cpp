#include <memory>

#include "PKB/Managers/CallsRelationshipManager.h"
#include "PKB/Managers/ModifiesProcRelationshipManager.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test Modifies Procedure-Variable Relationship Retrieval") {
    ModifiesProcRelationshipManager modifiesProcRelationshipManager = ModifiesProcRelationshipManager();

    Variable variableX = Variable("x");
    Variable variableY = Variable("y");
    Variable variableZ = Variable("z");

    Procedure procedure1 = Procedure("proc1");
    Procedure procedure2 = Procedure("proc2");
    Procedure procedure3 = Procedure("proc3");
    Procedure procedure4 = Procedure("proc4");
    Procedure procedure5 = Procedure("proc5");

    modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure1),
                                                      std::make_shared<Variable>(variableX));
    modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure2),
                                                      std::make_shared<Variable>(variableY));
    modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure3),
                                                      std::make_shared<Variable>(variableZ));
    modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4),
                                                      std::make_shared<Variable>(variableX));
    modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4),
                                                      std::make_shared<Variable>(variableY));
    modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4),
                                                      std::make_shared<Variable>(variableZ));

    REQUIRE(modifiesProcRelationshipManager.getRelationshipProcPair().size() == 6);

    REQUIRE(modifiesProcRelationshipManager.getRelationshipIdent(variableX).size() == 2);
    auto v = modifiesProcRelationshipManager.getRelationshipIdent(variableX);
    REQUIRE(find(v.begin(), v.end(), procedure1) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure4) != v.end());


    REQUIRE(modifiesProcRelationshipManager.getRelationshipProc().size() == 4);
    v = modifiesProcRelationshipManager.getRelationshipProc();
    REQUIRE(find(v.begin(), v.end(), procedure1) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure2) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure3) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure4) != v.end());

    REQUIRE(modifiesProcRelationshipManager.getRelationshipVar(procedure1).size() == 1);
    v = modifiesProcRelationshipManager.getRelationshipVar(procedure1);
    REQUIRE(find(v.begin(), v.end(), variableX) != v.end());
    REQUIRE(modifiesProcRelationshipManager.getRelationshipVar(procedure4).size() == 3);
    v = modifiesProcRelationshipManager.getRelationshipVar(procedure4);
    REQUIRE(find(v.begin(), v.end(), variableX) != v.end());
    REQUIRE(find(v.begin(), v.end(), variableY) != v.end());
    REQUIRE(find(v.begin(), v.end(), variableZ) != v.end());


    REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableX) == true);
    REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableY) == false);
    REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableZ) == false);
    REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableX) == false);
    REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableY) == true);
    REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableZ) == false);
    REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableX) == false);
    REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableY) == false);
    REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableZ) == true);
    REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableX) == true);
    REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableY) == true);
    REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableZ) == true);

    REQUIRE(modifiesProcRelationshipManager.hasRelationship(procedure1) == true);
    REQUIRE(modifiesProcRelationshipManager.hasRelationship(procedure2) == true);
    REQUIRE(modifiesProcRelationshipManager.hasRelationship(procedure3) == true);
    REQUIRE(modifiesProcRelationshipManager.hasRelationship(procedure4) == true);
    REQUIRE(modifiesProcRelationshipManager.hasRelationship(procedure5) == false);
}


TEST_CASE("Test Modifies Procedure-Variable Transitive Relationship Calculations") {

    SECTION("Test permutation 1") {
        ModifiesProcRelationshipManager modifiesProcRelationshipManager = ModifiesProcRelationshipManager();
        CallsRelationshipManager callRelationshipManager = CallsRelationshipManager();

        Procedure procedure1 = Procedure("proc1");
        Procedure procedure2 = Procedure("proc2");
        Procedure procedure3 = Procedure("proc3");
        Variable variableX = Variable("x");

        // 1 --> 2 --> 3
        callRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure1),
                                                  std::make_shared<Procedure>(procedure2), true);
        callRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure2),
                                                  std::make_shared<Procedure>(procedure3), true);
        callRelationshipManager.calculateTransitiveRelationship();

        modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure3),
                                                          std::make_shared<Variable>(variableX));

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableX) == true);

        modifiesProcRelationshipManager.calculateProcVarRelationshipForCallers(
                std::make_shared<CallsRelationshipManager>(callRelationshipManager));

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableX) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableX) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableX) == true);
    }

    SECTION("Test permutation 2") {
        ModifiesProcRelationshipManager modifiesProcRelationshipManager = ModifiesProcRelationshipManager();
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

        // 1 --> 2 --> 3
        // 1 --> 4
        // 5 --> 4
        callRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure1),
                                                  std::make_shared<Procedure>(procedure2), true);
        callRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure2),
                                                  std::make_shared<Procedure>(procedure3), true);
        callRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure1),
                                                  std::make_shared<Procedure>(procedure4), true);
        callRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure5),
                                                  std::make_shared<Procedure>(procedure4), true);

        modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure1),
                                                          std::make_shared<Variable>(variableX));
        modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure2),
                                                          std::make_shared<Variable>(variableY));
        modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure3),
                                                          std::make_shared<Variable>(variableZ));
        modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4),
                                                          std::make_shared<Variable>(variableA));
        modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure5),
                                                          std::make_shared<Variable>(variableB));

        callRelationshipManager.calculateTransitiveRelationship();

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableX) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableY) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableZ) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableA) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure5, variableB) == true);

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableZ) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableA) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableB) == false);

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableZ) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableA) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableB) == false);

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableA) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableB) == false);

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableZ) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableB) == false);

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure5, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure5, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure5, variableZ) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure5, variableA) == false);

        modifiesProcRelationshipManager.calculateProcVarRelationshipForCallers(
                std::make_shared<CallsRelationshipManager>(callRelationshipManager));

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableX) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableY) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableZ) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableA) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure5, variableB) == true);

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableY) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableZ) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableA) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure1, variableB) == false);

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableZ) == true);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableA) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure2, variableB) == false);

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableA) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure3, variableB) == false);

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableZ) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure4, variableB) == false);

        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure5, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure5, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure5, variableZ) == false);
        REQUIRE(modifiesProcRelationshipManager.isRelationship(procedure5, variableA) == true);
    }
}