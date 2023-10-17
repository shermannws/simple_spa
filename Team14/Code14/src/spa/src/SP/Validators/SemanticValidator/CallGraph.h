#pragma once

#include <unordered_map>
#include <unordered_set>

#include "SP/AST/Nodes/CallNode.h"
#include "SP/AST/Nodes/ProcedureNode.h"

class CallGraph {
private:
    std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> nodes;
    std::unordered_map<std::string, std::vector<std::string>> edges;

    /**
     * Recursive depth-first search to detect cycles in the call graph.
     * @param currentProcedure
     * @param visited
     * @param currentPath
     * @return
     */
    bool hasCycleDFS(const std::string &currentProcedure,
                     std::unordered_set<std::string> &visited,
                     std::unordered_set<std::string> &currentPath);

public:
    CallGraph();
    void addNode(const std::shared_ptr<ProcedureNode> &node);
    void addEdge(const std::string &caller, const std::string &callee);
    bool hasCycle();
};