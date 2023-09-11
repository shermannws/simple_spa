#include <utility>

#include "ProgramNode.h"

ProgramNode::ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procedures) : procedures(std::move(procedures)) {}

std::vector<std::shared_ptr<ProcedureNode>> ProgramNode::getProcedures() {
    return procedures;
}

void ProgramNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitProgramNode();
}
