#pragma once

#include "QPS/QueryEntity.h"
#include "Clause.h"
#include "QPS/Ref.h"
#include "QPS/Parsers/Token.h"
#include <string>
#include <stdexcept>

/**
 * @brief SuchThatClause class that extends from Clause
 */
class SuchThatClause : public Clause {
private:
    /**
     * @brief The second parameter of the SuchThatClause
     */
    Ref secondParam;

public:
    /**
     * @brief The constructor of SuchThatClause
     */
    SuchThatClause();

    /*
     * @brief The constructor of SuchThatClause that takes in a Token shared pointer
     */
    SuchThatClause(const std::shared_ptr<Token>& token);

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

    bool operator==(const Clause& other) const override;
};
