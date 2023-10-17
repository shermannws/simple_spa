#include "PrintStatement.h"

PrintStatement::PrintStatement(StatementNumber lineNo, AttrValue varName)
    : Statement(lineNo, StatementType::Print, varName) {}