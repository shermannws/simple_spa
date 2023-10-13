#pragma once

#include <string>
#include <utility>
#include <functional>

#include "QPS/Query.h"
#include "QPS/QueryEntity.h"
#include "QPS/QPSTypes.h"


class PqlSemanticValidator {
public:
    explicit PqlSemanticValidator();

    /**
     * @brief Validates the declarations in the query, throws a Semantic exception in case of
     * a synonym redeclaration
     * @param query the query object
     * @param synonyms the vector of declared synonyms
     */
    void validateDeclarations(const std::vector<Synonym>& synonyms);

    /**
     * @brief Validates the result clause semantically, throws a Semantic exception if synonym is undeclared
     * @param query the query object
     * @param syn the synonym selected in the query
     */
    void validateResultClause(const Query& query, const Synonym& syn);

    /**
     * @brief Validates all the clauses in the given query
     * @param query the query object
     */
    void validateConstraintClauses(const Query& query);

private:
    /**
     * @brief Validates SuchThatClause semantically, throws a SemanticException if semantically invalid
     * @param query the Query object
     * @param clause the shared pointer of SuchThatClause to validate
     */
    void validateClauseSemantics(const Query& query, std::shared_ptr<SuchThatClause> clause);

    /**
     * @brief Validates PatternClause semantically, throws a SemanticException if semantically invalid
     * @param query the Query object
     * @param clause the shared pointer of PatternClause to validate
     */
    void validateClauseSemantics(const Query& query, std::shared_ptr<PatternClause> clause);

    /**
     * @brief Validates WithClause semantically, throws a SemanticException if semantically invalid
     * @param query the Query object
     * @param clause the shared pointer of WithClause to validate
     */
    void validateClauseSemantics(const Query& query, std::shared_ptr<WithClause> clause);

};

