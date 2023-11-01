#include "PkbReaderManager.h"

PkbReaderManager::PkbReaderManager(std::shared_ptr<AssignPatternManager> assignmentManager,
                                   std::shared_ptr<EntitiesManager> entityManager,
                                   std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
                                   std::shared_ptr<UsesRelationshipManager> usesRelationshipManager,
                                   std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager,
                                   std::shared_ptr<ParentRelationshipManager> parentRelationshipManager,
                                   std::shared_ptr<CallsRelationshipManager> callsRelationshipManager,
                                   std::shared_ptr<ModifiesProcRelationshipManager> modifiesProcRelationshipManager,
                                   std::shared_ptr<UsesProcRelationshipManager> usesProcRelationshipManager,
                                   std::shared_ptr<IfPatternManager> ifPatternManager,
                                   std::shared_ptr<WhilePatternManager> whilePatternManager,
                                   std::shared_ptr<NextRelationshipManager> nextRelationshipManager,
                                   std::shared_ptr<AffectsRelationshipManager> affectsRelationshipManager)
    : assignmentManager(assignmentManager), entityManager(entityManager),
      followsRelationshipManager(followsRelationshipManager), usesRelationshipManager(usesRelationshipManager),
      modifiesRelationshipManager(modifiesRelationshipManager), parentRelationshipManager(parentRelationshipManager),
      callsRelationshipManager(callsRelationshipManager),
      modifiesProcRelationshipManager(modifiesProcRelationshipManager),
      usesProcRelationshipManager(usesProcRelationshipManager), ifPatternManager(ifPatternManager),
      whilePatternManager(whilePatternManager), nextRelationshipManager(nextRelationshipManager),
      affectsRelationshipManager(affectsRelationshipManager){};

EntitySet PkbReaderManager::getAllVariables() const { return this->entityManager->getAllVariables(); }

EntitySet PkbReaderManager::getAllConstants() const { return this->entityManager->getAllConstants(); }

EntitySet PkbReaderManager::getAllProcedures() const { return this->entityManager->getAllProcedures(); }

EntitySet PkbReaderManager::getAllStatements() const { return this->entityManager->getAllStatements(); }

EntitySet PkbReaderManager::getAllRead() const { return this->entityManager->getAllRead(); }

EntitySet PkbReaderManager::getAllPrint() const { return this->entityManager->getAllPrint(); }

EntitySet PkbReaderManager::getAllWhile() const { return this->entityManager->getAllWhile(); }

EntitySet PkbReaderManager::getAllIf() const { return this->entityManager->getAllIf(); }

EntitySet PkbReaderManager::getAllCall() const { return this->entityManager->getAllCall(); }

EntityPairSet PkbReaderManager::getUsesStmtPair(StatementType type) const {
    return this->usesRelationshipManager->getRelationshipStmtPair(type);
}

EntityPairSet PkbReaderManager::getUsesProcPair() const {
    return this->usesProcRelationshipManager->getRelationshipProcPair();
}

EntitySet PkbReaderManager::getUsesTypeIdent(StatementType type, Variable &var) const {
    return this->usesRelationshipManager->getRelationshipTypeIdent(type, var);
}

EntitySet PkbReaderManager::getUsesProcIdent(Variable &var) const {
    return this->usesProcRelationshipManager->getRelationshipIdent(var);
}

EntitySet PkbReaderManager::getUsesStmt(StatementType type) const {
    return this->usesRelationshipManager->getRelationshipStmt(type);
}

EntitySet PkbReaderManager::getUsesProc() const { return this->usesProcRelationshipManager->getRelationshipProc(); }

EntitySet PkbReaderManager::getUsesVar(Statement &stmt) const {
    return this->usesRelationshipManager->getRelationshipVar(stmt);
}

EntitySet PkbReaderManager::getUsesVar(Procedure &proc) const {
    return this->usesProcRelationshipManager->getRelationshipVar(proc);
}

