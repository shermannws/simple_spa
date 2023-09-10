#pragma once

#include <memory>

#include "PKB/Managers/AssignmentManager.h"
#include "PKB/AssignmentPatternStore/AssignmentPatternStore.h"
#include "PKB/EntityStorage/ConstantStore.h"
#include "PKB/EntityStorage/ProcedureStore.h"
#include "PKB/EntityStorage/StatementStore.h"
#include "PKB/EntityStorage/VariableStore.h"
#include "PKB/RelationshipStorage/FollowsRelationshipStore.h"
#include "PKB/RelationshipStorage/UsesRelationshipStore.h"
#include "PKB/Managers/UsesRelationshipManager.h"
#include "PKB/Managers/PkbReaderManager.h"
#include "PKB/PkbReader.h"
#include "PKB/PkbWriter.h"

class Pkb {
private:
    std::shared_ptr<AssignmentManager> assignmentManager;

    std::shared_ptr<ConstantStore> constantStore;
    std::shared_ptr<ProcedureStore> procedureStore;
    std::shared_ptr<StatementStore> statementStore;
    std::shared_ptr<VariableStore> variableStore;

    std::shared_ptr<FollowsRelationshipStore> followsRelationshipStore;
    std::shared_ptr<UsesRelationshipStore> usesRelationshipStore;
    std::shared_ptr<UsesRelationshipManager> usesRelationshipManager;
    std::shared_ptr<PkbReaderManager> pkbReaderManager;
public:
    Pkb();

    std::shared_ptr<PkbReader> createPkbReader();

    std::shared_ptr<PkbWriter> createPkbWriter();
};