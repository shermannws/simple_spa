#pragma once

#include "QPS/Clauses/PatternClause.h"
#include "QPS/Clauses/SuchThatClause.h"

/**
 *  Utility functions to create objects for testing
 */
class QPSTestUtil {
public:
    /**
     * Returns a shared pointer to a suchThat clause with the specified params
     * @param type
     * @param t1 RefType of lhs
     * @param r1 RootType of lhs
     * @param e1 EntityType of lhs
     * @param rep1 string representation of lhs
     * @param t1 RefType of rhs
     * @param r1 RootType of rhs
     * @param e1 EntityType of rhs
     * @param rep1 string representation of rhs
     * @return shared pointer to such that clause object
     */
    static std::shared_ptr<SuchThatClause> createSuchThatClause(ClauseType type, RefType t1, RootType r1,
                                                                QueryEntityType e1, std::string rep1, RefType t2,
                                                                RootType r2, QueryEntityType e2, std::string rep2);

    /**
     * Returns a shared pointer to a pattern clause with the specified params
     * @param type
     * @param syn synonym of the pattern clause
     * @param r1 RootType of lhs
     * @param rep1 string representation of lhs
     * @param t2 type of expr-spec (Wildcard, PartialMatch, ExactMatch)
     * @param rep2 string representation of the expr spec
     * @return
     */
    static std::shared_ptr<PatternClause> createPatternClause(ClauseType type, Synonym syn, RootType r1,
                                                              std::string rep1, ExpressionSpecType t2, Expression rep2);
};