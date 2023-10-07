#include "CallsExtractorVisitor.h"
#include "Commons/StatementTypeFactory.h"

CallsExtractorVisitor::CallsExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter) {
    this->pkbWriter = pkbWriter;
}

void CallsExtractorVisitor::visitCallNode(CallNode *node, std::vector<std::shared_ptr<ASTNode>> parents,
                                          std::shared_ptr<ASTNode> proc) const {

    std::shared_ptr<ProcedureNode> callerNode = std::dynamic_pointer_cast<ProcedureNode>(proc);
    Procedure caller = Procedure(callerNode->getProcedureName());
    Procedure callee = Procedure(node->getProcedureName());
    std::shared_ptr<Procedure> callerPtr = std::make_shared<Procedure>(caller);
    std::shared_ptr<Procedure> calleePtr = std::make_shared<Procedure>(callee);

    this->pkbWriter->addCallsRelationship(
            callerPtr,
            calleePtr
    );

    // Add procedure to statement mapping
    std::vector<std::shared_ptr<Statement>> statementsToAdd;
    Statement currStatement = Statement(
            node->getStatementNumber(),
            StatementTypeFactory::getStatementTypeFrom(node->getStatementType())
            );
    statementsToAdd.push_back(std::make_shared<Statement>(currStatement));

    // Add procedure to parent statements mapping for UsesP and ModifiesP
    for (auto parent = parents.rbegin(); parent != parents.rend(); parent++) {
        auto parentPtr = std::dynamic_pointer_cast<StatementNode>(*parent);
        assert(parentPtr != nullptr);
        Statement parentStatement = Statement(
                parentPtr->getStatementNumber(),
                StatementTypeFactory::getStatementTypeFrom(parentPtr->getStatementType())
                );
        statementsToAdd.push_back(std::make_shared<Statement>(parentStatement));
    }

    this->pkbWriter->addProcedureToStatementsMap(calleePtr, statementsToAdd);
}