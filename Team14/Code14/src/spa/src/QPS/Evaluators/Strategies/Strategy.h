#pragma once

#include "QPS/Evaluators/Result.h"
#include "QPS/Clauses/Clause.h"
#include "./PKB/PkbReader.h"
#include "Commons/Entities/StatementType.h"

/**
 * @brief The forward declaration of Clause
 */
class Clause;

/**
 * Strategy interface for each type of clause e.g. UsesStrategy, FollowsStrategy, AssignPatternStrategy, etc
 */
class Strategy {
protected:
    /**
     * The statement map that converts from QueryEntityType to the corresponding StatementType
     */
    std::unordered_map<QueryEntityType, StatementType> stmtMap{
            {QueryEntityType::Assign, StatementType::Assign},
            {QueryEntityType::Print, StatementType::Print},
            {QueryEntityType::Read, StatementType::Read},
            {QueryEntityType::If, StatementType::If},
            {QueryEntityType::While, StatementType::While},
            {QueryEntityType::Stmt, StatementType::Stmt}
    };
public:
    /**
     * @brief The constructor of Strategy
     */
    Strategy() = default;

    /**
     * @brief The destructor of Strategy
     */
    virtual ~Strategy() = default;

    /**
     * @brief Evaluates the clause using the appropriate pkbReader method
     * @param clause The shared pointer of the Clause to be evaluated
     * @param pkbReader The pkbReader of which the methods are to be called
     * @return The result of the clause evaluation
     */
    virtual Result evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const = 0;
};
