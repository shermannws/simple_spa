#pragma once

#include "PkbWriter.h"

#include "PKB/Relationships/FollowsRelationship.h"
#include "PKB/Relationships/UsesRelationship.h"
#include "PKB/AssignmentPatternStore/Assignment.h"

PkbWriter::PkbWriter(
        std::shared_ptr<AssignmentManager> assignmentManager,
        std::shared_ptr<ConstantStore> constantStore,
        std::shared_ptr<ProcedureStore> procedureStore,
        std::shared_ptr<StatementStore> statementStore,
        std::shared_ptr<VariableStore> variableStore,
        std::shared_ptr<FollowsRelationshipStore> followsRelationshipStore,
        std::shared_ptr<UsesRelationshipStore> usesRelationshipStore,
        std::shared_ptr<ReadStatementStore> readStmtStore,
        std::shared_ptr<PrintStatementStore> printStmtStore
) {
    this->assignmentManager = assignmentManager;
    this->constantStore = constantStore;
    this->procedureStore = procedureStore;
    this->statementStore = statementStore;
    this->variableStore = variableStore;
    this->followsRelationshipStore = followsRelationshipStore;
    this->usesRelationshipStore = usesRelationshipStore;
    this->readStmtStore = readStmtStore;
    this->printStmtStore = printStmtStore;
};

void PkbWriter::addConstant(std::shared_ptr<Constant> c) {
    this->constantStore->storeEntity(c);
}

void PkbWriter::addVariable(std::shared_ptr<Variable> v) {
    this->variableStore->storeEntity(v);
}

void PkbWriter::addProcedure(std::shared_ptr<Procedure> p) {
    this->procedureStore->storeEntity(p);
}

void PkbWriter::addPrintStatement(std::shared_ptr<Statement> s) {
    this->statementStore->storeEntity(s);
    this->printStmtStore->storeEntity(s);
}

void PkbWriter::addReadStatement(std::shared_ptr<Statement> s) {
    this->statementStore->storeEntity(s);
    this->readStmtStore->storeEntity(s);
}

void PkbWriter::addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<std::string> rhs) {
    this->statementStore->storeEntity(s);
    
    std::shared_ptr<Assignment> assignStmt = std::make_shared<Assignment>(s, lhs, rhs);
    this->assignmentManager->addAssignment(assignStmt);
}

void PkbWriter::addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2) {
    this->followsRelationshipStore->storeRelationship(std::make_shared<FollowsRelationship>(s1, s2));
}

void PkbWriter::addUsesRelalationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) {
    this->usesRelationshipStore->storeRelationship(std::make_shared<UsesRelationship>(s, v));
}