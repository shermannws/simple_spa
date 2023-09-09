#pragma once

#include <vector>

#include "ASTNode.h"
#include "ProcedureNode.h"

class ProgramNode : public ASTNode {
public:
    std::vector<std::shared_ptr<ProcedureNode>> procedures;

    void accept(DesignExtractorVisitor& visitor) override;
};
