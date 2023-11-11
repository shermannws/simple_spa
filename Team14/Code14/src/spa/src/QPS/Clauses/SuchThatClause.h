#pragma once

#include "Clause.h"
#include "QPS/Parsers/Token.h"
#include "QPS/QueryEntity.h"
#include "QPS/Ref.h"
#include <stdexcept>
#include <string>

/**
 * @brief SuchThatClause class that extends from Clause
 */
class SuchThatClause : public Clause {
private:
    /**
     * @brief The second parameter of the SuchThatClause
     */
    Ref secondParam;

    /**
     * @brief Returns true if the SuchThatClause object is equal to the other SuchThatClause object, false otherwise
     * @param other The other SuchThatClause object to compare against
     * @return True if the SuchThatClause object is equal to the other SuchThatClause object
     */
    bool isEqual(const Clause &other) const override;

public:
    /**
     * @brief The constructor of SuchThatClause
     */
    SuchThatClause();

    /*
     * @brief The constructor of SuchThatClause that takes in a Token shared pointer representing the design abstraction
     */
    SuchThatClause(const std::shared_ptr<Token> &token);

    /**
     * @brief The setter of the second parameter of the SuchThatClause
     * @param ref the Ref reference of the second parameter
     */
    void setSecondParam(Ref &ref);

    /**
     * @brief The getter of the second parameter of the SuchThatClause
     * @return The Ref reference of the second parameter
     */
    Ref &getSecondParam();

    /**
     * @brief returns the list of synonyms present in the such that clause, used for
     * defining the corresponding Result table header of the clause
     * @return vector of Synonyms
     */
    std::vector<Synonym> getSynonyms() const override;
};
