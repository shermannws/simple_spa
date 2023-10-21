#pragma once

#include <unordered_map>

#include "Commons/AppConstants.h"
#include "Commons/CFG/CFGNode.h"
#include "Commons/Entities/Statement.h"
#include "SP/AST/Nodes/IfNode.h"
#include "SP/AST/Nodes/ProcedureNode.h"
#include "SP/AST/Nodes/ProgramNode.h"
#include "SP/AST/Nodes/StatementListNode.h"
#include "SP/AST/Nodes/WhileNode.h"

/**
 * Builder class to build CFGs.
 */
class CFGBuilder {
private:
    /**
     * Builds a CFG for the procedure represented by the subtree rooted at the ProcedureNode given.
     * @param procedureNode The root (ASTNode) of the procedure subtree to create a CFG for
     * @return A pair of (1) head CFGNode of the procedure, and (2) a vector of all CFGNodes of the procedure
     */
    static std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>>
    buildCFGForProcedure(const std::shared_ptr<ProcedureNode> &procedureNode);

    /**
     * Builds a CFG subgraph for a statement list.
     * @param cfgNodes A vector to hold all CFGNodes of the procedure
     * @param statementListNode The root (ASTNode) of the statement list subtree to create a CFG subtree for
     * @return The head and tail nodes of this subgraph
     */
    static std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>
    buildStatementListSubgraph(std::vector<std::shared_ptr<CFGNode>> &cfgNodes,
                               const std::shared_ptr<StatementListNode> &statementListNode);

    /**
     * Builds a CFG subgraph for a statement (assign, call, print, read, if, while).
     * @param cfgNodes A vector to hold all CFGNodes of the procedure
     * @param statementNode The root (ASTNode) of the statement subtree to create a CFG subtree for
     * @return The head and tail nodes of this subgraph
     */
    static std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>
    buildStatementSubgraph(std::vector<std::shared_ptr<CFGNode>> &cfgNodes,
                           const std::shared_ptr<StatementNode> &statementNode);

    /**
     * Builds a CFG subgraph for an if statement and its statement lists.
     * @param cfgNodes A vector to hold all CFGNodes of the procedure
     * @param ifNode The root (ASTNode) of the if statement subtree to create a CFG subtree for
     * @return The head and tail nodes of this subgraph
     */
    static std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>
    buildIfSubgraph(std::vector<std::shared_ptr<CFGNode>> &cfgNodes, const std::shared_ptr<IfNode> &ifNode);

    /**
     * Builds a CFG subgraph for a while statement and its statement list.
     * @param cfgNodes A vector to hold all CFGNodes of the procedure
     * @param whileNode The root (ASTNode) of the while statement subtree to create a CFG subtree for
     * @return The head and tail nodes of this subgraph
     */
    static std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>
    buildWhileSubgraph(std::vector<std::shared_ptr<CFGNode>> &cfgNodes, const std::shared_ptr<WhileNode> &whileNode);

public:
    /**
     * Builds a CFG for each procedure in the AST given.
     * @param ASTRootNode The root node of the AST
     * @return An unordered map of ProcedureName to a pair of:
     * (1) head CFGNode of the procedure, and
     * (2) a vector of all CFGNodes of the procedure
     */
    static std::unordered_map<ProcedureName, std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>>>
    buildAllCFG(const std::shared_ptr<ProgramNode> &ASTRootNode);
};
