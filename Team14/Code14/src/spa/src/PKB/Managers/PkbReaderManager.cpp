#include "PkbReaderManager.h"

PkbReaderManager::PkbReaderManager(
    std::shared_ptr<AssignmentManager> assignmentManager,
    std::shared_ptr<EntitiesManager> entityManager,
    std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
    std::shared_ptr<UsesRelationshipManager> usesRelationshipManager,
    std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager,
    std::shared_ptr<ParentRelationshipManager> parentRelationshipManager,
    std::shared_ptr<CallsRelationshipManager> callsRelationshipManager,
    std::shared_ptr<ModifiesProcRelationshipManager> modifiesProcRelationshipManager,
    std::shared_ptr<UsesProcRelationshipManager> usesProcRelationshipManager)
    : assignmentManager(assignmentManager),
    entityManager(entityManager),
    followsRelationshipManager(followsRelationshipManager),
    usesRelationshipManager(usesRelationshipManager),
    modifiesRelationshipManager(modifiesRelationshipManager),
    parentRelationshipManager(parentRelationshipManager),
    callsRelationshipManager(callsRelationshipManager),
    modifiesProcRelationshipManager(modifiesProcRelationshipManager),
    usesProcRelationshipManager(usesProcRelationshipManager) {};

std::vector<Entity> PkbReaderManager::getAllVariables() const {
    return this->entityManager->getAllVariables();
}

std::vector<Entity> PkbReaderManager::getAllConstants() const {
    return this->entityManager->getAllConstants();
}

std::vector<Entity> PkbReaderManager::getAllProcedures() const {
    return this->entityManager->getAllProcedures();
}

std::vector<Entity> PkbReaderManager::getAllStatements() const {
    return this->entityManager->getAllStatements();
}

std::vector<Entity> PkbReaderManager::getAllRead() const {
    return this->entityManager->getAllRead();
}

std::vector<Entity> PkbReaderManager::getAllPrint() const {
    return this->entityManager->getAllPrint();
}

std::vector<Entity> PkbReaderManager::getAllWhile() const {
    return this->entityManager->getAllWhile();
}

std::vector<Entity> PkbReaderManager::getAllIf() const {
    return this->entityManager->getAllIf();
}

std::vector<Entity> PkbReaderManager::getAllCall() const {
    return this->entityManager->getAllCall();
}

std::vector<std::vector<Entity>> PkbReaderManager::getUsesStmtPair(StatementType type) const {
    return this->usesRelationshipManager->getUsesStmtPair(type);
}

std::vector<std::vector<Entity>> PkbReaderManager::getUsesProcPair() const {
    return this->usesProcRelationshipManager->getUsesProcPair();
}

std::vector<Entity> PkbReaderManager::getUsesTypeIdent(StatementType type, Variable& var) const {
    return this->usesRelationshipManager->getUsesTypeIdent(type, var);
}

std::vector<Entity> PkbReaderManager::getUsesProcIdent(Variable& var) const {
    return this->usesProcRelationshipManager->getUsesProcIdent(var);
}

std::vector<Entity> PkbReaderManager::getUsesStmt(StatementType type) const {
    return this->usesRelationshipManager->getUsesStmt(type);
}

std::vector<Entity> PkbReaderManager::getUsesProc() const {
    return this->usesProcRelationshipManager->getUsesProc();
}

std::vector<Entity> PkbReaderManager::getUsesVar(Statement& stmt) const {
    return this->usesRelationshipManager->getUsesVar(stmt);
}

std::vector<Entity> PkbReaderManager::getUsesVar(Procedure& proc) const {
    return this->usesProcRelationshipManager->getUsesProcVar(proc);
}

bool PkbReaderManager::isStmtUsesVar(Statement& stmt, Variable& var) const {
    return this->usesRelationshipManager->isStmtUsesVar(stmt, var);
}

