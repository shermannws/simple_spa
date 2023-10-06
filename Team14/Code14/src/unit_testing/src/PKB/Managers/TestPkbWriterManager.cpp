#include <memory>

#include "catch.hpp"
#include "PKB/Managers/PkbWriterManager.h"

using namespace std;

TEST_CASE("Test PkbWriterManager - Triggering Stmt to Var Transitive Calculation") {

    SECTION("Test Modifes(s,v) and Uses - v1") {
        auto assignmentManager = std::make_shared<AssignmentManager>(AssignmentManager());
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

        modifiesProcRelationshipManager->storeModifiesProcRelationship(std::make_shared<Procedure>(procedureA), std::make_shared<Variable>(variableA));
        modifiesProcRelationshipManager->storeModifiesProcRelationship(std::make_shared<Procedure>(procedureA), std::make_shared<Variable>(variableB));
        modifiesProcRelationshipManager->storeModifiesProcRelationship(std::make_shared<Procedure>(procedureA), std::make_shared<Variable>(variableC));
        usesProcRelationshipManager->storeUsesProcRelationship(std::make_shared<Procedure>(procedureB), std::make_shared<Variable>(variableX));
        usesProcRelationshipManager->storeUsesProcRelationship(std::make_shared<Procedure>(procedureB), std::make_shared<Variable>(variableY));
        usesProcRelationshipManager->storeUsesProcRelationship(std::make_shared<Procedure>(procedureB), std::make_shared<Variable>(variableZ));

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
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement1, variableA) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement1, variableB) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement1, variableC) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement1, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement1, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement1, variableZ) == false);                                                                                                                   
                                                              
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement2, variableA) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement2, variableB) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement2, variableC) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement2, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement2, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement2, variableZ) == false);

        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement3, variableA) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement3, variableB) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement3, variableC) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement3, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement3, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement3, variableZ) == false);

        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement4, variableA) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement4, variableB) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement4, variableC) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement4, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement4, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement4, variableZ) == false);

        //BEFORE STATE - Uses
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement1, variableA) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement1, variableB) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement1, variableC) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement1, variableX) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement1, variableY) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement1, variableZ) == false);

        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement2, variableA) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement2, variableB) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement2, variableC) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement2, variableX) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement2, variableY) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement2, variableZ) == false);

        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement3, variableA) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement3, variableB) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement3, variableC) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement3, variableX) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement3, variableY) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement3, variableZ) == false);

        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement4, variableA) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement4, variableB) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement4, variableC) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement4, variableX) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement4, variableY) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement4, variableZ) == false);

        pkbWriterManager.triggerStmtToVarTransitiveCalculation();

        //AFTER STATE - Modifies
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement1, variableA) == true);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement1, variableB) == true);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement1, variableC) == true);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement1, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement1, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement1, variableZ) == false);

        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement2, variableA) == true);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement2, variableB) == true);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement2, variableC) == true);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement2, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement2, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement2, variableZ) == false);

        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement3, variableA) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement3, variableB) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement3, variableC) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement3, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement3, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement3, variableZ) == false);

        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement4, variableA) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement4, variableB) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement4, variableC) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement4, variableX) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement4, variableY) == false);
        REQUIRE(modifiesRelationshipManager->isStmtModifiesVar(statement4, variableZ) == false);

        //AFTER STATE - Uses
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement1, variableA) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement1, variableB) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement1, variableC) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement1, variableX) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement1, variableY) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement1, variableZ) == false);

        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement2, variableA) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement2, variableB) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement2, variableC) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement2, variableX) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement2, variableY) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement2, variableZ) == false);

        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement3, variableA) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement3, variableB) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement3, variableC) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement3, variableX) == true);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement3, variableY) == true);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement3, variableZ) == true);

        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement4, variableA) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement4, variableB) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement4, variableC) == false);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement4, variableX) == true);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement4, variableY) == true);
        REQUIRE(usesRelationshipManager->isStmtUsesVar(statement4, variableZ) == true);
    }
}