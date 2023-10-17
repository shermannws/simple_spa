#include "StatementNode.h"

StatementNode::StatementNode(StatementNumber statementNumber) : statementNumber(statementNumber) {}

StatementNumber StatementNode::getStatementNumber() { return statementNumber; }