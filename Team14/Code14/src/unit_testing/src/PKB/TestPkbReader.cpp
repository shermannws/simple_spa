#include "PKB/Pkb.h"
#include "catch.hpp"

using namespace std;

TEST_CASE("Test initialising PKB Reader") {
    Pkb pkb = Pkb();

    REQUIRE_NOTHROW(pkb.createPkbReader());
}

TEST_CASE("Test Entities") {
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

    REQUIRE(reader->getAllVariables().size() == 0);
    REQUIRE(reader->getAllConstants().size() == 0);
    REQUIRE(reader->getAllProcedures().size() == 0);
    REQUIRE(reader->getAllStatements().size() == 0);
    REQUIRE(reader->getAllRead().size() == 0);
    REQUIRE(reader->getAllPrint().size() == 0);
    REQUIRE(reader->getAllAssign().size() == 0);
    REQUIRE(reader->getAllCall().size() == 0);
    REQUIRE(reader->getAllIf().size() == 0);
    REQUIRE(reader->getAllWhile().size() == 0);

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

TEST_CASE("Uses (Stmt) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Variable v = Variable("x");
    Statement s = Statement(1, StatementType::Print);

    REQUIRE(reader->getUsesStmtPair(StatementType::Stmt).size() == 0);
    REQUIRE(reader->getUsesStmt(StatementType::Print).size() == 0);
    REQUIRE(reader->getUsesVar(s).size() == 0);
    REQUIRE(reader->getUsesTypeIdent(StatementType::Stmt, v).size() == 0);
    REQUIRE(!reader->isStmtUsesVar(s, v));
    REQUIRE(!reader->hasUses(s));

    writer->addUsesRelationship(make_shared<Statement>(s), make_shared<Variable>(v));

    auto set1 = reader->getUsesStmtPair(StatementType::Stmt);
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({s, v}) != set1.end());

    auto set2 = reader->getUsesStmt(StatementType::Print);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(s) != set2.end());

    auto set3 = reader->getUsesVar(s);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(v) != set3.end());

    auto set4 = reader->getUsesTypeIdent(StatementType::Stmt, v);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(s) != set4.end());

    REQUIRE(reader->isStmtUsesVar(s, v));
    REQUIRE(reader->hasUses(s));

    // Negative tests
    Statement sNew = Statement(2, StatementType::Read);
    REQUIRE(reader->getUsesStmtPair(StatementType::Read).size() == 0);
    REQUIRE(reader->getUsesStmt(StatementType::Read).size() == 0);
    REQUIRE(reader->getUsesVar(sNew).size() == 0);
    REQUIRE(reader->getUsesTypeIdent(StatementType::Read, v).size() == 0);
    REQUIRE(!reader->isStmtUsesVar(sNew, v));
    REQUIRE(!reader->hasUses(sNew));
}

TEST_CASE("Uses (Proc) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Variable v = Variable("x");
    Procedure p = Procedure("main");

    REQUIRE(reader->getUsesProcPair().size() == 0);
    REQUIRE(reader->getUsesProc().size() == 0);
    REQUIRE(reader->getUsesVar(p).size() == 0);
    REQUIRE(reader->getUsesProcIdent(v).size() == 0);
    REQUIRE(!reader->isProcUsesVar(p, v));
    REQUIRE(!reader->hasUses(p));

    writer->addUsesProcRelationship(make_shared<Procedure>(p), make_shared<Variable>(v));

    auto set1 = reader->getUsesProcPair();
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({p, v}) != set1.end());

    auto set2 = reader->getUsesProc();
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(p) != set2.end());

    auto set3 = reader->getUsesVar(p);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(v) != set3.end());

    auto set4 = reader->getUsesProcIdent(v);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(p) != set4.end());

    REQUIRE(reader->isProcUsesVar(p, v));
    REQUIRE(reader->hasUses(p));

    // Negative tests
    Procedure pNew = Procedure("anotherProcedure");
    REQUIRE(reader->getUsesVar(pNew).size() == 0);
    REQUIRE(!reader->isProcUsesVar(pNew, v));
    REQUIRE(!reader->hasUses(pNew));
}


