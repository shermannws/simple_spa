#include "CallsExtractorVisitor.h"
#include "Commons/Entities/CallStatement.h"
#include "Commons/StatementFactory.h"
#include "Commons/StatementTypeFactory.h"

CallsExtractorVisitor::CallsExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter) { this->pkbWriter = pkbWriter; }

void CallsExtractorVisitor::visitCallNode(CallNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                          std::shared_ptr<Procedure> proc) const {

    Procedure callee = Procedure(node->getProcedureName());
    std::shared_ptr<Procedure> calleePtr = std::make_shared<Procedure>(callee);

    this->pkbWriter->addCallsRelationship(proc, calleePtr);

    // Add procedure to statement mapping
    std::vector<std::shared_ptr<Statement>> statementsToAdd;
    auto currStatement = std::make_shared<CallStatement>(node->getStatementNumber(), node->getProcedureName());
    statementsToAdd.push_back(currStatement);

    // Add procedure to parent statements mapping for UsesP and ModifiesP
    for (auto parent = parents.rbegin(); parent != parents.rend(); parent++) {
        statementsToAdd.push_back(*parent);
    }

    this->pkbWriter->addProcedureToStatementsMap(calleePtr, statementsToAdd);
}