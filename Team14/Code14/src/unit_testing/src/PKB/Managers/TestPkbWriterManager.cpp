#include <memory>

#include "catch.hpp"
#include "PKB/Managers/PkbWriterManager.h"

using namespace std;

TEST_CASE("Test PkbWriterManager - Triggering Stmt to Var Transitive Calculation through triggerTransitiveCalc") {

    SECTION("Test Modifes(s,v) and Uses - v1") {
        auto assignmentManager = std::make_shared<AssignPatternManager>(AssignPatternManager());
        auto entitiesManager = std::make_shared<EntitiesManager>(EntitiesManager());
        auto followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
        auto usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
        auto modifiesRelationshipManager = std::make_shared<ModifiesRelationshipManager>();
        auto parentRelationshipManager = std::make_shared<ParentRelationshipManager>();
        auto callsRelationshipManager = std::make_shared<CallsRelationshipManager>();
        auto modifiesProcRelationshipManager = std::make_shared<ModifiesProcRelationshipManager>();
        auto usesProcRelationshipManager = std::make_shared<UsesProcRelationshipManager>();

        PkbWriterManager pkbWriterManager = PkbWriterManager(
            assignmentManager,
            entitiesManager,
            followsRelationshipManager,
            usesRelationshipManager,
            modifiesRelationshipManager,
            parentRelationshipManager,
            callsRelationshipManager,
            modifiesProcRelationshipManager,
            usesProcRelationshipManager
        );

        // A -> modifies a, b, c
        // B -> uses x, y, z
        Procedure procedureA = Procedure("A");
        Procedure procedureB = Procedure("B");
        Variable variableA = Variable("a");
        Variable variableB = Variable("b");
        Variable variableC = Variable("c");
        Variable variableX = Variable("x");
        Variable variableY = Variable("y");
        Variable variableZ = Variable("z");

        modifiesProcRelationshipManager->storeRelationship(std::make_shared<Procedure>(procedureA), std::make_shared<Variable>(variableA));
        modifiesProcRelationshipManager->storeRelationship(std::make_shared<Procedure>(procedureA), std::make_shared<Variable>(variableB));
        modifiesProcRelationshipManager->storeRelationship(std::make_shared<Procedure>(procedureA), std::make_shared<Variable>(variableC));
        usesProcRelationshipManager->storeRelationship(std::make_shared<Procedure>(procedureB), std::make_shared<Variable>(variableX));
        usesProcRelationshipManager->storeRelationship(std::make_shared<Procedure>(procedureB), std::make_shared<Variable>(variableY));
        usesProcRelationshipManager->storeRelationship(std::make_shared<Procedure>(procedureB), std::make_shared<Variable>(variableZ));

        // Stmt 1,2 -> A
        // Stmt 3,4 -> B
        Statement statement1 = Statement(1, StatementType::If);
        Statement statement2 = Statement(2, StatementType::Call);
        Statement statement3 = Statement(3, StatementType::While);
        Statement statement4 = Statement(4, StatementType::Call);

        pkbWriterManager.addProcedureToStatementsMap(
            std::make_shared<Procedure>(procedureA),
            {
                std::make_shared<Statement>(statement1),
                std::make_shared<Statement>(statement2)
            }
        );
        pkbWriterManager.addProcedureToStatementsMap(
            std::make_shared<Procedure>(procedureB),
            {
                std::make_shared<Statement>(statement3),
                std::make_shared<Statement>(statement4)
            }
        );


        //BEFORE STATE - Modifies
        REQUIRE(modifiesRelationshipManager->isRelationship(statement1, variableA) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement1, variableB) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement1, variableC) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement1, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement1, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement1, variableZ) == false);                                                                                                                   
                                                              
        REQUIRE(modifiesRelationshipManager->isRelationship(statement2, variableA) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement2, variableB) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement2, variableC) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement2, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement2, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement2, variableZ) == false);

        REQUIRE(modifiesRelationshipManager->isRelationship(statement3, variableA) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement3, variableB) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement3, variableC) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement3, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement3, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement3, variableZ) == false);

        REQUIRE(modifiesRelationshipManager->isRelationship(statement4, variableA) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement4, variableB) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement4, variableC) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement4, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement4, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement4, variableZ) == false);

        //BEFORE STATE - Uses
        REQUIRE(usesRelationshipManager->isRelationship(statement1, variableA) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement1, variableB) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement1, variableC) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement1, variableX) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement1, variableY) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement1, variableZ) == false);

        REQUIRE(usesRelationshipManager->isRelationship(statement2, variableA) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement2, variableB) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement2, variableC) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement2, variableX) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement2, variableY) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement2, variableZ) == false);

        REQUIRE(usesRelationshipManager->isRelationship(statement3, variableA) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement3, variableB) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement3, variableC) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement3, variableX) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement3, variableY) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement3, variableZ) == false);

        REQUIRE(usesRelationshipManager->isRelationship(statement4, variableA) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement4, variableB) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement4, variableC) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement4, variableX) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement4, variableY) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement4, variableZ) == false);

        pkbWriterManager.triggerTransitiveCalc();

        //AFTER STATE - Modifies
        REQUIRE(modifiesRelationshipManager->isRelationship(statement1, variableA) == true);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement1, variableB) == true);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement1, variableC) == true);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement1, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement1, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement1, variableZ) == false);

        REQUIRE(modifiesRelationshipManager->isRelationship(statement2, variableA) == true);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement2, variableB) == true);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement2, variableC) == true);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement2, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement2, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement2, variableZ) == false);

        REQUIRE(modifiesRelationshipManager->isRelationship(statement3, variableA) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement3, variableB) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement3, variableC) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement3, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement3, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement3, variableZ) == false);

        REQUIRE(modifiesRelationshipManager->isRelationship(statement4, variableA) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement4, variableB) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement4, variableC) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement4, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement4, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isRelationship(statement4, variableZ) == false);

        //AFTER STATE - Uses
        REQUIRE(usesRelationshipManager->isRelationship(statement1, variableA) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement1, variableB) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement1, variableC) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement1, variableX) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement1, variableY) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement1, variableZ) == false);

        REQUIRE(usesRelationshipManager->isRelationship(statement2, variableA) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement2, variableB) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement2, variableC) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement2, variableX) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement2, variableY) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement2, variableZ) == false);

        REQUIRE(usesRelationshipManager->isRelationship(statement3, variableA) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement3, variableB) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement3, variableC) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement3, variableX) == true);
        REQUIRE(usesRelationshipManager->isRelationship(statement3, variableY) == true);
        REQUIRE(usesRelationshipManager->isRelationship(statement3, variableZ) == true);

        REQUIRE(usesRelationshipManager->isRelationship(statement4, variableA) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement4, variableB) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement4, variableC) == false);
        REQUIRE(usesRelationshipManager->isRelationship(statement4, variableX) == true);
        REQUIRE(usesRelationshipManager->isRelationship(statement4, variableY) == true);
        REQUIRE(usesRelationshipManager->isRelationship(statement4, variableZ) == true);
    }
}