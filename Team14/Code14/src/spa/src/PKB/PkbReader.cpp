#include "PkbReader.h"

PkbReader::PkbReader(
        std::shared_ptr<AssignmentManager> assignmentManager,
        std::shared_ptr<ConstantStore> constantStore,
        std::shared_ptr<ProcedureStore> procedureStore,
        std::shared_ptr<StatementStore> statementStore,
        std::shared_ptr<VariableStore> variableStore,
        std::shared_ptr<FollowsRelationshipStore> followsRelationshipStore,
        std::shared_ptr<UsesRelationshipStore> usesRelationshipStore
) {
    this->assignmentManager = assignmentManager;
    this->constantStore = constantStore;
    this->procedureStore = procedureStore;
    this->statementStore = statementStore;
    this->variableStore = variableStore;
    this->followsRelationshipStore = followsRelationshipStore;
    this->usesRelationshipStore = usesRelationshipStore;
};