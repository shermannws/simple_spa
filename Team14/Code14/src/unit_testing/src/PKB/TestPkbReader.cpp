#include "../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "PKB/Pkb.h"
#include "Commons/Entities/AssignStatement.h"
#include "catch.hpp"

using namespace std;

TEST_CASE_METHOD(UnitTestFixture, "Test initialising PKB Reader") {
    Pkb pkb = Pkb();

    REQUIRE_NOTHROW(pkb.createPkbReader());
}

TEST_CASE_METHOD(UnitTestFixture, "Test Entities") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Variable v = Variable("x");
    Constant c = Constant("1");
    Procedure p = Procedure("main");
    Statement s = Statement(1, StatementType::Print);
    Statement s2 = Statement(2, StatementType::Read);
    Statement s3 = Statement(3, StatementType::Assign);
    Statement s4 = Statement(4, StatementType::Call);
    Statement s5 = Statement(5, StatementType::If);
    Statement s6 = Statement(6, StatementType::While);

    REQUIRE(reader->getAllVariables().empty());
    REQUIRE(reader->getAllConstants().empty());
    REQUIRE(reader->getAllProcedures().empty());
    REQUIRE(reader->getAllStatements().empty());
    REQUIRE(reader->getAllRead().empty());
    REQUIRE(reader->getAllPrint().empty());
    REQUIRE(reader->getAllAssign().empty());
    REQUIRE(reader->getAllCall().empty());
    REQUIRE(reader->getAllIf().empty());
    REQUIRE(reader->getAllWhile().empty());

    writer->addVariable(make_shared<Variable>(v));
    writer->addConstant(make_shared<Constant>(c));
    writer->addProcedure(make_shared<Procedure>(p));
    writer->addPrintStatement(make_shared<Statement>(s));
    writer->addReadStatement(make_shared<Statement>(s2));
    writer->addAssignStatement(make_shared<Statement>(s3));
    writer->addAssignPattern(make_shared<Statement>(s3), make_shared<Variable>(v), make_shared<Expression>("(x)"));
    writer->addCallStatement(make_shared<Statement>(s4));
    writer->addIfStatement(make_shared<Statement>(s5));
    writer->addWhileStatement(make_shared<Statement>(s6));

    REQUIRE(reader->getAllVariables().size() == 1);
    REQUIRE(reader->getAllConstants().size() == 1);
    REQUIRE(reader->getAllProcedures().size() == 1);
    REQUIRE(reader->getAllStatements().size() == 6);
    REQUIRE(reader->getAllRead().size() == 1);
    REQUIRE(reader->getAllPrint().size() == 1);
    REQUIRE(reader->getAllAssign().size() == 1);
    REQUIRE(reader->getAllCall().size() == 1);
    REQUIRE(reader->getAllIf().size() == 1);
    REQUIRE(reader->getAllWhile().size() == 1);
}

TEST_CASE_METHOD(UnitTestFixture, "Uses (Stmt) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Variable v = Variable("x");
    Statement s = Statement(1, StatementType::Print);

    REQUIRE(reader->getUsesStmtPair(StatementType::Stmt).empty());
    REQUIRE(reader->getUsesStmt(StatementType::Print).empty());
    REQUIRE(reader->getUsesVar(s).empty());
    REQUIRE(reader->getUsesTypeIdent(StatementType::Stmt, v).empty());
    REQUIRE(!reader->isStmtUsesVar(s, v));
    REQUIRE(!reader->hasUses(s));

    writer->addUsesRelationship(make_shared<Statement>(s), make_shared<Variable>(v));

    REQUIRE(reader->getUsesStmtPair(StatementType::Stmt).size() == 1);
    REQUIRE(reader->getUsesStmtPair(StatementType::Stmt)[0][0] == s);
    REQUIRE(reader->getUsesStmtPair(StatementType::Stmt)[0][1] == v);

    REQUIRE(reader->getUsesStmt(StatementType::Print).size() == 1);
    REQUIRE(reader->getUsesStmt(StatementType::Print)[0] == s);

    REQUIRE(reader->getUsesVar(s).size() == 1);
    REQUIRE(reader->getUsesVar(s)[0] == v);

    REQUIRE(reader->getUsesTypeIdent(StatementType::Stmt, v).size() == 1);
    REQUIRE(reader->getUsesTypeIdent(StatementType::Stmt, v)[0] == s);

    REQUIRE(reader->isStmtUsesVar(s, v));
    REQUIRE(reader->hasUses(s));

    // Negative tests
    Statement sNew = Statement(2, StatementType::Read);
    REQUIRE(reader->getUsesStmtPair(StatementType::Read).empty());
    REQUIRE(reader->getUsesStmt(StatementType::Read).empty());
    REQUIRE(reader->getUsesVar(sNew).empty());
    REQUIRE(reader->getUsesTypeIdent(StatementType::Read, v).empty());
    REQUIRE(!reader->isStmtUsesVar(sNew, v));
    REQUIRE(!reader->hasUses(sNew));
}

