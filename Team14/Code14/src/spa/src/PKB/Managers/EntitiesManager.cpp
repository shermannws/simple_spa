#include "EntitiesManager.h"

EntitiesManager::EntitiesManager() {
    this->constantStore = std::make_shared<ConstantStore>();
    this->procedureStore = std::make_shared<ProcedureStore>();
    this->statementStore = std::make_shared<StatementStore>();
    this->variableStore = std::make_shared<VariableStore>();
}

template<typename E>
EntitySet EntitiesManager::getEntities(std::shared_ptr<EntityStore<E>> store,
                                       std::function<bool(std::shared_ptr<E>)> matcher) const {
    return ManagerUtils::getEntitiesFromEntityStore<E>(store, matcher, [](EntityPointer entity) { return entity; });
}

template<typename E>
EntitySet EntitiesManager::getAllEntities(std::shared_ptr<EntityStore<E>> store) const {
    return this->getEntities<E>(store, [](std::shared_ptr<E> entity) { return true; });
}

void EntitiesManager::storeConstant(std::shared_ptr<Constant> c) { this->constantStore->storeEntity(c); }

void EntitiesManager::storeVariable(std::shared_ptr<Variable> v) { this->variableStore->storeEntity(v); }

void EntitiesManager::storeProcedure(std::shared_ptr<Procedure> p) { this->procedureStore->storeEntity(p); }

void EntitiesManager::storeStatement(std::shared_ptr<Statement> s) { this->statementStore->storeEntity(s); }

EntitySet EntitiesManager::getAllVariables() const { return this->getAllEntities<Variable>(this->variableStore); }

EntitySet EntitiesManager::getAllConstants() const { return this->getAllEntities<Constant>(this->constantStore); }

EntitySet EntitiesManager::getAllProcedures() const { return this->getAllEntities<Procedure>(this->procedureStore); }

EntitySet EntitiesManager::getAllStatements() const { return this->getAllEntities<Statement>(this->statementStore); }

EntitySet EntitiesManager::getAllRead() const {
    return this->getEntities<Statement>(this->statementStore, [](std::shared_ptr<Statement> statement) {
        return statement->isStatementType(StatementType::Read);
    });
}

EntitySet EntitiesManager::getAllPrint() const {
    return this->getEntities<Statement>(this->statementStore, [](std::shared_ptr<Statement> statement) {
        return statement->isStatementType(StatementType::Print);
    });
}

EntitySet EntitiesManager::getAllWhile() const {
    return this->getEntities<Statement>(this->statementStore, [](std::shared_ptr<Statement> statement) {
        return statement->isStatementType(StatementType::While);
    });
}

EntitySet EntitiesManager::getAllIf() const {
    return this->getEntities<Statement>(this->statementStore, [](std::shared_ptr<Statement> statement) {
        return statement->isStatementType(StatementType::If);
    });
}

EntitySet EntitiesManager::getAllCall() const {
    return this->getEntities<Statement>(this->statementStore, [](std::shared_ptr<Statement> statement) {
        return statement->isStatementType(StatementType::Call);
    });
}

EntityPointer EntitiesManager::getStatement(std::shared_ptr<Statement> s) const {
    return this->statementStore->getEntity(s);
}

EntityPointer EntitiesManager::getVariable(std::shared_ptr<Variable> v) const {
    return this->variableStore->getEntity(v);
}

EntityPointer EntitiesManager::getConstant(std::shared_ptr<Constant> c) const {
    return this->constantStore->getEntity(c);
}

EntityPointer EntitiesManager::getProcedure(std::shared_ptr<Procedure> p) const {
    return this->procedureStore->getEntity(p);
}