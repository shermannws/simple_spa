#include "PkbConcreteReader.h"

PkbConcreteReader::PkbConcreteReader(std::shared_ptr<PkbReaderManager> readerManager) {
    this->readerManager = readerManager;
}

std::unordered_set<Entity> PkbConcreteReader::getAllVariables() const { return this->readerManager->getAllVariables(); }

std::unordered_set<Entity> PkbConcreteReader::getAllConstants() const { return this->readerManager->getAllConstants(); }

std::unordered_set<Entity> PkbConcreteReader::getAllProcedures() const {
    return this->readerManager->getAllProcedures();
}

std::unordered_set<Entity> PkbConcreteReader::getAllStatements() const {
    return this->readerManager->getAllStatements();
}

std::unordered_set<Entity> PkbConcreteReader::getAllRead() const { return this->readerManager->getAllRead(); }

std::unordered_set<Entity> PkbConcreteReader::getAllPrint() const { return this->readerManager->getAllPrint(); }

std::unordered_set<Entity> PkbConcreteReader::getAllWhile() const { return this->readerManager->getAllWhile(); }

std::unordered_set<Entity> PkbConcreteReader::getAllIf() const { return this->readerManager->getAllIf(); }

std::unordered_set<Entity> PkbConcreteReader::getAllCall() const { return this->readerManager->getAllCall(); }

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getUsesStmtPair(StatementType type) const {
    return this->readerManager->getUsesStmtPair(type);
}

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getUsesProcPair() const {
    return this->readerManager->getUsesProcPair();
}

std::unordered_set<Entity> PkbConcreteReader::getUsesTypeIdent(StatementType type, Variable &var) const {
    return this->readerManager->getUsesTypeIdent(type, var);
}

std::unordered_set<Entity> PkbConcreteReader::getUsesProcIdent(Variable &var) const {
    return this->readerManager->getUsesProcIdent(var);
};

std::unordered_set<Entity> PkbConcreteReader::getUsesStmt(StatementType type) const {
    return this->readerManager->getUsesStmt(type);
}

std::unordered_set<Entity> PkbConcreteReader::getUsesProc() const { return this->readerManager->getUsesProc(); }

std::unordered_set<Entity> PkbConcreteReader::getUsesVar(Statement &stmt) const {
    return this->readerManager->getUsesVar(stmt);
}

std::unordered_set<Entity> PkbConcreteReader::getUsesVar(Procedure &proc) const {
    return this->readerManager->getUsesVar(proc);
}

bool PkbConcreteReader::isStmtUsesVar(Statement &stmt, Variable &var) const {
    return this->readerManager->isStmtUsesVar(stmt, var);
}

bool PkbConcreteReader::isProcUsesVar(Procedure &proc, Variable &var) const {
    return this->readerManager->isProcUsesVar(proc, var);
}

bool PkbConcreteReader::hasUses(Statement &stmt) const { return this->readerManager->hasUses(stmt); }

bool PkbConcreteReader::hasUses(Procedure &proc) const { return this->readerManager->hasUses(proc); }

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getFollowsPair(StatementType formerType,
                                                                          StatementType latterType) const {
    return this->readerManager->getFollowsPair(formerType, latterType);
}

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getFollowsStarPair(StatementType formerType,
                                                                              StatementType latterType) const {
    return this->readerManager->getFollowsStarPair(formerType, latterType);
}

std::unordered_set<Entity> PkbConcreteReader::getFollowsTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getFollowsTypeStmt(type, statement);
}

std::unordered_set<Entity> PkbConcreteReader::getFollowsStarTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getFollowsStarTypeStmt(type, statement);
}

std::unordered_set<Entity> PkbConcreteReader::getFollowsTypeWildcard(StatementType type) const {
    return this->readerManager->getFollowsTypeWildcard(type);
}

std::unordered_set<Entity> PkbConcreteReader::getFollowsStarTypeWildcard(StatementType type) const {
    return this->readerManager->getFollowsStarTypeWildcard(type);
}

std::unordered_set<Entity> PkbConcreteReader::getFollowsStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getFollowsStmtType(statement, type);
}

std::unordered_set<Entity> PkbConcreteReader::getFollowsStarStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getFollowsStarStmtType(statement, type);
}

std::unordered_set<Entity> PkbConcreteReader::getFollowsWildcardType(StatementType type) const {
    return this->readerManager->getFollowsWildcardType(type);
}

std::unordered_set<Entity> PkbConcreteReader::getFollowsStarWildcardType(StatementType type) const {
    return this->readerManager->getFollowsStarWildcardType(type);
}

