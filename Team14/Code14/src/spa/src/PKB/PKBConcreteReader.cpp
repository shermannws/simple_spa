#pragma once

#include "PkbConcreteReader.h"

PkbConcreteReader::PkbConcreteReader(
    std::shared_ptr<PkbReaderManager> readerManager
) {
    this->readerManager = readerManager;
}

std::vector<Entity> PkbConcreteReader::getAllAssign() const {
    return this->readerManager->getAllAssign();
}

std::vector<Entity> PkbConcreteReader::getAllVariables() const {
    return this->readerManager->getAllVariables();
}

std::vector<Entity> PkbConcreteReader::getAllConstants() const {
    return this->readerManager->getAllConstants();
}

std::vector<Entity> PkbConcreteReader::getAllProcedures() const {
    return this->readerManager->getAllProcedures();
}

std::vector<Entity> PkbConcreteReader::getAllStatements() const {
    return this->readerManager->getAllStatements();
}

std::vector<std::vector<Entity>> PkbConcreteReader::getAllUsesAssignVariablePair() const {
    return this->readerManager->getAllUsesAssignVariablePair();
}

std::vector<Entity> PkbConcreteReader::getAllUsesAssignByVariable(Variable& variable) const {
    return this->readerManager->getAllUsesAssignByVariable(variable);
}

std::vector<std::vector<Entity>> PkbConcreteReader::getAllFollowsStatementPair() const {
    return this->readerManager->getAllFollowsStatementPair();
}

std::vector<Entity> PkbConcreteReader::getFollowsByStatement(Statement& statement) const {
    return this->readerManager->getFollowsByStatement(statement);
}

std::vector<Entity> PkbConcreteReader::getFollowingStatement(Statement& statement) const {
    return this->readerManager->getFollowingStatement(statement);
}

bool PkbConcreteReader::getIsFollows(Statement& statement1, Statement& statement2) const {
    return this->readerManager->getIsFollows(statement1, statement2);
}

std::vector<Entity> PkbConcreteReader::getAssignPatternStatements(Variable& variable, std::string& pattern, bool hasExpressionWildCard) const {
    return this->readerManager->getAssignPatternStatements(variable, pattern, hasExpressionWildCard);
}