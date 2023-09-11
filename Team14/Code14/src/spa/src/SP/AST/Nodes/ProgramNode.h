#pragma once

#include <vector>

#include "ASTNode.h"
#include "ProcedureNode.h"

class ProgramNode; // forward declaration
class ProgramNodeVisitor {
public:
    virtual void visitProgramNode(std::shared_ptr<ProgramNode> node) const = 0;
};

class ProgramNode : public ASTNode {
private:
    std::vector<std::shared_ptr<ProcedureNode>> procedures;
public:
    explicit ProgramNode(std::vector<std::shared_ptr<ProcedureNode>> procedures);
    std::vector<std::shared_ptr<ProcedureNode>> getProcedures();
    void accept(std::shared_ptr<DesignExtractorVisitor> visitor) override;
    std::vector<std::shared_ptr<ASTNode>> getAllChildNodes() override;
};
