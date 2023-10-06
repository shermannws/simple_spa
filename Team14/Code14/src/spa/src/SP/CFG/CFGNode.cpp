#include "CFGNode.h"

#include <utility>

CFGNode::CFGNode(StatementNumber statementNumber, std::vector<std::shared_ptr<CFGNode>> parents, std::vector<std::shared_ptr<CFGNode>> children)
    : statementNumber(std::move(statementNumber)), parents(std::move(parents)), children(std::move(children)) {}

StatementNumber CFGNode::getStatementNumber() {
    return this->statementNumber;
}

std::vector<std::shared_ptr<CFGNode>> CFGNode::getParentNodes() {
     return this->parents;
}

std::vector<std::shared_ptr<CFGNode>> CFGNode::getChildrenNodes() {
    return this->children;
}

