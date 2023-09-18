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

std::vector<std::vector<Entity>> StubPkbReader::getAllFollowsStatementPair() const {
    return std::vector<std::vector<Entity>>();
}

std::vector<Entity> StubPkbReader::getFollowsByStatement(Statement& statement) const {
    return std::vector<Entity>();
}

std::vector<Entity> StubPkbReader::getFollowingStatement(Statement& statement) const {
    return std::vector<Entity>();
}

bool StubPkbReader::getIsFollows(Statement& statement1, Statement& statement2) const {
    return false;
}

std::vector<Entity> StubPkbReader::getAssignPatternStatements(Variable& variable, std::string& pattern, bool hasExpressionWildCard) const {
    return std::vector<Entity>();
}
