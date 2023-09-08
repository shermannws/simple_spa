#include "ProgramNode.h"

void ProgramNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitProgramNode();
}
