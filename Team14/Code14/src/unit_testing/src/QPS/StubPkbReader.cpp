#include "StubPkbReader.h"
#include "Commons/Entities/CallStatement.h"
#include "Commons/Entities/ReadStatement.h"

#include "Commons/Entities/WhileStatement.h"

StubPkbReader::StubPkbReader() = default;

EntitySet StubPkbReader::getAllVariables() const {
    return EntitySet({
            std::make_shared<Variable>("var1"),
            std::make_shared<Variable>("var2"),
            std::make_shared<Variable>("var5"),
            std::make_shared<Variable>("var14"),
            std::make_shared<Variable>("var24"),
            std::make_shared<Variable>("var36"),
            std::make_shared<Variable>("var38"),
            std::make_shared<Variable>("var88"),
    });
}

EntitySet StubPkbReader::getAllConstants() const {
    return EntitySet({std::make_shared<Constant>("3"), std::make_shared<Constant>("7"),
                      std::make_shared<Constant>("21"), std::make_shared<Constant>("63")});
}

EntitySet StubPkbReader::getAllProcedures() const {
    return EntitySet({
            std::make_shared<Procedure>("proc1"),
            std::make_shared<Procedure>("proc2"),
            std::make_shared<Procedure>("proc3"),
    });
}

EntitySet StubPkbReader::getAllStatements() const {
    return EntitySet{
            std::make_shared<Statement>(1, StatementType::If),   std::make_shared<Statement>(2, StatementType::While),
            std::make_shared<Statement>(3, StatementType::Call), std::make_shared<Statement>(4, StatementType::Assign),
            std::make_shared<Statement>(5, StatementType::Read),
    };
}

EntitySet StubPkbReader::getAllRead() const {
    return EntitySet({
            std::make_shared<Statement>(88, StatementType::Read, "var88"),
            std::make_shared<Statement>(24, StatementType::Read, "var24"),
            std::make_shared<Statement>(36, StatementType::Read, "var36"),
            std::make_shared<Statement>(14, StatementType::Read, "var14"),
    });
}

EntitySet StubPkbReader::getAllPrint() const {
    return EntitySet({
            std::make_shared<Statement>(1, StatementType::Print, "var1"),
            std::make_shared<Statement>(3, StatementType::Print, "var3"),
            std::make_shared<Statement>(5, StatementType::Print, "var5"),
            std::make_shared<Statement>(7, StatementType::Print, "var7"),
            std::make_shared<Statement>(9, StatementType::Print, "var9"),
    });
}

EntitySet StubPkbReader::getAllWhile() const {
    return EntitySet{
            std::make_shared<Statement>(10, StatementType::While),
            std::make_shared<Statement>(13, StatementType::While),
            std::make_shared<Statement>(15, StatementType::While),
    };
}

EntitySet StubPkbReader::getAllIf() const {
    return EntitySet({
            std::make_shared<Statement>(101, StatementType::If),
            std::make_shared<Statement>(102, StatementType::If),
    });
}

EntitySet StubPkbReader::getAllCall() const {
    return EntitySet({std::make_shared<Statement>(7, StatementType::Call, "Proc1"),
                      std::make_shared<Statement>(10, StatementType::Call, "Proc2"),
                      std::make_shared<Statement>(21, StatementType::Call, "Proc3"),
                      std::make_shared<Statement>(22, StatementType::Call, "Proc3")});
}

EntityPairSet StubPkbReader::getUsesStmtPair(StatementType type) const {
    if (type == StatementType::Call) {
        return EntityPairSet({{std::make_shared<CallStatement>(1, "proc1"), std::make_shared<Variable>("var1")},
                              {std::make_shared<CallStatement>(2, "proc2"), std::make_shared<Variable>("var2")}});
    }
    std::vector<EntityPointer> pair1 = {std::make_shared<Statement>(1, StatementType::Assign),
                                        std::make_shared<Variable>("var")};
    std::vector<EntityPointer> pair2 = {std::make_shared<Statement>(2, StatementType::Assign),
                                        std::make_shared<Variable>("var")};
    return EntityPairSet({pair1, pair2});
}

EntityPairSet StubPkbReader::getUsesProcPair() const {
    std::vector<EntityPointer> pair1 = {std::make_shared<Procedure>("ProcedureName"),
                                        std::make_shared<Variable>("hello123")};
    std::vector<EntityPointer> pair2 = {std::make_shared<Procedure>("ProcedureName2"),
                                        std::make_shared<Variable>("hello321")};
    return EntityPairSet({pair1, pair2});
}

