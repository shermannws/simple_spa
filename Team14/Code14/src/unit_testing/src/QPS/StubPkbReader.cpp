#include "StubPkbReader.h"
#include "Commons/Entities/CallStatement.h"
#include "Commons/Entities/ReadStatement.h"

#include "Commons/Entities/WhileStatement.h"

StubPkbReader::StubPkbReader() = default;

std::vector<Entity> StubPkbReader::getAllVariables() const {
    return std::vector<Entity>({
            Variable("var1"),
            Variable("var2"),
            Variable("var5"),
            Variable("var14"),
            Variable("var24"),
            Variable("var36"),
            Variable("var38"),
            Variable("var88"),
    });
}

std::vector<Entity> StubPkbReader::getAllConstants() const {
    return std::vector<Entity>({Constant("3"), Constant("7"), Constant("21"), Constant("63")});
}

std::vector<Entity> StubPkbReader::getAllProcedures() const {
    return std::vector<Entity>({
            Procedure("proc1"),
            Procedure("proc2"),
            Procedure("proc3"),
    });
}

std::vector<Entity> StubPkbReader::getAllStatements() const {
    return std::vector<Entity>{
            Statement(1, StatementType::If),     Statement(2, StatementType::While), Statement(3, StatementType::Call),
            Statement(4, StatementType::Assign), Statement(5, StatementType::Read),
    };
}

std::vector<Entity> StubPkbReader::getAllRead() const {
    return std::vector<Entity>({
            Statement(88, StatementType::Read, "var88"),
            Statement(24, StatementType::Read, "var24"),
            Statement(36, StatementType::Read, "var36"),
            Statement(14, StatementType::Read, "var14"),
    });
}

std::vector<Entity> StubPkbReader::getAllPrint() const {
    return std::vector<Entity>({
            Statement(1, StatementType::Print, "var1"),
            Statement(3, StatementType::Print, "var3"),
            Statement(5, StatementType::Print, "var5"),
            Statement(7, StatementType::Print, "var7"),
            Statement(9, StatementType::Print, "var9"),
    });
}

std::vector<Entity> StubPkbReader::getAllWhile() const {
    return std::vector<Entity>{
            Statement(10, StatementType::While),
            Statement(13, StatementType::While),
            Statement(15, StatementType::While),
    };
}

std::vector<Entity> StubPkbReader::getAllIf() const {
    return std::vector<Entity>({
            Statement(101, StatementType::If),
            Statement(102, StatementType::If),
    });
}

std::vector<Entity> StubPkbReader::getAllCall() const {
    return std::vector<Entity>({Statement(7, StatementType::Call, "Proc1"), Statement(10, StatementType::Call, "Proc2"),
                                Statement(21, StatementType::Call, "Proc3"),
                                Statement(22, StatementType::Call, "Proc3")});
}

std::vector<std::vector<Entity>> StubPkbReader::getUsesStmtPair(StatementType type) const {
    if (type == StatementType::Call) {
        return std::vector<std::vector<Entity>>(
                {{CallStatement(1, "proc1"), Variable("var1")}, {CallStatement(2, "proc2"), Variable("var2")}});
    }
    std::vector<Entity> pair1 = {Statement(1, StatementType::Assign), Variable("var")};
    std::vector<Entity> pair2 = {Statement(2, StatementType::Assign), Variable("var")};
    return std::vector<std::vector<Entity>>({pair1, pair2});
}

std::vector<std::vector<Entity>> StubPkbReader::getUsesProcPair() const {
    std::vector<Entity> pair1 = {Procedure("ProcedureName"), Variable("hello123")};
    std::vector<Entity> pair2 = {Procedure("ProcedureName2"), Variable("hello321")};
    return std::vector<std::vector<Entity>>({pair1, pair2});
}

std::vector<Entity> StubPkbReader::getUsesTypeIdent(StatementType type, Variable &var) const {
    return std::vector<Entity>{
            Statement(2, StatementType::If),
            Statement(4, StatementType::If),
            Statement(5, StatementType::If),
    };
}

std::vector<Entity> StubPkbReader::getUsesProcIdent(Variable &var) const {
    return std::vector<Entity>{Procedure("ProcedureName")};
};

std::vector<Entity> StubPkbReader::getUsesStmt(StatementType type) const {
    return std::vector<Entity>{
            Statement(1, StatementType::Assign),
            Statement(3, StatementType::Call),
    };
}

