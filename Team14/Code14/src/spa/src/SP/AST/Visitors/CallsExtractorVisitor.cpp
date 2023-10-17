#include "CallsExtractorVisitor.h"
#include "Commons/StatementTypeFactory.h"
#include "Commons/Entities/CallStatement.h"
#include "Commons/Entities/IfStatement.h"
#include "Commons/Entities/WhileStatement.h"

CallsExtractorVisitor::CallsExtractorVisitor(std::shared_ptr<PkbWriter> pkbWriter) {
    this->pkbWriter = pkbWriter;
}

void CallsExtractorVisitor::visitCallNode(CallNode *node, std::vector<std::shared_ptr<ASTNode>> parents,
                                          std::shared_ptr<ASTNode> proc) const {

    std::shared_ptr<ProcedureNode> callerNode = std::static_pointer_cast<ProcedureNode>(proc);
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
    CallStatement currStatement(node->getStatementNumber(), node->getProcedureName());
    statementsToAdd.push_back(std::make_shared<CallStatement>(currStatement));

    // Add procedure to parent statements mapping for UsesP and ModifiesP
    for (auto parent = parents.rbegin(); parent != parents.rend(); parent++) {
        auto parentPtr = std::static_pointer_cast<StatementNode>(*parent);
        assert(parentPtr != nullptr);
        StatementType statementType = StatementTypeFactory::getStatementTypeFrom(parentPtr->getStatementType());
        if (statementType == StatementType::If) {
            IfStatement parentStatement(parentPtr->getStatementNumber());
            statementsToAdd.push_back(std::make_shared<IfStatement>(parentStatement));
        } else {
            assert(statementType == StatementType::While);
            WhileStatement parentStatement(parentPtr->getStatementNumber());
            statementsToAdd.push_back(std::make_shared<WhileStatement>(parentStatement));
        }
    }

    this->pkbWriter->addProcedureToStatementsMap(calleePtr, statementsToAdd);
}