bool PkbReaderManager::isProcUsesVar(Procedure& proc, Variable& var) const {
    return this->usesProcRelationshipManager->isProcUsesVar(proc, var);
}

bool PkbReaderManager::hasUses(Statement& stmt) const {
    return this->usesRelationshipManager->hasUses(stmt);
}

bool PkbReaderManager::hasUses(Procedure& proc) const {
    return this->usesProcRelationshipManager->hasProcUses(proc);
}

std::vector<std::vector<Entity>> PkbReaderManager::getFollowsPair(StatementType formerType, StatementType latterType) const {
    return this->followsRelationshipManager->getRelationshipPair(formerType, latterType, true);
}

std::vector<std::vector<Entity>> PkbReaderManager::getFollowsStarPair(StatementType formerType, StatementType latterType) const {
    return this->followsRelationshipManager->getRelationshipPair(formerType, latterType, false);
}

std::vector<Entity> PkbReaderManager::getFollowsTypeStmt(StatementType type, Statement& statement) const {
    return this->followsRelationshipManager->getRelationshipTypeStmt(type, statement, true);
}

std::vector<Entity> PkbReaderManager::getFollowsStarTypeStmt(StatementType type, Statement& statement) const {
    return this->followsRelationshipManager->getRelationshipTypeStmt(type, statement, false);
}

std::vector<Entity> PkbReaderManager::getFollowsTypeWildcard(StatementType type) const {
    return this->followsRelationshipManager->getRelationshipTypeWildcard(type);
}

std::vector<Entity> PkbReaderManager::getFollowsStarTypeWildcard(StatementType type) const {
    return this->followsRelationshipManager->getRelationshipTypeWildcard(type);
}

std::vector<Entity> PkbReaderManager::getFollowsStmtType(Statement& statement, StatementType type) const {
    return this->followsRelationshipManager->getRelationshipStmtType(statement, type, true);
}

std::vector<Entity> PkbReaderManager::getFollowsStarStmtType(Statement& statement, StatementType type) const {
    return this->followsRelationshipManager->getRelationshipStmtType(statement, type, false);
}

std::vector<Entity> PkbReaderManager::getFollowsWildcardType(StatementType type) const {
    return this->followsRelationshipManager->getRelationshipWildcardType(type);
}

std::vector<Entity> PkbReaderManager::getFollowsStarWildcardType(StatementType type) const {
    return this->followsRelationshipManager->getRelationshipWildcardType(type);
}

bool PkbReaderManager::isFollows(Statement& statement1, Statement& statement2) const {
    return this->followsRelationshipManager->isRelationship(statement1, statement2, true);
}

bool PkbReaderManager::isFollowsStar(Statement& statement1, Statement& statement2) const {
    return this->followsRelationshipManager->isRelationship(statement1, statement2, false);
}

bool PkbReaderManager::hasFollows() const {
    return this->followsRelationshipManager->hasRelationship();
}

bool PkbReaderManager::hasFollowsStar() const {
    return this->followsRelationshipManager->hasRelationship();
}

bool PkbReaderManager::hasLatterStmt(Statement& statement) const {
    return this->followsRelationshipManager->isFormer(statement);
}

bool PkbReaderManager::hasFormerStmt(Statement& statement) const {
    return this->followsRelationshipManager->isLatter(statement);
}

bool PkbReaderManager::hasLatterStarStmt(Statement& statement) const {
    return this->followsRelationshipManager->isFormer(statement);
}

bool PkbReaderManager::hasFormerStarStmt(Statement& statement) const {
    return this->followsRelationshipManager->isLatter(statement);
}

std::vector<std::vector<Entity>> PkbReaderManager::getModifiesStmtPair(StatementType type) const {
    return this->modifiesRelationshipManager->getRelationshipStmtPair(type);
}

std::vector<std::vector<Entity>> PkbReaderManager::getModifiesProcPair() const {
    return this->modifiesProcRelationshipManager->getRelationshipProcPair();
}

