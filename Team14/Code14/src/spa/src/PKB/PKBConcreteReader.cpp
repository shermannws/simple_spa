#include "PkbConcreteReader.h"

PkbConcreteReader::PkbConcreteReader(std::shared_ptr<PkbReaderManager> readerManager) {
    this->readerManager = readerManager;
}

EntitySet PkbConcreteReader::getAllVariables() const { return this->readerManager->getAllVariables(); }

EntitySet PkbConcreteReader::getAllConstants() const { return this->readerManager->getAllConstants(); }

EntitySet PkbConcreteReader::getAllProcedures() const { return this->readerManager->getAllProcedures(); }

EntitySet PkbConcreteReader::getAllStatements() const { return this->readerManager->getAllStatements(); }

EntitySet PkbConcreteReader::getAllRead() const { return this->readerManager->getAllRead(); }

EntitySet PkbConcreteReader::getAllPrint() const { return this->readerManager->getAllPrint(); }

EntitySet PkbConcreteReader::getAllWhile() const { return this->readerManager->getAllWhile(); }

EntitySet PkbConcreteReader::getAllIf() const { return this->readerManager->getAllIf(); }

EntitySet PkbConcreteReader::getAllCall() const { return this->readerManager->getAllCall(); }

EntityPairSet PkbConcreteReader::getUsesStmtPair(StatementType type) const {
    return this->readerManager->getUsesStmtPair(type);
}

EntityPairSet PkbConcreteReader::getUsesProcPair() const { return this->readerManager->getUsesProcPair(); }

EntitySet PkbConcreteReader::getUsesTypeIdent(StatementType type, Variable &var) const {
    return this->readerManager->getUsesTypeIdent(type, var);
}

EntitySet PkbConcreteReader::getUsesProcIdent(Variable &var) const {
    return this->readerManager->getUsesProcIdent(var);
};

EntitySet PkbConcreteReader::getUsesStmt(StatementType type) const { return this->readerManager->getUsesStmt(type); }

EntitySet PkbConcreteReader::getUsesProc() const { return this->readerManager->getUsesProc(); }

EntitySet PkbConcreteReader::getUsesVar(Statement &stmt) const { return this->readerManager->getUsesVar(stmt); }

EntitySet PkbConcreteReader::getUsesVar(Procedure &proc) const { return this->readerManager->getUsesVar(proc); }

bool PkbConcreteReader::isStmtUsesVar(Statement &stmt, Variable &var) const {
    return this->readerManager->isStmtUsesVar(stmt, var);
}

bool PkbConcreteReader::isProcUsesVar(Procedure &proc, Variable &var) const {
    return this->readerManager->isProcUsesVar(proc, var);
}

bool PkbConcreteReader::hasUses(Statement &stmt) const { return this->readerManager->hasUses(stmt); }

bool PkbConcreteReader::hasUses(Procedure &proc) const { return this->readerManager->hasUses(proc); }

EntityPairSet PkbConcreteReader::getFollowsPair(StatementType formerType, StatementType latterType) const {
    return this->readerManager->getFollowsPair(formerType, latterType);
}

EntityPairSet PkbConcreteReader::getFollowsStarPair(StatementType formerType, StatementType latterType) const {
    return this->readerManager->getFollowsStarPair(formerType, latterType);
}

EntitySet PkbConcreteReader::getFollowsTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getFollowsTypeStmt(type, statement);
}

EntitySet PkbConcreteReader::getFollowsStarTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getFollowsStarTypeStmt(type, statement);
}

EntitySet PkbConcreteReader::getFollowsTypeWildcard(StatementType type) const {
    return this->readerManager->getFollowsTypeWildcard(type);
}

EntitySet PkbConcreteReader::getFollowsStarTypeWildcard(StatementType type) const {
    return this->readerManager->getFollowsStarTypeWildcard(type);
}

EntitySet PkbConcreteReader::getFollowsStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getFollowsStmtType(statement, type);
}

EntitySet PkbConcreteReader::getFollowsStarStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getFollowsStarStmtType(statement, type);
}

EntitySet PkbConcreteReader::getFollowsWildcardType(StatementType type) const {
    return this->readerManager->getFollowsWildcardType(type);
}

