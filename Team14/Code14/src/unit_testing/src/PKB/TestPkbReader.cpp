#include "../TestingUtilities/TestFixture/UnitTestFixture.h"
#include "Commons/Entities/AssignStatement.h"
#include "PKB/Pkb.h"
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

    auto sp = make_shared<Statement>(s);
    auto vp = make_shared<Variable>(v);

    writer->addUsesRelationship(make_shared<Statement>(s), make_shared<Variable>(v));

    auto set1 = reader->getUsesStmtPair(StatementType::Stmt);
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({sp, vp}) != set1.end());

    auto set2 = reader->getUsesStmt(StatementType::Print);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(sp) != set2.end());

    auto set3 = reader->getUsesVar(s);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(vp) != set3.end());

    auto set4 = reader->getUsesTypeIdent(StatementType::Stmt, v);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(sp) != set4.end());

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

    auto pp = make_shared<Procedure>(p);
    auto vp = make_shared<Variable>(v);

    writer->addUsesProcRelationship(pp, vp);

    auto set1 = reader->getUsesProcPair();
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({pp, vp}) != set1.end());

    auto set2 = reader->getUsesProc();
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(pp) != set2.end());

    auto set3 = reader->getUsesVar(p);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(vp) != set3.end());

    auto set4 = reader->getUsesProcIdent(v);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(pp) != set4.end());

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

    auto sp = make_shared<Statement>(s);
    auto vp = make_shared<Variable>(v);

    writer->addModifiesRelationship(sp, vp);

    auto set1 = reader->getModifiesStmtPair(StatementType::Stmt);
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({sp, vp}) != set1.end());

    auto set2 = reader->getModifiesStmt(StatementType::Read);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(sp) != set2.end());

    auto set3 = reader->getModifiesVar(s);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(vp) != set3.end());

    auto set4 = reader->getModifiesTypeIdent(StatementType::Stmt, v);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(sp) != set4.end());

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

    auto pp = make_shared<Procedure>(p);
    auto vp = make_shared<Variable>(v);

    writer->addModifiesProcRelationship(pp, vp);

    auto set1 = reader->getModifiesProcPair();
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({pp, vp}) != set1.end());

    auto set2 = reader->getModifiesProc();
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(pp) != set2.end());

    auto set3 = reader->getModifiesVar(p);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(vp) != set3.end());

    auto set4 = reader->getModifiesProcIdent(v);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(pp) != set4.end());

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

    auto sp = make_shared<Statement>(s);
    auto sp2 = make_shared<Statement>(s2);

    writer->addFollowsRelationship(sp, sp2, true);

    auto set1 = reader->getFollowsPair(StatementType::Stmt, StatementType::Stmt);
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({sp, sp2}) != set1.end());

    auto set2 = reader->getFollowsStarPair(StatementType::Print, StatementType::Read);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find({sp, sp2}) != set2.end());

    auto set3 = reader->getFollowsTypeStmt(StatementType::Print, s2);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(sp) != set3.end());

    auto set4 = reader->getFollowsStarTypeStmt(StatementType::Stmt, s2);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(sp) != set4.end());

    auto set5 = reader->getFollowsStmtType(s, StatementType::Read);
    REQUIRE(set5.size() == 1);
    REQUIRE(set5.find(sp2) != set5.end());

    auto set6 = reader->getFollowsStarStmtType(s, StatementType::Stmt);
    REQUIRE(set6.size() == 1);
    REQUIRE(set6.find(sp2) != set6.end());

    auto set7 = reader->getFollowsTypeWildcard(StatementType::Print);
    REQUIRE(set7.size() == 1);
    REQUIRE(set7.find(sp) != set7.end());

    auto set8 = reader->getFollowsStarTypeWildcard(StatementType::Stmt);
    REQUIRE(set8.size() == 1);
    REQUIRE(set8.find(sp) != set8.end());

    auto set9 = reader->getFollowsWildcardType(StatementType::Read);
    REQUIRE(set9.size() == 1);
    REQUIRE(set9.find(sp2) != set9.end());

    auto set10 = reader->getFollowsStarWildcardType(StatementType::Stmt);
    REQUIRE(set10.size() == 1);
    REQUIRE(set10.find(sp2) != set10.end());

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

    auto sp = make_shared<Statement>(s);
    auto sp2 = make_shared<Statement>(s2);

    writer->addParentRelationship(sp, sp2, true);

    auto set1 = reader->getParentPair(StatementType::Stmt, StatementType::Stmt);
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({sp, sp2}) != set1.end());

    auto set2 = reader->getParentStarPair(StatementType::While, StatementType::Read);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find({sp, sp2}) != set2.end());

    auto set3 = reader->getParentTypeStmt(StatementType::While, s2);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(sp) != set3.end());

    auto set4 = reader->getParentStarTypeStmt(StatementType::Stmt, s2);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(sp) != set4.end());

    auto set5 = reader->getParentStmtType(s, StatementType::Read);
    REQUIRE(set5.size() == 1);
    REQUIRE(set5.find(sp2) != set5.end());

    auto set6 = reader->getParentStarStmtType(s, StatementType::Stmt);
    REQUIRE(set6.size() == 1);
    REQUIRE(set6.find(sp2) != set6.end());

    auto set7 = reader->getParentTypeWildcard(StatementType::While);
    REQUIRE(set7.size() == 1);
    REQUIRE(set7.find(sp) != set7.end());

    auto set8 = reader->getParentStarTypeWildcard(StatementType::Stmt);
    REQUIRE(set8.size() == 1);
    REQUIRE(set8.find(sp) != set8.end());

    auto set9 = reader->getParentWildcardType(StatementType::Read);
    REQUIRE(set9.size() == 1);
    REQUIRE(set9.find(sp2) != set9.end());

    auto set10 = reader->getParentStarWildcardType(StatementType::Stmt);
    REQUIRE(set10.size() == 1);
    REQUIRE(set10.find(sp2) != set10.end());

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

    auto pp = make_shared<Procedure>(p);
    auto pp2 = make_shared<Procedure>(p2);

    writer->addCallsRelationship(pp, pp2);
    writer->triggerTransitiveCalc();

    REQUIRE(reader->hasCalls());
    REQUIRE(reader->hasCallsStar());

    REQUIRE(reader->isCallee(p2));
    REQUIRE(reader->isCalleeStar(p2));

    REQUIRE(reader->isCaller(p));
    REQUIRE(reader->isCallerStar(p));

    REQUIRE(reader->isCalls(p, p2));
    REQUIRE(reader->isCallsStar(p, p2));

    auto set1 = reader->getCallees();
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find(pp2) != set1.end());

    auto set2 = reader->getCalleesStar();
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(pp2) != set2.end());

    auto set3 = reader->getCallers();
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(pp) != set3.end());

    auto set4 = reader->getCallersStar();
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(pp) != set4.end());

    auto set5 = reader->getCallsPair();
    REQUIRE(set5.size() == 1);
    REQUIRE(set5.find({pp, pp2}) != set5.end());

    auto set6 = reader->getCallsStarPair();
    REQUIRE(set6.size() == 1);
    REQUIRE(set6.find({pp, pp2}) != set6.end());

    auto set7 = reader->getCallers(p2);
    REQUIRE(set7.size() == 1);
    REQUIRE(set7.find(pp) != set7.end());

    auto set8 = reader->getCallersStar(p2);
    REQUIRE(set8.size() == 1);
    REQUIRE(set8.find(pp) != set8.end());

    auto set9 = reader->getCallees(p);
    REQUIRE(set9.size() == 1);
    REQUIRE(set9.find(pp2) != set9.end());

    auto set10 = reader->getCalleesStar(p);
    REQUIRE(set10.size() == 1);
    REQUIRE(set10.find(pp2) != set10.end());

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

    auto sp = make_shared<Statement>(s);
    auto vp = make_shared<Variable>(v);

    writer->addAssignStatement(sp);
    writer->addAssignPattern(sp, vp, make_shared<Expression>(e));

    auto set1 = reader->getAllAssign();
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find(sp) != set1.end());

    auto set2 = reader->getAssignStmtsByRhs(subExpr, true);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(sp) != set2.end());

    auto set3 = reader->getAssignStmtsByRhs(e, false);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(sp) != set3.end());

    auto set4 = reader->getAssignStmtsByLhs(v);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(sp) != set4.end());

    auto set5 = reader->getAssignStmtsByLhsRhs(v, subExpr, true);
    REQUIRE(set5.size() == 1);
    REQUIRE(set5.find(sp) != set5.end());

    auto set6 = reader->getAssignStmtsByLhsRhs(v, e, false);
    REQUIRE(set6.size() == 1);
    REQUIRE(set6.find(sp) != set6.end());

    auto set7 = reader->getAllAssignStmtVarPair();
    REQUIRE(set7.size() == 1);
    REQUIRE(set7.find({sp, vp}) != set7.end());

    auto set8 = reader->getAssignStmtsVarPairByRhs(subExpr, true);
    REQUIRE(set8.size() == 1);
    REQUIRE(set8.find({sp, vp}) != set8.end());

    auto set9 = reader->getAssignStmtsVarPairByRhs(e, false);
    REQUIRE(set9.size() == 1);
    REQUIRE(set9.find({sp, vp}) != set9.end());

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

    auto sp = make_shared<Statement>(s);
    auto sp1 = make_shared<Statement>(s1);

    writer->addNextRelationship(sp, sp1);
    writer->clearCache();

    auto set1 = reader->getNextPair(StatementType::Stmt, StatementType::Stmt);
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({sp, sp1}) != set1.end());

    auto set2 = reader->getNextStarPair(StatementType::Print, StatementType::Read);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find({sp, sp1}) != set2.end());

    auto set3 = reader->getNextStarSameStmt(StatementType::Stmt);
    REQUIRE(set3.size() == 0);

    auto set4 = reader->getNextTypeStmt(StatementType::Print, s1);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(sp) != set4.end());

    auto set5 = reader->getNextStarTypeStmt(StatementType::Stmt, s1);
    REQUIRE(set5.size() == 1);

    auto set6 = reader->getNextTypeWildcard(StatementType::Print);
    REQUIRE(set6.size() == 1);
    REQUIRE(set6.find(sp) != set6.end());

    auto set7 = reader->getNextStarTypeWildcard(StatementType::Stmt);
    REQUIRE(set7.size() == 1);
    REQUIRE(set7.find(sp) != set7.end());

    auto set8 = reader->getNextStmtType(s, StatementType::Read);
    REQUIRE(set8.size() == 1);
    REQUIRE(set8.find(sp1) != set8.end());

    auto set9 = reader->getNextStarStmtType(s, StatementType::Stmt);
    REQUIRE(set9.size() == 1);
    REQUIRE(set9.find(sp1) != set9.end());

    auto set10 = reader->getNextWildcardType(StatementType::Read);
    REQUIRE(set10.size() == 1);
    REQUIRE(set10.find(sp1) != set10.end());

    auto set11 = reader->getNextStarWildcardType(StatementType::Stmt);
    REQUIRE(set11.size() == 1);
    REQUIRE(set11.find(sp1) != set11.end());

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

    shared_ptr<Statement> s = make_shared<Statement>(1, StatementType::If);
    shared_ptr<Variable> v = make_shared<Variable>("x");

    REQUIRE(reader->getAllIfPatternStmts().empty());
    REQUIRE(reader->getIfStmtsByVar(*v).empty());
    REQUIRE(reader->getAllIfStmtVarPair().empty());

    writer->addIfPattern(s,
                         make_shared<vector<shared_ptr<Variable>>>(1, v));

    auto set1 = reader->getAllIfPatternStmts();
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find(s) != set1.end());

    auto set2 = reader->getIfStmtsByVar(*v);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(s) != set2.end());

    auto set3 = reader->getAllIfStmtVarPair();
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find({s, v}) != set3.end());
}

TEST_CASE_METHOD(UnitTestFixture, "While Pattern") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    shared_ptr<Statement> s = make_shared<Statement>(1, StatementType::While);
    shared_ptr<Variable> v = make_shared<Variable>("x");

    REQUIRE(reader->getAllWhilePatternStmts().empty());
    REQUIRE(reader->getWhileStmtsByVar(*v).empty());
    REQUIRE(reader->getAllWhileStmtVarPair().empty());

    writer->addWhilePattern(s,
                            make_shared<vector<shared_ptr<Variable>>>(1, v));

    auto set1 = reader->getAllWhilePatternStmts();
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find(s) != set1.end());

    auto set2 = reader->getWhileStmtsByVar(*v);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(s) != set2.end());

    auto set3 = reader->getAllWhileStmtVarPair();
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find({s, v}) != set3.end());
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

    REQUIRE(reader->getAffectsPair(StatementType::Assign, StatementType::Assign).size() == 3);

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
