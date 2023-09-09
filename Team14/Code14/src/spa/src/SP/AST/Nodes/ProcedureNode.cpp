#include "ProcedureNode.h"

void ProcedureNode::accept(DesignExtractorVisitor& visitor) {
    visitor.visitProcedureNode();
}
