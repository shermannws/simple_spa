#include <memory>

#include "Commons/Entities/AssignStatement.h"
#include "Commons/Entities/CallStatement.h"
#include "Commons/Entities/IfStatement.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Variable.h"
#include "Commons/Entities/WhileStatement.h"
#include "PKB/Managers/AffectsRelationshipManager.h"
#include "PKB/Managers/AssignPatternManager.h"
#include "PKB/Managers/CallsRelationshipManager.h"
#include "PKB/Managers/EntitiesManager.h"
#include "PKB/Managers/FollowsRelationshipManager.h"
#include "PKB/Managers/IfPatternManager.h"
#include "PKB/Managers/ModifiesProcRelationshipManager.h"
#include "PKB/Managers/ModifiesRelationshipManager.h"
#include "PKB/Managers/NextRelationshipManager.h"
#include "PKB/Managers/ParentRelationshipManager.h"
#include "PKB/Managers/PkbReaderManager.h"
#include "PKB/Managers/UsesProcRelationshipManager.h"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "PKB/Managers/WhilePatternManager.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test Affects Relationship Calculation & Retrieval") {
    SECTION("Test Affects Calculation") {
        auto assignmentManager = std::make_shared<AssignPatternManager>(AssignPatternManager());
        auto entitiesManager = std::make_shared<EntitiesManager>(EntitiesManager());
        auto followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
        auto usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
        auto modifiesRelationshipManager = std::make_shared<ModifiesRelationshipManager>();
        auto parentRelationshipManager = std::make_shared<ParentRelationshipManager>();
        auto callsRelationshipManager = std::make_shared<CallsRelationshipManager>();
        auto modifiesProcRelationshipManager = std::make_shared<ModifiesProcRelationshipManager>();
        auto usesProcRelationshipManager = std::make_shared<UsesProcRelationshipManager>();
        auto ifPatternManager = std::make_shared<IfPatternManager>(IfPatternManager());
        auto whilePatternManager = std::make_shared<WhilePatternManager>(WhilePatternManager());
        auto nextRelationshipManager = std::make_shared<NextRelationshipManager>();
        auto affectsRelationshipManager = std::make_shared<AffectsRelationshipManager>();

        auto pkbReaderManager = std::make_shared<PkbReaderManager>(PkbReaderManager(
                assignmentManager, entitiesManager, followsRelationshipManager, usesRelationshipManager,
                modifiesRelationshipManager, parentRelationshipManager, callsRelationshipManager,
                modifiesProcRelationshipManager, usesProcRelationshipManager, ifPatternManager, whilePatternManager,
                nextRelationshipManager, affectsRelationshipManager));

        /* Construct sample SIMPLE program
        procedure Second {
            01        x = 0;
            02        i = 5;
            03        while (i!=0) {
            04            x = x + 2*y;
            05            call Third;
            06            i = i - 1; }
            07        if (x==1) then {
            08            x = x+1; }
                      else {
            09            z = 1; }
            10        z = z + x + i;
            11        y = z + 2;
            12        x = x * y + z; }
        */

        auto stmt1 = make_shared<AssignStatement>(AssignStatement(1));
        auto varX = make_shared<Variable>("x");
        modifiesRelationshipManager->storeRelationship(stmt1, varX);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt1, varX, make_shared<Expression>("0"))));

        auto stmt2 = make_shared<AssignStatement>(AssignStatement(2));
        auto varI = make_shared<Variable>("i");
        modifiesRelationshipManager->storeRelationship(stmt2, varI);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt2, varI, make_shared<Expression>("5"))));
        nextRelationshipManager->storeRelationship(stmt1, stmt2, true);

        auto stmt3 = make_shared<WhileStatement>(WhileStatement(3));
        nextRelationshipManager->storeRelationship(stmt2, stmt3, true);

        auto stmt4 = make_shared<AssignStatement>(AssignStatement(4));
        auto varY = make_shared<Variable>("y");
        modifiesRelationshipManager->storeRelationship(stmt4, varX);
        usesRelationshipManager->storeRelationship(stmt4, varX);
        usesRelationshipManager->storeRelationship(stmt4, varY);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt4, varX, make_shared<Expression>("x + 2*y"))));
        nextRelationshipManager->storeRelationship(stmt3, stmt4, true);

        auto stmt5 = make_shared<CallStatement>(CallStatement(5, "Third"));
        auto varZ = make_shared<Variable>("z");
        auto varV = make_shared<Variable>("v");
        modifiesRelationshipManager->storeRelationship(stmt5, varZ);
        modifiesRelationshipManager->storeRelationship(stmt5, varV);
        nextRelationshipManager->storeRelationship(stmt4, stmt5, true);

        auto stmt6 = make_shared<AssignStatement>(AssignStatement(6));
        modifiesRelationshipManager->storeRelationship(stmt6, varI);
        usesRelationshipManager->storeRelationship(stmt6, varI);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt6, varI, make_shared<Expression>("i - 1"))));
        nextRelationshipManager->storeRelationship(stmt5, stmt6, true);
        nextRelationshipManager->storeRelationship(stmt6, stmt3, true);

        auto stmt7 = make_shared<IfStatement>(IfStatement(7));
        nextRelationshipManager->storeRelationship(stmt3, stmt7, true);

        auto stmt8 = make_shared<AssignStatement>(AssignStatement(8));
        modifiesRelationshipManager->storeRelationship(stmt8, varX);
        usesRelationshipManager->storeRelationship(stmt8, varX);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt8, varX, make_shared<Expression>("x+1"))));
        nextRelationshipManager->storeRelationship(stmt7, stmt8, true);

        auto stmt9 = make_shared<AssignStatement>(AssignStatement(9));
        modifiesRelationshipManager->storeRelationship(stmt9, varZ);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt9, varZ, make_shared<Expression>("1"))));
        nextRelationshipManager->storeRelationship(stmt7, stmt9, true);

        auto stmt10 = make_shared<AssignStatement>(AssignStatement(10));
        modifiesRelationshipManager->storeRelationship(stmt10, varZ);
        usesRelationshipManager->storeRelationship(stmt10, varZ);
        usesRelationshipManager->storeRelationship(stmt10, varX);
        usesRelationshipManager->storeRelationship(stmt10, varI);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt10, varZ, make_shared<Expression>("z + x + i"))));
        nextRelationshipManager->storeRelationship(stmt8, stmt10, true);
        nextRelationshipManager->storeRelationship(stmt9, stmt10, true);

        auto stmt11 = make_shared<AssignStatement>(AssignStatement(11));
        modifiesRelationshipManager->storeRelationship(stmt11, varY);
        usesRelationshipManager->storeRelationship(stmt11, varZ);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt11, varY, make_shared<Expression>("z + 2"))));
        nextRelationshipManager->storeRelationship(stmt10, stmt11, true);

        auto stmt12 = make_shared<AssignStatement>(AssignStatement(12));
        modifiesRelationshipManager->storeRelationship(stmt12, varX);
        usesRelationshipManager->storeRelationship(stmt12, varX);
        usesRelationshipManager->storeRelationship(stmt12, varY);
        usesRelationshipManager->storeRelationship(stmt12, varZ);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt12, varX, make_shared<Expression>("x * y + z"))));
        nextRelationshipManager->storeRelationship(stmt11, stmt12, true);

        REQUIRE(pkbReaderManager->isAffects(*stmt11, *stmt12));
        REQUIRE(pkbReaderManager->isAffects(*stmt2, *stmt6));
        REQUIRE(pkbReaderManager->isAffects(*stmt4, *stmt8));
        REQUIRE(pkbReaderManager->isAffects(*stmt4, *stmt10));
        REQUIRE(pkbReaderManager->isAffects(*stmt6, *stmt6));
        REQUIRE(pkbReaderManager->isAffects(*stmt1, *stmt4));
        REQUIRE(pkbReaderManager->isAffects(*stmt1, *stmt8));
        REQUIRE(pkbReaderManager->isAffects(*stmt1, *stmt10));
        REQUIRE(pkbReaderManager->isAffects(*stmt1, *stmt12));
        REQUIRE(pkbReaderManager->isAffects(*stmt2, *stmt10));
        REQUIRE(pkbReaderManager->isAffects(*stmt9, *stmt10));

        REQUIRE_FALSE(pkbReaderManager->isAffects(*stmt9, *stmt11));
        REQUIRE_FALSE(pkbReaderManager->isAffects(*stmt9, *stmt12));
        REQUIRE_FALSE(pkbReaderManager->isAffects(*stmt2, *stmt3));
        REQUIRE_FALSE(pkbReaderManager->isAffects(*stmt9, *stmt6));
    }

    SECTION("Test Affects Retrieval") {
        auto assignmentManager = std::make_shared<AssignPatternManager>(AssignPatternManager());
        auto entitiesManager = std::make_shared<EntitiesManager>(EntitiesManager());
        auto followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
        auto usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
        auto modifiesRelationshipManager = std::make_shared<ModifiesRelationshipManager>();
        auto parentRelationshipManager = std::make_shared<ParentRelationshipManager>();
        auto callsRelationshipManager = std::make_shared<CallsRelationshipManager>();
        auto modifiesProcRelationshipManager = std::make_shared<ModifiesProcRelationshipManager>();
        auto usesProcRelationshipManager = std::make_shared<UsesProcRelationshipManager>();
        auto ifPatternManager = std::make_shared<IfPatternManager>(IfPatternManager());
        auto whilePatternManager = std::make_shared<WhilePatternManager>(WhilePatternManager());
        auto nextRelationshipManager = std::make_shared<NextRelationshipManager>();
        auto affectsRelationshipManager = std::make_shared<AffectsRelationshipManager>();

        auto pkbReaderManager = std::make_shared<PkbReaderManager>(PkbReaderManager(
                assignmentManager, entitiesManager, followsRelationshipManager, usesRelationshipManager,
                modifiesRelationshipManager, parentRelationshipManager, callsRelationshipManager,
                modifiesProcRelationshipManager, usesProcRelationshipManager, ifPatternManager, whilePatternManager,
                nextRelationshipManager, affectsRelationshipManager));

        /* Construct sample SIMPLE program
        procedure Second {
            01        x = 0;
            02        x = x + 2*y;
            03        z = 1;
            04        z = z + x;
            05        x = x * y + z; }
        */

        auto stmt1 = make_shared<AssignStatement>(AssignStatement(1));
        auto varX = make_shared<Variable>("x");
        modifiesRelationshipManager->storeRelationship(stmt1, varX);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt1, varX, make_shared<Expression>("0"))));

        auto stmt2 = make_shared<AssignStatement>(AssignStatement(2));
        auto varY = make_shared<Variable>("y");
        modifiesRelationshipManager->storeRelationship(stmt2, varX);
        usesRelationshipManager->storeRelationship(stmt2, varX);
        usesRelationshipManager->storeRelationship(stmt2, varY);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt2, varX, make_shared<Expression>("x + 2*y"))));
        nextRelationshipManager->storeRelationship(stmt1, stmt2, true);

        auto stmt3 = make_shared<AssignStatement>(AssignStatement(3));
        auto varZ = make_shared<Variable>("z");
        modifiesRelationshipManager->storeRelationship(stmt3, varZ);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt3, varZ, make_shared<Expression>("1"))));
        nextRelationshipManager->storeRelationship(stmt2, stmt3, true);

        auto stmt4 = make_shared<AssignStatement>(AssignStatement(4));
        modifiesRelationshipManager->storeRelationship(stmt4, varZ);
        usesRelationshipManager->storeRelationship(stmt4, varZ);
        usesRelationshipManager->storeRelationship(stmt4, varX);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt4, varZ, make_shared<Expression>("z + x"))));
        nextRelationshipManager->storeRelationship(stmt3, stmt4, true);

        auto stmt5 = make_shared<AssignStatement>(AssignStatement(5));
        modifiesRelationshipManager->storeRelationship(stmt5, varX);
        usesRelationshipManager->storeRelationship(stmt5, varX);
        usesRelationshipManager->storeRelationship(stmt5, varY);
        usesRelationshipManager->storeRelationship(stmt5, varZ);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt5, varX, make_shared<Expression>("x * y + z"))));
        nextRelationshipManager->storeRelationship(stmt4, stmt5, true);

        REQUIRE(pkbReaderManager->getAffectsPair(StatementType::Assign, StatementType::Assign).size() == 5);

        REQUIRE(pkbReaderManager->getAffectsTypeStmt(StatementType::Assign, *stmt1).empty());
        REQUIRE(pkbReaderManager->getAffectsTypeStmt(StatementType::Assign, *stmt2).size() == 1);
        REQUIRE(pkbReaderManager->getAffectsTypeStmt(StatementType::Assign, *stmt3).empty());
        REQUIRE(pkbReaderManager->getAffectsTypeStmt(StatementType::Assign, *stmt4).size() == 2);
        REQUIRE(pkbReaderManager->getAffectsTypeStmt(StatementType::Assign, *stmt5).size() == 2);

        REQUIRE(pkbReaderManager->getAffectsTypeWildcard(StatementType::Assign).size() == 4);

        REQUIRE(pkbReaderManager->getAffectsStmtType(*stmt1, StatementType::Assign).size() == 1);
        REQUIRE(pkbReaderManager->getAffectsStmtType(*stmt2, StatementType::Assign).size() == 2);
        REQUIRE(pkbReaderManager->getAffectsStmtType(*stmt3, StatementType::Assign).size() == 1);
        REQUIRE(pkbReaderManager->getAffectsStmtType(*stmt4, StatementType::Assign).size() == 1);
        REQUIRE(pkbReaderManager->getAffectsStmtType(*stmt5, StatementType::Assign).empty());

        REQUIRE(pkbReaderManager->getAffectsWildcardType(StatementType::Assign).size() == 3);

        REQUIRE(pkbReaderManager->hasAffects());

        REQUIRE_FALSE(pkbReaderManager->hasAffectsStmt(*stmt1));
        REQUIRE(pkbReaderManager->hasAffectsStmt(*stmt2));
        REQUIRE_FALSE(pkbReaderManager->hasAffectsStmt(*stmt3));
        REQUIRE(pkbReaderManager->hasAffectsStmt(*stmt4));
        REQUIRE(pkbReaderManager->hasAffectsStmt(*stmt5));

        REQUIRE(pkbReaderManager->hasAffectedStmt(*stmt1));
        REQUIRE(pkbReaderManager->hasAffectedStmt(*stmt2));
        REQUIRE(pkbReaderManager->hasAffectedStmt(*stmt3));
        REQUIRE(pkbReaderManager->hasAffectedStmt(*stmt4));
        REQUIRE_FALSE(pkbReaderManager->hasAffectedStmt(*stmt5));
    }

    SECTION("Test Affects Retrieval Loop") {
        auto assignmentManager = std::make_shared<AssignPatternManager>(AssignPatternManager());
        auto entitiesManager = std::make_shared<EntitiesManager>(EntitiesManager());
        auto followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
        auto usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
        auto modifiesRelationshipManager = std::make_shared<ModifiesRelationshipManager>();
        auto parentRelationshipManager = std::make_shared<ParentRelationshipManager>();
        auto callsRelationshipManager = std::make_shared<CallsRelationshipManager>();
        auto modifiesProcRelationshipManager = std::make_shared<ModifiesProcRelationshipManager>();
        auto usesProcRelationshipManager = std::make_shared<UsesProcRelationshipManager>();
        auto ifPatternManager = std::make_shared<IfPatternManager>(IfPatternManager());
        auto whilePatternManager = std::make_shared<WhilePatternManager>(WhilePatternManager());
        auto nextRelationshipManager = std::make_shared<NextRelationshipManager>();
        auto affectsRelationshipManager = std::make_shared<AffectsRelationshipManager>();

        auto pkbReaderManager = std::make_shared<PkbReaderManager>(PkbReaderManager(
                assignmentManager, entitiesManager, followsRelationshipManager, usesRelationshipManager,
                modifiesRelationshipManager, parentRelationshipManager, callsRelationshipManager,
                modifiesProcRelationshipManager, usesProcRelationshipManager, ifPatternManager, whilePatternManager,
                nextRelationshipManager, affectsRelationshipManager));

        /* Construct sample SIMPLE program
        procedure Second {
            01        while (x) {
            02          x = x +1; }
        */

        auto stmt1 = make_shared<WhileStatement>(WhileStatement(1));
        auto varX = make_shared<Variable>("x");

        auto stmt2 = make_shared<AssignStatement>(AssignStatement(2));
        modifiesRelationshipManager->storeRelationship(stmt2, varX);
        usesRelationshipManager->storeRelationship(stmt2, varX);
        assignmentManager->storeAssignPattern(
                make_shared<Assignment>(Assignment(stmt2, varX, make_shared<Expression>("x + 1"))));
        nextRelationshipManager->storeRelationship(stmt1, stmt2, true);
        nextRelationshipManager->storeRelationship(stmt2, stmt1, true);

        REQUIRE(pkbReaderManager->getAffectsPair(StatementType::Assign, StatementType::Assign).size() == 1);

        auto set = pkbReaderManager->getAffectsSameStmt(StatementType::Assign);
        REQUIRE(set.size() == 1);
        REQUIRE(set.find(*stmt2) != set.end());

        REQUIRE(pkbReaderManager->getAffectsTypeStmt(StatementType::Assign, *stmt1).empty());
        REQUIRE(pkbReaderManager->getAffectsTypeStmt(StatementType::Assign, *stmt2).size() == 1);

        REQUIRE(pkbReaderManager->getAffectsTypeWildcard(StatementType::Assign).size() == 1);

        REQUIRE(pkbReaderManager->getAffectsStmtType(*stmt1, StatementType::Assign).empty());
        REQUIRE(pkbReaderManager->getAffectsStmtType(*stmt2, StatementType::Assign).size() == 1);

        REQUIRE(pkbReaderManager->getAffectsWildcardType(StatementType::Assign).size() == 1);

        REQUIRE(pkbReaderManager->hasAffects());

        REQUIRE_FALSE(pkbReaderManager->hasAffectsStmt(*stmt1));
        REQUIRE(pkbReaderManager->hasAffectsStmt(*stmt2));

        REQUIRE_FALSE(pkbReaderManager->hasAffectedStmt(*stmt1));
        REQUIRE(pkbReaderManager->hasAffectedStmt(*stmt2));
    }
}