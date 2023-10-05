#include <memory>

#include "catch.hpp"
#include "PKB/Managers/UsesProcRelationshipManager.h"

using namespace std;

TEST_CASE("Test Uses Procedure-Variable Relationship Retrieval") {
    UsesProcRelationshipManager usesProcRelationshipManager = UsesProcRelationshipManager();

    Variable variableX = Variable("x");
    Variable variableY = Variable("y");
    Variable variableZ = Variable("z");

    Procedure procedure1 = Procedure("proc1");
    Procedure procedure2 = Procedure("proc2");
    Procedure procedure3 = Procedure("proc3");
    Procedure procedure4 = Procedure("proc4");
    Procedure procedure5 = Procedure("proc5");

    usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Variable>(variableX));
    usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure2), std::make_shared<Variable>(variableY));
    usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure3), std::make_shared<Variable>(variableZ));
    usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableX));
    usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableY));
    usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableZ));

    REQUIRE(usesProcRelationshipManager.getUsesProcPair().size() == 6);

    REQUIRE(usesProcRelationshipManager.getUsesProcIdent(variableX).size() == 2);
    auto v = usesProcRelationshipManager.getUsesProcIdent(variableX);
    REQUIRE(find(v.begin(), v.end(), procedure1) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure4) != v.end());


    REQUIRE(usesProcRelationshipManager.getUsesProc().size() == 4);
    v = usesProcRelationshipManager.getUsesProc();
    REQUIRE(find(v.begin(), v.end(), procedure1) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure2) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure3) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure4) != v.end());

    REQUIRE(usesProcRelationshipManager.getUsesProcVar(procedure1).size() == 1);
    v = usesProcRelationshipManager.getUsesProcVar(procedure1);
    REQUIRE(find(v.begin(), v.end(), variableX) != v.end());
    REQUIRE(usesProcRelationshipManager.getUsesProcVar(procedure4).size() == 3);
    v = usesProcRelationshipManager.getUsesProcVar(procedure4);
    REQUIRE(find(v.begin(), v.end(), variableX) != v.end());
    REQUIRE(find(v.begin(), v.end(), variableY) != v.end());
    REQUIRE(find(v.begin(), v.end(), variableZ) != v.end());


    REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableX) == true);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableY) == false);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableZ) == false);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableX) == false);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableY) == true);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableZ) == false);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableX) == false);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableY) == false);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableZ) == true);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableX) == true);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableY) == true);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableZ) == true);

    REQUIRE(usesProcRelationshipManager.hasProcUses(procedure1) == true);
    REQUIRE(usesProcRelationshipManager.hasProcUses(procedure2) == true);
    REQUIRE(usesProcRelationshipManager.hasProcUses(procedure3) == true);
    REQUIRE(usesProcRelationshipManager.hasProcUses(procedure4) == true);
    REQUIRE(usesProcRelationshipManager.hasProcUses(procedure5) == false);
}


TEST_CASE("Test Uses Procedure-Variable Transitive Relationship Calculations") {

    SECTION("Test permutation 1") {
        UsesProcRelationshipManager usesProcRelationshipManager = UsesProcRelationshipManager();
        CallsRelationshipManager callRelationshipManager = CallsRelationshipManager();

        Procedure procedure1 = Procedure("proc1");
        Procedure procedure2 = Procedure("proc2");
        Procedure procedure3 = Procedure("proc3");
        Variable variableX = Variable("x");

        callRelationshipManager.storeCallsRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Procedure>(procedure2), false);
        callRelationshipManager.storeCallsRelationship(std::make_shared<Procedure>(procedure2), std::make_shared<Procedure>(procedure3), false);

        usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure3), std::make_shared<Variable>(variableX));

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableX) == true);

        usesProcRelationshipManager.calculateUsesRelationshipForCallers(std::make_shared<CallsRelationshipManager>(callRelationshipManager));

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableX) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableX) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableX) == true);
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
        callRelationshipManager.storeCallsRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Procedure>(procedure2), true);
        callRelationshipManager.storeCallsRelationship(std::make_shared<Procedure>(procedure3), std::make_shared<Procedure>(procedure4), true);
        callRelationshipManager.storeCallsRelationship(std::make_shared<Procedure>(procedure5), std::make_shared<Procedure>(procedure1), true);

        usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Variable>(variableX));
        usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure2), std::make_shared<Variable>(variableY));
        usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure3), std::make_shared<Variable>(variableZ));
        usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableA));
        usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure5), std::make_shared<Variable>(variableB));

        callRelationshipManager.calculateCallsStar();

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableX) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableY) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableZ) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableA) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure5, variableB) == true);

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableY) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableA) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableA) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableY) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableA) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableY) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure5, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure5, variableY) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure5, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure5, variableA) == false);

        usesProcRelationshipManager.calculateUsesRelationshipForCallers(std::make_shared<CallsRelationshipManager>(callRelationshipManager));

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableX) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableY) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableZ) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableA) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure5, variableB) == true);

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableY) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableA) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure1, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableA) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure2, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableY) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableA) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure3, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableX) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableY) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure4, variableB) == false);

        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure5, variableX) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure5, variableY) == true);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure5, variableZ) == false);
        REQUIRE(usesProcRelationshipManager.isProcUsesVar(procedure5, variableA) == false);
    }
}