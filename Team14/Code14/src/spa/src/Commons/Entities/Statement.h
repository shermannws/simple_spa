#pragma once

#include "Entity.h"
#include "StatementType.h"

class Statement : public Entity {
private:
    StatementType statementType;
public:
    /*!
     * Costructor for Constant object
     */
	Statement(int lineNo, StatementType statementType);

    /*!
     * Returns the exact statement type of the object
     */
    StatementType getStatementType() const;
};