EntitySet StubPkbReader::getUsesTypeIdent(StatementType type, Variable &var) const {
    return EntitySet{
            std::make_shared<Statement>(2, StatementType::If),
            std::make_shared<Statement>(4, StatementType::If),
            std::make_shared<Statement>(5, StatementType::If),
    };
}

EntitySet StubPkbReader::getUsesProcIdent(Variable &var) const {
    return EntitySet{std::make_shared<Procedure>("ProcedureName")};
};

EntitySet StubPkbReader::getUsesStmt(StatementType type) const {
    return EntitySet{
            std::make_shared<Statement>(1, StatementType::Assign),
            std::make_shared<Statement>(3, StatementType::Call),
    };
}

EntitySet StubPkbReader::getUsesProc() const { return {}; }

EntitySet StubPkbReader::getUsesVar(Statement &stmt) const {
    return EntitySet{std::make_shared<Variable>("name"), std::make_shared<Variable>("asdfghjkl")};
}

EntitySet StubPkbReader::getUsesVar(Procedure &proc) const {
    return EntitySet{std::make_shared<Variable>("proc"), std::make_shared<Variable>("anotherVar")};
}

bool StubPkbReader::isStmtUsesVar(Statement &stmt, Variable &var) const {
    if (stmt == Statement(1, StatementType::Stmt) && var == Variable("multiClauseSTonly")) { return false; }
    if (var == Variable("multiClauseTrue")) { return true; }
    return true;
}

bool StubPkbReader::isProcUsesVar(Procedure &proc, Variable &var) const { return false; }

bool StubPkbReader::hasUses(Statement &stmt) const { return false; }

bool StubPkbReader::hasUses(Procedure &proc) const { return true; }

EntityPairSet StubPkbReader::getFollowsPair(StatementType formerType, StatementType latterType) const {
    std::vector<EntityPointer> pair1 = {std::make_shared<Statement>(1, StatementType::Assign),
                                        std::make_shared<Statement>(5, StatementType::Print)};
    std::vector<EntityPointer> pair2 = {std::make_shared<Statement>(10, StatementType::Assign),
                                        std::make_shared<Statement>(11, StatementType::Print)};
    if (formerType == StatementType::Assign && latterType == StatementType::Print) {
        return EntityPairSet({pair1, pair2});
    }
    return EntityPairSet();
}

EntityPairSet StubPkbReader::getFollowsStarPair(StatementType formerType, StatementType latterType) const {
    std::vector<EntityPointer> pair1 = {std::make_shared<Statement>(1, StatementType::Assign),
                                        std::make_shared<Statement>(5, StatementType::Assign)};

    if (formerType == StatementType::Assign && latterType == StatementType::Assign) { return EntityPairSet({pair1}); }
    if (formerType == StatementType::Assign && latterType == StatementType::Read) {
        auto a1 = std::make_shared<Entity>(Statement(1, StatementType::Assign));
        auto a3 = std::make_shared<Entity>(Statement(3, StatementType::Assign));
        auto a7 = std::make_shared<Entity>(Statement(7, StatementType::Assign));

        auto r5 = std::make_shared<Entity>(Statement(5, StatementType::Read));
        auto r6 = std::make_shared<Entity>(Statement(6, StatementType::Read));
        auto r8 = std::make_shared<Entity>(Statement(8, StatementType::Read));
        return EntityPairSet({{a1, r5}, {a1, r6}, {a1, r8}, {a3, r5}, {a3, r6}, {a3, r8}, {a7, r8}});
    }
    return EntityPairSet();
}

