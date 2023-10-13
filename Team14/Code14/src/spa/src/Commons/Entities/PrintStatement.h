#pragma once

#include "Commons/AppConstants.h"
#include "Statement.h"
#include "StatementType.h"

/**
 * @brief An PrintStatement is a statement in the SIMPLE programming language
 * @details An PrintStatement is a statement in the SIMPLE programming language
 */
class PrintStatement : Statement {
public:
    /**
     * @brief Construct a new PrintStatement object
     * @param lineNo The line number of the statement as StatementNumber (int)
     * @param attrValue The name of the variable printed
     * @return A new PrintStatement object
     */
    PrintStatement(StatementNumber lineNo, AttrValue varName);
};
