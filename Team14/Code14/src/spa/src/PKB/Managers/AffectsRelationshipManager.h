#pragma once

#include <stack>

#include "PKB/Commons/Assignment.h"
#include "PKB/Commons/ClauseGroup.h"
#include "PKB/Managers/StmtToStmtRelationshipManager.h"
#include "PKB/RelationshipStores/AffectsRelationshipStore.h"

/**
 * @class AffectsRelationshipManager is responsible for storing and retrieving the Affects relationship
 * @brief Manages the Affects relationship
 * @note: A Affects relationship is a relationship between two assign statements where the first statement affects the
 * second statement
 */
class AffectsRelationshipManager : public StmtToStmtRelationshipManager<AffectsRelationshipStore> {
private:
    /**
     * Boolean flag to indicate if Affects relationship has been calculated
     */
    bool mutable isAffectsCalculated;

public:
    /**
     * @brief Constructs a AffectsRelationshipManager object
     * @return A AffectsRelationshipManager object
     */
    AffectsRelationshipManager();

    bool hasAffectsBeenCalculated() const;

    /**
     * @brief Calculates the Affects relationship
     */
    void
    calculateAffects(const std::unordered_set<std::shared_ptr<Statement>> &assignStmts,
                     const std::function<std::shared_ptr<Variable>(std::shared_ptr<Statement>)> &getVariable,
                     const std::function<bool(Statement &, Variable &)> &hasUses,
                     const std::function<bool(Statement &, Variable &)> &hasModifies,
                     const std::function<std::shared_ptr<EntityStore<Statement>>(std::shared_ptr<Statement>)> &getNext);

    /**
     * @brief Clears the Affects relationship store
     */
    void clearStore();

    /**
     * Returns an unordered_set of statements of the given statement type which affects itself
     * @param stmtType The type of statement to be retrieved
     * @return An unordered_set of statements
     */
    EntitySet getAffectsSameStmt(StatementType stmtType) const;
};