bool PkbConcreteReader::isFollows(Statement &statement1, Statement &statement2) const {
    return this->readerManager->isFollows(statement1, statement2);
}

bool PkbConcreteReader::isFollowsStar(Statement &statement1, Statement &statement2) const {
    return this->readerManager->isFollowsStar(statement1, statement2);
}

bool PkbConcreteReader::hasFollows() const { return this->readerManager->hasFollows(); }

bool PkbConcreteReader::hasFollowsStar() const { return this->readerManager->hasFollowsStar(); }

bool PkbConcreteReader::hasLatterStmt(Statement &statement) const {
    return this->readerManager->hasLatterStmt(statement);
}

bool PkbConcreteReader::hasFormerStmt(Statement &statement) const {
    return this->readerManager->hasFormerStmt(statement);
}

bool PkbConcreteReader::hasLatterStarStmt(Statement &statement) const {
    return this->readerManager->hasLatterStarStmt(statement);
}

bool PkbConcreteReader::hasFormerStarStmt(Statement &statement) const {
    return this->readerManager->hasFormerStarStmt(statement);
}

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getModifiesStmtPair(StatementType type) const {
    return this->readerManager->getModifiesStmtPair(type);
}

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getModifiesProcPair() const {
    return this->readerManager->getModifiesProcPair();
}

std::unordered_set<Entity> PkbConcreteReader::getModifiesTypeIdent(StatementType type, Variable &var) const {
    return this->readerManager->getModifiesTypeIdent(type, var);
}

std::unordered_set<Entity> PkbConcreteReader::getModifiesProcIdent(Variable &var) const {
    return this->readerManager->getModifiesProcIdent(var);
}

std::unordered_set<Entity> PkbConcreteReader::getModifiesStmt(StatementType type) const {
    return this->readerManager->getModifiesStmt(type);
}

std::unordered_set<Entity> PkbConcreteReader::getModifiesProc() const { return this->readerManager->getModifiesProc(); }

std::unordered_set<Entity> PkbConcreteReader::getModifiesVar(Statement &stmt) const {
    return this->readerManager->getModifiesVar(stmt);
}

std::unordered_set<Entity> PkbConcreteReader::getModifiesVar(Procedure &proc) const {
    return this->readerManager->getModifiesVar(proc);
}

bool PkbConcreteReader::isStmtModifiesVar(Statement &stmt, Variable &var) const {
    return this->readerManager->isStmtModifiesVar(stmt, var);
}

bool PkbConcreteReader::isProcModifiesVar(Procedure &proc, Variable &var) const {
    return this->readerManager->isProcModifiesVar(proc, var);
}

bool PkbConcreteReader::hasModifies(Statement &stmt) const { return this->readerManager->hasModifies(stmt); }

bool PkbConcreteReader::hasModifies(Procedure &proc) const { return this->readerManager->hasModifies(proc); }

// pattern a (_,_)
std::unordered_set<Entity> PkbConcreteReader::getAllAssign() const { return this->readerManager->getAllAssign(); }

// pattern a (_, "x")
std::unordered_set<Entity> PkbConcreteReader::getAssignStmtsByRhs(Expression &rhs, bool hasRhsWildCard) const {
    return this->readerManager->getAssignStmtsByRhs(rhs, hasRhsWildCard);
}

// pattern a (v, _)
std::unordered_set<std::vector<Entity>> PkbConcreteReader::getAllAssignStmtVarPair() const {
    return this->readerManager->getAllAssignStmtVarPair();
}

// pattern a (v, "x")
std::unordered_set<std::vector<Entity>> PkbConcreteReader::getAssignStmtsVarPairByRhs(Expression &rhs,
                                                                                      bool hasWildCard) const {
    return this->readerManager->getAssignStmtsVarPairByRhs(rhs, hasWildCard);
}

// pattern a ("x", _)
std::unordered_set<Entity> PkbConcreteReader::getAssignStmtsByLhs(Variable &lhs) const {
    return this->readerManager->getAssignStmtsByLhs(lhs);
}

// pattern a ("x", "x")
std::unordered_set<Entity> PkbConcreteReader::getAssignStmtsByLhsRhs(Variable &lhs, Expression &rhs,
                                                                     bool hasRhsWildCard) const {
    return this->readerManager->getAssignStmtsByLhsRhs(lhs, rhs, hasRhsWildCard);
}

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getParentPair(StatementType formerType,
                                                                         StatementType latterType) const {
    return this->readerManager->getParentPair(formerType, latterType);
}

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getParentStarPair(StatementType formerType,
                                                                             StatementType latterType) const {
    return this->readerManager->getParentStarPair(formerType, latterType);
}

