#pragma once

#include <memory>

#include "PKB/Managers/PkbReaderManager.h"

class PkbReader {
private:
    std::shared_ptr<PkbReaderManager> readerManager;
public:
    PkbReader(std::shared_ptr<PkbReaderManager> readerManager);

    std::vector<Entity> getAllAssign() const;

    std::vector<Entity> getAllVariables() const;

    std::vector<Entity> getAllConstants() const;

    std::vector<Entity> getAllProcedures() const;

    std::vector<Entity> getAllStatements() const;

    std::vector<std::vector<Entity>> getAllUsesAssignVariablePair() const;

    std::vector<Entity> getAllUsesAssignByVariable(Variable& variable) const;

    std::vector<std::vector<Entity>> getAllFollowsStatementPair() const;

    std::vector<Entity> getFollowsByStatement(Statement& statement) const; // Returns statement followed by (ahead) given statement

    std::vector<Entity> getFollowingStatement(Statement& statement) const; // Returns statement following (behind) given statement

    bool getIsFollows(Statement& statement1, Statement& statement2) const; // Returns true if statement1 follows statement2
};