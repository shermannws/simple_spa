#pragma once

#include "Entity.h"
#include "StatementType.h"

class Statement : public Entity {
private:
    StatementType statementType;
public:
	Statement(int lineNo, StatementType statementType);

    StatementType getStatementType() const;
};