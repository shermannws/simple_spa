#include "CFGNode.h"

#include <utility>

CFGNode::CFGNode(StatementNumber statementNumber)
    : statementNumber(statementNumber), statementType(StatementType::Stmt), attrValue(AppConstants::STRING_EMPTY) {}

CFGNode::CFGNode(StatementNumber statementNumber, StatementType statementType)
    : statementNumber(statementNumber), statementType(statementType), attrValue(AppConstants::STRING_EMPTY) {}

CFGNode::CFGNode(StatementNumber statementNumber, StatementType statementType, AttrValue attrValue)
    : statementNumber(statementNumber), statementType(statementType), attrValue(std::move(attrValue)) {}

StatementNumber CFGNode::getStatementNumber() const { return this->statementNumber; }

std::vector<std::shared_ptr<CFGNode>> CFGNode::getParentNodes() { return this->parents; }

std::vector<std::shared_ptr<CFGNode>> CFGNode::getChildrenNodes() { return this->children; }

void CFGNode::addParentNode(const std::shared_ptr<CFGNode> &parent) { this->parents.push_back(parent); }

void CFGNode::addChildNode(const std::shared_ptr<CFGNode> &child) { this->children.push_back(child); }

void CFGNode::removeChildNode(const std::shared_ptr<CFGNode> &child) {
    this->children.erase(std::remove(this->children.begin(), this->children.end(), child), this->children.end());
}

StatementType CFGNode::getStatementType() const { return this->statementType; }

AttrValue CFGNode::getAttrValue() const { return this->attrValue; }