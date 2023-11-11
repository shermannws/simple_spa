#pragma once

#include <memory>

#include "Clause.h"
#include "QPS/QPSUtil.h"

/**
 * @brief PatternClause class that extends from Clause
 */
class PatternClause : public Clause {
private:
    /**
     * @brief The second parameter of the PatternClause
     */
    ExpressionSpec secondParam;

    /**
     * @brief The synonym of the PatternClause
     */
    Synonym syn;

    /**
     * @brief The boolean that specifies whether a third parameter exists
     */
    bool thirdParam;

    /**
     * @brief Returns true if the PatternClause object is equal to the other PatternClause object, false otherwise
     * @param other The other PatternClause object to compare against
     * @return True if the PatternClause object is equal to the other PatternClause object
     */
    bool isEqual(const Clause &other) const override;

public:
    /**
     * @brief The constructor of PatternClause
     */
    PatternClause();

    /**
     * @brief The setter of the second parameter of the PatternClause
     * @param expr The ExpressionSpec reference of the second parameter
     */
    void setSecondParam(ExpressionSpec &expr);

    /**
     * @brief The getter of the second parameter of the PatternClause
     * @return The ExpressionSpec reference of the second parameter
     */
    ExpressionSpec &getSecondParam();

    /**
     * @brief The setter of the boolean of third parameter
     * @param exists The boolean that specifies whether a third parameter exists
     */
    void setThirdParam(bool exists);

    /**
     * @brief The getter of the boolean thirdParam
     * @return The boolean that specifies whether a third parameter exists
     */
    bool hasThirdParam() const;

    /**
     * @brief The setter of the synonym of the PatternClause
     * @param synonym The Synonym string of the PatternClause
     */
    void setSyn(Synonym synonym);

    /**
     * @brief The getter of the synonym of the PatternClause
     * @return The Synonym string of the PatternClause
     */
    Synonym getSyn();

    /**
     * @brief returns the list of synonyms present in the pattern clause, used for
     * defining the corresponding Result table header of the clause
     * @return vector of Synonyms
     */
    std::vector<Synonym> getSynonyms() const override;
};
