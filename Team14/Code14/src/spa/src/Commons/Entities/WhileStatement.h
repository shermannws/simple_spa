#pragma once

#include "Commons/AppConstants.h"
#include "Statement.h"
#include "StatementType.h"

/**
 * @brief An WhileStatement is a statement in the SIMPLE programming language
 * @details An WhileStatement is a statement in the SIMPLE programming language
 */
class WhileStatement : Statement {
public:
    /**
     * @brief Construct a new WhileStatement object
     * @param lineNo The line number of the statement as StatementNumber (int)
     * @return A new WhileStatement object
     */
    WhileStatement(StatementNumber lineNo)
};
