#pragma once

#include <unordered_map>
#include <unordered_set>

#include "SP/AST/Nodes/CallNode.h"
#include "SP/AST/Nodes/ProcedureNode.h"

/**
 * Subcomponent of the SemanticValidator to track recursive calls within a SIMPLE program.
 */
class CallGraph {
private:
    /**
     * An unordered map of procedure nodes in the call graph.
     */
    std::unordered_map<ProcedureName, std::shared_ptr<ProcedureNode>> nodes;

    /**
     * An unordered map of edges mapping caller to callee.
     */
    std::unordered_map<ProcedureName, std::vector<ProcedureName>> edges;

    /**
     * Recursive depth-first search to detect cycles in the call graph.
     * @param currentProcedure Current procedure in the DFS
     * @param visited Set of visited nodes for the DFS algorithm
     * @param currentPath Current path the DFS is taking
     * @return
     */
    bool hasCycleDFS(const ProcedureName &currentProcedure, std::unordered_set<ProcedureName> &visited,
                     std::unordered_set<ProcedureName> &currentPath);

public:
    /**
     * Creates an initialises a CallGraph.
     */
    CallGraph();

    /**
     * Adds a node to the call graph.
     * @param node Procedure node to add
     */
    void addNode(const std::shared_ptr<ProcedureNode> &node);

    /**
     * Adds an edge to the call graph, mapping caller to callee.
     * @param caller Procedure node that is calls the callee
     * @param callee Procedure node that is being called
     */
    void addEdge(const ProcedureName &caller, const ProcedureName &callee);

    /**
     * Entry point to semantically check if the call graph has got a cyclical call.
     * @return Whether there is a cyclical call in the graph
     */
    bool hasCycle();
};