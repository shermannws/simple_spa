#include <memory>

#include "catch.hpp"
#include "PKB/Managers/NextRelationshipManager.h"

using namespace std;

TEST_CASE("Test Next Relationship Retrieval") {
    NextRelationshipManager nextRelationshipManager = NextRelationshipManager();

    REQUIRE(nextRelationshipManager.hasRelationship() == false);

    // 1-->2-->3
    shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
    shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Call));
    shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::Print));

    nextRelationshipManager.storeRelationship(statement1, statement2, true);
    nextRelationshipManager.storeRelationship(statement2, statement3, true);
    nextRelationshipManager.storeRelationship(statement1, statement3, false);

    REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Stmt, true).size() == 2);
    REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Stmt, false).size() == 3);
    REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Call, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Call, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Print, true).size() == 0);
    REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Print, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Print, true).size() == 0);

    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement1, false).size() == 0);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement2, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement2, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Assign, *statement2, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Assign, *statement2, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Call, *statement2, false).size() == 0);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Print, *statement2, false).size() == 0);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement3, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement3, false).size() == 2);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Assign, *statement3, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Assign, *statement3, true).size() == 0);

    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Stmt).size() == 2);
    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Assign).size() == 0);
    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Print).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Call).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::If).size() == 0);
    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::While).size() == 0);
    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Read).size() == 0);

    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Stmt, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Stmt, false).size() == 2);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Print, true).size() == 0);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Print, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Stmt, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Stmt, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Print, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Print, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Assign, true).size() == 0);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Assign, false).size() == 0);

    REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Stmt).size() == 2);
    REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Assign).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Print).size() == 0);
    REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Call).size() == 1);

    REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement2, true) == true);
    REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement2, false) == true);
    REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement3, true) == false);
    REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement3, false) == true);
    REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement1, false) == false);
    REQUIRE(nextRelationshipManager.isRelationship(*statement2, *statement2, false) == false);
    REQUIRE(nextRelationshipManager.isRelationship(*statement3, *statement3, false) == false);
    REQUIRE(nextRelationshipManager.isRelationship(*statement2, *statement1, false) == false);
    REQUIRE(nextRelationshipManager.isRelationship(*statement3, *statement1, false) == false);
    REQUIRE(nextRelationshipManager.isRelationship(*statement3, *statement2, false) == false);

    REQUIRE(nextRelationshipManager.isFormer(*statement1) == true);
    REQUIRE(nextRelationshipManager.isFormer(*statement2) == true);
    REQUIRE(nextRelationshipManager.isFormer(*statement3) == false);

    REQUIRE(nextRelationshipManager.isLatter(*statement1) == false);
    REQUIRE(nextRelationshipManager.isLatter(*statement2) == true);
    REQUIRE(nextRelationshipManager.isLatter(*statement3) == true);

    REQUIRE(nextRelationshipManager.hasRelationship() == true);
}


TEST_CASE("Test Next/Next* Relationship Retrieval") {
    SECTION("Test simple loop") {
        NextRelationshipManager nextRelationshipManager = NextRelationshipManager();

        REQUIRE(nextRelationshipManager.hasRelationship() == false);

        //1 -- > 2 -- > 1
        shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::While));
        shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Call));

        nextRelationshipManager.storeRelationship(statement1, statement2, true);
        nextRelationshipManager.storeRelationship(statement2, statement1, true);
        nextRelationshipManager.storeRelationship(statement1, statement1, false);

        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::While, StatementType::While, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::While, StatementType::While, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::While, StatementType::Call, true).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::While, StatementType::Call, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Stmt, true).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Stmt, false).size() == 3);

        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::While, *statement1, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::While, *statement1, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Call, *statement1, true).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Call, *statement1, false).size() == 1);

        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Stmt).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::While).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Call).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::If).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Print).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Read).size() == 0);

        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Stmt, true).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Stmt, false).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Call, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Assign, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Assign, false).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Print, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Print, false).size() == 0);

        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Stmt).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Assign).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Print).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Call).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::While).size() == 1);

        REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement2, true) == true);
        REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement2, false) == true);
        REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement1, false) == true);
        REQUIRE(nextRelationshipManager.isRelationship(*statement2, *statement2, false) == false);
        REQUIRE(nextRelationshipManager.isRelationship(*statement2, *statement1, true) == true);

        REQUIRE(nextRelationshipManager.isFormer(*statement1) == true);
        REQUIRE(nextRelationshipManager.isFormer(*statement2) == true);

        REQUIRE(nextRelationshipManager.isLatter(*statement1) == true);
        REQUIRE(nextRelationshipManager.isLatter(*statement2) == true);

        REQUIRE(nextRelationshipManager.hasRelationship() == true);

        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::While).size() == 1);
        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::Stmt).size() == 1);
        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::Call).size() == 0);
    }
}