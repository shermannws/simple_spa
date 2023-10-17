#pragma once

#include "Commons/AppConstants.h"
#include "Statement.h"
#include "StatementType.h"

/**
 * @brief An CallStatement is a statement in the SIMPLE programming language
 * @details An CallStatement is a statement in the SIMPLE programming language
 */
class CallStatement : public Statement {
public:
    /**
     * @brief Construct a new CallStatement object
     * @param lineNo The line number of the statement as StatementNumber (int)
     * @param attrValue The name of the procedure called
     * @return A new CallStatement object
     */
    CallStatement(StatementNumber lineNo, AttrValue procName);
};
