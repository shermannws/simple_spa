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

    usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Variable>(variableX));
    usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure2), std::make_shared<Variable>(variableY));
    usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure3), std::make_shared<Variable>(variableZ));
    usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableX));
    usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableY));
    usesProcRelationshipManager.storeUsesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableZ));

    REQUIRE(usesProcRelationshipManager.getUsesProcPair().size() == 6);

    REQUIRE(usesProcRelationshipManager.getUsesProcIdent(Variable("x")).size() == 2);
    auto v = usesProcRelationshipManager.getUsesProcIdent(Variable("x"));
    REQUIRE(find(v.begin(), v.end(), procedure1) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure4) != v.end());


    REQUIRE(usesProcRelationshipManager.getUsesProc().size() == 4);
    v = usesProcRelationshipManager.getUsesProc();
    REQUIRE(find(v.begin(), v.end(), procedure1) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure2) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure3) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure4) != v.end());

    REQUIRE(usesProcRelationshipManager.getUsesProcVar(Procedure("proc1")).size() == 1);
    v = usesProcRelationshipManager.getUsesProcVar(Procedure("proc1"));
    REQUIRE(find(v.begin(), v.end(), variableX) != v.end());
    REQUIRE(usesProcRelationshipManager.getUsesProcVar(Procedure("proc4")).size() == 3);
    v = usesProcRelationshipManager.getUsesProcVar(Procedure("proc4"));
    REQUIRE(find(v.begin(), v.end(), variableX) != v.end());
    REQUIRE(find(v.begin(), v.end(), variableY) != v.end());
    REQUIRE(find(v.begin(), v.end(), variableZ) != v.end());


    REQUIRE(usesProcRelationshipManager.isProcUsesVar(Procedure("proc1"), Variable("x")) == true);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(Procedure("proc1"), Variable("y")) == false);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(Procedure("proc1"), Variable("z")) == false);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(Procedure("proc2"), Variable("x")) == false);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(Procedure("proc2"), Variable("y")) == true);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(Procedure("proc2"), Variable("z")) == false);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(Procedure("proc3"), Variable("x")) == false);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(Procedure("proc3"), Variable("y")) == false);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(Procedure("proc3"), Variable("z")) == true);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(Procedure("proc4"), Variable("x")) == true);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(Procedure("proc4"), Variable("y")) == true);
    REQUIRE(usesProcRelationshipManager.isProcUsesVar(Procedure("proc4"), Variable("z")) == true);

    REQUIRE(usesProcRelationshipManager.hasProcUses(Procedure("proc1")) == true);
    REQUIRE(usesProcRelationshipManager.hasProcUses(Procedure("proc2")) == true);
    REQUIRE(usesProcRelationshipManager.hasProcUses(Procedure("proc3")) == true);
    REQUIRE(usesProcRelationshipManager.hasProcUses(Procedure("proc4")) == true);
    REQUIRE(usesProcRelationshipManager.hasProcUses(Procedure("proc5")) == false);
}