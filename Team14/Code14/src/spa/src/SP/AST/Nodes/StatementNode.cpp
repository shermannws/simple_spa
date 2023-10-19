#include "StatementNode.h"

StatementNode::StatementNode(StatementNumber statementNumber) : statementNumber(statementNumber) {}

StatementNumber StatementNode::getStatementNumber() { return statementNumber; }

bool StatementNode::isParentNode() {
    return this->getStatementType() == StatementNodeType::If || this->getStatementType() == StatementNodeType::While;
}