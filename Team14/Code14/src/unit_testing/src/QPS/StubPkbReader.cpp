#include "StubPkbReader.h"

StubPkbReader::StubPkbReader() {}

std::vector<Entity> StubPkbReader::getAllAssign() const {
    return std::vector<Entity>{Statement(1, StatementType::Assign),
                               Statement(2, StatementType::Assign),
                               Statement(3, StatementType::Assign)};
}

std::vector<Entity> StubPkbReader::getAllVariables() const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getAllConstants() const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getAllProcedures() const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getAllStatements() const {
    return std::vector<Entity>();
}

std::vector<std::vector<Entity>> StubPkbReader::getAllUsesAssignVariablePair() const {
    return std::vector<std::vector<Entity>>();
}

std::vector<Entity> StubPkbReader::getAllUsesAssignByVariable(Variable& variable) const {
    return std::vector<Entity>();
}

std::vector<std::vector<Entity>> StubPkbReader::getFollowsPair(StatementType formerType, StatementType latterType) const {
    return std::vector<std::vector<Entity>>();
}

std::vector<std::vector<Entity>> StubPkbReader::getFollowsStarPair(StatementType formerType, StatementType latterType) const {
    return std::vector<std::vector<Entity>>();
}

std::vector<Entity> StubPkbReader::getFollowsTypeStmt(StatementType type, Statement& statement) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStarTypeStmt(StatementType type, Statement& statement) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsTypeWildcard(StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStarTypeWildcard(StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStmtType(Statement& statement, StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStarStmtType(Statement& statement, StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsWildcardType(StatementType type) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowsStarWildcardType(StatementType type) const {
    return std::vector<Entity>();
}

bool StubPkbReader::isFollows(Statement& statement1, Statement& statement2) const {
    return false;
}

bool StubPkbReader::isFollowsStar(Statement& statement1, Statement& statement2) const  {
    return false;
}

bool StubPkbReader::hasFollows() const {
    return false;
}