std::vector<Entity> PkbReaderManager::getModifiesTypeIdent(StatementType type, Variable& var) const {
    return this->modifiesRelationshipManager->getRelationshipTypeIdent(type, var);
}

std::vector<Entity> PkbReaderManager::getModifiesProcIdent(Variable& var) const {
    return this->modifiesProcRelationshipManager->getRelationshipIdent(var);
}

std::vector<Entity> PkbReaderManager::getModifiesStmt(StatementType type) const {
    return this->modifiesRelationshipManager->getRelationshipStmt(type);
}

std::vector<Entity> PkbReaderManager::getModifiesProc() const {
    return this->modifiesProcRelationshipManager->getRelationshipProc();
}

std::vector<Entity> PkbReaderManager::getModifiesVar(Statement& stmt) const {
    return this->modifiesRelationshipManager->getRelationshipVar(stmt);
}

std::vector<Entity> PkbReaderManager::getModifiesVar(Procedure& proc) const {
    return this->modifiesProcRelationshipManager->getRelationshipVar(proc);
}

bool PkbReaderManager::isStmtModifiesVar(Statement& stmt, Variable& var) const {
    return this->modifiesRelationshipManager->isRelationship(stmt, var);
}

bool PkbReaderManager::isProcModifiesVar(Procedure& proc, Variable& var) const {
    return this->modifiesProcRelationshipManager->isRelationship(proc, var);
}

bool PkbReaderManager::hasModifies(Statement& stmt) const {
    return this->modifiesRelationshipManager->hasRelationship(stmt);
}

bool PkbReaderManager::hasModifies(Procedure& proc) const {
    return this->modifiesProcRelationshipManager->hasRelationship(proc);
}

// Pattern queries i.e. pattern a (...,...)
// pattern a (_,_)
std::vector<Entity> PkbReaderManager::getAllAssign() const {
    return this->assignmentManager->getAllAssignStmts();
}

// pattern a (_, "x")
std::vector<Entity> PkbReaderManager::getAssignStmtsByRhs(Expression& rhs, bool hasRhsWildCard) const {
    return this->assignmentManager->getAssignStmtsByRhs(rhs, hasRhsWildCard);
}

// pattern a (v, _)
std::vector<std::vector<Entity>> PkbReaderManager::getAllAssignStmtVarPair() const {
    return this->assignmentManager->getAllAssignStmtVarPair();
}

// pattern a (v, "x")
std::vector<std::vector<Entity>> PkbReaderManager::getAssignStmtsVarPairByRhs(Expression& rhs, bool hasWildCard) const {
    return this->assignmentManager->getAssignStmtsVarPairByRhs(rhs, hasWildCard);
}

// pattern a ("x", _)
std::vector<Entity> PkbReaderManager::getAssignStmtsByLhs(Variable& lhs) const {
    return this->assignmentManager->getAssignStmtsByLhs(lhs);
}

// pattern a ("x", "x")
std::vector<Entity> PkbReaderManager::getAssignStmtsByLhsRhs(Variable& lhs, Expression& rhs, bool hasRhsWildCard) const {
    return this->assignmentManager->getAssignStmtsByLhsRhs(lhs, rhs, hasRhsWildCard);
}

std::vector<std::vector<Entity>> PkbReaderManager::getParentPair(StatementType formerType, StatementType latterType) const {
    return this->parentRelationshipManager->getRelationshipPair(formerType, latterType, true);
}

std::vector<std::vector<Entity>> PkbReaderManager::getParentStarPair(StatementType formerType, StatementType latterType) const {
    return this->parentRelationshipManager->getRelationshipPair(formerType, latterType, false);
}

std::vector<Entity> PkbReaderManager::getParentTypeStmt(StatementType type, Statement& statement) const {
    return this->parentRelationshipManager->getRelationshipTypeStmt(type, statement, true);
}

