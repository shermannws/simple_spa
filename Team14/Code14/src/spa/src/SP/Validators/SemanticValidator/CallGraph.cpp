#include "CallGraph.h"

CallGraph::CallGraph() = default;

void CallGraph::addNode(const std::shared_ptr<ProcedureNode> &node) { nodes[node->getProcedureName()] = node; }

void CallGraph::addEdge(const ProcedureName &caller, const ProcedureName &callee) { edges[caller].push_back(callee); }

bool CallGraph::hasCycle() {
    std::unordered_set<ProcedureName> visited;
    std::unordered_set<ProcedureName> currentPath;

    for (const auto &node: nodes) {
        const ProcedureName &procedureName = node.first;
        if (visited.count(procedureName) == 0) {
            if (hasCycleDFS(procedureName, visited, currentPath)) { return true; }
        }
    }
    return false;
}

bool CallGraph::hasCycleDFS(const ProcedureName &currentProcedure, std::unordered_set<ProcedureName> &visited,
                            std::unordered_set<ProcedureName> &currentPath) {
    visited.insert(currentProcedure);
    currentPath.insert(currentProcedure);

    for (const ProcedureName &callee: edges[currentProcedure]) {
        if (currentPath.count(callee) > 0) { return true; }
        if (visited.count(callee) == 0 && hasCycleDFS(callee, visited, currentPath)) { return true; }
    }

    currentPath.erase(currentProcedure);
    return false;
}