bool PkbReaderManager::isStmtUsesVar(Statement &stmt, Variable &var) const {
    return this->usesRelationshipManager->isRelationship(stmt, var);
}

bool PkbReaderManager::isProcUsesVar(Procedure &proc, Variable &var) const {
    return this->usesProcRelationshipManager->isRelationship(proc, var);
}

bool PkbReaderManager::hasUses(Statement &stmt) const { return this->usesRelationshipManager->hasRelationship(stmt); }

bool PkbReaderManager::hasUses(Procedure &proc) const {
    return this->usesProcRelationshipManager->hasRelationship(proc);
}

EntityPairSet PkbReaderManager::getFollowsPair(StatementType formerType, StatementType latterType) const {
    return this->followsRelationshipManager->getRelationshipPair(formerType, latterType, true);
}

EntityPairSet PkbReaderManager::getFollowsStarPair(StatementType formerType, StatementType latterType) const {
    return this->followsRelationshipManager->getRelationshipPair(formerType, latterType, false);
}

EntitySet PkbReaderManager::getFollowsTypeStmt(StatementType type, Statement &statement) const {
    return this->followsRelationshipManager->getRelationshipTypeStmt(type, statement, true);
}

EntitySet PkbReaderManager::getFollowsStarTypeStmt(StatementType type, Statement &statement) const {
    return this->followsRelationshipManager->getRelationshipTypeStmt(type, statement, false);
}

EntitySet PkbReaderManager::getFollowsTypeWildcard(StatementType type) const {
    return this->followsRelationshipManager->getRelationshipTypeWildcard(type);
}

EntitySet PkbReaderManager::getFollowsStarTypeWildcard(StatementType type) const {
    return this->followsRelationshipManager->getRelationshipTypeWildcard(type);
}

EntitySet PkbReaderManager::getFollowsStmtType(Statement &statement, StatementType type) const {
    return this->followsRelationshipManager->getRelationshipStmtType(statement, type, true);
}

EntitySet PkbReaderManager::getFollowsStarStmtType(Statement &statement, StatementType type) const {
    return this->followsRelationshipManager->getRelationshipStmtType(statement, type, false);
}

EntitySet PkbReaderManager::getFollowsWildcardType(StatementType type) const {
    return this->followsRelationshipManager->getRelationshipWildcardType(type);
}

EntitySet PkbReaderManager::getFollowsStarWildcardType(StatementType type) const {
    return this->followsRelationshipManager->getRelationshipWildcardType(type);
}

bool PkbReaderManager::isFollows(Statement &statement1, Statement &statement2) const {
    return this->followsRelationshipManager->isRelationship(statement1, statement2, true);
}

bool PkbReaderManager::isFollowsStar(Statement &statement1, Statement &statement2) const {
    return this->followsRelationshipManager->isRelationship(statement1, statement2, false);
}

bool PkbReaderManager::hasFollows() const { return this->followsRelationshipManager->hasRelationship(); }

bool PkbReaderManager::hasFollowsStar() const { return this->followsRelationshipManager->hasRelationship(); }

bool PkbReaderManager::hasLatterStmt(Statement &statement) const {
    return this->followsRelationshipManager->isFormer(statement);
}

bool PkbReaderManager::hasFormerStmt(Statement &statement) const {
    return this->followsRelationshipManager->isLatter(statement);
}

bool PkbReaderManager::hasLatterStarStmt(Statement &statement) const {
    return this->followsRelationshipManager->isFormer(statement);
}

bool PkbReaderManager::hasFormerStarStmt(Statement &statement) const {
    return this->followsRelationshipManager->isLatter(statement);
}

EntityPairSet PkbReaderManager::getModifiesStmtPair(StatementType type) const {
    return this->modifiesRelationshipManager->getRelationshipStmtPair(type);
}

EntityPairSet PkbReaderManager::getModifiesProcPair() const {
    return this->modifiesProcRelationshipManager->getRelationshipProcPair();
}

