#include <stack>

#include "Commons/StatementTypeFactory.h"
#include "SP/AST/Nodes/ProcedureNode.h"
#include "SP/AST/Nodes/StatementNode.h"
#include "SP/AST/Nodes/VariableNode.h"
#include "VisitorUtility.h"

void VisitorUtility::addAllVariableRelationshipFrom(
        std::shared_ptr<ASTNode> root, Statement s,
        std::vector<std::shared_ptr<ASTNode>> parents,
        std::function<void(std::shared_ptr<Statement>,
                           std::shared_ptr<Variable>)>
                funcStmt,
        std::shared_ptr<ASTNode> proc,
        std::function<void(std::shared_ptr<Procedure>,
                           std::shared_ptr<Variable>)>
                funcProc) {
    std::stack<std::shared_ptr<ASTNode>> frontier;
    frontier.push(root);

    while (!frontier.empty()) {
        std::shared_ptr<ASTNode> current = frontier.top();
        frontier.pop();

        VariableNode *ptr = dynamic_cast<VariableNode *>(current.get());
        if (ptr) {
            // Add stmt-var relationships
            // Add direct relationship
            funcStmt(std::make_shared<Statement>(s),
                     std::make_shared<Variable>(ptr->getVarName()));
            // Add indirect relationships between parent and variable
            for (auto parent: parents) {
                StatementNode *parentPtr =
                        dynamic_cast<StatementNode *>(parent.get());
                assert(parentPtr != nullptr);
                funcStmt(std::make_shared<Statement>(
                                 parentPtr->getStatementNumber(),
                                 StatementTypeFactory::getStatementTypeFrom(
                                         parentPtr->getStatementType())),
                         std::make_shared<Variable>(ptr->getVarName()));
            }

            // Add proc-var relationships
            ProcedureNode *procedurePtr =
                    dynamic_cast<ProcedureNode *>(proc.get());
            assert(procedurePtr != nullptr);
            funcProc(std::make_shared<Procedure>(
                             procedurePtr->getProcedureName()),
                     std::make_shared<Variable>(ptr->getVarName()));
        }

        std::vector<std::shared_ptr<ASTNode>> childrenOfCurrent =
                current->getAllChildNodes();
        for (auto it = childrenOfCurrent.rbegin();
             it != childrenOfCurrent.rend(); it++) {
            frontier.push(*it);
        }
    }
}