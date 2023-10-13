#pragma once

#include "Commons/AppConstants.h"
#include "Statement.h"
#include "StatementType.h"

/**
 * @brief An AssignStatement is a statement in the SIMPLE programming language
 * @details An AssignStatement is a statement in the SIMPLE programming language
 */
class AssignStatement : public Statement {
public:
    /**
     * @brief Construct a new AssignStatement object
     * @param lineNo The line number of the statement as StatementNumber (int)
     * @return A new AssignStatement object
     */
    AssignStatement(StatementNumber lineNo);
};