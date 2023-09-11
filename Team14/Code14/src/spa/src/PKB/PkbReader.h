#pragma once

#include <memory>

#include "PKB/Managers/PkbReaderManager.h"

class PkbReader {
private:
    std::shared_ptr<PkbReaderManager> readerManager;
public:
    PkbReader(std::shared_ptr<PkbReaderManager> readerManager);

    auto getAllAssign() const;

    auto getAllVariables() const;

    auto getAllConstants() const;

    auto getAllProcedures() const;

    auto getAllStatements() const;

    auto getAllAssignVariablePair() const;

    auto getAllAssignByVariable(std::shared_ptr<Variable> variable) const;

    auto getAllFollowsStatementPair() const;

    auto getFollowsByStatement(std::shared_ptr<Statement> statement) const; // Returns statement followed by (ahead) given statement

    auto getFollowingStatement(std::shared_ptr<Statement> statement) const; // Returns statement following (behind) given statement

    auto getIsFollows(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2) const; // Returns true if statement1 follows statement2
};