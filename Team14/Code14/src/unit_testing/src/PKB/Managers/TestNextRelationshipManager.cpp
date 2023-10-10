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
    REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Print, true).size().empty());
    REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Print, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipPair(StatementType::Assign, StatementType::Print, true).empty());

    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement1, false).size().empty());
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement2, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement2, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Assign, *statement2, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Assign, *statement2, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Call, *statement2, false).size().empty());
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Print, *statement2, false).size().empty());
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement3, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Stmt, *statement3, false).size() == 2);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Assign, *statement3, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeStmt(StatementType::Assign, *statement3, true).empty());

    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Stmt).size() == 2);
    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Assign).empty());
    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Print).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Call).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::If).empty());
    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::While).empty());
    REQUIRE(nextRelationshipManager.getRelationshipWildcardType(StatementType::Read).empty());

    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Stmt, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Stmt, false).size() == 2);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Print, true).empty());
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement1, StatementType::Print, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Stmt, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Stmt, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Print, true).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Print, false).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Assign, true).size().empty());
    REQUIRE(nextRelationshipManager.getRelationshipStmtType(*statement2, StatementType::Assign, false).size().empty());

    REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Stmt).size() == 2);
    REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Assign).size() == 1);
    REQUIRE(nextRelationshipManager.getRelationshipTypeWildcard(StatementType::Print).empty());
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

    REQUIRE(nextRelationshipManager.isFormer(*statement1, false) == true);
    REQUIRE(nextRelationshipManager.isFormer(*statement2, false) == true);
    REQUIRE(nextRelationshipManager.isFormer(*statement3, false) == false);

    REQUIRE(nextRelationshipManager.isLatter(*statement1, false) == false);
    REQUIRE(nextRelationshipManager.isLatter(*statement1, false) == true);
    REQUIRE(nextRelationshipManager.isLatter(*statement1, false) == true);

    REQUIRE(nextRelationshipManager.hasRelationship() == true);
}