std::unordered_set<Entity> PkbConcreteReader::getParentTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getParentTypeStmt(type, statement);
}

std::unordered_set<Entity> PkbConcreteReader::getParentStarTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getParentStarTypeStmt(type, statement);
}

std::unordered_set<Entity> PkbConcreteReader::getParentTypeWildcard(StatementType type) const {
    return this->readerManager->getParentTypeWildcard(type);
}

std::unordered_set<Entity> PkbConcreteReader::getParentStarTypeWildcard(StatementType type) const {
    return this->readerManager->getParentStarTypeWildcard(type);
}

std::unordered_set<Entity> PkbConcreteReader::getParentStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getParentStmtType(statement, type);
}

std::unordered_set<Entity> PkbConcreteReader::getParentStarStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getParentStarStmtType(statement, type);
}

std::unordered_set<Entity> PkbConcreteReader::getParentWildcardType(StatementType type) const {
    return this->readerManager->getParentWildcardType(type);
}

std::unordered_set<Entity> PkbConcreteReader::getParentStarWildcardType(StatementType type) const {
    return this->readerManager->getParentStarWildcardType(type);
}

bool PkbConcreteReader::isParent(Statement &statement1, Statement &statement2) const {
    return this->readerManager->isParent(statement1, statement2);
}

bool PkbConcreteReader::isParentStar(Statement &statement1, Statement &statement2) const {
    return this->readerManager->isParentStar(statement1, statement2);
}

bool PkbConcreteReader::hasParent() const { return this->readerManager->hasParent(); }

bool PkbConcreteReader::hasParentStar() const { return this->readerManager->hasParentStar(); }

bool PkbConcreteReader::hasParentStmt(Statement &statement) const {
    return this->readerManager->hasParentStmt(statement);
}

bool PkbConcreteReader::hasParentStarStmt(Statement &statement) const {
    return this->readerManager->hasParentStarStmt(statement);
}

bool PkbConcreteReader::hasChildStmt(Statement &statement) const {
    return this->readerManager->hasChildStmt(statement);
}

bool PkbConcreteReader::hasChildStarStmt(Statement &statement) const {
    return this->readerManager->hasChildStarStmt(statement);
}

bool PkbConcreteReader::hasCalls() const { return this->readerManager->hasCalls(); }

bool PkbConcreteReader::hasCallsStar() const { return this->readerManager->hasCallsStar(); }

bool PkbConcreteReader::isCallee(Procedure &proc) const { return this->readerManager->isCallee(proc); }

bool PkbConcreteReader::isCalleeStar(Procedure &proc) const { return this->readerManager->isCalleeStar(proc); }

bool PkbConcreteReader::isCaller(Procedure &proc) const { return this->readerManager->isCaller(proc); }

bool PkbConcreteReader::isCallerStar(Procedure &proc) const { return this->readerManager->isCallerStar(proc); }

bool PkbConcreteReader::isCalls(Procedure &caller, Procedure &callee) const {
    return this->readerManager->isCalls(caller, callee);
}

bool PkbConcreteReader::isCallsStar(Procedure &caller, Procedure &callee) const {
    return this->readerManager->isCallsStar(caller, callee);
}

std::unordered_set<Entity> PkbConcreteReader::getCallees() const { return this->readerManager->getCallees(); }

std::unordered_set<Entity> PkbConcreteReader::getCalleesStar() const { return this->readerManager->getCalleesStar(); }

std::unordered_set<Entity> PkbConcreteReader::getCallers() const { return this->readerManager->getCallers(); }

std::unordered_set<Entity> PkbConcreteReader::getCallersStar() const { return this->readerManager->getCallersStar(); }

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getCallsPair() const {
    return this->readerManager->getCallsPair();
}

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getCallsStarPair() const {
    return this->readerManager->getCallsStarPair();
}

std::unordered_set<Entity> PkbConcreteReader::getCallers(Procedure &callee) const {
    return this->readerManager->getCallers(callee);
}

std::unordered_set<Entity> PkbConcreteReader::getCallersStar(Procedure &callee) const {
    return this->readerManager->getCallersStar(callee);
}

std::unordered_set<Entity> PkbConcreteReader::getCallees(Procedure &caller) const {
    return this->readerManager->getCallees(caller);
}

std::unordered_set<Entity> PkbConcreteReader::getCalleesStar(Procedure &caller) const {
    return this->readerManager->getCalleesStar(caller);
}

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getNextPair(StatementType formerType,
                                                                       StatementType latterType) const {
    return this->readerManager->getNextPair(formerType, latterType);
}

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getNextStarPair(StatementType formerType,
                                                                           StatementType latterType) const {
    return this->readerManager->getNextStarPair(formerType, latterType);
}