EntitySet StubPkbReader::getFollowsTypeStmt(StatementType type, Statement &statement) const {
    if (type == StatementType::Print && statement == Statement(20, StatementType::Stmt)) {
        return EntitySet({std::make_shared<Statement>(19, StatementType::Print)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getFollowsStarTypeStmt(StatementType type, Statement &statement) const {
    if (type == StatementType::Assign && statement == Statement(700, StatementType::Stmt)) {
        return EntitySet({std::make_shared<Statement>(10, StatementType::Assign)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getFollowsTypeWildcard(StatementType type) const {
    if (type == StatementType::Call) {
        return EntitySet({std::make_shared<Statement>(8, StatementType::Call),
                          std::make_shared<Statement>(15, StatementType::Call)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getFollowsStarTypeWildcard(StatementType type) const {
    if (type == StatementType::If) {
        return EntitySet({std::make_shared<Statement>(11, StatementType::Call),
                          std::make_shared<Statement>(12, StatementType::Call)});
    }

    return EntitySet();
}

EntitySet StubPkbReader::getFollowsStmtType(Statement &statement, StatementType type) const {
    if (statement == Statement(23, StatementType::Stmt) && type == StatementType::Call) {
        return EntitySet({std::make_shared<Statement>(24, StatementType::Call)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getFollowsStarStmtType(Statement &statement, StatementType type) const {
    if (statement == Statement(24, StatementType::Stmt) && type == StatementType::While) {
        return EntitySet({std::make_shared<Statement>(25, StatementType::While)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getFollowsWildcardType(StatementType type) const {
    if (type == StatementType::Stmt) {
        return EntitySet({std::make_shared<Statement>(2, StatementType::Assign),
                          std::make_shared<Statement>(3, StatementType::Call),
                          std::make_shared<Statement>(4, StatementType::While),
                          std::make_shared<Statement>(5, StatementType::Print)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getFollowsStarWildcardType(StatementType type) const {
    if (type == StatementType::Assign) {
        return EntitySet({std::make_shared<Statement>(31, StatementType::Assign),
                          std::make_shared<Statement>(41, StatementType::Assign),
                          std::make_shared<Statement>(51, StatementType::Assign)});
    }
    return EntitySet();
}

bool StubPkbReader::isFollows(Statement &statement1, Statement &statement2) const {
    if (statement1 == Statement(3, StatementType::Stmt) && (statement2 == Statement(5, StatementType::Stmt))) {
        return false;
    }
    return true;
}

bool StubPkbReader::isFollowsStar(Statement &statement1, Statement &statement2) const {
    if (statement1 == Statement(3, StatementType::Stmt) && (statement2 == Statement(5, StatementType::Stmt))) {
        return true;
    }
    return false;
}

bool StubPkbReader::hasFollows() const { return true; }

bool StubPkbReader::hasFollowsStar() const { return true; }

bool StubPkbReader::hasLatterStmt(Statement &statement) const {
    if (statement == Statement(1, StatementType::Stmt)) { return true; }
    return false;
}

bool StubPkbReader::hasFormerStmt(Statement &statement) const {
    if (statement == Statement(1, StatementType::Stmt)) { return false; }
    return true;
}

bool StubPkbReader::hasLatterStarStmt(Statement &statement) const {
    if (statement == Statement(1, StatementType::Stmt)) { return true; }
    return false;
}

bool StubPkbReader::hasFormerStarStmt(Statement &statement) const {
    if (statement == Statement(1, StatementType::Stmt)) { return false; }
    return true;
}

EntityPairSet StubPkbReader::getModifiesStmtPair(StatementType type) const {
    std::vector<EntityPointer> pair1 = {std::make_shared<Statement>(1, StatementType::Assign),
                                        std::make_shared<Variable>("var1")};
    std::vector<EntityPointer> pair2 = {std::make_shared<Statement>(3, StatementType::Call),
                                        std::make_shared<Variable>("var2")};
    std::vector<EntityPointer> pair3 = {std::make_shared<Statement>(2, StatementType::While),
                                        std::make_shared<Variable>("var3")};
    if (type == StatementType::Assign) {
        std::vector<EntityPointer> pair4 = {std::make_shared<Statement>(4, StatementType::Assign),
                                            std::make_shared<Variable>("var3")};
        std::vector<EntityPointer> pair5 = {std::make_shared<Statement>(6, StatementType::Assign),
                                            std::make_shared<Variable>("var4")};
        return EntityPairSet({pair1, pair4, pair5});
    }
    return EntityPairSet({pair1, pair2, pair3});
}

EntityPairSet StubPkbReader::getModifiesProcPair() const {
    std::vector<EntityPointer> pair1 = {std::make_shared<Procedure>("first"), std::make_shared<Variable>("one")};
    std::vector<EntityPointer> pair2 = {std::make_shared<Procedure>("second"), std::make_shared<Variable>("two")};
    std::vector<EntityPointer> pair3 = {std::make_shared<Procedure>("third"), std::make_shared<Variable>("three")};
    std::vector<EntityPointer> pair4 = {std::make_shared<Procedure>("fourth"), std::make_shared<Variable>("four")};
    return EntityPairSet({pair1, pair2, pair3, pair4});
}

EntitySet StubPkbReader::getModifiesTypeIdent(StatementType type, Variable &var) const {
    return EntitySet{
            std::make_shared<Statement>(14, StatementType::Read),
            std::make_shared<Statement>(15, StatementType::Read),
    };
}

EntitySet StubPkbReader::getModifiesProcIdent(Variable &var) const {
    return EntitySet{std::make_shared<Procedure>("Procedure")};
}

EntitySet StubPkbReader::getModifiesStmt(StatementType type) const {
    return EntitySet{
            std::make_shared<Statement>(34, StatementType::While),
    };
}

EntitySet StubPkbReader::getModifiesProc() const {
    return EntitySet{
            std::make_shared<Procedure>("first"),
    };
}

EntitySet StubPkbReader::getModifiesVar(Statement &stmt) const {
    return EntitySet{std::make_shared<Variable>("myVar"), std::make_shared<Variable>("anotherVar")};
}

EntitySet StubPkbReader::getModifiesVar(Procedure &proc) const { return {}; }

bool StubPkbReader::isStmtModifiesVar(Statement &stmt, Variable &var) const { return false; }

bool StubPkbReader::isProcModifiesVar(Procedure &proc, Variable &var) const { return true; }

bool StubPkbReader::hasModifies(Statement &stmt) const { return true; }

bool StubPkbReader::hasModifies(Procedure &proc) const { return false; }

// Pattern queries i.e. pattern a (...,...)
// pattern a (_,_)
EntitySet StubPkbReader::getAllAssign() const {
    return EntitySet{std::make_shared<Statement>(1, StatementType::Assign),
                     std::make_shared<Statement>(2, StatementType::Assign),
                     std::make_shared<Statement>(3, StatementType::Assign)};
}

// pattern a (_, "x")
EntitySet StubPkbReader::getAssignStmtsByRhs(std::string &rhs, bool hasRhsWildCard) const {
    if (hasRhsWildCard) {
        return EntitySet{std::make_shared<Statement>(2, StatementType::Assign),
                         std::make_shared<Statement>(3, StatementType::Assign)};
    }
    return EntitySet{std::make_shared<Statement>(4, StatementType::Assign),
                     std::make_shared<Statement>(5, StatementType::Assign)};
}

// pattern a (v, _)
EntityPairSet StubPkbReader::getAllAssignStmtVarPair() const {
    std::vector<EntityPointer> pair1 = {std::make_shared<Statement>(1, StatementType::Assign),
                                        std::make_shared<Variable>("var1")};
    std::vector<EntityPointer> pair2 = {std::make_shared<Statement>(1, StatementType::Assign),
                                        std::make_shared<Variable>("var2")};
    std::vector<EntityPointer> pair3 = {std::make_shared<Statement>(2, StatementType::Assign),
                                        std::make_shared<Variable>("var3")};
    return EntityPairSet({pair1, pair2, pair3});
}

// pattern a (v, "x")
EntityPairSet StubPkbReader::getAssignStmtsVarPairByRhs(std::string &rhs, bool hasWildCard) const {
    std::vector<EntityPointer> pair1 = {std::make_shared<Statement>(1, StatementType::Assign),
                                        std::make_shared<Variable>("var1")};
    std::vector<EntityPointer> pair2 = {std::make_shared<Statement>(1, StatementType::Assign),
                                        std::make_shared<Variable>("var2")};
    std::vector<EntityPointer> pair3 = {std::make_shared<Statement>(2, StatementType::Assign),
                                        std::make_shared<Variable>("var3")};
    std::vector<EntityPointer> pair4 = {std::make_shared<Statement>(3, StatementType::Assign),
                                        std::make_shared<Variable>("var4")};
    std::vector<EntityPointer> pair5 = {std::make_shared<Statement>(4, StatementType::Assign),
                                        std::make_shared<Variable>("var3")};
    std::vector<EntityPointer> pair6 = {std::make_shared<Statement>(6, StatementType::Assign),
                                        std::make_shared<Variable>("var6")};
    if (rhs == "((1)+(multiclauseTest))" && hasWildCard) { return EntityPairSet({pair1, pair2, pair3, pair4, pair5}); }
    if (rhs == "((multiclauseTest)+(patternOnly))" && !hasWildCard) { return EntityPairSet({pair6}); }

    if (hasWildCard) {
        std::vector<EntityPointer> pair2 = {std::make_shared<Statement>(2, StatementType::Assign),
                                            std::make_shared<Variable>("var2")};
        std::vector<EntityPointer> pair3 = {std::make_shared<Statement>(3, StatementType::Assign),
                                            std::make_shared<Variable>("var3")};
        return EntityPairSet({pair2, pair3});
    }
    return EntityPairSet({pair1, pair2, pair3});
}

// pattern a ("x", _)
EntitySet StubPkbReader::getAssignStmtsByLhs(Variable &lhs) const {
    return EntitySet{std::make_shared<Statement>(6, StatementType::Assign)};
}

// pattern a ("x", "x")
EntitySet StubPkbReader::getAssignStmtsByLhsRhs(Variable &lhs, std::string &rhs, bool hasRhsWildCard) const {
    if (lhs == Variable("noneCase") && !hasRhsWildCard) { return EntitySet(); }
    return EntitySet{std::make_shared<Statement>(100, StatementType::Assign),
                     std::make_shared<Statement>(100000, StatementType::Assign)};
}

EntityPairSet StubPkbReader::getParentPair(StatementType formerType, StatementType latterType) const {
    std::vector<EntityPointer> pair2 = {std::make_shared<Statement>(2, StatementType::If),
                                        std::make_shared<Statement>(3, StatementType::Print)};
    std::vector<EntityPointer> pair3 = {std::make_shared<Statement>(5, StatementType::If),
                                        std::make_shared<Statement>(6, StatementType::Print)};
    if (formerType == StatementType::If && latterType == StatementType::Print) { return EntityPairSet({pair2, pair3}); }
    return EntityPairSet();
}

EntityPairSet StubPkbReader::getParentStarPair(StatementType formerType, StatementType latterType) const {
    std::vector<EntityPointer> pair1 = {std::make_shared<Statement>(2, StatementType::While),
                                        std::make_shared<Statement>(3, StatementType::Assign)};
    std::vector<EntityPointer> pair2 = {std::make_shared<Statement>(2, StatementType::While),
                                        std::make_shared<Statement>(4, StatementType::Call)};
    if (formerType == StatementType::While && latterType == StatementType::Stmt) {
        return EntityPairSet({pair1, pair2});
    }
    return EntityPairSet();
}

EntitySet StubPkbReader::getParentTypeStmt(StatementType type, Statement &statement) const {
    if (type == StatementType::Print) { return EntitySet(); }
    return EntitySet();
}

EntitySet StubPkbReader::getParentStarTypeStmt(StatementType type, Statement &statement) const {
    if (type == StatementType::While && statement == Statement(700, StatementType::Stmt)) {
        return EntitySet({std::make_shared<Statement>(Statement(2, StatementType::While))});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getParentTypeWildcard(StatementType type) const {
    if (type == StatementType::While) {
        return EntitySet({std::make_shared<Statement>(6, StatementType::While),
                          std::make_shared<Statement>(7, StatementType::While),
                          std::make_shared<Statement>(8, StatementType::While)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getParentStarTypeWildcard(StatementType type) const {
    if (type == StatementType::If) {
        return EntitySet({std::make_shared<Statement>(10, StatementType::If),
                          std::make_shared<Statement>(11, StatementType::If),
                          std::make_shared<Statement>(12, StatementType::If)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getParentStmtType(Statement &statement, StatementType type) const {
    if (statement == Statement(23, StatementType::Stmt) && type == StatementType::Print) {
        return EntitySet({
                std::make_shared<Statement>(24, StatementType::Print),
        });
    }
    return EntitySet();
}

EntitySet StubPkbReader::getParentStarStmtType(Statement &statement, StatementType type) const {
    if (statement == Statement(24, StatementType::Stmt) && type == StatementType::Call) { return EntitySet(); }
    return EntitySet();
}

EntitySet StubPkbReader::getParentWildcardType(StatementType type) const {
    if (type == StatementType::Stmt) {
        return EntitySet({
                std::make_shared<Statement>(2, StatementType::Stmt),
                std::make_shared<Statement>(4, StatementType::Stmt),
                std::make_shared<Statement>(5, StatementType::Stmt),
                std::make_shared<Statement>(7, StatementType::Stmt),
        });
    }
    return EntitySet();
}

EntitySet StubPkbReader::getParentStarWildcardType(StatementType type) const {
    if (type == StatementType::If) {
        return EntitySet({std::make_shared<Statement>(11, StatementType::If),
                          std::make_shared<Statement>(12, StatementType::If)});
    }
    return EntitySet();
}

bool StubPkbReader::isParent(Statement &statement1, Statement &statement2) const {
    if (statement1 == Statement(1, StatementType::Stmt) && statement2 == Statement(10, StatementType::Stmt)) {
        return true;
    }
    if (statement1 == Statement(3, StatementType::Stmt) && statement2 == Statement(5, StatementType::Stmt)) {
        return false;
    }
    return true;
}

bool StubPkbReader::isParentStar(Statement &statement1, Statement &statement2) const {
    if (statement1 == Statement(3, StatementType::Stmt) && statement2 == Statement(5, StatementType::Stmt)) {
        return true;
    }
    return false;
}

bool StubPkbReader::hasParent() const { return true; }

bool StubPkbReader::hasParentStar() const { return true; }

bool StubPkbReader::hasParentStmt(Statement &statement) const {
    if (statement == Statement(1, StatementType::Stmt)) { return false; }
    return false;
}

bool StubPkbReader::hasParentStarStmt(Statement &statement) const {
    if (statement == Statement(2, StatementType::Stmt)) { return true; }
    return false;
}

bool StubPkbReader::hasChildStmt(Statement &statement) const {
    if (statement == Statement(1, StatementType::Stmt)) { return true; }
    return false;
}

bool StubPkbReader::hasChildStarStmt(Statement &statement) const {
    if (statement == Statement(1, StatementType::Stmt)) { return true; }
    return false;
}

bool StubPkbReader::hasCalls() const { return true; }

bool StubPkbReader::hasCallsStar() const { return true; }

bool StubPkbReader::isCallee(Procedure &proc) const {
    if (proc == Procedure("testIdent")) { return false; }
    return false;
}

bool StubPkbReader::isCalleeStar(Procedure &proc) const {
    if (proc == Procedure("isCalled")) { return true; }
    return false;
}

bool StubPkbReader::isCaller(Procedure &proc) const {
    if (proc == Procedure("notCaller")) { return false; }
    return true;
}

bool StubPkbReader::isCallerStar(Procedure &proc) const {
    if (proc == Procedure("testIdent")) { return false; }
    return false;
}

bool StubPkbReader::isCalls(Procedure &caller, Procedure &callee) const {
    if (caller == Procedure("caller") && callee == Procedure("callee")) { return true; }
    return false;
}

bool StubPkbReader::isCallsStar(Procedure &caller, Procedure &callee) const {
    if (caller == Procedure("testIdent") && callee == Procedure("testIdent2")) { return true; }
    return false;
}

EntitySet StubPkbReader::getCallees() const {
    return EntitySet({std::make_shared<Procedure>("procedure1"), std::make_shared<Procedure>("procedure2")});
}

EntitySet StubPkbReader::getCalleesStar() const { return EntitySet(); }

EntitySet StubPkbReader::getCallers() const { return EntitySet(); }

EntitySet StubPkbReader::getCallersStar() const { return EntitySet({std::make_shared<Procedure>("procName")}); }

EntityPairSet StubPkbReader::getCallsPair() const {
    auto proc1 = std::make_shared<Procedure>("procedureLHS");
    auto proc2 = std::make_shared<Procedure>("procedureRHS");
    return EntityPairSet({{proc1, proc2}});
}

EntityPairSet StubPkbReader::getCallsStarPair() const {
    auto proc1 = std::make_shared<Procedure>("procedureLHS");
    auto proc2 = std::make_shared<Procedure>("procedureLHS&RHS");
    auto proc3 = std::make_shared<Procedure>("procedureRHS");
    return EntityPairSet({{proc1, proc2}, {proc2, proc3}});
}

EntitySet StubPkbReader::getCallers(Procedure &callee) const {
    if (callee == Procedure("procName")) { return EntitySet(); }
    return EntitySet();
}

EntitySet StubPkbReader::getCallersStar(Procedure &callee) const {
    return EntitySet({std::make_shared<Procedure>("procName1")});
}


EntitySet StubPkbReader::getCallees(Procedure &caller) const {
    if (caller == Procedure("Proc1")) { return EntitySet({std::make_shared<Procedure>("Proc2")}); }
    return EntitySet();
}

EntitySet StubPkbReader::getCalleesStar(Procedure &caller) const {
    if (caller == Procedure("procName")) { return EntitySet(); }
    return EntitySet();
}

EntityPairSet StubPkbReader::getNextPair(StatementType formerType, StatementType latterType) const {
    if (formerType == StatementType::Assign && latterType == StatementType::Read) {
        std::vector<EntityPointer> pair1 = {std::make_shared<Statement>(1, StatementType::Assign),
                                            std::make_shared<Statement>(2, StatementType::Read)};
        std::vector<EntityPointer> pair2 = {std::make_shared<Statement>(3, StatementType::Assign),
                                            std::make_shared<Statement>(4, StatementType::Read)};
        std::vector<EntityPointer> pair3 = {std::make_shared<Statement>(5, StatementType::Assign),
                                            std::make_shared<Statement>(6, StatementType::Read)};
        return EntityPairSet({pair1, pair2, pair3});
    }
    return EntityPairSet();
}

EntityPairSet StubPkbReader::getNextStarPair(StatementType formerType, StatementType latterType) const {
    if (formerType == StatementType::Read && latterType == StatementType::If) {
        return EntityPairSet({{std::make_shared<Statement>(11, StatementType::Read),
                               std::make_shared<Statement>(12, StatementType::If)},
                              {std::make_shared<Statement>(21, StatementType::Read),
                               std::make_shared<Statement>(22, StatementType::If)},
                              {std::make_shared<Statement>(31, StatementType::Read),
                               std::make_shared<Statement>(32, StatementType::If)}});
    }
    return EntityPairSet();
}

EntitySet StubPkbReader::getNextStarSameStmt(StatementType stmtType) const {
    if (stmtType == StatementType::Assign) {
        return EntitySet({std::make_shared<Statement>(102, StatementType::Assign)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getNextTypeStmt(StatementType type, Statement &statement) const {
    if (type == StatementType::Stmt && statement == Statement(14, StatementType::Stmt)) {
        return EntitySet({std::make_shared<Statement>(13, StatementType::Call)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getNextStarTypeStmt(StatementType type, Statement &statement) const {
    if (type == StatementType::Stmt && statement == Statement(15, StatementType::Stmt)) {
        return EntitySet({std::make_shared<Statement>(1, StatementType::Call),
                          std::make_shared<Statement>(2, StatementType::Assign),
                          std::make_shared<Statement>(5, StatementType::Read)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getNextTypeWildcard(StatementType type) const {
    if (type == StatementType::If) {
        return EntitySet({
                std::make_shared<Statement>(11, StatementType::If),
        });
    }
    return EntitySet();
}

EntitySet StubPkbReader::getNextStarTypeWildcard(StatementType type) const {
    if (type == StatementType::While) {
        return EntitySet({
                std::make_shared<Statement>(20, StatementType::While),
        });
    }
    return EntitySet();
}

EntitySet StubPkbReader::getNextStmtType(Statement &statement, StatementType type) const {
    if (statement == Statement(23, StatementType::Stmt) && type == StatementType::Call) {
        return EntitySet({std::make_shared<Statement>(24, StatementType::Call)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getNextStarStmtType(Statement &statement, StatementType type) const {
    if (statement == Statement(23, StatementType::Stmt) && type == StatementType::If) {
        return EntitySet({std::make_shared<Statement>(26, StatementType::If)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getNextWildcardType(StatementType type) const {
    if (type == StatementType::Assign) {
        return EntitySet({
                std::make_shared<Statement>(10, StatementType::Assign),
                std::make_shared<Statement>(12, StatementType::Assign),
                std::make_shared<Statement>(13, StatementType::Assign),
        });
    }
    return EntitySet();
}

EntitySet StubPkbReader::getNextStarWildcardType(StatementType type) const {
    if (type == StatementType::Read) {
        return EntitySet({
                std::make_shared<Statement>(10, StatementType::Read),
                std::make_shared<Statement>(12, StatementType::Read),
                std::make_shared<Statement>(15, StatementType::Read),
        });
    }
    return EntitySet();
}

bool StubPkbReader::isNext(Statement &statement1, Statement &statement2) const { return true; }

bool StubPkbReader::isNextStar(Statement &statement1, Statement &statement2) const {
    if (statement1 == Statement(1, StatementType::Stmt) && statement2 == Statement(2, StatementType::Stmt)) {
        return false;
    }
    return true;
}

bool StubPkbReader::hasNext() const { return true; }

bool StubPkbReader::hasNextStar() const { return true; }

bool StubPkbReader::hasBeforeStmt(Statement &statement) const { return false; }

bool StubPkbReader::hasBeforeStarStmt(Statement &statement) const {
    if (statement == Statement(1, StatementType::Stmt)) { return false; }
    return true;
}

bool StubPkbReader::hasAfterStmt(Statement &statement) const { return false; }

bool StubPkbReader::hasAfterStarStmt(Statement &statement) const {
    if (statement == Statement(1, StatementType::Stmt)) { return true; }
    return false;
}

EntitySet StubPkbReader::getAllIfPatternStmts() const {
    return EntitySet({
            std::make_shared<Statement>(101, StatementType::If),
            std::make_shared<Statement>(102, StatementType::If),
            std::make_shared<Statement>(103, StatementType::If),
    });
};

EntitySet StubPkbReader::getIfStmtsByVar(Variable &var) const {
    if (var.getEntityValue() == "ifPatternVar") {
        return EntitySet({std::make_shared<Statement>(3, StatementType::If),
                          std::make_shared<Statement>(59, StatementType::If),
                          std::make_shared<Statement>(100, StatementType::If)});
    }
    return EntitySet{};
};

EntityPairSet StubPkbReader::getAllIfStmtVarPair() const {
    return EntityPairSet({{std::make_shared<Statement>(1, StatementType::If), std::make_shared<Variable>("var2")},
                          {std::make_shared<Statement>(3, StatementType::If), std::make_shared<Variable>("var3")}});
}

EntitySet StubPkbReader::getAllWhilePatternStmts() const { return EntitySet({std::make_shared<WhileStatement>(847)}); }

EntitySet StubPkbReader::getWhileStmtsByVar(Variable &var) const {
    if (var.getEntityValue() == "x") { return EntitySet{std::make_shared<WhileStatement>(873)}; }
    return EntitySet{};
}

EntityPairSet StubPkbReader::getAllWhileStmtVarPair() const {
    return EntityPairSet{
            {std::make_shared<WhileStatement>(860), std::make_shared<Variable>("var860")},
            {std::make_shared<WhileStatement>(861), std::make_shared<Variable>("var861")},
    };
}

EntityPairSet StubPkbReader::getAffectsPair(StatementType formerType, StatementType latterType) const {
    if (formerType == StatementType::Assign && latterType == StatementType::Assign) {
        std::vector<EntityPointer> pair1 = {std::make_shared<Statement>(1, StatementType::Assign),
                                            std::make_shared<Statement>(2, StatementType::Assign)};
        std::vector<EntityPointer> pair2 = {std::make_shared<Statement>(3, StatementType::Assign),
                                            std::make_shared<Statement>(4, StatementType::Assign)};
        std::vector<EntityPointer> pair3 = {std::make_shared<Statement>(5, StatementType::Assign),
                                            std::make_shared<Statement>(6, StatementType::Assign)};
        return EntityPairSet({pair1, pair2, pair3});
    }
    return EntityPairSet();
}

EntitySet StubPkbReader::getAffectsSameStmt(StatementType stmtType) const {
    if (stmtType == StatementType::Assign) {
        return EntitySet({std::make_shared<Statement>(61, StatementType::Assign)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getAffectsTypeStmt(StatementType type, Statement &statement) const {
    if (type == StatementType::Stmt && statement == Statement(71, StatementType::Stmt)) {
        return EntitySet({std::make_shared<Statement>(7, StatementType::Assign)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getAffectsTypeWildcard(StatementType type) const {
    if (type == StatementType::Assign) { return EntitySet({std::make_shared<Statement>(8, StatementType::Assign)}); }
    return EntitySet();
}

EntitySet StubPkbReader::getAffectsStmtType(Statement &statement, StatementType type) const {
    if (type == StatementType::Assign && statement == Statement(91, StatementType::Stmt)) {
        return EntitySet({std::make_shared<Statement>(9, StatementType::Assign)});
    }
    return EntitySet();
}

EntitySet StubPkbReader::getAffectsWildcardType(StatementType type) const {
    if (type == StatementType::Assign) { return EntitySet({std::make_shared<Statement>(10, StatementType::Assign)}); }
    return EntitySet();
}

bool StubPkbReader::isAffects(Statement &statement1, Statement &statement2) const {
    if (statement1 == Statement(11, StatementType::Stmt) && statement2 == Statement(12, StatementType::Stmt)) {
        return true;
    }
    return false;
}

bool StubPkbReader::hasAffects() const { return true; }

bool StubPkbReader::hasAffectedStmt(Statement &statement) const { return false; }

bool StubPkbReader::hasAffectsStmt(Statement &statement) const { return false; }