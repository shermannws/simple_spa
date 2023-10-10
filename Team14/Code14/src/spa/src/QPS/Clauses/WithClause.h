#pragma once

#include <memory>

#include "Clause.h"

/**
 * @brief PatternClause class that extends from Clause
 */
class WithClause :  public Clause {
private:
private:
    /**
     * @brief The second parameter of the SuchThatClause
     */
    Ref secondParam;

public:
    /**
     * @brief The constructor of PatternClause
     */
    WithClause();

    /**
     * @brief The setter of the second parameter of the SuchThatClause
     * @param ref the Ref reference of the second parameter
     */
    void setSecondParam(Ref& ref);

    /**
     * @brief The getter of the second parameter of the SuchThatClause
     * @return The Ref reference of the second parameter
     */
    Ref& getSecondParam();

    /**
     * @brief returns the list of synonyms present in the with clause, used for
     * defining the corresponding Result table header of the clause
     * @return vector of Synonyms
     */
    std::vector<Synonym> getSynonyms() const override;

    bool operator==(const Clause& other) const override;
};
