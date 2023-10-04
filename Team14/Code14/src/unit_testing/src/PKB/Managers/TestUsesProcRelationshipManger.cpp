#include <memory>

#include "catch.hpp"
#include "PKB/Managers/MapStoresManagers/UsesProcRelationshipManager.h"

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