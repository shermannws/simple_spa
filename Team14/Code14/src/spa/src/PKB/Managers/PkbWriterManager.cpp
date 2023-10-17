#include "PkbWriterManager.h"

#include "PKB/Managers/ManagerUtils.h"
#include "PKB/PkbWriter.h"

PkbWriterManager::PkbWriterManager(std::shared_ptr<AssignPatternManager> assignmentManager,
                                   std::shared_ptr<EntitiesManager> entitiesManager,
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
                                   std::shared_ptr<CFGManager> cfgManager)
    : assignmentManager(assignmentManager), entitiesManager(entitiesManager),
      followsRelationshipManager(followsRelationshipManager), usesRelationshipManager(usesRelationshipManager),
      modifiesRelationshipManager(modifiesRelationshipManager), parentRelationshipManager(parentRelationshipManager),
      callsRelationshipManager(callsRelationshipManager),
      modifiesProcRelationshipManager(modifiesProcRelationshipManager),
      usesProcRelationshipManager(usesProcRelationshipManager), ifPatternManager(ifPatternManager),
      whilePatternManager(whilePatternManager), nextRelationshipManager(nextRelationshipManager),
      cfgManager(cfgManager) {}

void PkbWriterManager::addConstant(std::shared_ptr<Constant> c) { this->entitiesManager->storeConstant(c); }

void PkbWriterManager::addVariable(std::shared_ptr<Variable> v) { this->entitiesManager->storeVariable(v); }

void PkbWriterManager::addProcedure(std::shared_ptr<Procedure> p) { this->entitiesManager->storeProcedure(p); }

void PkbWriterManager::addStatement(std::shared_ptr<Statement> s) { this->entitiesManager->storeStatement(s); }

void PkbWriterManager::addAssignPattern(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs,
                                        std::shared_ptr<Expression> rhs) {
    std::shared_ptr<Assignment> assignStmt = std::make_shared<Assignment>(s, lhs, rhs);
    this->assignmentManager->storeAssignPattern(assignStmt);
}

void PkbWriterManager::addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2,
                                              bool isDirect) {
    this->followsRelationshipManager->storeRelationship(s1, s2, isDirect);
}

void PkbWriterManager::addUsesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) {
    this->usesRelationshipManager->storeRelationship(s, v);
}

void PkbWriterManager::addModifiesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) {
    this->modifiesRelationshipManager->storeRelationship(s, v);
}

void PkbWriterManager::addParentRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2,
                                             bool isDirect) {
    this->parentRelationshipManager->storeRelationship(s1, s2, isDirect);
}

void PkbWriterManager::addCallsRelationship(std::shared_ptr<Procedure> p1, std::shared_ptr<Procedure> p2) {
    this->callsRelationshipManager->storeRelationship(p1, p2, true);
}

void PkbWriterManager::addModifiesProcRelationship(std::shared_ptr<Procedure> p, std::shared_ptr<Variable> v) {
    this->modifiesProcRelationshipManager->storeRelationship(p, v);
}

void PkbWriterManager::addUsesProcRelationship(std::shared_ptr<Procedure> p, std::shared_ptr<Variable> v) {
    this->usesProcRelationshipManager->storeRelationship(p, v);
}

void PkbWriterManager::triggerCallsTransitiveCalculation() {
    this->callsRelationshipManager->calculateTransitiveRelationship();
}

void PkbWriterManager::addProcedureToStatementsMap(std::shared_ptr<Procedure> p,
                                                   std::vector<std::shared_ptr<Statement>> s) {
    for (auto stmt: s) { this->tempProcedureToStatementsMap.storeRelationship(p, stmt); }
}

void PkbWriterManager::addIfPattern(std::shared_ptr<Statement> s,
                                    std::shared_ptr<std::vector<std::shared_ptr<Variable>>> v) {
    this->ifPatternManager->storeIfPattern(s, v);
}

void PkbWriterManager::addWhilePattern(std::shared_ptr<Statement> s,
                                       std::shared_ptr<std::vector<std::shared_ptr<Variable>>> v) {
    this->whilePatternManager->storeWhilePattern(s, v);
}

void PkbWriterManager::triggerProcToVarTransitiveCalculation() {
    this->modifiesProcRelationshipManager->calculateProcVarRelationshipForCallers(this->callsRelationshipManager);
    this->usesProcRelationshipManager->calculateProcVarRelationshipForCallers(this->callsRelationshipManager);
}

void PkbWriterManager::triggerStmtToVarTransitiveCalculation() {
    ManagerUtils::addStmtVarFromProcVar(
            this->modifiesRelationshipManager,
            std::make_shared<RelationshipStore<Procedure, Statement>>(this->tempProcedureToStatementsMap),
            this->modifiesProcRelationshipManager);
    ManagerUtils::addStmtVarFromProcVar(
            this->usesRelationshipManager,
            std::make_shared<RelationshipStore<Procedure, Statement>>(this->tempProcedureToStatementsMap),
            this->usesProcRelationshipManager);
    this->tempProcedureToStatementsMap.clear();
}

void PkbWriterManager::triggerTransitiveCalc() {
    // The order of these 3 calls are important, as each transitivity calculation depends on the previous one
    triggerCallsTransitiveCalculation();
    triggerProcToVarTransitiveCalculation();
    triggerStmtToVarTransitiveCalculation();
}

void PkbWriterManager::addNextRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2) {
    this->nextRelationshipManager->storeRelationship(s1, s2, true);
}

void PkbWriterManager::setCFGMap(std::unordered_map<ProcedureName, std::shared_ptr<CFGNode>> cfgMap) {
    this->cfgManager->setCFG(cfgMap);
}

void PkbWriterManager::clearCache() { this->nextRelationshipManager->clearNextStarStore(); }