#include "CallsExtractorVisitor.h"
#include "Commons/Entities/CallStatement.h"
#include "Commons/StatementFactory.h"
#include "Commons/StatementTypeFactory.h"

CallsExtractorVisitor::CallsExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter) { this->pkbWriter = pkbWriter; }

void CallsExtractorVisitor::visitCallNode(CallNode *node, std::vector<std::shared_ptr<Statement>> parents,
                                          std::shared_ptr<ASTNode> proc) const {

    std::shared_ptr<ProcedureNode> callerNode = std::static_pointer_cast<ProcedureNode>(proc);
    Procedure caller = Procedure(callerNode->getProcedureName());
    Procedure callee = Procedure(node->getProcedureName());
    std::shared_ptr<Procedure> callerPtr = std::make_shared<Procedure>(caller);
    std::shared_ptr<Procedure> calleePtr = std::make_shared<Procedure>(callee);

    this->pkbWriter->addCallsRelationship(callerPtr, calleePtr);

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