TEST_CASE_METHOD(UnitTestFixture, "Uses (Proc) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Variable v = Variable("x");
    Procedure p = Procedure("main");

    REQUIRE(reader->getUsesProcPair().empty());
    REQUIRE(reader->getUsesProc().empty());
    REQUIRE(reader->getUsesVar(p).empty());
    REQUIRE(reader->getUsesProcIdent(v).empty());
    REQUIRE(!reader->isProcUsesVar(p, v));
    REQUIRE(!reader->hasUses(p));

    writer->addUsesProcRelationship(make_shared<Procedure>(p), make_shared<Variable>(v));

    REQUIRE(reader->getUsesProcPair().size() == 1);
    REQUIRE(reader->getUsesProcPair()[0][0] == p);
    REQUIRE(reader->getUsesProcPair()[0][1] == v);

    REQUIRE(reader->getUsesProc().size() == 1);
    REQUIRE(reader->getUsesProc()[0] == p);

    REQUIRE(reader->getUsesVar(p).size() == 1);
    REQUIRE(reader->getUsesVar(p)[0] == v);

    REQUIRE(reader->getUsesProcIdent(v).size() == 1);
    REQUIRE(reader->getUsesProcIdent(v)[0] == p);

    REQUIRE(reader->isProcUsesVar(p, v));
    REQUIRE(reader->hasUses(p));

    // Negative tests
    Procedure pNew = Procedure("anotherProcedure");
    REQUIRE(reader->getUsesVar(pNew).empty());
    REQUIRE(!reader->isProcUsesVar(pNew, v));
    REQUIRE(!reader->hasUses(pNew));
}


TEST_CASE_METHOD(UnitTestFixture, "Modifies (Stmt) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Variable v = Variable("x");
    Statement s = Statement(1, StatementType::Read);

    REQUIRE(reader->getModifiesStmtPair(StatementType::Stmt).empty());
    REQUIRE(reader->getModifiesStmt(StatementType::Read).empty());
    REQUIRE(reader->getModifiesVar(s).empty());
    REQUIRE(reader->getModifiesTypeIdent(StatementType::Stmt, v).empty());
    REQUIRE(!reader->isStmtModifiesVar(s, v));
    REQUIRE(!reader->hasModifies(s));

    writer->addModifiesRelationship(make_shared<Statement>(s), make_shared<Variable>(v));

    REQUIRE(reader->getModifiesStmtPair(StatementType::Stmt).size() == 1);
    REQUIRE(reader->getModifiesStmtPair(StatementType::Stmt)[0][0] == s);
    REQUIRE(reader->getModifiesStmtPair(StatementType::Stmt)[0][1] == v);

    REQUIRE(reader->getModifiesStmt(StatementType::Read).size() == 1);
    REQUIRE(reader->getModifiesStmt(StatementType::Read)[0] == s);

    REQUIRE(reader->getModifiesVar(s).size() == 1);
    REQUIRE(reader->getModifiesVar(s)[0] == v);

    REQUIRE(reader->getModifiesTypeIdent(StatementType::Stmt, v).size() == 1);
    REQUIRE(reader->getModifiesTypeIdent(StatementType::Stmt, v)[0] == s);

    REQUIRE(reader->isStmtModifiesVar(s, v));
    REQUIRE(reader->hasModifies(s));

    // Negative tests
    Statement sNew = Statement(2, StatementType::Print);
    REQUIRE(reader->getModifiesStmtPair(StatementType::Print).empty());
    REQUIRE(reader->getModifiesStmt(StatementType::Print).empty());
    REQUIRE(reader->getModifiesVar(sNew).empty());
    REQUIRE(reader->getModifiesTypeIdent(StatementType::Print, v).empty());
    REQUIRE(!reader->isStmtModifiesVar(sNew, v));
    REQUIRE(!reader->hasModifies(sNew));
}

