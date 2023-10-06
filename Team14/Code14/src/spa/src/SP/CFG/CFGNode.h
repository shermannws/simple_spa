#pragma once

#include <string>
#include <utility>
#include <vector>

#include "Commons/AppConstants.h"

/**
 * CFGNode to represent a single statement in the CFG.
 */
class CFGNode {
private:
    /**
     * The statement number of the node.
     */
    StatementNumber statementNumber;

    /**
     * The parents of the node (statements that come before).
     */
    std::vector<std::shared_ptr<CFGNode>> parents;

    /**
     * The children of the node (statements that come after).
     */
    std::vector<std::shared_ptr<CFGNode>> children;

public:
    /**
     * Creates and initialises a CFGNode.
     * @param statementNumber The statement number of the node
     * @param parent A vector of parent nodes
     * @param children A vector of children nodes
     */
    CFGNode(StatementNumber statementNumber, std::vector<std::shared_ptr<CFGNode>> parents,
            std::vector<std::shared_ptr<CFGNode>> children);

    /**
     * Returns the statement number of the node.
     * @return The statement number of the node
     */
    StatementNumber getStatementNumber();

    /**
     * Returns the parent nodes of the current CFGNode.
     * @return Vector of CFGNodes
     */
    std::vector<std::shared_ptr<CFGNode>> getParentNodes();

    /**
     * Returns the children nodes of the current CFGNode.
     * @return Vector of CFGNodes
     */
    std::vector<std::shared_ptr<CFGNode>> getChildrenNodes();
};