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

    modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure1), std::make_shared<Variable>(variableX));
    modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure2), std::make_shared<Variable>(variableY));
    modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure3), std::make_shared<Variable>(variableZ));
    modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableX));
    modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableY));
    modifiesProcRelationshipManager.storeModifiesProcRelationship(std::make_shared<Procedure>(procedure4), std::make_shared<Variable>(variableZ));

    REQUIRE(modifiesProcRelationshipManager.getModifiesProcPair().size() == 6);

    REQUIRE(modifiesProcRelationshipManager.getModifiesProcIdent(Variable("x")).size() == 2);
    auto v = modifiesProcRelationshipManager.getModifiesProcIdent(Variable("x"));
    REQUIRE(find(v.begin(), v.end(), procedure1) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure4) != v.end());


    REQUIRE(modifiesProcRelationshipManager.getModifiesProc().size() == 4);
    v = modifiesProcRelationshipManager.getModifiesProc();
    REQUIRE(find(v.begin(), v.end(), procedure1) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure2) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure3) != v.end());
    REQUIRE(find(v.begin(), v.end(), procedure4) != v.end());

    REQUIRE(modifiesProcRelationshipManager.getModifiesProcVar(Procedure("proc1")).size() == 1);
    v = modifiesProcRelationshipManager.getModifiesProcVar(Procedure("proc1"));
    REQUIRE(find(v.begin(), v.end(), variableX) != v.end());
    REQUIRE(modifiesProcRelationshipManager.getModifiesProcVar(Procedure("proc4")).size() == 3);
    v = modifiesProcRelationshipManager.getModifiesProcVar(Procedure("proc4"));
    REQUIRE(find(v.begin(), v.end(), variableX) != v.end());
    REQUIRE(find(v.begin(), v.end(), variableY) != v.end());
    REQUIRE(find(v.begin(), v.end(), variableZ) != v.end());

    
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(Procedure("proc1"), Variable("x")) == true);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(Procedure("proc1"), Variable("y")) == false);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(Procedure("proc1"), Variable("z")) == false);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(Procedure("proc2"), Variable("x")) == false);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(Procedure("proc2"), Variable("y")) == true);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(Procedure("proc2"), Variable("z")) == false);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(Procedure("proc3"), Variable("x")) == false);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(Procedure("proc3"), Variable("y")) == false);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(Procedure("proc3"), Variable("z")) == true);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(Procedure("proc4"), Variable("x")) == true);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(Procedure("proc4"), Variable("y")) == true);
    REQUIRE(modifiesProcRelationshipManager.isProcModifiesVar(Procedure("proc4"), Variable("z")) == true);

    REQUIRE(modifiesProcRelationshipManager.hasProcModifies(Procedure("proc1")) == true);
    REQUIRE(modifiesProcRelationshipManager.hasProcModifies(Procedure("proc2")) == true);
    REQUIRE(modifiesProcRelationshipManager.hasProcModifies(Procedure("proc3")) == true);
    REQUIRE(modifiesProcRelationshipManager.hasProcModifies(Procedure("proc4")) == true);
    REQUIRE(modifiesProcRelationshipManager.hasProcModifies(Procedure("proc5")) == false);
}