TEST_CASE_METHOD(UnitTestFixture, "Modifies (Proc) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Variable v = Variable("x");
    Procedure p = Procedure("main");

    REQUIRE(reader->getModifiesProcPair().empty());
    REQUIRE(reader->getModifiesProc().empty());
    REQUIRE(reader->getModifiesVar(p).empty());
    REQUIRE(reader->getModifiesProcIdent(v).empty());
    REQUIRE(!reader->isProcModifiesVar(p, v));
    REQUIRE(!reader->hasModifies(p));

    writer->addModifiesProcRelationship(make_shared<Procedure>(p), make_shared<Variable>(v));

    REQUIRE(reader->getModifiesProcPair().size() == 1);
    REQUIRE(reader->getModifiesProcPair()[0][0] == p);
    REQUIRE(reader->getModifiesProcPair()[0][1] == v);

    REQUIRE(reader->getModifiesProc().size() == 1);
    REQUIRE(reader->getModifiesProc()[0] == p);

    REQUIRE(reader->getModifiesVar(p).size() == 1);
    REQUIRE(reader->getModifiesVar(p)[0] == v);

    REQUIRE(reader->getModifiesProcIdent(v).size() == 1);
    REQUIRE(reader->getModifiesProcIdent(v)[0] == p);

    REQUIRE(reader->isProcModifiesVar(p, v));
    REQUIRE(reader->hasModifies(p));

    // Negative tests
    Procedure pNew = Procedure("anotherProcedure");
    REQUIRE(reader->getModifiesVar(pNew).empty());
    REQUIRE(!reader->isProcModifiesVar(pNew, v));
    REQUIRE(!reader->hasModifies(pNew));
}


TEST_CASE_METHOD(UnitTestFixture, "Follows(*) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Statement s = Statement(1, StatementType::Print);
    Statement s2 = Statement(2, StatementType::Read);

    REQUIRE(reader->getFollowsPair(StatementType::Stmt, StatementType::Stmt).empty());
    REQUIRE(reader->getFollowsStarPair(StatementType::Print, StatementType::Read).empty());
    REQUIRE(reader->getFollowsTypeStmt(StatementType::Print, s2).empty());
    REQUIRE(reader->getFollowsStarTypeStmt(StatementType::Stmt, s2).empty());
    REQUIRE(reader->getFollowsStmtType(s, StatementType::Read).empty());
    REQUIRE(reader->getFollowsStarStmtType(s, StatementType::Stmt).empty());
    REQUIRE(reader->getFollowsTypeWildcard(StatementType::Print).empty());
    REQUIRE(reader->getFollowsStarTypeWildcard(StatementType::Stmt).empty());
    REQUIRE(reader->getFollowsWildcardType(StatementType::Read).empty());
    REQUIRE(reader->getFollowsStarWildcardType(StatementType::Stmt).empty());
    REQUIRE(!reader->isFollows(s, s2));
    REQUIRE(!reader->isFollowsStar(s, s2));
    REQUIRE(!reader->hasFollows());
    REQUIRE(!reader->hasFollowsStar());
    REQUIRE(!reader->hasLatterStmt(s));
    REQUIRE(!reader->hasLatterStarStmt(s));
    REQUIRE(!reader->hasFormerStmt(s2));
    REQUIRE(!reader->hasFormerStarStmt(s2));

    writer->addFollowsRelationship(make_shared<Statement>(s), make_shared<Statement>(s2), true);

    REQUIRE(reader->getFollowsPair(StatementType::Stmt, StatementType::Stmt).size() == 1);
    REQUIRE(reader->getFollowsPair(StatementType::Stmt, StatementType::Stmt)[0][0] == s);
    REQUIRE(reader->getFollowsPair(StatementType::Stmt, StatementType::Stmt)[0][1] == s2);

    REQUIRE(reader->getFollowsStarPair(StatementType::Print, StatementType::Read).size() == 1);
    REQUIRE(reader->getFollowsStarPair(StatementType::Print, StatementType::Read)[0][0] == s);
    REQUIRE(reader->getFollowsStarPair(StatementType::Print, StatementType::Read)[0][1] == s2);

    REQUIRE(reader->getFollowsTypeStmt(StatementType::Print, s2).size() == 1);
    REQUIRE(reader->getFollowsTypeStmt(StatementType::Print, s2)[0] == s);

    REQUIRE(reader->getFollowsStarTypeStmt(StatementType::Stmt, s2).size() == 1);
    REQUIRE(reader->getFollowsStarTypeStmt(StatementType::Stmt, s2)[0] == s);

    REQUIRE(reader->getFollowsStmtType(s, StatementType::Read).size() == 1);
    REQUIRE(reader->getFollowsStmtType(s, StatementType::Read)[0] == s2);

    REQUIRE(reader->getFollowsStarStmtType(s, StatementType::Stmt).size() == 1);
    REQUIRE(reader->getFollowsStarStmtType(s, StatementType::Stmt)[0] == s2);

    REQUIRE(reader->getFollowsTypeWildcard(StatementType::Print).size() == 1);
    REQUIRE(reader->getFollowsTypeWildcard(StatementType::Print)[0] == s);

    REQUIRE(reader->getFollowsStarTypeWildcard(StatementType::Stmt).size() == 1);
    REQUIRE(reader->getFollowsStarTypeWildcard(StatementType::Stmt)[0] == s);

    REQUIRE(reader->getFollowsWildcardType(StatementType::Read).size() == 1);
    REQUIRE(reader->getFollowsWildcardType(StatementType::Read)[0] == s2);

    REQUIRE(reader->getFollowsStarWildcardType(StatementType::Stmt).size() == 1);
    REQUIRE(reader->getFollowsStarWildcardType(StatementType::Stmt)[0] == s2);

    REQUIRE(reader->isFollows(s, s2));
    REQUIRE(reader->isFollowsStar(s, s2));

    REQUIRE(reader->hasFollows());
    REQUIRE(reader->hasFollowsStar());

    REQUIRE(reader->hasLatterStmt(s));
    REQUIRE(reader->hasLatterStarStmt(s));
    REQUIRE(reader->hasFormerStmt(s2));
    REQUIRE(reader->hasFormerStarStmt(s2));
}

