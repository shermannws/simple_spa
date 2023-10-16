#include "CallGraph.h"

CallGraph::CallGraph() = default;

void CallGraph::addNode(const std::shared_ptr<ProcedureNode> &node) {
    nodes[node->getProcedureName()] = node;
}

void CallGraph::addEdge(const std::string &caller, const std::string &callee) {
    edges[caller].push_back(callee);
}

bool CallGraph::hasCycle() {
    std::unordered_set<std::string> visited;
    std::unordered_set<std::string> currentPath;

    for (const auto &node: nodes) {
        const std::string &procedureName = node.first;
        if (visited.count(procedureName) == 0) {
            if (hasCycleDFS(procedureName, visited, currentPath)) {
                return true;
            }
        }
    }
    return false;
}

bool CallGraph::hasCycleDFS(const std::string &currentProcedure,
                            std::unordered_set<std::string> &visited,
                            std::unordered_set<std::string> &currentPath) {
    visited.insert(currentProcedure);
    currentPath.insert(currentProcedure);

    for (const std::string &callee: edges[currentProcedure]) {
        if (currentPath.count(callee) > 0) { return true; }
        if (visited.count(callee) == 0 &&
            hasCycleDFS(callee, visited, currentPath)) {
            return true;
        }
    }

    currentPath.erase(currentProcedure);
    return false;
}