EntitySet PkbReaderManager::getModifiesTypeIdent(StatementType type, Variable &var) const {
    return this->modifiesRelationshipManager->getRelationshipTypeIdent(type, var);
}

EntitySet PkbReaderManager::getModifiesProcIdent(Variable &var) const {
    return this->modifiesProcRelationshipManager->getRelationshipIdent(var);
}

EntitySet PkbReaderManager::getModifiesStmt(StatementType type) const {
    return this->modifiesRelationshipManager->getRelationshipStmt(type);
}

EntitySet PkbReaderManager::getModifiesProc() const {
    return this->modifiesProcRelationshipManager->getRelationshipProc();
}

EntitySet PkbReaderManager::getModifiesVar(Statement &stmt) const {
    return this->modifiesRelationshipManager->getRelationshipVar(stmt);
}

EntitySet PkbReaderManager::getModifiesVar(Procedure &proc) const {
    return this->modifiesProcRelationshipManager->getRelationshipVar(proc);
}

bool PkbReaderManager::isStmtModifiesVar(Statement &stmt, Variable &var) const {
    return this->modifiesRelationshipManager->isRelationship(stmt, var);
}

bool PkbReaderManager::isProcModifiesVar(Procedure &proc, Variable &var) const {
    return this->modifiesProcRelationshipManager->isRelationship(proc, var);
}

bool PkbReaderManager::hasModifies(Statement &stmt) const {
    return this->modifiesRelationshipManager->hasRelationship(stmt);
}

bool PkbReaderManager::hasModifies(Procedure &proc) const {
    return this->modifiesProcRelationshipManager->hasRelationship(proc);
}

// Pattern queries i.e. pattern a (...,...)
// pattern a (_,_)
EntitySet PkbReaderManager::getAllAssign() const { return this->assignmentManager->getAllAssignStmts(); }

// pattern a (_, "x")
EntitySet PkbReaderManager::getAssignStmtsByRhs(Expression &rhs, bool hasRhsWildCard) const {
    return this->assignmentManager->getAssignStmtsByRhs(rhs, hasRhsWildCard);
}

// pattern a (v, _)
EntityPairSet PkbReaderManager::getAllAssignStmtVarPair() const {
    return this->assignmentManager->getAllAssignStmtVarPair();
}

// pattern a (v, "x")
EntityPairSet PkbReaderManager::getAssignStmtsVarPairByRhs(Expression &rhs, bool hasWildCard) const {
    return this->assignmentManager->getAssignStmtsVarPairByRhs(rhs, hasWildCard);
}

// pattern a ("x", _)
EntitySet PkbReaderManager::getAssignStmtsByLhs(Variable &lhs) const {
    return this->assignmentManager->getAssignStmtsByLhs(lhs);
}

// pattern a ("x", "x")
EntitySet PkbReaderManager::getAssignStmtsByLhsRhs(Variable &lhs, Expression &rhs, bool hasRhsWildCard) const {
    return this->assignmentManager->getAssignStmtsByLhsRhs(lhs, rhs, hasRhsWildCard);
}

EntityPairSet PkbReaderManager::getParentPair(StatementType formerType, StatementType latterType) const {
    return this->parentRelationshipManager->getRelationshipPair(formerType, latterType, true);
}

EntityPairSet PkbReaderManager::getParentStarPair(StatementType formerType, StatementType latterType) const {
    return this->parentRelationshipManager->getRelationshipPair(formerType, latterType, false);
}

EntitySet PkbReaderManager::getParentTypeStmt(StatementType type, Statement &statement) const {
    return this->parentRelationshipManager->getRelationshipTypeStmt(type, statement, true);
}

EntitySet PkbReaderManager::getParentStarTypeStmt(StatementType type, Statement &statement) const {
    return this->parentRelationshipManager->getRelationshipTypeStmt(type, statement, false);
}

EntitySet PkbReaderManager::getParentTypeWildcard(StatementType type) const {
    return this->parentRelationshipManager->getRelationshipTypeWildcard(type);
}

