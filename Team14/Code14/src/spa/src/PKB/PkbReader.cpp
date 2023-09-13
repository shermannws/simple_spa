#pragma once

#include "PkbReader.h"

PkbReader::PkbReader(
        std::shared_ptr<PkbReaderManager> readerManager
) {
    this->readerManager = readerManager;
}

std::vector<Entity> PkbReader::getAllAssign() const {
    return this->readerManager->getAllAssign();
}

std::vector<Entity>  PkbReader::getAllVariables() const {
    return this->readerManager->getAllVariables();
}

std::vector<Entity> PkbReader::getAllConstants() const {
    return this->readerManager->getAllConstants();
}

std::vector<Entity> PkbReader::getAllProcedures() const {
    return this->readerManager->getAllProcedures();
}

std::vector<Entity> PkbReader::getAllStatements() const {
    return this->readerManager->getAllStatements();
}

std::vector<std::vector<Entity>> PkbReader::getAllUsesAssignVariablePair() const {
    return this->readerManager->getAllUsesAssignVariablePair();
}

std::vector<Entity> PkbReader::getAllUsesAssignByVariable(Variable& variable) const {
    return this->readerManager->getAllUsesAssignByVariable(variable);
}

std::vector<std::vector<Entity>> PkbReader::getAllFollowsStatementPair() const {
    return this->readerManager->getAllFollowsStatementPair();
}

std::vector<Entity> PkbReader::getFollowsByStatement(Statement& statement) const {
    return this->readerManager->getFollowsByStatement(statement);
}

std::vector<Entity> PkbReader::getFollowingStatement(Statement& statement) const {
    return this->readerManager->getFollowingStatement(statement);
}

bool PkbReader::getIsFollows(Statement& statement1, Statement& statement2) const {
    return this->readerManager->getIsFollows(statement1, statement2);
}