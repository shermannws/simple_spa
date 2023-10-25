#include "EntitiesManager.h"

EntitiesManager::EntitiesManager() {
    this->constantStore = std::make_shared<ConstantStore>();
    this->procedureStore = std::make_shared<ProcedureStore>();
    this->statementStore = std::make_shared<StatementStore>();
    this->variableStore = std::make_shared<VariableStore>();
}

template<typename E>
std::unordered_set<Entity> EntitiesManager::getEntities(std::shared_ptr<EntityStore<E>> store,
                                                        std::function<bool(E &)> matcher) const {
    return ManagerUtils::getEntitiesFromEntityStore<E>(store, matcher, [](Entity &entity) { return entity; });
}

template<typename E>
std::unordered_set<Entity> EntitiesManager::getAllEntities(std::shared_ptr<EntityStore<E>> store) const {
    return this->getEntities<E>(store, [](E &entity) { return true; });
}

void EntitiesManager::storeConstant(std::shared_ptr<Constant> c) { this->constantStore->storeEntity(c); }

void EntitiesManager::storeVariable(std::shared_ptr<Variable> v) { this->variableStore->storeEntity(v); }

void EntitiesManager::storeProcedure(std::shared_ptr<Procedure> p) { this->procedureStore->storeEntity(p); }

void EntitiesManager::storeStatement(std::shared_ptr<Statement> s) { this->statementStore->storeEntity(s); }

std::unordered_set<Entity> EntitiesManager::getAllVariables() const {
    return this->getAllEntities<Variable>(this->variableStore);
}

std::unordered_set<Entity> EntitiesManager::getAllConstants() const {
    return this->getAllEntities<Constant>(this->constantStore);
}

std::unordered_set<Entity> EntitiesManager::getAllProcedures() const {
    return this->getAllEntities<Procedure>(this->procedureStore);
}

std::unordered_set<Entity> EntitiesManager::getAllStatements() const {
    return this->getAllEntities<Statement>(this->statementStore);
}

std::unordered_set<Entity> EntitiesManager::getAllRead() const {
    return this->getEntities<Statement>(
            this->statementStore, [](Statement &statement) { return statement.isStatementType(StatementType::Read); });
}

std::unordered_set<Entity> EntitiesManager::getAllPrint() const {
    return this->getEntities<Statement>(
            this->statementStore, [](Statement &statement) { return statement.isStatementType(StatementType::Print); });
}

std::unordered_set<Entity> EntitiesManager::getAllWhile() const {
    return this->getEntities<Statement>(
            this->statementStore, [](Statement &statement) { return statement.isStatementType(StatementType::While); });
}

std::unordered_set<Entity> EntitiesManager::getAllIf() const {
    return this->getEntities<Statement>(
            this->statementStore, [](Statement &statement) { return statement.isStatementType(StatementType::If); });
}

std::unordered_set<Entity> EntitiesManager::getAllCall() const {
    return this->getEntities<Statement>(
            this->statementStore, [](Statement &statement) { return statement.isStatementType(StatementType::Call); });
}

std::shared_ptr<Entity> EntitiesManager::getStatement(std::shared_ptr<Statement> s) const {
    return this->statementStore->getEntity(s);
}

std::shared_ptr<Entity> EntitiesManager::getVariable(std::shared_ptr<Variable> v) const {
    return this->variableStore->getEntity(v);
}

std::shared_ptr<Entity> EntitiesManager::getConstant(std::shared_ptr<Constant> c) const {
    return this->constantStore->getEntity(c);
}

std::shared_ptr<Entity> EntitiesManager::getProcedure(std::shared_ptr<Procedure> p) const {
    return this->procedureStore->getEntity(p);
}