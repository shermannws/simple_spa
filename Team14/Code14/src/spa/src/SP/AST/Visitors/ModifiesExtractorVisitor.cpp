#include <functional>

#include "Commons/Entities/Statement.h"
#include "Commons/Entities/StatementType.h"
#include "Commons/Entities/Variable.h"
#include "ModifiesExtractorVisitor.h"
#include "VisitorUtility.h"

ModifiesExtractorVisitor::ModifiesExtractorVisitor(
        std::shared_ptr<PkbWriter> writer) {
    this->pkbWriter = writer;
    this->funcStmt = [this](std::shared_ptr<Statement> s,
                            std::shared_ptr<Variable> v) -> void {
        this->pkbWriter->addModifiesRelationship(s, v);
    };
    this->funcProc = [this](std::shared_ptr<Procedure> p,
                            std::shared_ptr<Variable> v) -> void {
        this->pkbWriter->addModifiesProcRelationship(p, v);
    };
}

void ModifiesExtractorVisitor::visitAssignNode(
        AssignNode *node, std::vector<std::shared_ptr<ASTNode>> parents,
        std::shared_ptr<ASTNode> proc) const {
    return VisitorUtility::addAllVariableRelationshipFrom(
            node->getVar(),
            Statement(node->getStatementNumber(), StatementType::Assign),
            parents, this->funcStmt, proc, this->funcProc);
}

void ModifiesExtractorVisitor::visitReadNode(
        ReadNode *node, std::vector<std::shared_ptr<ASTNode>> parents,
        std::shared_ptr<ASTNode> proc) const {
    return VisitorUtility::addAllVariableRelationshipFrom(
            node->getVar(),
            Statement(node->getStatementNumber(), StatementType::Read), parents,
            this->funcStmt, proc, this->funcProc);
}