std::vector<Entity> PkbReaderManager::getParentStarTypeStmt(StatementType type, Statement& statement) const {
    return this->parentRelationshipManager->getRelationshipTypeStmt(type, statement, false);
}

std::vector<Entity> PkbReaderManager::getParentTypeWildcard(StatementType type) const {
    return this->parentRelationshipManager->getRelationshipTypeWildcard(type);
}

std::vector<Entity> PkbReaderManager::getParentStarTypeWildcard(StatementType type) const {
    return this->parentRelationshipManager->getRelationshipTypeWildcard(type);
}

std::vector<Entity> PkbReaderManager::getParentStmtType(Statement& statement, StatementType type) const {
    return this->parentRelationshipManager->getRelationshipStmtType(statement, type, true);
}

std::vector<Entity> PkbReaderManager::getParentStarStmtType(Statement& statement, StatementType type) const {
    return this->parentRelationshipManager->getRelationshipStmtType(statement, type, false);
}

std::vector<Entity> PkbReaderManager::getParentWildcardType(StatementType type) const {
    return this->parentRelationshipManager->getRelationshipWildcardType(type);
}

std::vector<Entity> PkbReaderManager::getParentStarWildcardType(StatementType type) const {
    return this->parentRelationshipManager->getRelationshipWildcardType(type);
}

bool PkbReaderManager::isParent(Statement& statement1, Statement& statement2) const {
    return this->parentRelationshipManager->isRelationship(statement1, statement2, true);
}

bool PkbReaderManager::isParentStar(Statement& statement1, Statement& statement2) const {
    return this->parentRelationshipManager->isRelationship(statement1, statement2, false);
}

bool PkbReaderManager::hasParent() const {
    return this->parentRelationshipManager->hasRelationship();
}

bool PkbReaderManager::hasParentStar() const {
    return this->parentRelationshipManager->hasRelationship();
}

bool PkbReaderManager::hasChildStmt(Statement& statement) const {
    return this->parentRelationshipManager->isFormer(statement);
}

bool PkbReaderManager::hasChildStarStmt(Statement& statement) const {
    return this->parentRelationshipManager->isFormer(statement);
}

bool PkbReaderManager::hasParentStmt(Statement& statement) const {
    return this->parentRelationshipManager->isLatter(statement);
}

bool PkbReaderManager::hasParentStarStmt(Statement& statement) const {
    return this->parentRelationshipManager->isLatter(statement);
}

bool PkbReaderManager::hasCalls() const {
    return this->callsRelationshipManager->hasRelationship();
}

bool PkbReaderManager::hasCallsStar() const {
    return this->callsRelationshipManager->hasRelationship();
}

bool PkbReaderManager::isCallee(Procedure& proc) const {
    return this->callsRelationshipManager->isLatter(proc);
}

bool PkbReaderManager::isCalleeStar(Procedure& proc) const {
    return this->callsRelationshipManager->isLatter(proc);
}

bool PkbReaderManager::isCaller(Procedure& proc) const {
    return this->callsRelationshipManager->isFormer(proc);
}

bool PkbReaderManager::isCallerStar(Procedure& proc) const {
    return this->callsRelationshipManager->isFormer(proc);
}

bool PkbReaderManager::isCalls(Procedure& caller, Procedure& callee) const {
    return this->callsRelationshipManager->isRelationship(caller, callee, true);
}

bool PkbReaderManager::isCallsStar(Procedure& caller, Procedure& callee) const {
    return this->callsRelationshipManager->isRelationship(caller, callee, false);
}

std::vector<Entity> PkbReaderManager::getCallees() const {
    return this->callsRelationshipManager->getRelationshipLatter();
}

std::vector<Entity> PkbReaderManager::getCalleesStar() const {
    return this->callsRelationshipManager->getRelationshipLatter();
}

std::vector<Entity> PkbReaderManager::getCallers() const {
    return this->callsRelationshipManager->getRelationshipFormer();
}

