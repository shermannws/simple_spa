#include <memory>

#include "catch.hpp"
#include "PKB/Managers/ModifiesProcRelationshipManager.h"
#include "PKB/Managers/CallsRelationshipManager.h"

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

    modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Variable>(variableX));
    modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure2), std::make_shared<Variable>(variableY));
    modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure3), std::make_shared<Variable>(variableZ));
    modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableX));
    modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableY));
    modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableZ));

    REQUIRE(modifiesProcRelationshipManager.getModifiesProcPair().size() == 6);

    REQUIRE(modifiesProcRelationshipManager.getModifiesProcIdent(variableX).size() == 2);
    auto v = modifiesProcRelationshipManager.getModifiesProcIdent(variableX);
    REQUIRE(find(v.begin(), v.end(), procedure1) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure4) != v.end());


    REQUIRE(modifiesProcRelationshipManager.getModifiesProc().size() == 4);
    v = modifiesProcRelationshipManager.getModifiesProc();
    REQUIRE(find(v.begin(), v.end(), procedure1) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure2) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure3) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure4) != v.end());

    REQUIRE(modifiesProcRelationshipManager.getModifiesProcVar(procedure1).size() == 1);
    v = modifiesProcRelationshipManager.getModifiesProcVar(procedure1);
    REQUIRE(find(v.begin(), v.end(), variableX) != v.end());
    REQUIRE(modifiesProcRelationshipManager.getModifiesProcVar(procedure4).size() == 3);
    v = modifiesProcRelationshipManager.getModifiesProcVar(procedure4);
    REQUIRE(find(v.begin(), v.end(), variableX) != v.end());
    REQUIRE(find(v.begin(), v.end(), variableY) != v.end());
    REQUIRE(find(v.begin(), v.end(), variableZ) != v.end());

    
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableX) == true);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableY) == false);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableZ) == false);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableX) == false);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableY) == true);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableZ) == false);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableX) == false);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableY) == false);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableZ) == true);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableX) == true);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableY) == true);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableZ) == true);

    REQUIRE(modifiesProcRelationshipManager.hasProcModifies(procedure1) == true);
    REQUIRE(modifiesProcRelationshipManager.hasProcModifies(procedure2) == true);
    REQUIRE(modifiesProcRelationshipManager.hasProcModifies(procedure3) == true);
    REQUIRE(modifiesProcRelationshipManager.hasProcModifies(procedure4) == true);
    REQUIRE(modifiesProcRelationshipManager.hasProcModifies(procedure5) == false);
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
        callRelationshipManager.storeCallsRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Procedure>(procedure2), true);
        callRelationshipManager.storeCallsRelationship(std::make_shared<Procedure>(procedure2), std::make_shared<Procedure>(procedure3), true);
        callRelationshipManager.calculateCallsStar();

        modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure3), std::make_shared<Variable>(variableX));

        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableX) == true);

        modifiesProcRelationshipManager.calculateModifiesRelationshipForCallers(std::make_shared<CallsRelationshipManager>(callRelationshipManager));

        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableX) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableX) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableX) == true);
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
        callRelationshipManager.storeCallsRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Procedure>(procedure2), true);
        callRelationshipManager.storeCallsRelationship(std::make_shared<Procedure>(procedure2), std::make_shared<Procedure>(procedure3), true);
        callRelationshipManager.storeCallsRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Procedure>(procedure4), true);
        callRelationshipManager.storeCallsRelationship(std::make_shared<Procedure>(procedure5), std::make_shared<Procedure>(procedure4), true);

        modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Variable>(variableX));
        modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure2), std::make_shared<Variable>(variableY));
        modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure3), std::make_shared<Variable>(variableZ));
        modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableA));
        modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure5), std::make_shared<Variable>(variableB));

        callRelationshipManager.calculateCallsStar();

        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableX) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableY) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableZ) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableA) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure5, variableB) == true);

        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableY) == false);
		REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableZ) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableA) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableB) == false);

		REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableZ) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableA) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableB) == false);

		REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableA) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableB) == false);

		REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableZ) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableB) == false);

		REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure5, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure5, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure5, variableZ) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure5, variableA) == false);

        modifiesProcRelationshipManager.calculateModifiesRelationshipForCallers(std::make_shared<CallsRelationshipManager>(callRelationshipManager));

        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableX) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableY) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableZ) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableA) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure5, variableB) == true);

        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableY) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableZ) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableA) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure1, variableB) == false);

        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableZ) == true);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableA) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure2, variableB) == false);

        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableA) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure3, variableB) == false);

        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableZ) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure4, variableB) == false);

        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure5, variableX) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure5, variableY) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure5, variableZ) == false);
        REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(procedure5, variableA) == true);
    }
}