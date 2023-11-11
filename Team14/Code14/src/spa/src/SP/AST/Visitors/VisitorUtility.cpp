#include <stack>

#include "Commons/EntityFactory.h"
#include "SP/AST/Nodes/StatementNode.h"
#include "SP/AST/Nodes/VariableNode.h"
#include "VisitorUtility.h"

VisitorUtilsParams::VisitorUtilsParams(std::shared_ptr<ASTNode> subtree) { this->subtree = subtree; }

void VisitorUtilsParams::setStatement(std::shared_ptr<Statement> statement) { this->statement = statement; }

void VisitorUtilsParams::setParents(std::vector<std::shared_ptr<Statement>> parents) { this->parents = parents; }

void VisitorUtilsParams::setProcedure(std::shared_ptr<Procedure> procedure) { this->procedure = procedure; }

std::shared_ptr<ASTNode> VisitorUtilsParams::getSubtree() const { return subtree; }

std::shared_ptr<Statement> VisitorUtilsParams::getStatement() const { return statement; }

std::vector<std::shared_ptr<Statement>> VisitorUtilsParams::getParents() const { return parents; }

std::shared_ptr<Procedure> VisitorUtilsParams::getProcedure() const { return procedure; }

VisitorUtility::VisitorUtility(StmtVarFunc &funcStmt, ProcVarFunc &funcProc) {
    this->funcStmt = funcStmt;
    this->funcProc = funcProc;
}

void VisitorUtility::addAllVariableRelationship(VisitorUtilsParams &params) const {
    std::stack<std::shared_ptr<ASTNode>> frontier;
    frontier.push(params.getSubtree());


    while (!frontier.empty()) {
        std::shared_ptr<ASTNode> current = frontier.top();
        frontier.pop();

        auto variableNodePtr = std::dynamic_pointer_cast<VariableNode>(current);
        if (variableNodePtr) {
            // Add stmt-var relationships direct relationships
            auto variable = EntityFactory::createVariable(variableNodePtr->getVarName());
            funcStmt(params.getStatement(), variable);

            // Add indirect relationships between parent and variable
            for (const auto &parent: params.getParents()) { funcStmt(parent, variable); }

            // Add proc-var relationships
            funcProc(params.getProcedure(), variable);
        }

        std::vector<std::shared_ptr<ASTNode>> childrenOfCurrent = current->getAllChildNodes();
        for (auto it = childrenOfCurrent.rbegin(); it != childrenOfCurrent.rend(); it++) { frontier.push(*it); }
    }
}