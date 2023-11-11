#pragma once

#include <functional>

#include "PKB/EntityStores/ConstantStore.h"
#include "PKB/EntityStores/ProcedureStore.h"
#include "PKB/EntityStores/StatementStore.h"
#include "PKB/EntityStores/VariableStore.h"
#include "PKB/Managers/ManagerUtils.h"

/**
 * @brief A class that manages all the entities in the SIMPLE source program
 * @details A class that manages all the entities in the SIMPLE source program
 */
class EntitiesManager {
private:
    /**
     * @brief The ConstantStore that stores all the constants in the SIMPLE source program
     */
    std::shared_ptr<ConstantStore> constantStore;

    /**
     * @brief The ProcedureStore that stores all the procedures in the SIMPLE source program
     */
    std::shared_ptr<ProcedureStore> procedureStore;

    /**
     * @brief The StatementStore that stores all the statements in the SIMPLE source program
     */
    std::shared_ptr<StatementStore> statementStore;

    /**
     * @brief The VariableStore that stores all the variables in the SIMPLE source program
     */
    std::shared_ptr<VariableStore> variableStore;

protected:
    /**
     * @brief Returns all the entities of type E in the EntityStore of type E
     * @tparam E The type of the Entity
     * @param entityStore The EntityStore to retrieve the entities from
     * @return An unordered_set of entities of type E
     */
    template<typename E>
    EntitySet getAllEntities(std::shared_ptr<EntityStore<E>>) const;

    /**
     * @brief Returns all the entities of type E in the EntityStore of type E that matches the matcher function
     * @tparam E The type of the Entity
     * @param entityStore The EntityStore to retrieve the entities from
     * @param matcher The matcher function to match the entities against
     * @return An unordered_set of entities of type E
     */
    template<typename E>
    EntitySet getEntities(std::shared_ptr<EntityStore<E>>, std::function<bool(std::shared_ptr<E>)> matcher) const;

public:
    /**
     * @brief Construct a new EntitiesManager object
     * @return A new EntitiesManager object
     */
    EntitiesManager();

    /**
     * @brief Adds a Constant object to the ConstantStore
     * @param c The Constant object to be added
     * @return None
     */
    void storeConstant(std::shared_ptr<Constant> c);

    /**
     * @brief Adds a Variable object to the VariableStore
     * @param v The Variable object to be added
     * @return None
     */
    void storeVariable(std::shared_ptr<Variable> v);

    /**
     * @brief Adds a Procedure object to the ProcedureStore
     * @param p The Procedure object to be added
     * @return None
     */
    void storeProcedure(std::shared_ptr<Procedure> p);

    /**
     * @brief Adds a Statement object to the StatementStore
     * @param s The Statement object to be added
     * @return None
     */
    void storeStatement(std::shared_ptr<Statement> s);

    /**
     * @brief Returns all the variables in the SIMPLE source program
     * @return An unordered_set of variables
     */
    EntitySet getAllVariables() const;

    /**
     * @brief Returns all the constants in the SIMPLE source program
     * @return An unordered_set of constants
     */
    EntitySet getAllConstants() const;

    /**
     * @brief Returns all the procedures in the SIMPLE source program
     * @return An unordered_set of procedures
     */
    EntitySet getAllProcedures() const;

    /**
     * @brief Returns all the statements in the SIMPLE source program
     * @return An unordered_set of statements
     */
    EntitySet getAllStatements() const;

    /**
     * @brief Returns all the read statements in the SIMPLE source program
     * @return An unordered_set of read statements
     */
    EntitySet getAllRead() const;

    /**
     * @brief Returns all the print statements in the SIMPLE source program
     * @return An unordered_set of print statements
     */
    EntitySet getAllPrint() const;

    /**
     * @brief Returns all the call statements in the SIMPLE source program
     * @return An unordered_set of call statements
     */
    EntitySet getAllWhile() const;

    /**
     * @brief Returns all the if statements in the SIMPLE source program
     * @return An unordered_set of if statements
     */
    EntitySet getAllIf() const;

    /**
     * @brief Returns all the call statements in the SIMPLE source program
     * @return An unordered_set of call statements
     */
    EntitySet getAllCall() const;

    /**
     * @brief Returns the Statement object from the StatementStore that is equal to the Statement object passed in
     * @param s The Statement object to be compared against
     * @return The Statement object from the StatementStore that is equal to the Statement object passed in
     */
    EntityPointer getStatement(std::shared_ptr<Statement> s) const;

    /**
     * @brief Returns the Variable object from the VariableStore that is equal to the Variable object passed in
     * @param v The Variable object to be compared against
     * @return The Variable object from the VariableStore that is equal to the Variable object passed in
     */
    EntityPointer getVariable(std::shared_ptr<Variable> v) const;

    /**
     * @brief Returns the Constant object from the ConstantStore that is equal to the Constant object passed in
     * @param c The Constant object to be compared against
     * @return The Constant object from the ConstantStore that is equal to the Constant object passed in
     */
    EntityPointer getConstant(std::shared_ptr<Constant> c) const;

    /**
     * @brief Returns the Procedure object from the ProcedureStore that is equal to the Procedure object passed in
     * @param p The Procedure object to be compared against
     * @return The Procedure object from the ProcedureStore that is equal to the Procedure object passed in
     */
    EntityPointer getProcedure(std::shared_ptr<Procedure> p) const;
};