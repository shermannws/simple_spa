#pragma once

#include "CFGNode.h"

class DummyCFGNode : public CFGNode {
private:
    // Hide the inherited methods below, should not be valid for a DummyCFGNode
    using CFGNode::CFGNode;
    using CFGNode::getStatementNumber;
    using CFGNode::getStatementType;
public:
    DummyCFGNode();
};
