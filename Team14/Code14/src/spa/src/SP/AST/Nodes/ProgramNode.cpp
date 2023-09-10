#include <utility>

#include "ProgramNode.h"

ProgramNode::ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procedures) : procedures(std::move(procedures)) {}

void ProgramNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitProgramNode();
}
