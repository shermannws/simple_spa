#include "PkbWriterManager.h"

#include "PKB/PkbWriter.h"

PkbWriterManager::PkbWriterManager(
        std::shared_ptr<AssignmentManager> assignmentManager,
        std::shared_ptr<EntitiesManager> entitiesManager,
        std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
        std::shared_ptr<UsesRelationshipManager> usesRelationshipManager,
        std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager,
        std::shared_ptr<ParentRelationshipManager> parentRelationshipManager,
        std::shared_ptr<CallsRelationshipManager> callsRelationshipManager,
        std::shared_ptr<ModifiesProcRelationshipManager> modifiesProcRelationshipManager,
        std::shared_ptr<UsesProcRelationshipManager> usesProcRelationshipManager)
    : assignmentManager(assignmentManager),
    entitiesManager(entitiesManager),
    followsRelationshipManager(followsRelationshipManager),
    usesRelationshipManager(usesRelationshipManager),
    modifiesRelationshipManager(modifiesRelationshipManager),
    parentRelationshipManager(parentRelationshipManager),
    callsRelationshipManager(callsRelationshipManager),
    modifiesProcRelationshipManager(modifiesProcRelationshipManager),
    usesProcRelationshipManager(usesProcRelationshipManager) {}

void PkbWriterManager::addConstant(std::shared_ptr<Constant> c) {
    this->entitiesManager->storeConstant(c);
}

void PkbWriterManager::addVariable(std::shared_ptr<Variable> v) {
    this->entitiesManager->storeVariable(v);
}

void PkbWriterManager::addProcedure(std::shared_ptr<Procedure> p) {
    this->entitiesManager->storeProcedure(p);
}

void PkbWriterManager::addStatement(std::shared_ptr<Statement> s) {
    this->entitiesManager->storeStatement(s);
}

void PkbWriterManager::addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<Expression> rhs) {
    this->entitiesManager->storeStatement(s);

    std::shared_ptr<Assignment> assignStmt = std::make_shared<Assignment>(s, lhs, rhs);
    this->assignmentManager->addAssignment(assignStmt);
}

void PkbWriterManager::addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect) {
    this->followsRelationshipManager->storeRelationship(s1, s2, isDirect);
}

void PkbWriterManager::addUsesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) {
    this->usesRelationshipManager->storeRelationship(s, v);
}

void PkbWriterManager::addModifiesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) {
    this->modifiesRelationshipManager->storeRelationship(s, v);
}

void PkbWriterManager::addParentRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect) {
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