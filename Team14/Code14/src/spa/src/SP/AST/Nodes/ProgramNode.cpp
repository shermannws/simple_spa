#include <utility>

#include "ProgramNode.h"

ProgramNode::ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procedures) : procedures(std::move(procedures)) {}

std::vector<std::shared_ptr<ProcedureNode>> ProgramNode::getProcedures() {
    return procedures;
}

std::vector<std::shared_ptr<ASTNode>> ProgramNode::getAllChildNodes() {
    std::vector<std::shared_ptr<ASTNode>> children(procedures.begin(), procedures.end());
    return children;
}

void ProgramNode::accept(DesignExtractorVisitor& visitor) {
    if (auto programVisitor = dynamic_cast<ProgramNodeVisitor*>(&visitor)) {
        std::shared_ptr<ProgramNode> self(this);
        programVisitor->visitProgramNode(self);
    }
}