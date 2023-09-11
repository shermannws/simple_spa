#pragma once

#include "Pkb.h"

Pkb::Pkb() {
    std::shared_ptr<AssignmentPatternStore> assignmentPatternStore = std::make_shared<AssignmentPatternStore>(AssignmentPatternStore());
    this->assignmentManager = std::make_shared<AssignmentManager>(
            AssignmentManager(
                    assignmentPatternStore
            )
    );
    this->constantStore = std::make_shared<ConstantStore>(ConstantStore());
    this->procedureStore = std::make_shared<ProcedureStore>(ProcedureStore());
    this->statementStore = std::make_shared<StatementStore>(StatementStore());
    this->variableStore = std::make_shared<VariableStore>(VariableStore());
    this->followsRelationshipStore = std::make_shared<FollowsRelationshipStore>(FollowsRelationshipStore());
    this->usesRelationshipStore = std::make_shared<UsesRelationshipStore>(UsesRelationshipStore());
    this->usesRelationshipManager = std::make_shared<UsesRelationshipManager>(UsesRelationshipManager(this->usesRelationshipStore));
    this->pkbReaderManager = std::make_shared<PkbReaderManager>(
            PkbReaderManager(
                    this->assignmentManager,
                    this->constantStore,
                    this->procedureStore,
                    this->statementStore,
                    this->variableStore,
                    this->followsRelationshipStore,
                    this->usesRelationshipManager
            )
    );
};

std::shared_ptr<PkbReader> Pkb::createPkbReader() {
    return std::make_shared<PkbReader>(
            PkbReader(
                    this->pkbReaderManager
            )
    );
};

std::shared_ptr<PkbWriter> Pkb::createPkbWriter() {
    return std::make_shared<PkbWriter>(
            PkbWriter(
                    this->assignmentManager,
                    this->constantStore,
                    this->procedureStore,
                    this->statementStore,
                    this->variableStore,
                    this->followsRelationshipStore,
                    this->usesRelationshipStore
            )
    );
};