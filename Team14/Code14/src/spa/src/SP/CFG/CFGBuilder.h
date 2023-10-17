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

class CFGBuilder {
private:
    /**
     * Builds a CFG for the procedure represented by the subtree rooted at the ProcedureNode given.
     * @param procedureNode The root (ASTNode) of the procedure subtree to create a CFG for
     * @return Unordered map of Statement to CFGNode
     */
    static std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>> buildCFGForProcedure(
            const std::shared_ptr<ProcedureNode>& procedureNode);

    /**
     * Builds a CFG subgraph for a statement list.
     * @param map Unordered map of each procedure to a map of Statement to CFGNode
     * @param statementListNode The root (ASTNode) of the statement list subtree to create a CFG subtree for
     * @return The head and tail nodes of this subgraph
     */
    static std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>> buildStatementListSubgraph(
            std::vector<std::shared_ptr<CFGNode>>& cfgNodes, const std::shared_ptr<StatementListNode>& statementListNode);

    /**
     * Builds a CFG subgraph for a statement (assign, call, print, read, if, while).
     * @param map Unordered map of each procedure to a map of Statement to CFGNode
     * @param statementNode The root (ASTNode) of the statement subtree to create a CFG subtree for
     * @return The head and tail nodes of this subgraph
     */
    static std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>> buildStatementSubgraph(
            std::vector<std::shared_ptr<CFGNode>>& cfgNodes, const std::shared_ptr<StatementNode>& statementNode);

    /**
     * Builds a CFG subgraph for an if statement and its statement lists.
     * @param map Unordered map of each procedure to a map of Statement to CFGNode
     * @param ifNode The root (ASTNode) of the if statement subtree to create a CFG subtree for
     * @return The head and tail nodes of this subgraph
     */
    static std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>> buildIfSubgraph(
            std::vector<std::shared_ptr<CFGNode>>& cfgNodes, const std::shared_ptr<IfNode>& ifNode);

    /**
     * Builds a CFG subgraph for a while statement and its statement list.
     * @param map Unordered map of each procedure to a map of Statement to CFGNode
     * @param whileNode The root (ASTNode) of the while statement subtree to create a CFG subtree for
     * @return The head and tail nodes of this subgraph
     */
    static std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>> buildWhileSubgraph(
            std::vector<std::shared_ptr<CFGNode>>& cfgNodes, const std::shared_ptr<WhileNode>& whileNode);
public:
    /**
     * Builds a CFG for each procedure in the AST given.
     * Returns a pair of 2 maps required to traverse CFGs.
     * 1. Unordered map of each procedure to the first Statement in the procedure, i.e. heads of each CFG, and
     * 2. Unordered map of each procedure to an unordered map of Statement to CFGNode
     * @param ASTRootNode The root node of the AST
     * @return A pair of:
     * (1) Unordered map of ProcedureName to Statement, and
     * (2) Unordered map of ProcedureName to an unordered map of Statement to CFGNode
     */
    static std::unordered_map<ProcedureName, std::pair<std::shared_ptr<CFGNode>, std::vector<std::shared_ptr<CFGNode>>>>
    buildAllCFG(const std::shared_ptr<ProgramNode>& ASTRootNode);
};
