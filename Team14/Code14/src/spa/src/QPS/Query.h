#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "QPS/Clauses/PatternClause.h"
#include "QPS/Clauses/SuchThatClause.h"
#include "QPS/Clauses/WithClause.h"
#include "QPSTypes.h"
#include "QueryEntity.h"

/**
 * @brief Represents a PQL query
 *
 * This class stores information related to a PQL query, including declarations,
 * selected entities, such-that clause, and pattern clause.
 */
class Query {
private:
    /**
     * Map of entity declarations
     */
    std::unordered_map<Synonym, std::shared_ptr<QueryEntity>> declarations;

    /**
     * Vector of selected entities
     */
    std::vector<Synonym> selects;

    /**
     * True if the result clause is a tuple of '<' elem ( ',' elem )* '>'
     */
    bool isMultiTuple;

    /**
     * Vector of such that clauses
     */
    std::vector<std::shared_ptr<SuchThatClause>> suchThatClauses;

    /**
     * Vector of pattern clauses
     */
    std::vector<std::shared_ptr<PatternClause>> patternClauses;

    /**
     * Vector of with clauses
     */
    std::vector<std::shared_ptr<WithClause>> withClauses;

public:
    /**
     * @brief Default constructor for the Query class.
     */
    Query();

    /**
     * @brief Adds a design entity declaration to the query's declaration map
     * @param entity A shared pointer to the QueryEntity to be added
     */
    void addDeclaration(const std::shared_ptr<QueryEntity> &entity);

    /**
     * @brief Adds a selected entity to the query.
     * @param Synonym A shared pointer to the QueryEntity to be added as a selected entity.
     */
    void addSelect(const Synonym);

    /**
     * @brief sets the Query selects for BOOLEAN result-clause queries
     */
    void setBooleanResult();

    /**
     * @brief sets the Query isMultiTuple to true
     */
    void setMultiTupleResult();

    /**
     * @brief returns true if the query's result clause is tuple of '<' elem ( ',' elem )* '>'
     */
    bool isMultiTupleResult() const;

    /**
     * @brief Adds a such-that clause to the query.
     * @param clause A shared pointer to the SuchThatClause to be added.
     */
    void addClause(std::shared_ptr<SuchThatClause> clause);

    /**
     * @brief Adds a pattern clause to the query.
     * @param clause A shared pointer to the PatternClause to be added.
     */
    void addClause(std::shared_ptr<PatternClause> clause);

    /**
     * @brief Adds a pattern clause to the query.
     * @param clause A shared pointer to the PatternClause to be added.
     */
    void addClause(std::shared_ptr<WithClause> clause);

    /**
     * @brief Checks if there are any declarations in the query.
     * @return True if there are declarations, false otherwise.
     */
    bool hasDeclarations() const;

    /**
     * @brief Retrieves a query entity based on its synonym.
     * @param syn The synonym of the entity to retrieve.
     * @return A shared pointer to the QueryEntity with the specified synonym, or nullptr if not found.
     */
    std::shared_ptr<QueryEntity> getEntity(const std::string &syn) const;

    /**
     * @brief Retrieves the map of synonyms to entity declarations in the query.
     * @return An unordered map of synonym to entity
     */
    std::unordered_map<std::string, std::shared_ptr<QueryEntity>> getDeclarations() const;

    /**
     * @brief Retrieves the vector of selected entities in the query.
     * @return A vector of shared pointers to the selected QueryEntities.
     */
    std::vector<Synonym> getSelect() const;

    /**
     * @brief Retrieves the vector of such-that clauses in the query.
     * @return A vector of shared pointers to the SuchThatClauses.
     */
    std::vector<std::shared_ptr<SuchThatClause>> getSuchThat() const;

    /**
     * @brief Retrieves the vector of pattern clauses in the query.
     * @return A vector of shared pointers to the PatternClauses.
     */
    std::vector<std::shared_ptr<PatternClause>> getPattern() const;

    /**
     * @brief Retrieves the vector of with clauses in the query.
     * @return A vector of shared pointers to the WithClauses.
     */
    std::vector<std::shared_ptr<WithClause>> getWith() const;

    /**
     * @brief Retrieves the vector of pattern clauses in the query.
     * @return A vector of shared pointers to the Clauses.
     */
    std::vector<std::shared_ptr<Clause>> getAllClause() const;
};