TEST_CASE_METHOD(UnitTestFixture, "Parent(*) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Statement s = Statement(1, StatementType::While);
    Statement s2 = Statement(2, StatementType::Read);

    writer->addParentRelationship(make_shared<Statement>(s), make_shared<Statement>(s2), true);

    REQUIRE(reader->getParentPair(StatementType::Stmt, StatementType::Stmt).size() == 1);
    REQUIRE(reader->getParentPair(StatementType::Stmt, StatementType::Stmt)[0][0] == s);
    REQUIRE(reader->getParentPair(StatementType::Stmt, StatementType::Stmt)[0][1] == s2);

    REQUIRE(reader->getParentStarPair(StatementType::While, StatementType::Read).size() == 1);
    REQUIRE(reader->getParentStarPair(StatementType::While, StatementType::Read)[0][0] == s);
    REQUIRE(reader->getParentStarPair(StatementType::While, StatementType::Read)[0][1] == s2);

    REQUIRE(reader->getParentTypeStmt(StatementType::While, s2).size() == 1);
    REQUIRE(reader->getParentTypeStmt(StatementType::While, s2)[0] == s);

    REQUIRE(reader->getParentStarTypeStmt(StatementType::Stmt, s2).size() == 1);
    REQUIRE(reader->getParentStarTypeStmt(StatementType::Stmt, s2)[0] == s);

    REQUIRE(reader->getParentStmtType(s, StatementType::Read).size() == 1);
    REQUIRE(reader->getParentStmtType(s, StatementType::Read)[0] == s2);

    REQUIRE(reader->getParentStarStmtType(s, StatementType::Stmt).size() == 1);
    REQUIRE(reader->getParentStarStmtType(s, StatementType::Stmt)[0] == s2);

    REQUIRE(reader->getParentTypeWildcard(StatementType::While).size() == 1);
    REQUIRE(reader->getParentTypeWildcard(StatementType::While)[0] == s);

    REQUIRE(reader->getParentStarTypeWildcard(StatementType::Stmt).size() == 1);
    REQUIRE(reader->getParentStarTypeWildcard(StatementType::Stmt)[0] == s);

    REQUIRE(reader->getParentWildcardType(StatementType::Read).size() == 1);
    REQUIRE(reader->getParentWildcardType(StatementType::Read)[0] == s2);

    REQUIRE(reader->getParentStarWildcardType(StatementType::Stmt).size() == 1);
    REQUIRE(reader->getParentStarWildcardType(StatementType::Stmt)[0] == s2);

    REQUIRE(reader->isParent(s, s2));
    REQUIRE(reader->isParentStar(s, s2));

    REQUIRE(reader->hasParent());
    REQUIRE(reader->hasParentStar());

    REQUIRE(reader->hasChildStmt(s));
    REQUIRE(reader->hasChildStarStmt(s));
    REQUIRE(reader->hasParentStmt(s2));
    REQUIRE(reader->hasParentStarStmt(s2));

    // Negative tests
    Statement sNew = Statement(3, StatementType::Print);
    REQUIRE(reader->getParentPair(StatementType::Print, StatementType::Stmt).empty());
    REQUIRE(reader->getParentStarPair(StatementType::Print, StatementType::Read).empty());
    REQUIRE(reader->getParentTypeStmt(StatementType::Print, s2).empty());
    REQUIRE(reader->getParentStarTypeStmt(StatementType::Print, s2).empty());
    REQUIRE(reader->getParentStmtType(sNew, StatementType::Read).empty());
    REQUIRE(reader->getParentStarStmtType(sNew, StatementType::Stmt).empty());
    REQUIRE(reader->getParentTypeWildcard(StatementType::Print).empty());
    REQUIRE(reader->getParentStarTypeWildcard(StatementType::Print).empty());
    REQUIRE(reader->getParentWildcardType(StatementType::Print).empty());
    REQUIRE(reader->getParentStarWildcardType(StatementType::Print).empty());
    REQUIRE(!reader->isParent(sNew, s2));
    REQUIRE(!reader->isParentStar(sNew, s2));
    REQUIRE(!reader->hasChildStmt(sNew));
    REQUIRE(!reader->hasChildStarStmt(sNew));
    REQUIRE(!reader->hasParentStmt(sNew));
    REQUIRE(!reader->hasParentStarStmt(sNew));
}