std::unordered_set<Entity> PkbConcreteReader::getNextStarSameStmt(StatementType stmtType) const {
    return this->readerManager->getNextStarSameStmt(stmtType);
}

std::unordered_set<Entity> PkbConcreteReader::getNextTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getNextTypeStmt(type, statement);
}

std::unordered_set<Entity> PkbConcreteReader::getNextStarTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getNextStarTypeStmt(type, statement);
}

std::unordered_set<Entity> PkbConcreteReader::getNextTypeWildcard(StatementType type) const {
    return this->readerManager->getNextTypeWildcard(type);
}

std::unordered_set<Entity> PkbConcreteReader::getNextStarTypeWildcard(StatementType type) const {
    return this->readerManager->getNextStarTypeWildcard(type);
}

std::unordered_set<Entity> PkbConcreteReader::getNextStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getNextStmtType(statement, type);
}

std::unordered_set<Entity> PkbConcreteReader::getNextStarStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getNextStarStmtType(statement, type);
}

std::unordered_set<Entity> PkbConcreteReader::getNextWildcardType(StatementType type) const {
    return this->readerManager->getNextWildcardType(type);
}

std::unordered_set<Entity> PkbConcreteReader::getNextStarWildcardType(StatementType type) const {
    return this->readerManager->getNextStarWildcardType(type);
}

bool PkbConcreteReader::isNext(Statement &statement1, Statement &statement2) const {
    return this->readerManager->isNext(statement1, statement2);
}

bool PkbConcreteReader::isNextStar(Statement &statement1, Statement &statement2) const {
    return this->readerManager->isNextStar(statement1, statement2);
}

bool PkbConcreteReader::hasNext() const { return this->readerManager->hasNext(); }

bool PkbConcreteReader::hasNextStar() const { return this->readerManager->hasNextStar(); }

bool PkbConcreteReader::hasBeforeStmt(Statement &statement) const {
    return this->readerManager->hasBeforeStmt(statement);
}

bool PkbConcreteReader::hasBeforeStarStmt(Statement &statement) const {
    return this->readerManager->hasBeforeStarStmt(statement);
}

bool PkbConcreteReader::hasAfterStmt(Statement &statement) const {
    return this->readerManager->hasAfterStmt(statement);
}

bool PkbConcreteReader::hasAfterStarStmt(Statement &statement) const {
    return this->readerManager->hasAfterStarStmt(statement);
}

std::unordered_set<Entity> PkbConcreteReader::getAllIfPatternStmts() const {
    return this->readerManager->getAllIfPatternStmts();
}

std::unordered_set<Entity> PkbConcreteReader::getIfStmtsByVar(Variable &var) const {
    return this->readerManager->getIfStmtsByVar(var);
};

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getAllIfStmtVarPair() const {
    return this->readerManager->getAllIfStmtVarPair();
}

std::unordered_set<Entity> PkbConcreteReader::getAllWhilePatternStmts() const {
    return this->readerManager->getAllWhilePatternStmts();
}

std::unordered_set<Entity> PkbConcreteReader::getWhileStmtsByVar(Variable &var) const {
    return this->readerManager->getWhileStmtsByVar(var);
}

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getAllWhileStmtVarPair() const {
    return this->readerManager->getAllWhileStmtVarPair();
}

std::unordered_set<std::vector<Entity>> PkbConcreteReader::getAffectsPair(StatementType formerType,
                                                                          StatementType latterType) const {
    return this->readerManager->getAffectsPair(formerType, latterType);
}

std::unordered_set<Entity> PkbConcreteReader::getAffectsTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getAffectsTypeStmt(type, statement);
}

std::unordered_set<Entity> PkbConcreteReader::getAffectsTypeWildcard(StatementType type) const {
    return this->readerManager->getAffectsTypeWildcard(type);
}

std::unordered_set<Entity> PkbConcreteReader::getAffectsStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getAffectsStmtType(statement, type);
}

std::unordered_set<Entity> PkbConcreteReader::getAffectsWildcardType(StatementType type) const {
    return this->readerManager->getAffectsWildcardType(type);
}

bool PkbConcreteReader::isAffects(Statement &statement1, Statement &statement2) const {
    return this->readerManager->isAffects(statement1, statement2);
}

bool PkbConcreteReader::hasAffects() const { return this->readerManager->hasAffects(); }

bool PkbConcreteReader::hasAffectedStmt(Statement &statement) const {
    return this->readerManager->hasAffectedStmt(statement);
}

bool PkbConcreteReader::hasAffectsStmt(Statement &statement) const {
    return this->readerManager->hasAffectsStmt(statement);
}