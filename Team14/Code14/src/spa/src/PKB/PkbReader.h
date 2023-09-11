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
};