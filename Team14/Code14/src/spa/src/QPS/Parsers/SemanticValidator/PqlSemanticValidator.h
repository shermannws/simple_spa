#pragma once

#include <functional>
#include <string>
#include <utility>

#include "QPS/QPSTypes.h"
#include "QPS/Query.h"
#include "QPS/QueryEntity.h"


class PqlSemanticValidator {
private:
    /**
     * @brief Validates SuchThatClause semantically, throws a SemanticException if semantically invalid
     * @param query the Query object
     * @param clause the shared pointer of SuchThatClause to validate
     */
    void validateClauseSemantics(const Query &query, std::shared_ptr<SuchThatClause> clause);

    /**
     * @brief Validates PatternClause semantically, throws a SemanticException if semantically invalid
     * @param query the Query object
     * @param clause the shared pointer of PatternClause to validate
     */
    void validateClauseSemantics(const Query &query, std::shared_ptr<PatternClause> clause);

    /**
     * @brief Validates WithClause semantically, throws a SemanticException if semantically invalid
     * @param query the Query object
     * @param clause the shared pointer of WithClause to validate
     */
    void validateClauseSemantics(const Query &query, std::shared_ptr<WithClause> clause);

    /**
     * @brief validates a synonym in the result-clause, throws a SemanticException
     * if synonym is semantically invalid
     * @param query query that contains the result-clause
     * @param elem synonym element to validate
     **/
    void validateResultSynonym(const Query &query, Synonym elem);

    /**
     * @brief validates a attrRef in the result-clause, throws a SemanticException
     * if attrRef is semantically invalid
     * @param query query that contains the result-clause
     * @param elem attrRef element to validate
     * @param dotPos index of '.' in the attrRef
     */
    void validateResultAttrRef(const Query &query, Synonym elem, size_t dotPos);

    /**
     * @brief validates an element in the result-clause of the query, throws semantic error if element is semantically
     * invalid
     * @param query query that contains the result-clause
     * @param elem element to validate
     */
    void validateResultElem(const Query &query, Synonym elem);

    /**
     * @brief Checks if the query has a boolean result-clause
     * @param query query to check
     * @return true if result-clause is boolean, otherwise false
     */
    bool isBooleanResult(const Query &query);

public:
    /**
     * The constructor of PqlSemanticValidator
     */
    explicit PqlSemanticValidator();

    /**
     * @brief Validates the declarations in the query, throws a SemanticException in case of
     * a synonym redeclaration
     * @param synonyms the vector of declared synonyms
     */
    void validateDeclarations(const std::vector<Synonym> &synonyms);

    /**
     * @brief Validates the result clause semantically, throws a SemanticException if synonym is undeclared
     * @param query the query object
     */
    void validateResultClause(Query &query);

    /**
     * @brief Validates all the clauses in the given query
     * @param query the query object
     */
    void validateConstraintClauses(const Query &query);
};
