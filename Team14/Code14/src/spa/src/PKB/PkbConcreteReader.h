#pragma once

#include <memory>

#include "PKB/Managers/PkbReaderManager.h"
#include "PkbReader.h"

class PkbConcreteReader : public PkbReader {
private:
    std::shared_ptr<PkbReaderManager> readerManager;
public:
    PkbConcreteReader(std::shared_ptr<PkbReaderManager> readerManager);

    std::vector<Entity> getAllAssign() const override;

    std::vector<Entity> getAllVariables() const override;

    std::vector<Entity> getAllConstants() const override;

    std::vector<Entity> getAllProcedures() const override;

    std::vector<Entity> getAllStatements() const override;

    std::vector<std::vector<Entity>> getAllUsesAssignVariablePair() const override;

    std::vector<Entity> getAllUsesAssignByVariable(Variable& variable) const override;

    std::vector<std::vector<Entity>> getAllFollowsStatementPair() const override;

    // Returns statement followed by (ahead) given statement
    std::vector<Entity> getFollowsByStatement(Statement& statement) const override;

    // Returns statement following (behind) given statement
    std::vector<Entity> getFollowingStatement(Statement& statement) const override;

    // Returns true if statement1 follows statement2
    bool getIsFollows(Statement& statement1, Statement& statement2) const override;

    std::vector<Entity> getAssignPatternStatements(Variable& variable, std::string& pattern, bool hasExpressionWildCard) const override;
};