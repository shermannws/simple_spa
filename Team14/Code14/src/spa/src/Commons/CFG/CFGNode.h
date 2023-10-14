#pragma once

#include <string>
#include <utility>
#include <memory>
#include <vector>

#include "Commons/AppConstants.h"
#include "Commons/Entities/StatementType.h"

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

    /**
     * The type of the statement.
     */
    StatementType statementType;

public:
    // Added to allow this class to be used in dynamic_cast expression
    virtual ~CFGNode() = default;
    /**
     * Creates and initialises a CFGNode.
     * @param statementNumber The statement number of the node
     */
    explicit CFGNode(StatementNumber statementNumber);

    /**
     * Creates and initialises a CFGNode.
     * @param statementNumber The statement number of the node
     * @param statementType The type of the statement represented by the node
     */
    CFGNode(StatementNumber statementNumber, StatementType statementType);

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

    /**
     * Adds a parent node to this CFGNode.
     * @param parent CFGNode to be added as a parent of this CFGNode
     */
    void addParentNode(const std::shared_ptr<CFGNode>& parent);

    /**
     * Adds a child node to this CFGNode.
     * @param child CFGNode to be added as a child of this CFGNode
     */
    void addChildNode(const std::shared_ptr<CFGNode>& child);

    /**
     * Removes a child node from this CFGNode by reference. Used in CFG building.
     * @param child CFGNode to be removed as a child of this CFGNode
     */
    void removeChildNode(const std::shared_ptr<CFGNode>& child);

    /**
     * Returns the statement type of this CFGNode
     * @return Statement type of the CFGNode
     */
    StatementType getStatementType();
};