EntitySet PkbReaderManager::getParentStarTypeWildcard(StatementType type) const {
    return this->parentRelationshipManager->getRelationshipTypeWildcard(type);
}

EntitySet PkbReaderManager::getParentStmtType(Statement &statement, StatementType type) const {
    return this->parentRelationshipManager->getRelationshipStmtType(statement, type, true);
}

EntitySet PkbReaderManager::getParentStarStmtType(Statement &statement, StatementType type) const {
    return this->parentRelationshipManager->getRelationshipStmtType(statement, type, false);
}

EntitySet PkbReaderManager::getParentWildcardType(StatementType type) const {
    return this->parentRelationshipManager->getRelationshipWildcardType(type);
}

EntitySet PkbReaderManager::getParentStarWildcardType(StatementType type) const {
    return this->parentRelationshipManager->getRelationshipWildcardType(type);
}

bool PkbReaderManager::isParent(Statement &statement1, Statement &statement2) const {
    return this->parentRelationshipManager->isRelationship(statement1, statement2, true);
}

bool PkbReaderManager::isParentStar(Statement &statement1, Statement &statement2) const {
    return this->parentRelationshipManager->isRelationship(statement1, statement2, false);
}

bool PkbReaderManager::hasParent() const { return this->parentRelationshipManager->hasRelationship(); }

bool PkbReaderManager::hasParentStar() const { return this->parentRelationshipManager->hasRelationship(); }

bool PkbReaderManager::hasChildStmt(Statement &statement) const {
    return this->parentRelationshipManager->isFormer(statement);
}

bool PkbReaderManager::hasChildStarStmt(Statement &statement) const {
    return this->parentRelationshipManager->isFormer(statement);
}

bool PkbReaderManager::hasParentStmt(Statement &statement) const {
    return this->parentRelationshipManager->isLatter(statement);
}

bool PkbReaderManager::hasParentStarStmt(Statement &statement) const {
    return this->parentRelationshipManager->isLatter(statement);
}

bool PkbReaderManager::hasCalls() const { return this->callsRelationshipManager->hasRelationship(); }

bool PkbReaderManager::hasCallsStar() const { return this->callsRelationshipManager->hasRelationship(); }

bool PkbReaderManager::isCallee(Procedure &proc) const { return this->callsRelationshipManager->isLatter(proc); }

bool PkbReaderManager::isCalleeStar(Procedure &proc) const { return this->callsRelationshipManager->isLatter(proc); }

bool PkbReaderManager::isCaller(Procedure &proc) const { return this->callsRelationshipManager->isFormer(proc); }

bool PkbReaderManager::isCallerStar(Procedure &proc) const { return this->callsRelationshipManager->isFormer(proc); }

bool PkbReaderManager::isCalls(Procedure &caller, Procedure &callee) const {
    return this->callsRelationshipManager->isRelationship(caller, callee, true);
}

bool PkbReaderManager::isCallsStar(Procedure &caller, Procedure &callee) const {
    return this->callsRelationshipManager->isRelationship(caller, callee, false);
}

EntitySet PkbReaderManager::getCallees() const { return this->callsRelationshipManager->getRelationshipLatter(); }

EntitySet PkbReaderManager::getCalleesStar() const { return this->callsRelationshipManager->getRelationshipLatter(); }

EntitySet PkbReaderManager::getCallers() const { return this->callsRelationshipManager->getRelationshipFormer(); }

EntitySet PkbReaderManager::getCallersStar() const { return this->callsRelationshipManager->getRelationshipFormer(); }

EntityPairSet PkbReaderManager::getCallsPair() const {
    return this->callsRelationshipManager->getRelationshipPair(true);
}

EntityPairSet PkbReaderManager::getCallsStarPair() const {
    return this->callsRelationshipManager->getRelationshipPair(false);
}

EntitySet PkbReaderManager::getCallers(Procedure &callee) const {
    return this->callsRelationshipManager->getRelationshipFormer(callee, true);
}

