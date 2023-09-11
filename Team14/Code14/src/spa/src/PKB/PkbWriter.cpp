#pragma once

#include "PkbWriter.h"

#include "PKB/Relationships/FollowsRelationship.h"
#include "PKB/Relationships/UsesRelationship.h"
#include "PKB/AssignmentPatternStore/Assignment.h"

PkbWriter::PkbWriter(
        std::shared_ptr<PkbWriterManager> writerManager
) {
    this->writerManager = writerManager;
};

void PkbWriter::addConstant(std::shared_ptr<Constant> c) {
    this->writerManager->addConstant(c);
}

void PkbWriter::addVariable(std::shared_ptr<Variable> v) {
    this->writerManager->addVariable(v);
}

void PkbWriter::addProcedure(std::shared_ptr<Procedure> p) {
    this->writerManager->addProcedure(p);
}

void PkbWriter::addPrintStatement(std::shared_ptr<Statement> s) {
    this->writerManager->addPrintStatement(s);
}

void PkbWriter::addReadStatement(std::shared_ptr<Statement> s) {
    this->writerManager->addReadStatement(s);
}

void PkbWriter::addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<std::string> rhs) {
    this->writerManager->addAssignStatement(s, lhs, rhs);
}

void PkbWriter::addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2) {
    this->writerManager->addFollowsRelationship(s1, s2);
}

void PkbWriter::addUsesRelalationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) {
    this->writerManager->addUsesRelalationship(s, v);
}