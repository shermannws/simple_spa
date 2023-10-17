#include "CFGNode.h"

CFGNode::CFGNode(StatementNumber statementNumber) : statementNumber(std::move(statementNumber)) {}

CFGNode::CFGNode(StatementNumber statementNumber, StatementType statementType)
        : statementNumber(std::move(statementNumber)), statementType(statementType) {}

CFGNode::CFGNode(StatementNumber statementNumber, std::vector<std::shared_ptr<CFGNode>> parents,
                 std::vector<std::shared_ptr<CFGNode>> children)
        : statementNumber(std::move(statementNumber)), parents(std::move(parents)), children(std::move(children)) {}

StatementNumber CFGNode::getStatementNumber() { return this->statementNumber; }

std::vector<std::shared_ptr<CFGNode>> CFGNode::getParentNodes() { return this->parents; }

std::vector<std::shared_ptr<CFGNode>> CFGNode::getChildrenNodes() { return this->children; }

void CFGNode::addParentNode(const std::shared_ptr<CFGNode> &parent) { this->parents.push_back(parent); }

void CFGNode::addChildNode(const std::shared_ptr<CFGNode> &child) { this->children.push_back(child); }

void CFGNode::removeChildNode(const std::shared_ptr<CFGNode> &child) {
    this->children.erase(std::remove(this->children.begin(), this->children.end(), child), this->children.end());
}

StatementType CFGNode::getStatementType() { return this->statementType; }