TEST_CASE_METHOD(UnitTestFixture, "Calls(*) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Procedure p = Procedure("main");
    Procedure p2 = Procedure("main2");

    REQUIRE(!reader->hasCalls());
    REQUIRE(!reader->hasCallsStar());
    REQUIRE(!reader->isCallee(p2));
    REQUIRE(!reader->isCalleeStar(p2));
    REQUIRE(!reader->isCaller(p));
    REQUIRE(!reader->isCallerStar(p));
    REQUIRE(reader->getCallees().empty());
    REQUIRE(reader->getCalleesStar().empty());
    REQUIRE(reader->getCallers().empty());
    REQUIRE(reader->getCallersStar().empty());
    REQUIRE(reader->getCallsPair().empty());
    REQUIRE(reader->getCallsStarPair().empty());
    REQUIRE(reader->getCallers(p2).empty());
    REQUIRE(reader->getCallersStar(p2).empty());
    REQUIRE(reader->getCallees(p).empty());
    REQUIRE(reader->getCalleesStar(p).empty());

    writer->addCallsRelationship(make_shared<Procedure>(p), make_shared<Procedure>(p2));
    writer->triggerTransitiveCalc();

    REQUIRE(reader->hasCalls());
    REQUIRE(reader->hasCallsStar());

    REQUIRE(reader->isCallee(p2));
    REQUIRE(reader->isCalleeStar(p2));

    REQUIRE(reader->isCaller(p));
    REQUIRE(reader->isCallerStar(p));

    REQUIRE(reader->isCalls(p, p2));
    REQUIRE(reader->isCallsStar(p, p2));

    REQUIRE(reader->getCallees().size() == 1);
    REQUIRE(reader->getCallees()[0] == p2);
    REQUIRE(reader->getCalleesStar().size() == 1);
    REQUIRE(reader->getCalleesStar()[0] == p2);

    REQUIRE(reader->getCallers().size() == 1);
    REQUIRE(reader->getCallers()[0] == p);
    REQUIRE(reader->getCallersStar().size() == 1);
    REQUIRE(reader->getCallersStar()[0] == p);

    REQUIRE(reader->getCallsPair().size() == 1);
    REQUIRE(reader->getCallsPair()[0][0] == p);
    REQUIRE(reader->getCallsPair()[0][1] == p2);
    REQUIRE(reader->getCallsStarPair().size() == 1);
    REQUIRE(reader->getCallsStarPair()[0][0] == p);
    REQUIRE(reader->getCallsStarPair()[0][1] == p2);

    REQUIRE(reader->getCallers(p2).size() == 1);
    REQUIRE(reader->getCallers(p2)[0] == p);
    REQUIRE(reader->getCallersStar(p2).size() == 1);
    REQUIRE(reader->getCallersStar(p2)[0] == p);

    REQUIRE(reader->getCallees(p).size() == 1);
    REQUIRE(reader->getCallees(p)[0] == p2);
    REQUIRE(reader->getCalleesStar(p).size() == 1);
    REQUIRE(reader->getCalleesStar(p)[0] == p2);

    // Negative Cases
    Procedure pNew = Procedure("main3");
    REQUIRE(!reader->isCallee(pNew));
    REQUIRE(!reader->isCalleeStar(pNew));
    REQUIRE(!reader->isCaller(pNew));
    REQUIRE(!reader->isCallerStar(pNew));
    REQUIRE(reader->getCallers(pNew).empty());
    REQUIRE(reader->getCallersStar(pNew).empty());
    REQUIRE(reader->getCallees(pNew).empty());
    REQUIRE(reader->getCalleesStar(pNew).empty());
}

