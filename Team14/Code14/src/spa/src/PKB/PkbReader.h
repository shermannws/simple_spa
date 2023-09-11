#pragma once

#include <memory>

#include "PKB/Managers/PkbReaderManager.h"

class PkbReader {
private:
    std::shared_ptr<PkbReaderManager> readerManager;
public:
    PkbReader(std::shared_ptr<PkbReaderManager> readerManager);

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllAssign() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllVariables() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllConstants() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllProcedures() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllStatements() const;

    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>> getAllUsesAssignVariablePair() const;

    std::shared_ptr<std::vector<std::shared_ptr<Entity>>> getAllUsesAssignByVariable(std::shared_ptr<Variable> variable) const;

    std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>> getAllFollowsStatementPair() const;

    std::shared_ptr<Entity> getFollowsByStatement(std::shared_ptr<Statement> statement) const; // Returns statement followed by (ahead) given statement

    std::shared_ptr<Entity> getFollowingStatement(std::shared_ptr<Statement> statement) const; // Returns statement following (behind) given statement

    bool getIsFollows(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2) const; // Returns true if statement1 follows statement2
};