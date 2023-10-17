#include <utility>

#include "ProgramNode.h"

ProgramNode::ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procedures)
    : procedures(std::move(procedures)) {}

std::vector<std::shared_ptr<ProcedureNode>> ProgramNode::getProcedures() {
    return procedures;
}

std::vector<std::shared_ptr<ASTNode>> ProgramNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children(procedures.begin(),
                                                   procedures.end());
    return children;
}

void ProgramNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor,
                         std::vector<std::shared_ptr<ASTNode>> parents,
                         std::shared_ptr<ASTNode> proc) {
    if (auto programVisitor =
                std::dynamic_pointer_cast<ProgramNodeVisitor>(visitor)) {
        programVisitor->visitProgramNode(this, parents, proc);
    }
}