std::vector<Entity> StubPkbReader::getUsesProc() const { return {}; }

std::vector<Entity> StubPkbReader::getUsesVar(Statement &stmt) const {
    return std::vector<Entity>{Variable("name"), Variable("asdfghjkl")};
}

std::vector<Entity> StubPkbReader::getUsesVar(Procedure &proc) const {
    return std::vector<Entity>{Variable("proc"), Variable("anotherVar")};
}

bool StubPkbReader::isStmtUsesVar(Statement &stmt, Variable &var) const {
    if (stmt == Statement(1, StatementType::Stmt) && var == Variable("multiClauseSTonly")) { return false; }
    if (var == Variable("multiClauseTrue")) { return true; }
    return true;
}

bool StubPkbReader::isProcUsesVar(Procedure &proc, Variable &var) const { return false; }

bool StubPkbReader::hasUses(Statement &stmt) const { return false; }

bool StubPkbReader::hasUses(Procedure &proc) const { return true; }

std::vector<std::vector<Entity>> StubPkbReader::getFollowsPair(StatementType formerType,
                                                               StatementType latterType) const {
    return std::vector<std::vector<Entity>>();
}

std::vector<std::vector<Entity>> StubPkbReader::getFollowsStarPair(StatementType formerType,
                                                                   StatementType latterType) const {
    return std::vector<std::vector<Entity>>();
}

