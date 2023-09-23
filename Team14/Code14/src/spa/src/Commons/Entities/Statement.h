#pragma once

#include "Entity.h"
#include "StatementType.h"

/**
 * @brief A Statement is a statement in the SIMPLE programming language
 * @details A Statement is a statement in the SIMPLE programming language
 */
class Statement : public Entity {
private:
    /**
     * @brief The Statement Type of the Statement object of enum type `StatementType`
     */
    StatementType statementType;
public:
    /**
     * @brief Construct a new Statement object
     * @param lineNo The line number of the statement
     * @param statementType The Statement Type of the Statement object of enum type `StatementType`
     * @return A new Statement object
     */
    Statement(int lineNo, StatementType statementType);

    /**
     * @brief Returns the Statement Type of the Statement object of enum type `StatementType`
     * @return The Statement Type of the Statement object of enum type `StatementType`
     */
    StatementType getStatementType() const;

    /**
     * @brief Returns true if the Statement Type of the Statement object is of type `statementType`, false otherwise
     * @param statementType The Statement Type to check against
     * @return True if the Statement Type of the Statement object is of type `statementType`, false otherwise
     */
    bool isStatementType(StatementType statementType) const;
};