EntitySet PkbConcreteReader::getFollowsStarWildcardType(StatementType type) const {
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

EntityPairSet PkbConcreteReader::getModifiesStmtPair(StatementType type) const {
    return this->readerManager->getModifiesStmtPair(type);
}

EntityPairSet PkbConcreteReader::getModifiesProcPair() const { return this->readerManager->getModifiesProcPair(); }

EntitySet PkbConcreteReader::getModifiesTypeIdent(StatementType type, Variable &var) const {
    return this->readerManager->getModifiesTypeIdent(type, var);
}

EntitySet PkbConcreteReader::getModifiesProcIdent(Variable &var) const {
    return this->readerManager->getModifiesProcIdent(var);
}

EntitySet PkbConcreteReader::getModifiesStmt(StatementType type) const {
    return this->readerManager->getModifiesStmt(type);
}

EntitySet PkbConcreteReader::getModifiesProc() const { return this->readerManager->getModifiesProc(); }

EntitySet PkbConcreteReader::getModifiesVar(Statement &stmt) const { return this->readerManager->getModifiesVar(stmt); }

EntitySet PkbConcreteReader::getModifiesVar(Procedure &proc) const { return this->readerManager->getModifiesVar(proc); }

bool PkbConcreteReader::isStmtModifiesVar(Statement &stmt, Variable &var) const {
    return this->readerManager->isStmtModifiesVar(stmt, var);
}

bool PkbConcreteReader::isProcModifiesVar(Procedure &proc, Variable &var) const {
    return this->readerManager->isProcModifiesVar(proc, var);
}

bool PkbConcreteReader::hasModifies(Statement &stmt) const { return this->readerManager->hasModifies(stmt); }

bool PkbConcreteReader::hasModifies(Procedure &proc) const { return this->readerManager->hasModifies(proc); }

// pattern a (_,_)
EntitySet PkbConcreteReader::getAllAssign() const { return this->readerManager->getAllAssign(); }

// pattern a (_, "x")
EntitySet PkbConcreteReader::getAssignStmtsByRhs(Expression &rhs, bool hasRhsWildCard) const {
    return this->readerManager->getAssignStmtsByRhs(rhs, hasRhsWildCard);
}

// pattern a (v, _)
EntityPairSet PkbConcreteReader::getAllAssignStmtVarPair() const {
    return this->readerManager->getAllAssignStmtVarPair();
}

// pattern a (v, "x")
EntityPairSet PkbConcreteReader::getAssignStmtsVarPairByRhs(Expression &rhs, bool hasWildCard) const {
    return this->readerManager->getAssignStmtsVarPairByRhs(rhs, hasWildCard);
}

// pattern a ("x", _)
EntitySet PkbConcreteReader::getAssignStmtsByLhs(Variable &lhs) const {
    return this->readerManager->getAssignStmtsByLhs(lhs);
}

// pattern a ("x", "x")
EntitySet PkbConcreteReader::getAssignStmtsByLhsRhs(Variable &lhs, Expression &rhs, bool hasRhsWildCard) const {
    return this->readerManager->getAssignStmtsByLhsRhs(lhs, rhs, hasRhsWildCard);
}

EntityPairSet PkbConcreteReader::getParentPair(StatementType formerType, StatementType latterType) const {
    return this->readerManager->getParentPair(formerType, latterType);
}

EntityPairSet PkbConcreteReader::getParentStarPair(StatementType formerType, StatementType latterType) const {
    return this->readerManager->getParentStarPair(formerType, latterType);
}

EntitySet PkbConcreteReader::getParentTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getParentTypeStmt(type, statement);
}

EntitySet PkbConcreteReader::getParentStarTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getParentStarTypeStmt(type, statement);
}

EntitySet PkbConcreteReader::getParentTypeWildcard(StatementType type) const {
    return this->readerManager->getParentTypeWildcard(type);
}

EntitySet PkbConcreteReader::getParentStarTypeWildcard(StatementType type) const {
    return this->readerManager->getParentStarTypeWildcard(type);
}

EntitySet PkbConcreteReader::getParentStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getParentStmtType(statement, type);
}

EntitySet PkbConcreteReader::getParentStarStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getParentStarStmtType(statement, type);
}

EntitySet PkbConcreteReader::getParentWildcardType(StatementType type) const {
    return this->readerManager->getParentWildcardType(type);
}