TEST_CASE("Modifies (Stmt) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Variable v = Variable("x");
    Statement s = Statement(1, StatementType::Read);

    REQUIRE(reader->getModifiesStmtPair(StatementType::Stmt).size() == 0);
    REQUIRE(reader->getModifiesStmt(StatementType::Read).size() == 0);
    REQUIRE(reader->getModifiesVar(s).size() == 0);
    REQUIRE(reader->getModifiesTypeIdent(StatementType::Stmt, v).size() == 0);
    REQUIRE(!reader->isStmtModifiesVar(s, v));
    REQUIRE(!reader->hasModifies(s));

    writer->addModifiesRelationship(make_shared<Statement>(s), make_shared<Variable>(v));

    auto set1 = reader->getModifiesStmtPair(StatementType::Stmt);
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({s, v}) != set1.end());

    auto set2 = reader->getModifiesStmt(StatementType::Read);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(s) != set2.end());

    auto set3 = reader->getModifiesVar(s);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(v) != set3.end());

    auto set4 = reader->getModifiesTypeIdent(StatementType::Stmt, v);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(s) != set4.end());

    REQUIRE(reader->isStmtModifiesVar(s, v));
    REQUIRE(reader->hasModifies(s));

    // Negative tests
    Statement sNew = Statement(2, StatementType::Print);
    REQUIRE(reader->getModifiesStmtPair(StatementType::Print).size() == 0);
    REQUIRE(reader->getModifiesStmt(StatementType::Print).size() == 0);
    REQUIRE(reader->getModifiesVar(sNew).size() == 0);
    REQUIRE(reader->getModifiesTypeIdent(StatementType::Print, v).size() == 0);
    REQUIRE(!reader->isStmtModifiesVar(sNew, v));
    REQUIRE(!reader->hasModifies(sNew));
}

TEST_CASE("Modifies (Proc) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Variable v = Variable("x");
    Procedure p = Procedure("main");

    REQUIRE(reader->getModifiesProcPair().size() == 0);
    REQUIRE(reader->getModifiesProc().size() == 0);
    REQUIRE(reader->getModifiesVar(p).size() == 0);
    REQUIRE(reader->getModifiesProcIdent(v).size() == 0);
    REQUIRE(!reader->isProcModifiesVar(p, v));
    REQUIRE(!reader->hasModifies(p));

    writer->addModifiesProcRelationship(make_shared<Procedure>(p), make_shared<Variable>(v));

    auto set1 = reader->getModifiesProcPair();
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({p, v}) != set1.end());

    auto set2 = reader->getModifiesProc();
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(p) != set2.end());

    auto set3 = reader->getModifiesVar(p);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(v) != set3.end());

    auto set4 = reader->getModifiesProcIdent(v);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(p) != set4.end());

    REQUIRE(reader->isProcModifiesVar(p, v));
    REQUIRE(reader->hasModifies(p));

    // Negative tests
    Procedure pNew = Procedure("anotherProcedure");
    REQUIRE(reader->getModifiesVar(pNew).size() == 0);
    REQUIRE(!reader->isProcModifiesVar(pNew, v));
    REQUIRE(!reader->hasModifies(pNew));
}


