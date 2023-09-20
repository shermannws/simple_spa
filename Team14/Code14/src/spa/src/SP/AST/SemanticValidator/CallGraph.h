#pragma once

#include <unordered_map>
#include <set>

#include "SP/AST/Nodes/ProcedureNode.h"
#include "SP/AST/Nodes/CallNode.h"

class CallGraph {
private:
    std::unordered_map<std::string, std::shared_ptr<ProcedureNode>> nodes;
    std::unordered_map<std::string, std::vector<std::string>> edges;
    bool hasCycleDFS(const std::string& currentProcedure, std::set<std::string>& visited, std::set<std::string>& currentPath);

public:
    CallGraph();
    void addNode(const std::shared_ptr<ProcedureNode>& node);
    void addEdge(const std::string&caller, const std::string& callee);
    bool hasCycle();
};