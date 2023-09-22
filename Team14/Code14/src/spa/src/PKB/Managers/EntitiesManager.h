#pragma once

#include <memory>
#include <vector>
#include <algorithm>

#include "PKB/EntityStores/ConstantStore.h"
#include "PKB/EntityStores/ProcedureStore.h"
#include "PKB/EntityStores/StatementStore.h"
#include "PKB/EntityStores/VariableStore.h"
#include "PKB/Managers/ManagerUtils.h"

class EntitiesManager {
private:
    std::shared_ptr<ConstantStore> constantStore;
    std::shared_ptr<ProcedureStore> procedureStore;
    std::shared_ptr<StatementStore> statementStore;
    std::shared_ptr<VariableStore> variableStore;
protected:
    template <typename S, typename E>
    std::vector<Entity> getAllEntities(std::shared_ptr<S>) const;

    template <typename S, typename E>
    std::vector<Entity> getEntities(std::shared_ptr<S>, std::function<bool(E&)> matcher) const;
public:
    EntitiesManager();

    void storeConstant(std::shared_ptr<Constant> c);

    void storeVariable(std::shared_ptr<Variable> v);

    void storeProcedure(std::shared_ptr<Procedure> p);

    void storeStatement(std::shared_ptr<Statement> s);

    std::vector<Entity> getAllVariables() const;

    std::vector<Entity> getAllConstants() const;

    std::vector<Entity> getAllProcedures() const;

    std::vector<Entity> getAllStatements() const;

    std::vector<Entity> getAllRead() const;

    std::vector<Entity> getAllPrint() const;

    std::vector<Entity> getAllWhile() const;

    std::vector<Entity> getAllIf() const;

    std::shared_ptr<Entity> getStatement(std::shared_ptr<Statement> s) const;

    std::shared_ptr<Entity> getVariable(std::shared_ptr<Variable> v) const;

    std::shared_ptr<Entity> getConstant(std::shared_ptr<Constant> c) const;

    std::shared_ptr<Entity> getProcedure(std::shared_ptr<Procedure> p) const;
};