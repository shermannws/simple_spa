#include <memory>

#include "catch.hpp"
#include "PKB/Managers/MapStoresManagers/ModifiesProcRelationshipManager.h"

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