std::vector<Entity> StubPkbReader::getFollowsTypeStmt(StatementType type, Statement &statement) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStarTypeStmt(StatementType type, Statement &statement) const {
    if (type == StatementType::Stmt && statement == Statement(700, StatementType::Stmt)) {
        return std::vector<Entity>({Statement(10, StatementType::Assign)});
    }
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsTypeWildcard(StatementType type) const { return std::vector<Entity>(); }

std::vector<Entity> StubPkbReader::getFollowsStarTypeWildcard(StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStmtType(Statement &statement, StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStarStmtType(Statement &statement, StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsWildcardType(StatementType type) const { return std::vector<Entity>(); }

std::vector<Entity> StubPkbReader::getFollowsStarWildcardType(StatementType type) const {
    return std::vector<Entity>();
}

bool StubPkbReader::isFollows(Statement &statement1, Statement &statement2) const { return false; }

bool StubPkbReader::isFollowsStar(Statement &statement1, Statement &statement2) const { return false; }

bool StubPkbReader::hasFollows() const { return false; }

bool StubPkbReader::hasFollowsStar() const { return false; }

bool StubPkbReader::hasLatterStmt(Statement &statement) const { return false; }

bool StubPkbReader::hasFormerStmt(Statement &statement) const { return false; }

bool StubPkbReader::hasLatterStarStmt(Statement &statement) const { return false; }

bool StubPkbReader::hasFormerStarStmt(Statement &statement) const { return false; }

std::vector<std::vector<Entity>> StubPkbReader::getModifiesStmtPair(StatementType type) const {
    std::vector<Entity> pair1 = {Statement(1, StatementType::Assign), Variable("var1")};
    std::vector<Entity> pair2 = {Statement(3, StatementType::Call), Variable("var2")};
    std::vector<Entity> pair3 = {Statement(2, StatementType::While), Variable("var3")};
    return std::vector<std::vector<Entity>>({pair1, pair2, pair3});
}

std::vector<std::vector<Entity>> StubPkbReader::getModifiesProcPair() const {
    std::vector<Entity> pair1 = {Procedure("first"), Variable("one")};
    std::vector<Entity> pair2 = {Procedure("second"), Variable("two")};
    std::vector<Entity> pair3 = {Procedure("third"), Variable("three")};
    std::vector<Entity> pair4 = {Procedure("fourth"), Variable("four")};
    return std::vector<std::vector<Entity>>({pair1, pair2, pair3, pair4});
}

std::vector<Entity> StubPkbReader::getModifiesTypeIdent(StatementType type, Variable &var) const {
    return std::vector<Entity>{
            Statement(14, StatementType::Read),
            Statement(15, StatementType::Read),
    };
}

std::vector<Entity> StubPkbReader::getModifiesProcIdent(Variable &var) const {
    return std::vector<Entity>{Procedure("Procedure")};
}

std::vector<Entity> StubPkbReader::getModifiesStmt(StatementType type) const {
    return std::vector<Entity>{
            Statement(34, StatementType::While),
    };
}

std::vector<Entity> StubPkbReader::getModifiesProc() const {
    return std::vector<Entity>{
            Procedure("first"),
    };
}

std::vector<Entity> StubPkbReader::getModifiesVar(Statement &stmt) const {
    return std::vector<Entity>{Variable("myVar"), Variable("anotherVar")};
}

std::vector<Entity> StubPkbReader::getModifiesVar(Procedure &proc) const { return {}; }

bool StubPkbReader::isStmtModifiesVar(Statement &stmt, Variable &var) const { return false; }

bool StubPkbReader::isProcModifiesVar(Procedure &proc, Variable &var) const { return true; }

bool StubPkbReader::hasModifies(Statement &stmt) const { return true; }

bool StubPkbReader::hasModifies(Procedure &proc) const { return false; }

// Pattern queries i.e. pattern a (...,...)
// pattern a (_,_)
std::vector<Entity> StubPkbReader::getAllAssign() const {
    return std::vector<Entity>{Statement(1, StatementType::Assign), Statement(2, StatementType::Assign),
                               Statement(3, StatementType::Assign)};
}

// pattern a (_, "x")
std::vector<Entity> StubPkbReader::getAssignStmtsByRhs(std::string &rhs, bool hasRhsWildCard) const {
    if (hasRhsWildCard) {
        return std::vector<Entity>{Statement(2, StatementType::Assign), Statement(3, StatementType::Assign)};
    }
    return std::vector<Entity>{Statement(4, StatementType::Assign), Statement(5, StatementType::Assign)};
}

// pattern a (v, _)
std::vector<std::vector<Entity>> StubPkbReader::getAllAssignStmtVarPair() const {
    std::vector<Entity> pair1 = {Statement(1, StatementType::Assign), Variable("var1")};
    std::vector<Entity> pair2 = {Statement(1, StatementType::Assign), Variable("var2")};
    std::vector<Entity> pair3 = {Statement(2, StatementType::Assign), Variable("var3")};
    return std::vector<std::vector<Entity>>({pair1, pair2, pair3});
}

// pattern a (v, "x")
std::vector<std::vector<Entity>> StubPkbReader::getAssignStmtsVarPairByRhs(std::string &rhs, bool hasWildCard) const {
    std::vector<Entity> pair1 = {Statement(1, StatementType::Assign), Variable("var1")};
    std::vector<Entity> pair2 = {Statement(1, StatementType::Assign), Variable("var2")};
    std::vector<Entity> pair3 = {Statement(2, StatementType::Assign), Variable("var3")};
    std::vector<Entity> pair4 = {Statement(3, StatementType::Assign), Variable("var4")};
    std::vector<Entity> pair5 = {Statement(4, StatementType::Assign), Variable("var3")};
    std::vector<Entity> pair6 = {Statement(6, StatementType::Assign), Variable("var6")};
    if (rhs == "((1)+(multiclauseTest))" && hasWildCard) {
        return std::vector<std::vector<Entity>>({pair1, pair2, pair3, pair4, pair5});
    }
    if (rhs == "((multiclauseTest)+(patternOnly))" && !hasWildCard) {
        return std::vector<std::vector<Entity>>({pair6});
    }

    if (hasWildCard) {
        std::vector<Entity> pair2 = {Statement(2, StatementType::Assign), Variable("var2")};
        std::vector<Entity> pair3 = {Statement(3, StatementType::Assign), Variable("var3")};
        return std::vector<std::vector<Entity>>({pair2, pair3});
    }
    return std::vector<std::vector<Entity>>({pair1, pair2, pair3});
}

// pattern a ("x", _)
std::vector<Entity> StubPkbReader::getAssignStmtsByLhs(Variable &lhs) const {
    return std::vector<Entity>{Statement(6, StatementType::Assign)};
}

// pattern a ("x", "x")
std::vector<Entity> StubPkbReader::getAssignStmtsByLhsRhs(Variable &lhs, std::string &rhs, bool hasRhsWildCard) const {
    if (lhs == Variable("noneCase") && !hasRhsWildCard) { return std::vector<Entity>(); }
    return std::vector<Entity>{Statement(100, StatementType::Assign), Statement(100000, StatementType::Assign)};
}

std::vector<std::vector<Entity>> StubPkbReader::getParentPair(StatementType formerType,
                                                              StatementType latterType) const {
    return std::vector<std::vector<Entity>>();
}

std::vector<std::vector<Entity>> StubPkbReader::getParentStarPair(StatementType formerType,
                                                                  StatementType latterType) const {
    return std::vector<std::vector<Entity>>();
}

std::vector<Entity> StubPkbReader::getParentTypeStmt(StatementType type, Statement &statement) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getParentStarTypeStmt(StatementType type, Statement &statement) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getParentTypeWildcard(StatementType type) const { return std::vector<Entity>(); }

std::vector<Entity> StubPkbReader::getParentStarTypeWildcard(StatementType type) const { return std::vector<Entity>(); }

std::vector<Entity> StubPkbReader::getParentStmtType(Statement &statement, StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getParentStarStmtType(Statement &statement, StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getParentWildcardType(StatementType type) const { return std::vector<Entity>(); }

std::vector<Entity> StubPkbReader::getParentStarWildcardType(StatementType type) const { return std::vector<Entity>(); }

bool StubPkbReader::isParent(Statement &statement1, Statement &statement2) const {
    if (statement1 == Statement(1, StatementType::Stmt) && statement2 == Statement(10, StatementType::Stmt)) {
        return true;
    }
    return true;
}

bool StubPkbReader::isParentStar(Statement &statement1, Statement &statement2) const { return false; }

bool StubPkbReader::hasParent() const { return false; }

bool StubPkbReader::hasParentStar() const { return false; }

bool StubPkbReader::hasParentStmt(Statement &statement) const { return false; }

bool StubPkbReader::hasParentStarStmt(Statement &statement) const { return false; }

bool StubPkbReader::hasChildStmt(Statement &statement) const { return false; }

bool StubPkbReader::hasChildStarStmt(Statement &statement) const { return false; }

bool StubPkbReader::hasCalls() const { return true; }

bool StubPkbReader::hasCallsStar() const { return false; }

bool StubPkbReader::isCallee(Procedure &proc) const {
    if (proc == Procedure("testIdent")) { return false; }
    return false;
}

bool StubPkbReader::isCalleeStar(Procedure &proc) const { return false; }

bool StubPkbReader::isCaller(Procedure &proc) const { return false; }

bool StubPkbReader::isCallerStar(Procedure &proc) const {
    if (proc == Procedure("testIdent")) { return false; }
    return false;
}

bool StubPkbReader::isCalls(Procedure &caller, Procedure &callee) const { return false; }

bool StubPkbReader::isCallsStar(Procedure &caller, Procedure &callee) const {
    if (caller == Procedure("testIdent") && callee == Procedure("testIdent2")) { return true; }
    return false;
}

std::vector<Entity> StubPkbReader::getCallees() const {
    return std::vector<Entity>({Procedure("procedure1"), Procedure("procedure2")});
}

std::vector<Entity> StubPkbReader::getCalleesStar() const { return std::vector<Entity>(); }

std::vector<Entity> StubPkbReader::getCallers() const { return std::vector<Entity>(); }

std::vector<Entity> StubPkbReader::getCallersStar() const { return std::vector<Entity>({Procedure("procName")}); }

std::vector<std::vector<Entity>> StubPkbReader::getCallsPair() const {
    auto proc1 = Procedure("procedureLHS");
    auto proc2 = Procedure("procedureRHS");
    return std::vector<std::vector<Entity>>({{proc1, proc2}});
}

std::vector<std::vector<Entity>> StubPkbReader::getCallsStarPair() const { return std::vector<std::vector<Entity>>(); }

std::vector<Entity> StubPkbReader::getCallers(Procedure &callee) const {
    if (callee == Procedure("procName")) { return std::vector<Entity>(); }
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getCallersStar(Procedure &callee) const { return std::vector<Entity>(); }

std::vector<Entity> StubPkbReader::getCallees(Procedure &caller) const { return std::vector<Entity>(); }

std::vector<Entity> StubPkbReader::getCalleesStar(Procedure &caller) const {
    if (caller == Procedure("procName")) { return std::vector<Entity>(); }
    return std::vector<Entity>();
}

std::vector<std::vector<Entity>> StubPkbReader::getNextPair(StatementType formerType, StatementType latterType) const {
    if (formerType == StatementType::Assign && latterType == StatementType::Read) {
        std::vector<Entity> pair1 = {Statement(1, StatementType::Assign), Statement(2, StatementType::Read)};
        std::vector<Entity> pair2 = {Statement(3, StatementType::Assign), Statement(4, StatementType::Read)};
        std::vector<Entity> pair3 = {Statement(5, StatementType::Assign), Statement(6, StatementType::Read)};
        return std::vector<std::vector<Entity>>({pair1, pair2, pair3});
    }
    return std::vector<std::vector<Entity>>();
}

std::vector<std::vector<Entity>> StubPkbReader::getNextStarPair(StatementType formerType,
                                                                StatementType latterType) const {
    if (formerType == StatementType::Read && latterType == StatementType::If) {
        return std::vector<std::vector<Entity>>(
                {{Statement(11, StatementType::Read), Statement(12, StatementType::If)},
                 {Statement(21, StatementType::Read), Statement(22, StatementType::If)},
                 {Statement(31, StatementType::Read), Statement(32, StatementType::If)}});
    }
    return std::vector<std::vector<Entity>>();
}

std::vector<Entity> StubPkbReader::getNextStarSameStmt(StatementType stmtType) const {
    if (stmtType == StatementType::Assign) { return std::vector<Entity>({Statement(102, StatementType::Assign)}); }
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getNextTypeStmt(StatementType type, Statement &statement) const {
    if (type == StatementType::Stmt && statement == Statement(14, StatementType::Stmt)) {
        return std::vector<Entity>({Statement(13, StatementType::Call)});
    }
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getNextStarTypeStmt(StatementType type, Statement &statement) const {
    if (type == StatementType::Stmt && statement == Statement(15, StatementType::Stmt)) {
        return std::vector<Entity>({Statement(1, StatementType::Call), Statement(2, StatementType::Assign),
                                    Statement(5, StatementType::Read)});
    }
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getNextTypeWildcard(StatementType type) const {
    if (type == StatementType::If) {
        return std::vector<Entity>({
                Statement(11, StatementType::If),
        });
    }
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getNextStarTypeWildcard(StatementType type) const {
    if (type == StatementType::While) {
        return std::vector<Entity>({
                Statement(20, StatementType::While),
        });
    }
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getNextStmtType(Statement &statement, StatementType type) const {
    if (statement == Statement(23, StatementType::Stmt) && type == StatementType::Call) {
        return std::vector<Entity>({Statement(24, StatementType::Call)});
    }
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getNextStarStmtType(Statement &statement, StatementType type) const {
    if (statement == Statement(23, StatementType::Stmt) && type == StatementType::If) {
        return std::vector<Entity>({Statement(26, StatementType::If)});
    }
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getNextWildcardType(StatementType type) const {
    if (type == StatementType::Assign) {
        return std::vector<Entity>({
                Statement(10, StatementType::Assign),
                Statement(12, StatementType::Assign),
                Statement(13, StatementType::Assign),
        });
    }
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getNextStarWildcardType(StatementType type) const {
    if (type == StatementType::Read) {
        return std::vector<Entity>({
                Statement(10, StatementType::Read),
                Statement(12, StatementType::Read),
                Statement(15, StatementType::Read),
        });
    }
    return std::vector<Entity>();
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

std::vector<Entity> StubPkbReader::getAllIfPatternStmts() const {
    return std::vector<Entity>({
            Statement(101, StatementType::If),
            Statement(102, StatementType::If),
            Statement(103, StatementType::If),
    });
};

std::vector<Entity> StubPkbReader::getIfStmtsByVar(Variable &var) const {
    if (var.getEntityValue() == "ifPatternVar") {
        return std::vector<Entity>(
                {Statement(3, StatementType::If), Statement(59, StatementType::If), Statement(100, StatementType::If)});
    }
    return std::vector<Entity>{};
};

std::vector<std::vector<Entity>> StubPkbReader::getAllIfStmtVarPair() const {
    return std::vector<std::vector<Entity>>(
            {{Statement(1, StatementType::If), Variable("var2")}, {Statement(3, StatementType::If), Variable("var3")}});
}

std::vector<Entity> StubPkbReader::getAllWhilePatternStmts() const {
    return std::vector<Entity>({WhileStatement(847)});
}

std::vector<Entity> StubPkbReader::getWhileStmtsByVar(Variable &var) const {
    if (var.getEntityValue() == "x") { return std::vector<Entity>{WhileStatement(873)}; }
    return std::vector<Entity>{};
}

std::vector<std::vector<Entity>> StubPkbReader::getAllWhileStmtVarPair() const {
    return std::vector<std::vector<Entity>>{
            {WhileStatement(860), Variable("var860")},
            {WhileStatement(861), Variable("var861")},
    };
}