TEST_CASE("Follows(*) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Statement s = Statement(1, StatementType::Print);
    Statement s2 = Statement(2, StatementType::Read);

    REQUIRE(reader->getFollowsPair(StatementType::Stmt, StatementType::Stmt).size() == 0);
    REQUIRE(reader->getFollowsStarPair(StatementType::Print, StatementType::Read).size() == 0);
    REQUIRE(reader->getFollowsTypeStmt(StatementType::Print, s2).size() == 0);
    REQUIRE(reader->getFollowsStarTypeStmt(StatementType::Stmt, s2).size() == 0);
    REQUIRE(reader->getFollowsStmtType(s, StatementType::Read).size() == 0);
    REQUIRE(reader->getFollowsStarStmtType(s, StatementType::Stmt).size() == 0);
    REQUIRE(reader->getFollowsTypeWildcard(StatementType::Print).size() == 0);
    REQUIRE(reader->getFollowsStarTypeWildcard(StatementType::Stmt).size() == 0);
    REQUIRE(reader->getFollowsWildcardType(StatementType::Read).size() == 0);
    REQUIRE(reader->getFollowsStarWildcardType(StatementType::Stmt).size() == 0);
    REQUIRE(!reader->isFollows(s, s2));
    REQUIRE(!reader->isFollowsStar(s, s2));
    REQUIRE(!reader->hasFollows());
    REQUIRE(!reader->hasFollowsStar());
    REQUIRE(!reader->hasLatterStmt(s));
    REQUIRE(!reader->hasLatterStarStmt(s));
    REQUIRE(!reader->hasFormerStmt(s2));
    REQUIRE(!reader->hasFormerStarStmt(s2));

    writer->addFollowsRelationship(make_shared<Statement>(s), make_shared<Statement>(s2), true);

    auto set1 = reader->getFollowsPair(StatementType::Stmt, StatementType::Stmt);
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({s, s2}) != set1.end());

    auto set2 = reader->getFollowsStarPair(StatementType::Print, StatementType::Read);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find({s, s2}) != set2.end());

    auto set3 = reader->getFollowsTypeStmt(StatementType::Print, s2);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(s) != set3.end());

    auto set4 = reader->getFollowsStarTypeStmt(StatementType::Stmt, s2);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(s) != set4.end());

    auto set5 = reader->getFollowsStmtType(s, StatementType::Read);
    REQUIRE(set5.size() == 1);
    REQUIRE(set5.find(s2) != set5.end());

    auto set6 = reader->getFollowsStarStmtType(s, StatementType::Stmt);
    REQUIRE(set6.size() == 1);
    REQUIRE(set6.find(s2) != set6.end());

    auto set7 = reader->getFollowsTypeWildcard(StatementType::Print);
    REQUIRE(set7.size() == 1);
    REQUIRE(set7.find(s) != set7.end());

    auto set8 = reader->getFollowsStarTypeWildcard(StatementType::Stmt);
    REQUIRE(set8.size() == 1);
    REQUIRE(set8.find(s) != set8.end());

    auto set9 = reader->getFollowsWildcardType(StatementType::Read);
    REQUIRE(set9.size() == 1);
    REQUIRE(set9.find(s2) != set9.end());

    auto set10 = reader->getFollowsStarWildcardType(StatementType::Stmt);
    REQUIRE(set10.size() == 1);
    REQUIRE(set10.find(s2) != set10.end());

    REQUIRE(reader->isFollows(s, s2));
    REQUIRE(reader->isFollowsStar(s, s2));

    REQUIRE(reader->hasFollows());
    REQUIRE(reader->hasFollowsStar());

    REQUIRE(reader->hasLatterStmt(s));
    REQUIRE(reader->hasLatterStarStmt(s));
    REQUIRE(reader->hasFormerStmt(s2));
    REQUIRE(reader->hasFormerStarStmt(s2));
}

TEST_CASE("Parent(*) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Statement s = Statement(1, StatementType::While);
    Statement s2 = Statement(2, StatementType::Read);

    writer->addParentRelationship(make_shared<Statement>(s), make_shared<Statement>(s2), true);

    auto set1 = reader->getParentPair(StatementType::Stmt, StatementType::Stmt);
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({s, s2}) != set1.end());

    auto set2 = reader->getParentStarPair(StatementType::While, StatementType::Read);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find({s, s2}) != set2.end());

    auto set3 = reader->getParentTypeStmt(StatementType::While, s2);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(s) != set3.end());

    auto set4 = reader->getParentStarTypeStmt(StatementType::Stmt, s2);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(s) != set4.end());

    auto set5 = reader->getParentStmtType(s, StatementType::Read);
    REQUIRE(set5.size() == 1);
    REQUIRE(set5.find(s2) != set5.end());

    auto set6 = reader->getParentStarStmtType(s, StatementType::Stmt);
    REQUIRE(set6.size() == 1);
    REQUIRE(set6.find(s2) != set6.end());

    auto set7 = reader->getParentTypeWildcard(StatementType::While);
    REQUIRE(set7.size() == 1);
    REQUIRE(set7.find(s) != set7.end());

    auto set8 = reader->getParentStarTypeWildcard(StatementType::Stmt);
    REQUIRE(set8.size() == 1);
    REQUIRE(set8.find(s) != set8.end());

    auto set9 = reader->getParentWildcardType(StatementType::Read);
    REQUIRE(set9.size() == 1);
    REQUIRE(set9.find(s2) != set9.end());

    auto set10 = reader->getParentStarWildcardType(StatementType::Stmt);
    REQUIRE(set10.size() == 1);
    REQUIRE(set10.find(s2) != set10.end());

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
    REQUIRE(reader->getParentPair(StatementType::Print, StatementType::Stmt).size() == 0);
    REQUIRE(reader->getParentStarPair(StatementType::Print, StatementType::Read).size() == 0);
    REQUIRE(reader->getParentTypeStmt(StatementType::Print, s2).size() == 0);
    REQUIRE(reader->getParentStarTypeStmt(StatementType::Print, s2).size() == 0);
    REQUIRE(reader->getParentStmtType(sNew, StatementType::Read).size() == 0);
    REQUIRE(reader->getParentStarStmtType(sNew, StatementType::Stmt).size() == 0);
    REQUIRE(reader->getParentTypeWildcard(StatementType::Print).size() == 0);
    REQUIRE(reader->getParentStarTypeWildcard(StatementType::Print).size() == 0);
    REQUIRE(reader->getParentWildcardType(StatementType::Print).size() == 0);
    REQUIRE(reader->getParentStarWildcardType(StatementType::Print).size() == 0);
    REQUIRE(!reader->isParent(sNew, s2));
    REQUIRE(!reader->isParentStar(sNew, s2));
    REQUIRE(!reader->hasChildStmt(sNew));
    REQUIRE(!reader->hasChildStarStmt(sNew));
    REQUIRE(!reader->hasParentStmt(sNew));
    REQUIRE(!reader->hasParentStarStmt(sNew));
}


