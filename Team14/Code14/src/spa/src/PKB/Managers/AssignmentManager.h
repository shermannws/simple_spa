#pragma once

#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <regex>

#include "PKB/AssignmentPatternStore/AssignmentPatternStore.h"
#include "Commons/Entities/Statement.h"
#include "Commons/Entities/Variable.h"
#include "Commons/AppConstants.h"

class AssignmentManager {
private:
    std::shared_ptr<AssignmentPatternStore> assignmentStore;
public:
    AssignmentManager();

    bool addAssignment(std::shared_ptr<Assignment> assignment);

    bool matchExpression(std::string& expression, std::regex& pattern, bool hasWildCard) const;

    std::regex parsePattern(std::string& pattern) const;

    bool contains(Statement& statement) const;


    // Pattern queries i.e. pattern a (...,...)
    // pattern a (_,_)
    std::vector<Entity> getAllAssignStmts() const;

    // pattern a (_, "x")
    std::vector<Entity> getAssignStmtsByRhs(std::string& rhs, bool hasRhsWildCard) const;

    // pattern a (v, _)
    std::vector<std::vector<Entity>> getAllAssignStmtVarPair() const;

    // pattern a (v, "x")
    std::vector<std::vector<Entity>> getAssignStmtsVarPairByRhs(std::string& rhs, bool hasWildCard) const;

    // pattern a ("x", _)
    std::vector<Entity> getAssignStmtsByLhs(Variable& lhs) const;

    // pattern a ("x", "x")
    std::vector<Entity> getAssignStmtsByLhsRhs(Variable& lhs, std::string& rhs, bool hasRhsWildCard) const;
};
