#include "StatementNode.h"

StatementNode::StatementNode(int statementNumber) : statementNumber(statementNumber) {}

int StatementNode::getStatementNumber() {
    return statementNumber;
}