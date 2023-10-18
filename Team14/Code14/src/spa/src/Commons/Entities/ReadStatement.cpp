#include "ReadStatement.h"

ReadStatement::ReadStatement(StatementNumber lineNo, AttrValue varName)
    : Statement(lineNo, StatementType::Read, varName) {}