std::vector<Entity> PkbReaderManager::getCallersStar() const {
    return this->callsRelationshipManager->getRelationshipFormer();
}

std::vector<std::vector<Entity>> PkbReaderManager::getCallsPair() const {
    return this->callsRelationshipManager->getRelationshipPair(true);
}

std::vector<std::vector<Entity>> PkbReaderManager::getCallsStarPair() const {
    return this->callsRelationshipManager->getRelationshipPair(false);
}

std::vector<Entity> PkbReaderManager::getCallers(Procedure& callee) const {
    return this->callsRelationshipManager->getRelationshipFormer(callee, true);
}

std::vector<Entity> PkbReaderManager::getCallersStar(Procedure& callee) const {
    return this->callsRelationshipManager->getRelationshipFormer(callee, false);
}

std::vector<Entity> PkbReaderManager::getCallees(Procedure& caller) const {
    return this->callsRelationshipManager->getRelationshipLatter(caller, true);
}

std::vector<Entity> PkbReaderManager::getCalleesStar(Procedure& caller) const {
    return this->callsRelationshipManager->getRelationshipLatter(caller, false);
}

std::vector<std::vector<Entity>> PkbReaderManager::getNextPair(StatementType formerType, StatementType latterType) const {
    // TODO: Implement this
    return std::vector<std::vector<Entity>>();
}

std::vector<std::vector<Entity>> PkbReaderManager::getNextStarPair(StatementType formerType, StatementType latterType) const {
    // TODO: Implement this
    return std::vector<std::vector<Entity>>();
}

std::vector<Entity> PkbReaderManager::getNextTypeStmt(StatementType type, Statement& statement) const {
    // TODO: Implement this
    return std::vector<Entity>();
}

std::vector<Entity> PkbReaderManager::getNextStarTypeStmt(StatementType type, Statement& statement) const {
    // TODO: Implement this
    return std::vector<Entity>();
}

std::vector<Entity> PkbReaderManager::getNextTypeWildcard(StatementType type) const {
    // TODO: Implement this
    return std::vector<Entity>();
}

std::vector<Entity> PkbReaderManager::getNextStarTypeWildcard(StatementType type) const {
    // TODO: Implement this
    return std::vector<Entity>();
}

std::vector<Entity> PkbReaderManager::getNextStmtType(Statement& statement, StatementType type) const {
    // TODO: Implement this
    return std::vector<Entity>();
}

std::vector<Entity> PkbReaderManager::getNextStarStmtType(Statement& statement, StatementType type) const {
    // TODO: Implement this
    return std::vector<Entity>();
}

std::vector<Entity> PkbReaderManager::getNextWildcardType(StatementType type) const {
    // TODO: Implement this
    return std::vector<Entity>();
}

std::vector<Entity> PkbReaderManager::getNextStarWildcardType(StatementType type) const {
    // TODO: Implement this
    return std::vector<Entity>();
}

bool PkbReaderManager::isNext(Statement& statement1, Statement& statement2) const {
    // TODO: Implement this
    return false;
}

bool PkbReaderManager::isNextStar(Statement& statement1, Statement& statement2) const {
    // TODO: Implement this
    return false;
}

bool PkbReaderManager::hasNext() const {
    // TODO: Implement this
    return false;
}

bool PkbReaderManager::hasNextStar() const {
    // TODO: Implement this
    return false;
}

bool PkbReaderManager::hasBeforeStmt(Statement& statement) const {
    // TODO: Implement this
    return false;
}

bool PkbReaderManager::hasBeforeStarStmt(Statement& statement) const {
    // TODO: Implement this
    return false;
}

bool PkbReaderManager::hasAfterStmt(Statement& statement) const {
    // TODO: Implement this
    return false;
}

bool PkbReaderManager::hasAfterStarStmt(Statement& statement) const {
    // TODO: Implement this
    return false;
}