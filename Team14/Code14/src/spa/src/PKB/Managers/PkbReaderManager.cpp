#pragma once

#include "PkbReaderManager.h"

PkbReaderManager::PkbReaderManager(
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

template <typename T>
std::vector<Entity> PkbReaderManager::getAllEntities(const std::shared_ptr<EntityStore<T>>& store) const {
    return store->getAllEntities();
}

std::vector<Entity> PkbReaderManager::getAllVariables() const {
    return this->getAllEntities<Variable>(this->variableStore);
}

std::vector<Entity> PkbReaderManager::getAllConstants() const {
    return this->getAllEntities<Constant>(this->constantStore);
}

std::vector<Entity> PkbReaderManager::getAllProcedures() const {
    return this->getAllEntities<Procedure>(this->procedureStore);
}

std::vector<Entity> PkbReaderManager::getAllStatements() const {
    return this->getAllEntities<Statement>(this->statementStore);
}

std::vector<std::vector<Entity>> PkbReaderManager::getAllUsesAssignVariablePair() const {
    return this->usesRelationshipManager->getAllAssignVariable();
}

std::vector<Entity> PkbReaderManager::getAllUsesAssignByVariable(Variable& variable) const {
    return this->usesRelationshipManager->getVariableAssignment(variable);
}

std::vector<std::vector<Entity>> PkbReaderManager::getAllFollowsStatementPair() const {
    return this->followsRelationshipManager->getAllFollowsStatementPair();
}

std::vector<Entity> PkbReaderManager::getFollowsByStatement(Statement& statement) const {
    return this->followsRelationshipManager->getFollowsByStatement(statement);
}

std::vector<Entity> PkbReaderManager::getFollowingStatement(Statement& statement) const {
    return this->followsRelationshipManager->getFollowingStatement(statement);
}

bool PkbReaderManager::getIsFollows(Statement& statement1, Statement& statement2) const {
    return this->followsRelationshipManager->getIsFollows(statement1, statement2);
}


// Pattern queries i.e. pattern a (...,...)
// pattern a (_,_)
std::vector<Entity> PkbReaderManager::getAllAssign() const {
    return this->assignmentManager->getAllAssignStmts();
}

// pattern a (_, "x")
std::vector<Entity> PkbReaderManager::getAssignStmtsByRhs(std::string& rhs, bool hasRhsWildCard) const {
    return this->assignmentManager->getAssignStmtsByRhs(rhs, hasRhsWildCard);
}

// pattern a (v, _)
std::vector<std::vector<Entity>> PkbReaderManager::getAllAssignStmtVarPair() const {
    return this->assignmentManager->getAllAssignStmtVarPair();
}

// pattern a (v, "x")
std::vector<std::vector<Entity>> PkbReaderManager::getAssignStmtsVarPairByRhs(std::string& rhs, bool hasWildCard) const {
    return this->assignmentManager->getAssignStmtsVarPairByRhs(rhs, hasWildCard);
}

// pattern a ("x", _)
std::vector<Entity> PkbReaderManager::getAssignStmtsByLhs(Variable& lhs) const {
    return this->assignmentManager->getAssignStmtsByLhs(lhs);
}

// pattern a ("x", "x")
std::vector<Entity> PkbReaderManager::getAssignStmtsByLhsRhs(Variable& lhs, std::string& rhs, bool hasRhsWildCard) const {
    return this->assignmentManager->getAssignStmtsByLhsRhs(lhs, rhs, hasRhsWildCard);
}
