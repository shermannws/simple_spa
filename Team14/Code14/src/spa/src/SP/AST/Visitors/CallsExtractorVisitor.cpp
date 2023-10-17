#include "CallsExtractorVisitor.h"
#include "Commons/Entities/CallStatement.h"
#include "Commons/StatementFactory.h"
#include "Commons/StatementTypeFactory.h"

CallsExtractorVisitor::CallsExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter) { this->pkbWriter = pkbWriter; }

void CallsExtractorVisitor::visitCallNode(CallNode *node, std::vector<std::shared_ptr<ASTNode>> parents,
                                          std::shared_ptr<ASTNode> proc) const {

    std::shared_ptr<ProcedureNode> callerNode = std::static_pointer_cast<ProcedureNode>(proc);
    Procedure caller = Procedure(callerNode->getProcedureName());
    Procedure callee = Procedure(node->getProcedureName());
    std::shared_ptr<Procedure> callerPtr = std::make_shared<Procedure>(caller);
    std::shared_ptr<Procedure> calleePtr = std::make_shared<Procedure>(callee);

    this->pkbWriter->addCallsRelationship(callerPtr, calleePtr);

    // Add procedure to statement mapping
    std::vector<std::shared_ptr<Statement>> statementsToAdd;
    CallStatement currStatement(node->getStatementNumber(), node->getProcedureName());
    statementsToAdd.push_back(std::make_shared<CallStatement>(currStatement));

    // Add procedure to parent statements mapping for UsesP and ModifiesP
    for (auto parent = parents.rbegin(); parent != parents.rend(); parent++) {
        auto parentPtr = std::static_pointer_cast<StatementNode>(*parent);
        assert(parentPtr != nullptr);
        std::shared_ptr<Statement> statement = StatementFactory::createStatementFromStatementNode(parentPtr);
        statementsToAdd.push_back(statement);
    }

    this->pkbWriter->addProcedureToStatementsMap(calleePtr, statementsToAdd);
}