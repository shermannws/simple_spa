#pragma once

#include "PkbWriterManager.h"

#include "PKB/Relationships/FollowsRelationship.h"
#include "PKB/Relationships/UsesRelationship.h"
#include "PKB/AssignmentPatternStore/Assignment.h"
#include "PKB/PkbWriter.h"

PkbWriterManager::PkbWriterManager(
        std::shared_ptr<AssignmentManager> assignmentManager,
        std::shared_ptr<ConstantStore> constantStore,
        std::shared_ptr<ProcedureStore> procedureStore,
        std::shared_ptr<StatementStore> statementStore,
        std::shared_ptr<VariableStore> variableStore,
        std::shared_ptr<FollowsRelationshipManager> followsRelationshipManager,
        std::shared_ptr<UsesRelationshipManager> usesRelationshipManager,
        std::shared_ptr<ModifiesRelationshipManager> modifiesRelationshipManager,
        std::shared_ptr<ParentRelationshipManager> parentRelationshipManager)
    : assignmentManager(assignmentManager),
    constantStore(constantStore),
    procedureStore(procedureStore),
    statementStore(statementStore),
    variableStore(variableStore),
    followsRelationshipManager(followsRelationshipManager),
    usesRelationshipManager(usesRelationshipManager),
    modifiesRelationshipManager(modifiesRelationshipManager),
    parentRelationshipManager(parentRelationshipManager) {}

void PkbWriterManager::addConstant(std::shared_ptr<Constant> c) {
    this->constantStore->storeEntity(c);
}

void PkbWriterManager::addVariable(std::shared_ptr<Variable> v) {
    this->variableStore->storeEntity(v);
}

void PkbWriterManager::addProcedure(std::shared_ptr<Procedure> p) {
    this->procedureStore->storeEntity(p);
}

void PkbWriterManager::addPrintStatement(std::shared_ptr<Statement> s) {
    this->statementStore->storeEntity(s);
}

void PkbWriterManager::addReadStatement(std::shared_ptr<Statement> s) {
    this->statementStore->storeEntity(s);
}

void PkbWriterManager::addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<std::string> rhs) {
    this->statementStore->storeEntity(s);

    std::shared_ptr<Assignment> assignStmt = std::make_shared<Assignment>(s, lhs, rhs);
    this->assignmentManager->addAssignment(assignStmt);
}

void PkbWriterManager::addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect) {
    this->followsRelationshipManager->storeFollowsRelationship(s1, s2, isDirect);
}

void PkbWriterManager::addUsesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) {
    this->usesRelationshipManager->storeUsesRelationship(s, v);
}