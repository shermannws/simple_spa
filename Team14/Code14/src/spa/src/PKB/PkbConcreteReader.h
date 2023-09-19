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

    std::vector<std::vector<Entity>> getFollowsPair(StatementType formerType, StatementType latterType) const override;

    std::vector<std::vector<Entity>> getFollowsStarPair(StatementType formerType, StatementType latterType) const override;

    std::vector<Entity> getFollowsTypeStmt(StatementType type, Statement& statement) const override;

    std::vector<Entity> getFollowsStarTypeStmt(StatementType type, Statement& statement) const override;

    std::vector<Entity> getFollowsTypeWildcard(StatementType type) const override;

    std::vector<Entity> getFollowsStarTypeWildcard(StatementType type) const override;

    std::vector<Entity> getFollowsStmtType(Statement& statement, StatementType type) const override;

    std::vector<Entity> getFollowsStarStmtType(Statement& statement, StatementType type) const override;

    std::vector<Entity> getFollowsWildcardType(StatementType type) const override;

    std::vector<Entity> getFollowsStarWildcardType(StatementType type) const override;

    bool isFollows(Statement& statement1, Statement& statement2) const override;

    bool isFollowsStar(Statement& statement1, Statement& statement2) const override;

    bool hasFollows() const override;

};