TEST_CASE_METHOD(UnitTestFixture, "Assign Pattern") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Statement s = Statement(1, StatementType::Assign);
    Variable v = Variable("x");
    Expression e = Expression("((x)+(y))*1");//(x+y) * 1
    Expression subExpr = Expression("((x)+(y))");

    REQUIRE(reader->getAllAssign().empty());
    REQUIRE(reader->getAssignStmtsByRhs(subExpr, true).empty());
    REQUIRE(reader->getAssignStmtsByRhs(e, false).empty());
    REQUIRE(reader->getAssignStmtsByLhs(v).empty());
    REQUIRE(reader->getAssignStmtsByLhsRhs(v, subExpr, true).empty());
    REQUIRE(reader->getAssignStmtsByLhsRhs(v, e, false).empty());
    REQUIRE(reader->getAllAssignStmtVarPair().empty());
    REQUIRE(reader->getAssignStmtsVarPairByRhs(subExpr, true).empty());
    REQUIRE(reader->getAssignStmtsVarPairByRhs(e, false).empty());

    writer->addAssignStatement(make_shared<Statement>(s));
    writer->addAssignPattern(make_shared<Statement>(s), make_shared<Variable>(v), make_shared<Expression>(e));

    REQUIRE(reader->getAllAssign().size() == 1);
    REQUIRE(reader->getAllAssign()[0] == s);

    REQUIRE(reader->getAssignStmtsByRhs(subExpr, true).size() == 1);
    REQUIRE(reader->getAssignStmtsByRhs(subExpr, true)[0] == s);
    REQUIRE(reader->getAssignStmtsByRhs(e, false).size() == 1);
    REQUIRE(reader->getAssignStmtsByRhs(e, false)[0] == s);

    REQUIRE(reader->getAssignStmtsByLhs(v).size() == 1);
    REQUIRE(reader->getAssignStmtsByLhs(v)[0] == s);

    REQUIRE(reader->getAssignStmtsByLhsRhs(v, subExpr, true).size() == 1);
    REQUIRE(reader->getAssignStmtsByLhsRhs(v, subExpr, true)[0] == s);
    REQUIRE(reader->getAssignStmtsByLhsRhs(v, e, false).size() == 1);
    REQUIRE(reader->getAssignStmtsByLhsRhs(v, e, false)[0] == s);

    REQUIRE(reader->getAllAssignStmtVarPair().size() == 1);
    REQUIRE(reader->getAllAssignStmtVarPair()[0][0] == s);
    REQUIRE(reader->getAllAssignStmtVarPair()[0][1] == v);

    REQUIRE(reader->getAssignStmtsVarPairByRhs(subExpr, true).size() == 1);
    REQUIRE(reader->getAssignStmtsVarPairByRhs(subExpr, true)[0][0] == s);
    REQUIRE(reader->getAssignStmtsVarPairByRhs(subExpr, true)[0][1] == v);
    REQUIRE(reader->getAssignStmtsVarPairByRhs(e, false).size() == 1);
    REQUIRE(reader->getAssignStmtsVarPairByRhs(e, false)[0][0] == s);
    REQUIRE(reader->getAssignStmtsVarPairByRhs(e, false)[0][1] == v);

    // Negative tests
    Expression eNew = Expression("((x)+(z))*2");
    Expression subExprNew = Expression("((x)+(z))");
    REQUIRE(reader->getAssignStmtsByRhs(subExprNew, true).empty());
    REQUIRE(reader->getAssignStmtsByRhs(eNew, false).empty());
    REQUIRE(reader->getAssignStmtsByLhsRhs(v, subExprNew, true).empty());
    REQUIRE(reader->getAssignStmtsByLhsRhs(v, eNew, false).empty());
    REQUIRE(reader->getAssignStmtsVarPairByRhs(subExprNew, true).empty());
    REQUIRE(reader->getAssignStmtsVarPairByRhs(eNew, false).empty());
}

