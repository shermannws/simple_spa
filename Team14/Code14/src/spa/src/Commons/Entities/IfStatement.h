#pragma once

#include "Commons/AppConstants.h"
#include "Statement.h"
#include "StatementType.h"

/**
 * @brief An IfStatement is a statement in the SIMPLE programming language
 * @details An IfStatement is a statement in the SIMPLE programming language
 */
class IfStatement : Statement {
public:
    /**
     * @brief Construct a new IfStatement object
     * @param lineNo The line number of the statement as StatementNumber (int)
     * @return A new IfStatement object
     */
    IfStatement(StatementNumber lineNo);
};
