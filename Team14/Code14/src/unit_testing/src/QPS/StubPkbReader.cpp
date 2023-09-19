#include "StubPkbReader.h"

StubPkbReader::StubPkbReader() {}

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

// Pattern queries i.e. pattern a (...,...)
// pattern a (_,_)
std::vector<Entity> StubPkbReader::getAllAssign() const {
    return std::vector<Entity>{Statement(1, StatementType::Assign),
                               Statement(2, StatementType::Assign),
                               Statement(3, StatementType::Assign)};
}

// pattern a (_, "x")
std::vector<Entity> StubPkbReader::getAssignStmtsByRhs(std::string& rhs, bool hasRhsWildCard) const {
    return std::vector<Entity>();
}

// pattern a (v, _)
std::vector<std::vector<Entity>> StubPkbReader::getAllAssignStmtVarPair() const {
    return std::vector<std::vector<Entity>>();
}

// pattern a (v, "x")
std::vector<std::vector<Entity>> StubPkbReader::getAssignStmtsVarPairByRhs(std::string& rhs, bool hasWildCard) const {
    return std::vector<std::vector<Entity>>();
}

// pattern a ("x", _)
std::vector<Entity> StubPkbReader::getAssignStmtsByLhs(Variable& lhs) const {
    return std::vector<Entity>();
}

// pattern a ("x", "x")
std::vector<Entity> StubPkbReader::getAssignStmtsByLhsRhs(Variable& lhs, std::string& rhs, bool hasRhsWildCard) const {
    return std::vector<Entity>();
}