TEST_CASE_METHOD(UnitTestFixture, "Next(*) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Statement s = Statement(1, StatementType::Print);
    Statement s1 = Statement(2, StatementType::Read);

    REQUIRE(reader->getNextPair(StatementType::Stmt, StatementType::Stmt).empty());
    REQUIRE(reader->getNextStarPair(StatementType::Print, StatementType::Read).empty());
    REQUIRE(reader->getNextStarSameStmt(StatementType::Stmt).empty());
    REQUIRE(reader->getNextTypeStmt(StatementType::Print, s1).empty());
    REQUIRE(reader->getNextStarTypeStmt(StatementType::Stmt, s1).empty());
    REQUIRE(reader->getNextTypeWildcard(StatementType::Print).empty());
    REQUIRE(reader->getNextStarTypeWildcard(StatementType::Stmt).empty());
    REQUIRE(reader->getNextStmtType(s, StatementType::Read).empty());
    REQUIRE(reader->getNextStarStmtType(s, StatementType::Stmt).empty());
    REQUIRE(reader->getNextWildcardType(StatementType::Read).empty());
    REQUIRE(reader->getNextStarWildcardType(StatementType::Stmt).empty());
    REQUIRE(!reader->isNext(s, s1));
    REQUIRE(!reader->isNextStar(s, s1));
    REQUIRE(!reader->hasNext());
    REQUIRE(!reader->hasNextStar());
    REQUIRE(!reader->hasBeforeStmt(s1));
    REQUIRE(!reader->hasBeforeStarStmt(s1));
    REQUIRE(!reader->hasAfterStmt(s));
    REQUIRE(!reader->hasAfterStarStmt(s));

    writer->addNextRelationship(make_shared<Statement>(s), make_shared<Statement>(s1));

    REQUIRE(reader->getNextPair(StatementType::Stmt, StatementType::Stmt).size() == 1);
    REQUIRE(reader->getNextPair(StatementType::Stmt, StatementType::Stmt)[0][0] == s);
    REQUIRE(reader->getNextPair(StatementType::Stmt, StatementType::Stmt)[0][1] == s1);

    REQUIRE(reader->getNextStarPair(StatementType::Print, StatementType::Read).size() == 1);
    REQUIRE(reader->getNextStarPair(StatementType::Print, StatementType::Read)[0][0] == s);
    REQUIRE(reader->getNextStarPair(StatementType::Print, StatementType::Read)[0][1] == s1);

    REQUIRE(reader->getNextStarSameStmt(StatementType::Stmt).empty());

    REQUIRE(reader->getNextTypeStmt(StatementType::Print, s1).size() == 1);
    REQUIRE(reader->getNextTypeStmt(StatementType::Print, s1)[0] == s);

    REQUIRE(reader->getNextStarTypeStmt(StatementType::Stmt, s1).size() == 1);
    REQUIRE(reader->getNextStarTypeStmt(StatementType::Stmt, s1)[0] == s);

    REQUIRE(reader->getNextTypeWildcard(StatementType::Print).size() == 1);
    REQUIRE(reader->getNextTypeWildcard(StatementType::Print)[0] == s);

    REQUIRE(reader->getNextStarTypeWildcard(StatementType::Stmt).size() == 1);
    REQUIRE(reader->getNextStarTypeWildcard(StatementType::Stmt)[0] == s);

    REQUIRE(reader->getNextStmtType(s, StatementType::Read).size() == 1);
    REQUIRE(reader->getNextStmtType(s, StatementType::Read)[0] == s1);

    REQUIRE(reader->getNextStarStmtType(s, StatementType::Stmt).size() == 1);
    REQUIRE(reader->getNextStarStmtType(s, StatementType::Stmt)[0] == s1);

    REQUIRE(reader->getNextWildcardType(StatementType::Read).size() == 1);
    REQUIRE(reader->getNextWildcardType(StatementType::Read)[0] == s1);

    REQUIRE(reader->getNextStarWildcardType(StatementType::Stmt).size() == 1);
    REQUIRE(reader->getNextStarWildcardType(StatementType::Stmt)[0] == s1);

    REQUIRE(reader->isNext(s, s1));
    REQUIRE(reader->isNextStar(s, s1));

    REQUIRE(reader->hasNext());
    REQUIRE(reader->hasNextStar());

    REQUIRE(reader->hasBeforeStmt(s1));
    REQUIRE(reader->hasBeforeStarStmt(s1));

    REQUIRE(reader->hasAfterStmt(s));
    REQUIRE(reader->hasAfterStarStmt(s));

    // Negative tests
    Statement sNew = Statement(3, StatementType::Assign);
    REQUIRE(reader->getNextPair(StatementType::Assign, StatementType::Stmt).empty());
    REQUIRE(reader->getNextStarPair(StatementType::Assign, StatementType::Read).empty());
    REQUIRE(reader->getNextTypeStmt(StatementType::Assign, s1).empty());
    REQUIRE(reader->getNextStarTypeStmt(StatementType::Assign, s1).empty());
    REQUIRE(reader->getNextStmtType(sNew, StatementType::Read).empty());
    REQUIRE(reader->getNextStarStmtType(sNew, StatementType::Stmt).empty());
    REQUIRE(reader->getNextTypeWildcard(StatementType::Assign).empty());
    REQUIRE(reader->getNextStarTypeWildcard(StatementType::Assign).empty());
    REQUIRE(reader->getNextWildcardType(StatementType::Assign).empty());
    REQUIRE(reader->getNextStarWildcardType(StatementType::Assign).empty());
    REQUIRE(!reader->isNext(sNew, s1));
    REQUIRE(!reader->isNextStar(sNew, s1));
    REQUIRE(!reader->hasBeforeStmt(sNew));
    REQUIRE(!reader->hasBeforeStarStmt(sNew));
    REQUIRE(!reader->hasAfterStmt(sNew));
    REQUIRE(!reader->hasAfterStarStmt(sNew));

    writer->clearCache();
}

TEST_CASE_METHOD(UnitTestFixture, "If Pattern") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Statement s = Statement(1, StatementType::If);
    Variable v = Variable("x");

    REQUIRE(reader->getAllIfPatternStmts().empty());
    REQUIRE(reader->getIfStmtsByVar(v).empty());
    REQUIRE(reader->getAllIfStmtVarPair().empty());

    writer->addIfPattern(make_shared<Statement>(s),
                         make_shared<vector<shared_ptr<Variable>>>(1, make_shared<Variable>(v)));

    REQUIRE(reader->getAllIfPatternStmts().size() == 1);
    REQUIRE(reader->getAllIfPatternStmts()[0] == s);
    REQUIRE(reader->getIfStmtsByVar(v).size() == 1);
    REQUIRE(reader->getIfStmtsByVar(v)[0] == s);
    REQUIRE(reader->getAllIfStmtVarPair().size() == 1);
    REQUIRE(reader->getAllIfStmtVarPair()[0][0] == s);
    REQUIRE(reader->getAllIfStmtVarPair()[0][1] == v);
}

