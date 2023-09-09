#pragma once

#include <memory>
#include <vector>
#include <string>

#include "AssignmentPatternStore.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"

class AssignmentManager {
private:
    std::shared_ptr<AssignmentPatternStore> assignmentStore;
public:
    AssignmentManager(std::shared_ptr<AssignmentPatternStore> assignmentStore);

    bool addAssignment(std::shared_ptr<Assignment> assignment);

    std::shared_ptr<std::vector<std::shared_ptr<Statement>>> getAssignStatements(std::shared_ptr<Variable> variable, std::string pattern) const;
};