TEST_CASE("Calls(*) Relationship") {
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
    REQUIRE(reader->getCallees().size() == 0);
    REQUIRE(reader->getCalleesStar().size() == 0);
    REQUIRE(reader->getCallers().size() == 0);
    REQUIRE(reader->getCallersStar().size() == 0);
    REQUIRE(reader->getCallsPair().size() == 0);
    REQUIRE(reader->getCallsStarPair().size() == 0);
    REQUIRE(reader->getCallers(p2).size() == 0);
    REQUIRE(reader->getCallersStar(p2).size() == 0);
    REQUIRE(reader->getCallees(p).size() == 0);
    REQUIRE(reader->getCalleesStar(p).size() == 0);

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

    auto set1 = reader->getCallees();
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find(p2) != set1.end());

    auto set2 = reader->getCalleesStar();
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(p2) != set2.end());

    auto set3 = reader->getCallers();
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(p) != set3.end());

    auto set4 = reader->getCallersStar();
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(p) != set4.end());

    auto set5 = reader->getCallsPair();
    REQUIRE(set5.size() == 1);
    REQUIRE(set5.find({p, p2}) != set5.end());

    auto set6 = reader->getCallsStarPair();
    REQUIRE(set6.size() == 1);
    REQUIRE(set6.find({p, p2}) != set6.end());

    auto set7 = reader->getCallers(p2);
    REQUIRE(set7.size() == 1);
    REQUIRE(set7.find(p) != set7.end());

    auto set8 = reader->getCallersStar(p2);
    REQUIRE(set8.size() == 1);
    REQUIRE(set8.find(p) != set8.end());

    auto set9 = reader->getCallees(p);
    REQUIRE(set9.size() == 1);
    REQUIRE(set9.find(p2) != set9.end());

    auto set10 = reader->getCalleesStar(p);
    REQUIRE(set10.size() == 1);
    REQUIRE(set10.find(p2) != set10.end());

    // Negative Cases
    Procedure pNew = Procedure("main3");
    REQUIRE(!reader->isCallee(pNew));
    REQUIRE(!reader->isCalleeStar(pNew));
    REQUIRE(!reader->isCaller(pNew));
    REQUIRE(!reader->isCallerStar(pNew));
    REQUIRE(reader->getCallers(pNew).size() == 0);
    REQUIRE(reader->getCallersStar(pNew).size() == 0);
    REQUIRE(reader->getCallees(pNew).size() == 0);
    REQUIRE(reader->getCalleesStar(pNew).size() == 0);
}

