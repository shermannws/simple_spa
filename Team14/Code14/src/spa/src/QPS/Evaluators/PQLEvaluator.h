#pragma once

#include <list>
#include <string>

#include "./PKB/PkbReader.h"
#include "ClauseHandler.h"
#include "QPS/QPSTypes.h"
#include "QPS/Query.h"
#include "Result.h"
#include "ResultHandler.h"

using transformFunc = std::function<std::string(Entity &)>;

/**
 * @brief PQL (Program Query Language) evaluator class.
 *
 * The PQLEvaluator class is responsible for evaluating PQL queries and producing results.
 * It uses a PKB reader, clause handler, and result handler for query evaluation.
 */
class PQLEvaluator {
private:
    /**
     * Shared pointer to the PKB reader which retrieves the required information for query evaluation
     */
    std::shared_ptr<PkbReader> pkbReader;

    /**
     * Shared pointer to the clause handler which evaluates each clause in the PQL query
     */
    std::shared_ptr<ClauseHandler> clauseHandler;

    /**
     * Shared pointer to the result handler which is responsible for combining results
     */
    std::shared_ptr<ResultHandler> resultHandler;

    /**
     * @brief Retrieves all instances of a query entity from the PKB, the method
     * is responsible for choosing which PKB API to call
     * @param queryEntity A pointer to the query entity to retrieve instances for.
     * @return A set of entities representing all instances of the query entity.
     */
    std::unordered_set<Entity> getAll(const EntityPtr &queryEntity);

    /**
     * @brief Evaluates a clause and updates the result accordingly.
     * @param clause A shared pointer to the Clause to evaluate.
     * @return shared pointer to result object
     */
    std::shared_ptr<Result> evaluateClause(const std::shared_ptr<Clause> clause);

    /**
     * @brief Evaluates a select clause with the given entity as the result clause without any constraint clauses
     * @param entity the selected entity to be evaluated
     * @return shared pointer to result object
     */
    std::shared_ptr<Result> evaluateSelect(const std::shared_ptr<QueryEntity> entity);

    /**
     * @brief Evaluates a subset of the result clause of a query
     * @param query the query object whose result clause is being evaluated
     * @param resultSyns the vector of synonyms representing the subset of result clause to be evaluated
     * @return shared pointer to result object
     */
    std::shared_ptr<Result> evaluateResultClause(const Query &query, std::vector<Synonym> resultSyns);

    /**
     * @brief returns the vector of synonyms in the result clause that is not present in the result object
     * @param resultClause vector of synonyms
     * @param result result object
     * @return vector of unevaluated synonyms
     */
    std::vector<Synonym> getUnevaluatedSyn(const std::vector<Synonym> resultClause, std::shared_ptr<Result> result);

    /**
     * applies the transformFunc to the entity at index equal to the int and stores the result in the returned vector
     * @param row vector of entities to transform
     * @param transformations pair of index of entity to transform and toString function to apply
     * @return the vector of transformation results
     */
    std::vector<std::string> project(std::vector<Entity> row,
                                     std::vector<std::pair<int, transformFunc>> transformations);

    /**
     * creates a vector of transformations to convert a row from a result table into the format specified by
     * resultClause a transformation is a pair of int, transformFunc where int represents index of entity
     * @param inputMap synonym indices of input tuples
     * @param resultClause vector of synonyms we want to build
     * @return
     */
    std::vector<std::pair<int, transformFunc>> getTransformations(SynonymMap inputMap,
                                                                  std::vector<Synonym> resultClause);

    /**
     * concatenates a vector of strings with a whitespace as the connector
     * @param strings vector of strings to join
     * @return resultant string
     */
    std::string concat(std::vector<std::string> strings);

    /**
     * evaluates whether any of the results in the vector is a False Result or is an empty result tuple
     * @param results vector of results to evaluate
     * @return true if all the results in the vector are non-false and non-empty, false otherwise
     */
    bool evaluateBoolResults(std::vector<std::shared_ptr<Result>> results);

    /**
     * evaluate the overall result of the given results
     * @param results vector of results to combine
     * @return shared pointer to the result object
     */
    std::shared_ptr<Result> evaluateMainResults(std::vector<std::shared_ptr<Result>> results);

    /**
     * evaluates the vector of clauses
     * @param clauseGroup the vector of clauses to evaluate
     * @return shared pointer to the result object
     */
    std::shared_ptr<Result> evaluateClauses(std::vector<std::shared_ptr<Clause>> clauseGroup);

    /**
     * groups the clauses in the query based on synonyms
     * @param adjacency_list An unordered map representing the adjacency list of synonym graph
     * @param clauses vector of clauses to group
     * @return vector of grouped clauses
     */
    std::vector<std::unordered_set<std::shared_ptr<Clause>>>
    groupClauses(std::unordered_map<Synonym, std::unordered_set<Synonym>> &adjacency_list,
                 std::vector<std::shared_ptr<Clause>> clauses);

    /**
     * builds a graph with synonyms as nodes and edges representing synonyms that are connected by clause(s)
     * @param query the query object
     * @param clauses vector of clauses that defines the edges in the graph
     * @return an unordered map representing a adjacency list
     */
    std::unordered_map<Synonym, std::unordered_set<Synonym>>
    buildSynGraph(Query &query, std::vector<std::shared_ptr<Clause>> clauses);

    /**
     * performs depth first search on a adjacency graph of synonyms from current as the starting node
     * @param adjacency_list An unordered map representing the adjacency list of synonym graph
     * @param current The current synonym being explored in the graph
     * @param visited A set of visited synonyms
     * @param connected A set of synonyms that are reachable from current
     */
    void DFS(const std::unordered_map<Synonym, std::unordered_set<Synonym>> &adjacency_list, const std::string &current,
             std::unordered_set<std::string> &visited, std::unordered_set<std::string> &connected);

    /**
     * checks if the selected synonyms intersect with the synonyms in the result table
     * @param selects vector of synonyms to check
     * @param res result table to check
     * @return true if the synonyms in the result table intersects wiht the sunonyms in the vector
     */
    bool intersect(std::vector<Synonym> selects, std::shared_ptr<Result> res);

public:
    /**
     * @brief Explicit constructor for the PQLEvaluator class.
     * @param pkbReader A shared pointer to the PKB reader.
     */
    explicit PQLEvaluator(std::shared_ptr<PkbReader> pkbReader);

    /**
     * @brief Evaluates a PQL query and returns the result.
     * @param query The PQL query to evaluate.
     * @return The result of the PQL query evaluation as a Result object
     */
    Result evaluate(Query &query);

    /**
     * @brief Formats the result of a PQL query based on the given query and result table.
     * @param query The PQL query.
     * @param result The result of the PQL query evaluation.
     * @return The formatted result list
     */
    ResultList formatResult(Query &query, Result &result);
};