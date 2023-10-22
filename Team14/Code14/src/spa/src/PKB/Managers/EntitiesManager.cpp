#include "EntitiesManager.h"

EntitiesManager::EntitiesManager() {
    this->constantStore = std::make_shared<ConstantStore>();
    this->procedureStore = std::make_shared<ProcedureStore>();
    this->statementStore = std::make_shared<StatementStore>();
    this->variableStore = std::make_shared<VariableStore>();
}

template<typename E>
std::vector<Entity> EntitiesManager::getEntities(std::shared_ptr<EntityStore<E>> store,
                                                 std::function<bool(E &)> matcher) const {
    return ManagerUtils::getEntitiesFromEntityStore<E>(store, matcher, [](Entity &entity) { return entity; });
}

template<typename E>
std::vector<Entity> EntitiesManager::getAllEntities(std::shared_ptr<EntityStore<E>> store) const {
    return this->getEntities<E>(store, [](E &entity) { return true; });
}

void EntitiesManager::storeConstant(std::shared_ptr<Constant> c) { this->constantStore->storeEntity(c); }

void EntitiesManager::storeVariable(std::shared_ptr<Variable> v) { this->variableStore->storeEntity(v); }

void EntitiesManager::storeProcedure(std::shared_ptr<Procedure> p) { this->procedureStore->storeEntity(p); }

void EntitiesManager::storeStatement(std::shared_ptr<Statement> s) { this->statementStore->storeEntity(s); }

std::vector<Entity> EntitiesManager::getAllVariables() const {
    return this->getAllEntities<Variable>(this->variableStore);
}

std::vector<Entity> EntitiesManager::getAllConstants() const {
    return this->getAllEntities<Constant>(this->constantStore);
}

std::vector<Entity> EntitiesManager::getAllProcedures() const {
    return this->getAllEntities<Procedure>(this->procedureStore);
}

std::vector<Entity> EntitiesManager::getAllStatements() const {
    return this->getAllEntities<Statement>(this->statementStore);
}

std::vector<Entity> EntitiesManager::getAllRead() const {
    return this->getEntities<Statement>(
            this->statementStore, [](Statement &statement) { return statement.isStatementType(StatementType::Read); });
}

std::vector<Entity> EntitiesManager::getAllPrint() const {
    return this->getEntities<Statement>(
            this->statementStore, [](Statement &statement) { return statement.isStatementType(StatementType::Print); });
}

std::vector<Entity> EntitiesManager::getAllWhile() const {
    return this->getEntities<Statement>(
            this->statementStore, [](Statement &statement) { return statement.isStatementType(StatementType::While); });
}

std::vector<Entity> EntitiesManager::getAllIf() const {
    return this->getEntities<Statement>(
            this->statementStore, [](Statement &statement) { return statement.isStatementType(StatementType::If); });
}

std::vector<Entity> EntitiesManager::getAllCall() const {
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