TEST_CASE("Assign Pattern") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Statement s = Statement(1, StatementType::Assign);
    Variable v = Variable("x");
    Expression e = Expression("((x)+(y))*1");//(x+y) * 1
    Expression subExpr = Expression("((x)+(y))");

    REQUIRE(reader->getAllAssign().size() == 0);
    REQUIRE(reader->getAssignStmtsByRhs(subExpr, true).size() == 0);
    REQUIRE(reader->getAssignStmtsByRhs(e, false).size() == 0);
    REQUIRE(reader->getAssignStmtsByLhs(v).size() == 0);
    REQUIRE(reader->getAssignStmtsByLhsRhs(v, subExpr, true).size() == 0);
    REQUIRE(reader->getAssignStmtsByLhsRhs(v, e, false).size() == 0);
    REQUIRE(reader->getAllAssignStmtVarPair().size() == 0);
    REQUIRE(reader->getAssignStmtsVarPairByRhs(subExpr, true).size() == 0);
    REQUIRE(reader->getAssignStmtsVarPairByRhs(e, false).size() == 0);

    writer->addAssignStatement(make_shared<Statement>(s));
    writer->addAssignPattern(make_shared<Statement>(s), make_shared<Variable>(v), make_shared<Expression>(e));

    auto set1 = reader->getAllAssign();
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find(s) != set1.end());

    auto set2 = reader->getAssignStmtsByRhs(subExpr, true);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(s) != set2.end());

    auto set3 = reader->getAssignStmtsByRhs(e, false);
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find(s) != set3.end());

    auto set4 = reader->getAssignStmtsByLhs(v);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(s) != set4.end());

    auto set5 = reader->getAssignStmtsByLhsRhs(v, subExpr, true);
    REQUIRE(set5.size() == 1);
    REQUIRE(set5.find(s) != set4.end());

    auto set6 = reader->getAssignStmtsByLhsRhs(v, e, false);
    REQUIRE(set6.size() == 1);
    REQUIRE(set6.find(s) != set6.end());

    auto set7 = reader->getAllAssignStmtVarPair();
    REQUIRE(set7.size() == 1);
    REQUIRE(set7.find({s, v}) != set7.end());

    auto set8 = reader->getAssignStmtsVarPairByRhs(subExpr, true);
    REQUIRE(set8.size() == 1);
    REQUIRE(set8.find({s, v}) != set8.end());

    auto set9 = reader->getAssignStmtsVarPairByRhs(e, false);
    REQUIRE(set9.size() == 1);
    REQUIRE(set9.find({s, v}) != set9.end());

    // Negative tests
    Expression eNew = Expression("((x)+(z))*2");
    Expression subExprNew = Expression("((x)+(z))");
    REQUIRE(reader->getAssignStmtsByRhs(subExprNew, true).size() == 0);
    REQUIRE(reader->getAssignStmtsByRhs(eNew, false).size() == 0);
    REQUIRE(reader->getAssignStmtsByLhsRhs(v, subExprNew, true).size() == 0);
    REQUIRE(reader->getAssignStmtsByLhsRhs(v, eNew, false).size() == 0);
    REQUIRE(reader->getAssignStmtsVarPairByRhs(subExprNew, true).size() == 0);
    REQUIRE(reader->getAssignStmtsVarPairByRhs(eNew, false).size() == 0);
}

