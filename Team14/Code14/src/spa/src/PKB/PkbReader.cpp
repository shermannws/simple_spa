#pragma once

#include "PkbReader.h"

PkbReader::PkbReader(
    std::shared_ptr<PkbReaderManager> readerManager
) : readerManager(readerManager) {}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReader::getAllAssign() const {
    return this->readerManager->getAllAssign();
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>>  PkbReader::getAllVariables() const {
    return this->readerManager->getAllVariables();
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReader::getAllConstants() const {
    return this->readerManager->getAllConstants();
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReader::getAllProcedures() const {
    return this->readerManager->getAllProcedures();
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReader::getAllStatements() const {
    return this->readerManager->getAllStatements();
}

std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>> PkbReader::getAllUsesAssignVariablePair() const {
    return this->readerManager->getAllUsesAssignVariablePair();
}

std::shared_ptr<std::vector<std::shared_ptr<Entity>>> PkbReader::getAllUsesAssignByVariable(std::shared_ptr<Variable> variable) const {
    return this->readerManager->getAllUsesAssignByVariable(variable);
}

std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::shared_ptr<Entity>>>>> PkbReader::getAllFollowsStatementPair() const {
    return this->readerManager->getAllFollowsStatementPair();
}

std::shared_ptr<Entity> PkbReader::getFollowsByStatement(std::shared_ptr<Statement> statement) const {
    return this->readerManager->getFollowsByStatement(statement);
}

std::shared_ptr<Entity>  PkbReader::getFollowingStatement(std::shared_ptr<Statement> statement) const {
    return this->readerManager->getFollowingStatement(statement);
}

bool PkbReader::getIsFollows(std::shared_ptr<Statement> statement1, std::shared_ptr<Statement> statement2) const {
    return this->readerManager->getIsFollows(statement1, statement2);
}