#include <utility>

#include "ProgramNode.h"

ProgramNode::ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procedures) : procedures(std::move(procedures)) {}

std::vector<std::shared_ptr<ProcedureNode>> ProgramNode::getProcedures() { return procedures; }

std::vector<std::shared_ptr<ASTNode>> ProgramNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children(procedures.begin(), procedures.end());
    return children;
}

void ProgramNode::accept(std::shared_ptr<DesignExtractorVisitor> visitor,
                         std::vector<std::shared_ptr<Statement>> parents, std::shared_ptr<Procedure> proc) {
    if (auto programVisitor = std::dynamic_pointer_cast<ProgramNodeVisitor>(visitor)) {
        programVisitor->visitProgramNode(std::enable_shared_from_this<ProgramNode>::shared_from_this(), parents, proc);
    }
}