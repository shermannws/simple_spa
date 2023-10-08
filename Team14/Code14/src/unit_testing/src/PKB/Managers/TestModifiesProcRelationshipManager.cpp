#include <memory>

#include "catch.hpp"
#include "PKB/Managers/ModifiesProcRelationshipManager.h"

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

    modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Variable>(variableX));
    modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure2), std::make_shared<Variable>(variableY));
    modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure3), std::make_shared<Variable>(variableZ));
    modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableX));
    modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableY));
    modifiesProcRelationshipManager.storeRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableZ));

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