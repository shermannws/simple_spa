#pragma once

#include "PKB/Pkb.h"
#include <list>

/**
 * @brief Query Processing Subsystem (QPS) class.
 *
 * The QPS class is responsible for processing queries using a provided PKB reader
 * and producing a list of results based on the given query.
 */
class QPS {
private:
    /**
     * Shared pointer to the PKB reader.
     */
    std::shared_ptr<PkbReader> pkbReader;
public:
    /**
    * @brief Explicit constructor for the QPS class.
    * @param pkbReader A shared pointer to the PKB reader.
    */
    explicit QPS(std::shared_ptr<PkbReader> pkbReader);

    /**
    * @brief Evaluates a query and produces a list of results.
    * Processes the given query and populates the results list with the query's results.
    * @param query The query to evaluate.
    * @param results A list to store the results of the query.
    */
    void evaluate(std::string& query, std::list<std::string>& results);
};