EntitySet PkbConcreteReader::getParentStarWildcardType(StatementType type) const {
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

EntitySet PkbConcreteReader::getCallees() const { return this->readerManager->getCallees(); }

EntitySet PkbConcreteReader::getCalleesStar() const { return this->readerManager->getCalleesStar(); }

EntitySet PkbConcreteReader::getCallers() const { return this->readerManager->getCallers(); }

EntitySet PkbConcreteReader::getCallersStar() const { return this->readerManager->getCallersStar(); }

EntityPairSet PkbConcreteReader::getCallsPair() const { return this->readerManager->getCallsPair(); }

EntityPairSet PkbConcreteReader::getCallsStarPair() const { return this->readerManager->getCallsStarPair(); }

EntitySet PkbConcreteReader::getCallers(Procedure &callee) const { return this->readerManager->getCallers(callee); }

EntitySet PkbConcreteReader::getCallersStar(Procedure &callee) const {
    return this->readerManager->getCallersStar(callee);
}

EntitySet PkbConcreteReader::getCallees(Procedure &caller) const { return this->readerManager->getCallees(caller); }

EntitySet PkbConcreteReader::getCalleesStar(Procedure &caller) const {
    return this->readerManager->getCalleesStar(caller);
}

EntityPairSet PkbConcreteReader::getNextPair(StatementType formerType, StatementType latterType) const {
    return this->readerManager->getNextPair(formerType, latterType);
}

EntityPairSet PkbConcreteReader::getNextStarPair(StatementType formerType, StatementType latterType) const {
    return this->readerManager->getNextStarPair(formerType, latterType);
}

EntitySet PkbConcreteReader::getNextStarSameStmt(StatementType stmtType) const {
    return this->readerManager->getNextStarSameStmt(stmtType);
}

EntitySet PkbConcreteReader::getNextTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getNextTypeStmt(type, statement);
}

EntitySet PkbConcreteReader::getNextStarTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getNextStarTypeStmt(type, statement);
}

EntitySet PkbConcreteReader::getNextTypeWildcard(StatementType type) const {
    return this->readerManager->getNextTypeWildcard(type);
}

EntitySet PkbConcreteReader::getNextStarTypeWildcard(StatementType type) const {
    return this->readerManager->getNextStarTypeWildcard(type);
}

EntitySet PkbConcreteReader::getNextStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getNextStmtType(statement, type);
}

EntitySet PkbConcreteReader::getNextStarStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getNextStarStmtType(statement, type);
}

EntitySet PkbConcreteReader::getNextWildcardType(StatementType type) const {
    return this->readerManager->getNextWildcardType(type);
}

EntitySet PkbConcreteReader::getNextStarWildcardType(StatementType type) const {
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

EntitySet PkbConcreteReader::getAllIfPatternStmts() const { return this->readerManager->getAllIfPatternStmts(); }

EntitySet PkbConcreteReader::getIfStmtsByVar(Variable &var) const { return this->readerManager->getIfStmtsByVar(var); };

EntityPairSet PkbConcreteReader::getAllIfStmtVarPair() const { return this->readerManager->getAllIfStmtVarPair(); }

EntitySet PkbConcreteReader::getAllWhilePatternStmts() const { return this->readerManager->getAllWhilePatternStmts(); }

EntitySet PkbConcreteReader::getWhileStmtsByVar(Variable &var) const {
    return this->readerManager->getWhileStmtsByVar(var);
}

EntityPairSet PkbConcreteReader::getAllWhileStmtVarPair() const {
    return this->readerManager->getAllWhileStmtVarPair();
}

EntityPairSet PkbConcreteReader::getAffectsPair(StatementType formerType, StatementType latterType) const {
    return this->readerManager->getAffectsPair(formerType, latterType);
}

EntitySet PkbConcreteReader::getAffectsSameStmt(StatementType stmtType) const {
    return this->readerManager->getAffectsSameStmt(stmtType);
}

EntitySet PkbConcreteReader::getAffectsTypeStmt(StatementType type, Statement &statement) const {
    return this->readerManager->getAffectsTypeStmt(type, statement);
}

EntitySet PkbConcreteReader::getAffectsTypeWildcard(StatementType type) const {
    return this->readerManager->getAffectsTypeWildcard(type);
}

EntitySet PkbConcreteReader::getAffectsStmtType(Statement &statement, StatementType type) const {
    return this->readerManager->getAffectsStmtType(statement, type);
}

EntitySet PkbConcreteReader::getAffectsWildcardType(StatementType type) const {
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