TEST_CASE("Next(*) Relationship") {
    Pkb pkb = Pkb();
    auto reader = pkb.createPkbReader();
    auto writer = pkb.createPkbWriter();

    Statement s = Statement(1, StatementType::Print);
    Statement s1 = Statement(2, StatementType::Read);

    REQUIRE(reader->getNextPair(StatementType::Stmt, StatementType::Stmt).size() == 0);
    REQUIRE(reader->getNextStarPair(StatementType::Print, StatementType::Read).size() == 0);
    REQUIRE(reader->getNextStarSameStmt(StatementType::Stmt).size() == 0);
    REQUIRE(reader->getNextTypeStmt(StatementType::Print, s1).size() == 0);
    REQUIRE(reader->getNextStarTypeStmt(StatementType::Stmt, s1).size() == 0);
    REQUIRE(reader->getNextTypeWildcard(StatementType::Print).size() == 0);
    REQUIRE(reader->getNextStarTypeWildcard(StatementType::Stmt).size() == 0);
    REQUIRE(reader->getNextStmtType(s, StatementType::Read).size() == 0);
    REQUIRE(reader->getNextStarStmtType(s, StatementType::Stmt).size() == 0);
    REQUIRE(reader->getNextWildcardType(StatementType::Read).size() == 0);
    REQUIRE(reader->getNextStarWildcardType(StatementType::Stmt).size() == 0);
    REQUIRE(!reader->isNext(s, s1));
    REQUIRE(!reader->isNextStar(s, s1));
    REQUIRE(!reader->hasNext());
    REQUIRE(!reader->hasNextStar());
    REQUIRE(!reader->hasBeforeStmt(s1));
    REQUIRE(!reader->hasBeforeStarStmt(s1));
    REQUIRE(!reader->hasAfterStmt(s));
    REQUIRE(!reader->hasAfterStarStmt(s));

    writer->addNextRelationship(make_shared<Statement>(s), make_shared<Statement>(s1));

    auto set1 = reader->getNextPair(StatementType::Stmt, StatementType::Stmt);
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find({s, s1}) != set1.end());

    auto set2 = reader->getNextStarPair(StatementType::Print, StatementType::Read);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find({s, s1}) != set2.end());

    auto set3 = reader->getNextStarSameStmt(StatementType::Stmt);
    REQUIRE(set3.size() == 0);

    auto set4 = reader->getNextTypeStmt(StatementType::Print, s1);
    REQUIRE(set4.size() == 1);
    REQUIRE(set4.find(s) != set4.end());

    auto set5 = reader->getNextStarTypeStmt(StatementType::Stmt, s1);
    REQUIRE(set5.size() == 1);

    auto set6 = reader->getNextTypeWildcard(StatementType::Print);
    REQUIRE(set6.size() == 1);
    REQUIRE(set6.find(s) != set6.end());

    auto set7 = reader->getNextStarTypeWildcard(StatementType::Stmt);
    REQUIRE(set7.size() == 1);
    REQUIRE(set7.find(s) != set7.end());

    auto set8 = reader->getNextStmtType(s, StatementType::Read);
    REQUIRE(set8.size() == 1);
    REQUIRE(set8.find(s1) != set8.end());

    auto set9 = reader->getNextStarStmtType(s, StatementType::Stmt);
    REQUIRE(set9.size() == 1);
    REQUIRE(set9.find(s1) != set9.end());

    auto set10 = reader->getNextWildcardType(StatementType::Read);
    REQUIRE(set10.size() == 1);
    REQUIRE(set10.find(s1) != set10.end());

    auto set11 = reader->getNextStarWildcardType(StatementType::Stmt);
    REQUIRE(set11.size() == 1);
    REQUIRE(set11.find(s1) != set11.end());

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
    REQUIRE(reader->getNextPair(StatementType::Assign, StatementType::Stmt).size() == 0);
    REQUIRE(reader->getNextStarPair(StatementType::Assign, StatementType::Read).size() == 0);
    REQUIRE(reader->getNextTypeStmt(StatementType::Assign, s1).size() == 0);
    REQUIRE(reader->getNextStarTypeStmt(StatementType::Assign, s1).size() == 0);
    REQUIRE(reader->getNextStmtType(sNew, StatementType::Read).size() == 0);
    REQUIRE(reader->getNextStarStmtType(sNew, StatementType::Stmt).size() == 0);
    REQUIRE(reader->getNextTypeWildcard(StatementType::Assign).size() == 0);
    REQUIRE(reader->getNextStarTypeWildcard(StatementType::Assign).size() == 0);
    REQUIRE(reader->getNextWildcardType(StatementType::Assign).size() == 0);
    REQUIRE(reader->getNextStarWildcardType(StatementType::Assign).size() == 0);
    REQUIRE(!reader->isNext(sNew, s1));
    REQUIRE(!reader->isNextStar(sNew, s1));
    REQUIRE(!reader->hasBeforeStmt(sNew));
    REQUIRE(!reader->hasBeforeStarStmt(sNew));
    REQUIRE(!reader->hasAfterStmt(sNew));
    REQUIRE(!reader->hasAfterStarStmt(sNew));

    writer->clearCache();
}

TEST_CASE("If Pattern") {
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

    auto set1 = reader->getAllIfPatternStmts();
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find(s) != set1.end());

    auto set2 = reader->getIfStmtsByVar(v);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(s) != set2.end());

    auto set3 = reader->getAllIfStmtVarPair();
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find({s, v}) != set3.end());
}

TEST_CASE("While Pattern") {
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

    auto set1 = reader->getAllWhilePatternStmts();
    REQUIRE(set1.size() == 1);
    REQUIRE(set1.find(s) != set1.end());

    auto set2 = reader->getWhileStmtsByVar(v);
    REQUIRE(set2.size() == 1);
    REQUIRE(set2.find(s) != set2.end());

    auto set3 = reader->getAllWhileStmtVarPair();
    REQUIRE(set3.size() == 1);
    REQUIRE(set3.find({s, v}) != set3.end());
}

TEST_CASE("Affects Relationship") {
    // TODO
}
