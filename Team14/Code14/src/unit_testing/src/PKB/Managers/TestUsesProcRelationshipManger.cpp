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

    usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Variable>(variableX));
    usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure2), std::make_shared<Variable>(variableY));
    usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure3), std::make_shared<Variable>(variableZ));
    usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableX));
    usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableY));
    usesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableZ));

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