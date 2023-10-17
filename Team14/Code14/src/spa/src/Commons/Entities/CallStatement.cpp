#include "CallStatement.h"

CallStatement::CallStatement(StatementNumber lineNo, AttrValue procName)
        : Statement(lineNo, StatementType::Call, procName) {}