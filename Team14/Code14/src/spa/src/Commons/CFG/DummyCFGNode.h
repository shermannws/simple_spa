#pragma once

#include "CFGNode.h"

/**
 * CFGNode subclass representing a dummy node.
 * Only used when creating CFG.
 * Should not be present in the final CFG.
 */
class DummyCFGNode : public CFGNode {
private:
    /**
     * Hide the inherited methods below, should not be valid for a DummyCFGNode
     * @warning These methods are still accessible if the DummyCFGNode is cast into CFGNode, which is dangerous.
     */
    using CFGNode::CFGNode;
    using CFGNode::getStatementNumber;
    using CFGNode::getStatementType;
public:
    /**
     * Creates a DummyCFGNode.
     */
    DummyCFGNode();
};
