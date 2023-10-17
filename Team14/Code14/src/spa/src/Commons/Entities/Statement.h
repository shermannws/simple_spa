#pragma once

#include "../AppConstants.h"
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
     * @param lineNo The line number of the statement as StatementNumber (int)
     * @param statementType The Statement Type of the Statement object of enum type `StatementType`
     * @return A new Statement object
     */
    Statement(StatementNumber lineNo, StatementType statementType);

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

/**
 * @brief A hash function for Statement objects. Necessary as Statement class has an additional
 * member field compared to its base class, so CPP doesn't allow using hash function of Entity.
 * @details A hash function for Statement objects.
 * StatementType not used to differentiate State ment objects as lineno (as EntityValue) should uniquely identify a
 * Statement
 */
template<>
struct std::hash<Statement> {
    std::size_t operator()(const Statement &statement) const;
};