EntitySet PkbReaderManager::getCallersStar(Procedure &callee) const {
    return this->callsRelationshipManager->getRelationshipFormer(callee, false);
}

EntitySet PkbReaderManager::getCallees(Procedure &caller) const {
    return this->callsRelationshipManager->getRelationshipLatter(caller, true);
}

EntitySet PkbReaderManager::getCalleesStar(Procedure &caller) const {
    return this->callsRelationshipManager->getRelationshipLatter(caller, false);
}

EntityPairSet PkbReaderManager::getNextPair(StatementType formerType, StatementType latterType) const {
    return this->nextRelationshipManager->getRelationshipPair(formerType, latterType, true);
}

EntityPairSet PkbReaderManager::getNextStarPair(StatementType formerType, StatementType latterType) const {
    return this->nextRelationshipManager->getRelationshipPair(formerType, latterType, false);
}

EntitySet PkbReaderManager::getNextStarSameStmt(StatementType stmtType) const {
    return this->nextRelationshipManager->getNextStarSameStmt(stmtType);
}

EntitySet PkbReaderManager::getNextTypeStmt(StatementType type, Statement &statement) const {
    return this->nextRelationshipManager->getRelationshipTypeStmt(type, statement, true);
}

EntitySet PkbReaderManager::getNextStarTypeStmt(StatementType type, Statement &statement) const {
    return this->nextRelationshipManager->getRelationshipTypeStmt(type, statement, false);
}

EntitySet PkbReaderManager::getNextTypeWildcard(StatementType type) const {
    return this->nextRelationshipManager->getRelationshipTypeWildcard(type, true);
}

EntitySet PkbReaderManager::getNextStarTypeWildcard(StatementType type) const {
    return this->nextRelationshipManager->getRelationshipTypeWildcard(type, false);
}

EntitySet PkbReaderManager::getNextStmtType(Statement &statement, StatementType type) const {
    return this->nextRelationshipManager->getRelationshipStmtType(statement, type, true);
}

EntitySet PkbReaderManager::getNextStarStmtType(Statement &statement, StatementType type) const {
    return this->nextRelationshipManager->getRelationshipStmtType(statement, type, false);
}

EntitySet PkbReaderManager::getNextWildcardType(StatementType type) const {
    return this->nextRelationshipManager->getRelationshipWildcardType(type, true);
}

EntitySet PkbReaderManager::getNextStarWildcardType(StatementType type) const {
    return this->nextRelationshipManager->getRelationshipWildcardType(type, false);
}

bool PkbReaderManager::isNext(Statement &statement1, Statement &statement2) const {
    return this->nextRelationshipManager->isRelationship(statement1, statement2, true);
}

bool PkbReaderManager::isNextStar(Statement &statement1, Statement &statement2) const {
    return this->nextRelationshipManager->isRelationship(statement1, statement2, false);
}

bool PkbReaderManager::hasNext() const { return this->nextRelationshipManager->hasRelationship(); }

bool PkbReaderManager::hasNextStar() const { return this->nextRelationshipManager->hasRelationship(); }

bool PkbReaderManager::hasBeforeStmt(Statement &statement) const {
    return this->nextRelationshipManager->isLatter(statement);
}

bool PkbReaderManager::hasBeforeStarStmt(Statement &statement) const {
    return this->nextRelationshipManager->isLatter(statement);
}

bool PkbReaderManager::hasAfterStmt(Statement &statement) const {
    return this->nextRelationshipManager->isFormer(statement);
}

bool PkbReaderManager::hasAfterStarStmt(Statement &statement) const {
    return this->nextRelationshipManager->isFormer(statement);
}

EntitySet PkbReaderManager::getAllIfPatternStmts() const { return this->ifPatternManager->getAllStmts(); }

EntitySet PkbReaderManager::getIfStmtsByVar(Variable &var) const { return this->ifPatternManager->getStmtsByVar(var); };

