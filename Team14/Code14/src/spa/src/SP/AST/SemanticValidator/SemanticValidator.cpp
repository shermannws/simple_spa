#include "SemanticValidator.h"
#include "CallGraph.h"

class SemanticError : public std::runtime_error {
public:
    SemanticError(const std::string& message) : std::runtime_error(message) {}
};

SemanticValidator::SemanticValidator() = default;

/**
 * Semantically validate current program
 * 1. A program cannot have two procedures with the same name.
 * 2. A procedure cannot call a non-existing procedure.
 * 3. Recursive and cyclic calls are not allowed. i.e. A-->B-->C-->A or A-->A
 * @param root
 */
void SemanticValidator::validate(std::shared_ptr<ProgramNode> root) {

    std::vector<std::shared_ptr<ProcedureNode>> procedures = root->getProcedures();
    std::set<std::string> procedureNames;

    // insert procedure names into set and check for duplicates
    for (const auto& procedure : procedures) {
        std::string name = procedure->getProcedureName();

        if (procedureNames.count(name) > 0) {
            throw SemanticError("Semantic error: Repeated procedure names detected");
        } else {
            procedureNames.insert(name);
        }
    }

    // call graph
    CallGraph callGraph;
    std::shared_ptr<ProcedureNode> currProcedureNode;

    // -----------------------------------
    // Same DFS algorithm used in traverser
    frontier.push(root);
    while (!frontier.empty()) {
        std::shared_ptr<ASTNode> current = frontier.top();

        frontier.pop();

        // Create CallGraph
        if (auto procedureNode = std::dynamic_pointer_cast<ProcedureNode>(current)) {
            currProcedureNode = procedureNode;
            callGraph.addNode(procedureNode);
        } else if (auto callNode = std::dynamic_pointer_cast<CallNode>(current)) {
            if (procedureNames.count(callNode->getProcedureName()) == 0) {
                throw SemanticError("Semantic error: Called non-existing procedure");
            }
            callGraph.addEdge(currProcedureNode->getProcedureName(), callNode->getProcedureName());
        }

        // Add child of current node into the frontier
        std::vector<std::shared_ptr<ASTNode>> childrenOfCurrent = current->getAllChildNodes();
        for (auto it = childrenOfCurrent.rbegin(); it != childrenOfCurrent.rend(); it++) {
            frontier.push(*it);
        }
    }

    if (callGraph.hasCycle()) {
        throw SemanticError("Semantic error: Cyclic procedure calls detected");
    }
    // End of DFS algorithm
    // -----------------------------------
}
