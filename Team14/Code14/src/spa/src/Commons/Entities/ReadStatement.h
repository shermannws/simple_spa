#pragma once

#include "Commons/AppConstants.h"
#include "Statement.h"
#include "StatementType.h"

/**
 * @brief An ReadStatement is a statement in the SIMPLE programming language
 * @details An ReadStatement is a statement in the SIMPLE programming language
 */
class ReadStatement : public Statement {
public:
    /**
     * @brief Construct a new ReadStatement object
     * @param lineNo The line number of the statement as StatementNumber (int)
     * @param attrValue The name of the variable read
     * @return A new ReadStatement object
     */
    ReadStatement(StatementNumber lineNo, AttrValue varName);
};