EntityPairSet PkbReaderManager::getAllIfStmtVarPair() const { return this->ifPatternManager->getAllStmtVarPair(); }

EntitySet PkbReaderManager::getAllWhilePatternStmts() const { return this->whilePatternManager->getAllStmts(); }

EntitySet PkbReaderManager::getWhileStmtsByVar(Variable &var) const {
    return this->whilePatternManager->getStmtsByVar(var);
}

EntityPairSet PkbReaderManager::getAllWhileStmtVarPair() const {
    return this->whilePatternManager->getAllStmtVarPair();
}

void PkbReaderManager::triggerAffectsCalculation() const {
    if (this->affectsRelationshipManager->hasAffectsBeenCalculated()) { return; }
    this->affectsRelationshipManager->calculateAffects(
            assignmentManager->getAllAssignStmtsAsStmts(),
            [this](std::shared_ptr<Statement> stmt) { return modifiesRelationshipManager->getModifiedVar(stmt); },
            [this](Statement &stmt, Variable &var) { return usesRelationshipManager->isRelationship(stmt, var); },
            [this](Statement &stmt, Variable &var) { return modifiesRelationshipManager->isRelationship(stmt, var); },
            [this](std::shared_ptr<Statement> stmt) { return nextRelationshipManager->getAllNextOfStmt(stmt); });
}

EntityPairSet PkbReaderManager::getAffectsPair(StatementType formerType, StatementType latterType) const {
    if (!ManagerUtils::isStmtTypeAllowed(affectsRelationshipManager->clauseGroup, latterType)) {
        return EntityPairSet();
    }
    this->triggerAffectsCalculation();
    return this->affectsRelationshipManager->getRelationshipPair(formerType, latterType, true);
}

EntitySet PkbReaderManager::getAffectsSameStmt(StatementType stmtType) const {
    if (!ManagerUtils::isStmtTypeAllowed(affectsRelationshipManager->clauseGroup, stmtType)) { return EntitySet(); }
    this->triggerAffectsCalculation();
    return this->affectsRelationshipManager->getAffectsSameStmt(stmtType);
}

EntitySet PkbReaderManager::getAffectsTypeStmt(StatementType type, Statement &statement) const {
    this->triggerAffectsCalculation();
    return this->affectsRelationshipManager->getRelationshipTypeStmt(type, statement, true);
}

EntitySet PkbReaderManager::getAffectsTypeWildcard(StatementType type) const {
    this->triggerAffectsCalculation();
    return this->affectsRelationshipManager->getRelationshipTypeWildcard(type);
}

EntitySet PkbReaderManager::getAffectsStmtType(Statement &statement, StatementType type) const {
    if (!ManagerUtils::isStmtTypeAllowed(affectsRelationshipManager->clauseGroup, type)) { return EntitySet(); }
    this->triggerAffectsCalculation();
    return this->affectsRelationshipManager->getRelationshipStmtType(statement, type, true);
}

EntitySet PkbReaderManager::getAffectsWildcardType(StatementType type) const {
    if (!ManagerUtils::isStmtTypeAllowed(affectsRelationshipManager->clauseGroup, type)) { return EntitySet(); }
    this->triggerAffectsCalculation();
    return this->affectsRelationshipManager->getRelationshipWildcardType(type);
}

bool PkbReaderManager::isAffects(Statement &statement1, Statement &statement2) const {
    this->triggerAffectsCalculation();
    return this->affectsRelationshipManager->isRelationship(statement1, statement2, true);
}

bool PkbReaderManager::hasAffects() const {
    this->triggerAffectsCalculation();
    return this->affectsRelationshipManager->hasRelationship();
}

bool PkbReaderManager::hasAffectedStmt(Statement &statement) const {
    this->triggerAffectsCalculation();
    return this->affectsRelationshipManager->isFormer(statement);
}

bool PkbReaderManager::hasAffectsStmt(Statement &statement) const {
    this->triggerAffectsCalculation();
    return this->affectsRelationshipManager->isLatter(statement);
}