#include <memory>

#include "PKB/Managers/NextRelationshipManager.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test Next/Next* Relationship Retrieval") {
    SECTION("Simple Test 1") {
        NextRelationshipManager nextRelationshipManager = NextRelationshipManager();

        REQUIRE(nextRelationshipManager.hasRelationship() == false);

        // 1-->2-->3
        shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Assign));
        shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Call));
        shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::Print));

        nextRelationshipManager.storeRelationship(statement1, statement2, true);
        nextRelationshipManager.storeRelationship(statement2, statement3, true);

        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Stmt, true).size() ==
                2);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Stmt, false).size() ==
                3);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Call, true).size() ==
                1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Call, false).size() ==
                1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Print, true).size() ==
                0);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Print, false)
                        .size() == 1);

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

        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Stmt, true).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Assign, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Print, true).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Call, true).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::If, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::While, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Read, true).size() == 0);

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

        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Stmt, true).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Assign, true).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Print, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Call, true).size() == 1);

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

    SECTION("Simple Test 2") {
        NextRelationshipManager nextRelationshipManager = NextRelationshipManager();

        REQUIRE(nextRelationshipManager.hasRelationship() == false);

        // 1 -- > 2 -- > 1
        shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::While));
        shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Call));

        nextRelationshipManager.storeRelationship(statement1, statement2, true);
        nextRelationshipManager.storeRelationship(statement2, statement1, true);

        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::While, StatementType::While, true).size() ==
                0);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::While, StatementType::While, false).size() ==
                1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::While, StatementType::Call, true).size() ==
                1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::While, StatementType::Call, false).size() ==
                1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Stmt, true).size() ==
                2);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Stmt, false).size() ==
                4);

        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::While, *statement1, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::While, *statement1, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Call, *statement1, true).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Call, *statement1, false).size() == 1);

        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Stmt, true).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::While, true).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Call, true).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::If, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Print, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Read, true).size() == 0);

        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Stmt, true).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Stmt, false).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Call, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Assign, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Assign, false).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Print, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Print, false).size() == 0);

        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Stmt, true).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Assign, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Print, true).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Call, true).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::While, true).size() == 1);

        REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement2, true) == true);
        REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement2, false) == true);
        REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement1, false) == true);
        REQUIRE(nextRelationshipManager.isRelationship(*statement2, *statement2, false) == true);
        REQUIRE(nextRelationshipManager.isRelationship(*statement2, *statement1, true) == true);

        REQUIRE(nextRelationshipManager.isFormer(*statement1) == true);
        REQUIRE(nextRelationshipManager.isFormer(*statement2) == true);

        REQUIRE(nextRelationshipManager.isLatter(*statement1) == true);
        REQUIRE(nextRelationshipManager.isLatter(*statement2) == true);

        REQUIRE(nextRelationshipManager.hasRelationship() == true);

        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::While).size() == 1);
        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::Stmt).size() == 2);
        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::Call).size() == 1);
    }

    SECTION("Intermediate Test 1 - While Loop at node 3") {
        NextRelationshipManager nextRelationshipManager = NextRelationshipManager();

        REQUIRE(nextRelationshipManager.hasRelationship() == false);

        // 1 -- > 2 -- > 3 --> 4,5
        //                 <--
        //                 --------> 6
        shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Call));
        shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Call));
        shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::While));
        shared_ptr<Statement> statement4 = make_shared<Statement>(Statement(4, StatementType::Print));
        shared_ptr<Statement> statement5 = make_shared<Statement>(Statement(5, StatementType::Read));
        shared_ptr<Statement> statement6 = make_shared<Statement>(Statement(6, StatementType::Call));

        nextRelationshipManager.storeRelationship(statement1, statement2, true);
        nextRelationshipManager.storeRelationship(statement2, statement3, true);
        nextRelationshipManager.storeRelationship(statement3, statement4, true);
        nextRelationshipManager.storeRelationship(statement4, statement5, true);
        nextRelationshipManager.storeRelationship(statement5, statement3, true);
        nextRelationshipManager.storeRelationship(statement3, statement6, true);

        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Call, StatementType::Call, false).size() ==
                3);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::While, StatementType::While, false).size() ==
                1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Read, StatementType::Read, false).size() ==
                1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Read, StatementType::Print, false).size() ==
                1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::While, StatementType::Stmt, false).size() ==
                4);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Call, StatementType::Stmt, false).size() ==
                9);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Stmt, StatementType::Print, false).size() ==
                5);
        nextRelationshipManager.clearNextStarStore();

        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Call, *statement1, false).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Call, *statement2, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::While, *statement3, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Read, *statement6, false).size() == 1);
        nextRelationshipManager.clearNextStarStore();

        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Call, false).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::While, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Read, false).size() == 1);
        nextRelationshipManager.clearNextStarStore();

        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Call, false).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Call, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement3, StatementType::While, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement4, StatementType::While, false).size() == 1);
        nextRelationshipManager.clearNextStarStore();

        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Call, false).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::While, false).size() == 1);
        nextRelationshipManager.clearNextStarStore();

        REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement2, false) == true);
        REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement6, false) == true);
        REQUIRE(nextRelationshipManager.isRelationship(*statement5, *statement5, false) == true);
        nextRelationshipManager.clearNextStarStore();

        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::Stmt).size() == 3);
        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::While).size() == 1);
        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::Read).size() == 1);
        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::Print).size() == 1);
        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::Call).size() == 0);
        nextRelationshipManager.clearNextStarStore();
    }

    SECTION("Intermeidate Test 2 - If at node 3") {
        NextRelationshipManager nextRelationshipManager = NextRelationshipManager();

        REQUIRE(nextRelationshipManager.hasRelationship() == false);

        // 1c -- > 2c -- > 3if --> 4pn --> 6c
        //                     --> 5rd -->
        shared_ptr<Statement> statement1 = make_shared<Statement>(Statement(1, StatementType::Call));
        shared_ptr<Statement> statement2 = make_shared<Statement>(Statement(2, StatementType::Call));
        shared_ptr<Statement> statement3 = make_shared<Statement>(Statement(3, StatementType::If));
        shared_ptr<Statement> statement4 = make_shared<Statement>(Statement(4, StatementType::Print));
        shared_ptr<Statement> statement5 = make_shared<Statement>(Statement(5, StatementType::Read));
        shared_ptr<Statement> statement6 = make_shared<Statement>(Statement(6, StatementType::Call));

        nextRelationshipManager.storeRelationship(statement1, statement2, true);
        nextRelationshipManager.storeRelationship(statement2, statement3, true);
        nextRelationshipManager.storeRelationship(statement3, statement4, true);
        nextRelationshipManager.storeRelationship(statement3, statement5, true);
        nextRelationshipManager.storeRelationship(statement4, statement6, true);
        nextRelationshipManager.storeRelationship(statement5, statement6, true);

        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Call, StatementType::Call, false).size() ==
                3);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::If, StatementType::If, false).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::If, StatementType::Read, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::If, StatementType::Print, false).size() ==
                1);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::If, StatementType::Stmt, false).size() == 3);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Print, StatementType::Read, false).size() ==
                0);
        REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Print, StatementType::Stmt, false).size() ==
                1);
        nextRelationshipManager.clearNextStarStore();

        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Call, *statement1, false).size() == 0);
        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Call, *statement2, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::If, *statement4, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::If, *statement6, false).size() == 1);
        nextRelationshipManager.clearNextStarStore();

        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Call, false).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::If, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Read, false).size() == 1);
        nextRelationshipManager.clearNextStarStore();

        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Call, false).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Call, false).size() == 1);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement3, StatementType::Stmt, false).size() == 3);
        REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement4, StatementType::Call, false).size() == 1);
        nextRelationshipManager.clearNextStarStore();

        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Call, false).size() == 2);
        REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::If, false).size() == 1);
        nextRelationshipManager.clearNextStarStore();

        REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement2, false) == true);
        REQUIRE(nextRelationshipManager.isRelationship(*statement1, *statement6, false) == true);
        REQUIRE(nextRelationshipManager.isRelationship(*statement4, *statement5, false) == false);
        nextRelationshipManager.clearNextStarStore();

        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::Stmt).size() == 0);
        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::While).size() == 0);
        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::Read).size() == 0);
        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::Print).size() == 0);
        REQUIRE(nextRelationshipManager.getNextStarSameStmt(StatementType::Call).size() == 0);
        nextRelationshipManager.clearNextStarStore();
    }
}