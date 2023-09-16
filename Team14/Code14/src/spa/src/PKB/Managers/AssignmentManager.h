#pragma once

#include <memory>
#include <vector>
#include <string>

#include "PKB/AssignmentPatternStore/AssignmentPatternStore.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

class AssignmentManager {
private:
    std::shared_ptr<AssignmentPatternStore> assignmentStore;
public:
    AssignmentManager();

    bool addAssignment(std::shared_ptr<Assignment> assignment);

    std::vector<Entity> getAllAssignStatements() const;

    std::vector<Entity> getAssignStatements(Variable& variable, std::string pattern) const;

    bool contains(Statement& statement) const;
};
