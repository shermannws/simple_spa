#pragma once

#include "PkbReader.h"

PkbReader::PkbReader(
        std::shared_ptr<PkbReaderManager> readerManager
) {
    this->readerManager = readerManager;
}

auto PkbReader::getAllAssign() const {
    return this->readerManager->getAllAssign();
}

auto PkbReader::getAllVariables() const {
    return this->readerManager->getAllVariables();
}

auto PkbReader::getAllConstants() const {
    return this->readerManager->getAllConstants();
}

auto PkbReader::getAllProcedures() const {
    return this->readerManager->getAllProcedures();
}

auto PkbReader::getAllStatements() const {
    return this->readerManager->getAllStatements();
}

auto PkbReader::getAllAssignVariablePair() const {
    return this->readerManager->getAllAssignVariablePair();
}

auto PkbReader::getAllAssignByVariable(std::shared_ptr<Variable> variable) const {
    return this->readerManager->getAllAssignByVariable(variable);
}

//auto PkbReader::getUsesAssignVariables() const {
//    return this->usesRelationshipStore->getUsesAssignVariables();
//}