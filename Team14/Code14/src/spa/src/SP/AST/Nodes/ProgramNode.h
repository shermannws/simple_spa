#pragma once

#include <vector>

#include "ASTNode.h"
#include "ProcedureNode.h"

class ProgramNode : public ASTNode {
private:
    std::vector<std::shared_ptr<ProcedureNode>> procedures;
public:
    explicit ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procedures);
    std::vector<std::shared_ptr<ProcedureNode>> getProcedures();
    void accept(DesignExtractorVisitor& visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
