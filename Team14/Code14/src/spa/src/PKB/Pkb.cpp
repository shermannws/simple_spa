#pragma once

#include "Pkb.h"
#include "PKB/PkbConcreteReader.h"

Pkb::Pkb() {
    this->assignmentManager = std::make_shared<AssignmentManager>(AssignmentManager());
    this->constantStore = std::make_shared<ConstantStore>(ConstantStore());
    this->procedureStore = std::make_shared<ProcedureStore>(ProcedureStore());
    this->statementStore = std::make_shared<StatementStore>(StatementStore());
    this->variableStore = std::make_shared<VariableStore>(VariableStore());
    this->followsRelationshipManager = std::make_shared<FollowsRelationshipManager>();
    this->usesRelationshipManager = std::make_shared<UsesRelationshipManager>();
    this->pkbReaderManager = std::make_shared<PkbReaderManager>(
            PkbReaderManager(
                    this->assignmentManager,
                    this->constantStore,
                    this->procedureStore,
                    this->statementStore,
                    this->variableStore,
                    this->followsRelationshipManager,
                    this->usesRelationshipManager
            )
    );
    this->pkbWriterManager = std::make_shared<PkbWriterManager>(
            PkbWriterManager(
                    this->assignmentManager,
                    this->constantStore,
                    this->procedureStore,
                    this->statementStore,
                    this->variableStore,
                    this->followsRelationshipManager,
                    this->usesRelationshipManager
            )
    );
};

std::shared_ptr<PkbReader> Pkb::createPkbReader() {
    return static_cast<std::shared_ptr<PkbReader>>(std::make_shared<PkbConcreteReader>(
        PkbConcreteReader(
            this->pkbReaderManager
        ))
    );
};

std::shared_ptr<PkbWriter> Pkb::createPkbWriter() {
    return std::make_shared<PkbWriter>(
            PkbWriter(
                    this->pkbWriterManager
            )
    );
};