TEST_CASE_METHOD(UnitTestFixture, "While Pattern") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Statement s = Statement(1, StatementType::While);
    Variable v = Variable("x");

    REQUIRE(reader->getAllWhilePatternStmts().empty());
    REQUIRE(reader->getWhileStmtsByVar(v).empty());
    REQUIRE(reader->getAllWhileStmtVarPair().empty());

    writer->addWhilePattern(make_shared<Statement>(s),
                            make_shared<vector<shared_ptr<Variable>>>(1, make_shared<Variable>(v)));

    REQUIRE(reader->getAllWhilePatternStmts().size() == 1);
    REQUIRE(reader->getAllWhilePatternStmts()[0] == s);
    REQUIRE(reader->getWhileStmtsByVar(v).size() == 1);
    REQUIRE(reader->getWhileStmtsByVar(v)[0] == s);
    REQUIRE(reader->getAllWhileStmtVarPair().size() == 1);
    REQUIRE(reader->getAllWhileStmtVarPair()[0][0] == s);
    REQUIRE(reader->getAllWhileStmtVarPair()[0][1] == v);
}

TEST_CASE_METHOD(UnitTestFixture, "Affects Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    REQUIRE_FALSE(reader->hasAffects());
    writer->clearCache();

    /* Construct sample SIMPLE program
    procedure Second {
        01        x = 0;
        02        z = x + 2*y;
        03        z = z + x;
    */

    auto stmt1 = make_shared<AssignStatement>(AssignStatement(1));
    auto varX = make_shared<Variable>("x");
    writer->addModifiesRelationship(stmt1, varX);
    writer->addAssignPattern(stmt1, varX, make_shared<Expression>("0"));

    auto stmt2 = make_shared<AssignStatement>(AssignStatement(2));
    auto varY = make_shared<Variable>("y");
    auto varZ = make_shared<Variable>("z");
    writer->addModifiesRelationship(stmt2, varZ);
    writer->addUsesRelationship(stmt2, varX);
    writer->addUsesRelationship(stmt2, varY);
    writer->addAssignPattern(stmt2, varZ, make_shared<Expression>("x + 2*y"));
    writer->addNextRelationship(stmt1, stmt2);

    auto stmt3 = make_shared<AssignStatement>(AssignStatement(3));
    writer->addModifiesRelationship(stmt3, varZ);
    writer->addUsesRelationship(stmt3, varZ);
    writer->addUsesRelationship(stmt3, varX);
    writer->addAssignPattern(stmt3, varZ, make_shared<Expression>("z + x"));
    writer->addNextRelationship(stmt2, stmt3);

    REQUIRE(reader->getAffectsPair(StatementType::Assign, StatementType::Assign).size() ==3);

    REQUIRE(reader->getAffectsTypeStmt(StatementType::Assign, *stmt1).empty());
    REQUIRE(reader->getAffectsTypeStmt(StatementType::Assign, *stmt2).size() == 1);
    REQUIRE(reader->getAffectsTypeStmt(StatementType::Assign, *stmt3).size() == 2);

    REQUIRE(reader->getAffectsTypeWildcard(StatementType::Assign).size() == 2);

    REQUIRE(reader->getAffectsStmtType(*stmt1, StatementType::Assign).size() == 2);
    REQUIRE(reader->getAffectsStmtType(*stmt2, StatementType::Assign).size() == 1);
    REQUIRE(reader->getAffectsStmtType(*stmt3, StatementType::Assign).empty());

    REQUIRE(reader->getAffectsWildcardType(StatementType::Assign).size() == 2);

    REQUIRE(reader->hasAffects());

    REQUIRE(reader->isAffects(*stmt1, *stmt2));
    REQUIRE(reader->isAffects(*stmt2, *stmt3));
    REQUIRE(reader->isAffects(*stmt1, *stmt3));

    REQUIRE_FALSE(reader->hasAffectsStmt(*stmt1));
    REQUIRE(reader->hasAffectsStmt(*stmt2));
    REQUIRE(reader->hasAffectsStmt(*stmt3));

    REQUIRE(reader->hasAffectedStmt(*stmt1));
    REQUIRE(reader->hasAffectedStmt(*stmt2));
    REQUIRE_FALSE(reader->hasAffectedStmt(*stmt3));
}
