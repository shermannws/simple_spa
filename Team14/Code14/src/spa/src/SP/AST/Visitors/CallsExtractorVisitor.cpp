#include "CallsExtractorVisitor.h"

CallsExtractorVisitor::CallsExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter) {
    this->pkbWriter = pkbWriter;
}

void CallsExtractorVisitor::visitCallNode(CallNode *node, std::vector<std::shared_ptr<ASTNode>> parents,
                                          std::shared_ptr<ASTNode> proc) const {

    std::shared_ptr<ProcedureNode> callerNode = std::dynamic_pointer_cast<ProcedureNode>(proc);
    Procedure caller = Procedure(callerNode->getProcedureName());
    Procedure callee = Procedure(node->getProcedureName());

    this->pkbWriter->addCallsRelationship(
            std::make_shared<Procedure>(caller),
            std::make_shared<Procedure>(callee)
    );
}