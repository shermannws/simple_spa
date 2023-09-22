#pragma once

#include "PkbConcreteWriter.h"

#include "PKB/Relationships/FollowsRelationship.h"
#include "PKB/Relationships/UsesRelationship.h"
#include "PKB/AssignmentPatternStore/Assignment.h"

PkbConcreteWriter::PkbConcreteWriter(
    std::shared_ptr<PkbWriterManager> writerManager
) : writerManager(writerManager) {}

void PkbConcreteWriter::addConstant(std::shared_ptr<Constant> c) {
    this->writerManager->addConstant(c);
}

void PkbConcreteWriter::addVariable(std::shared_ptr<Variable> v) {
    this->writerManager->addVariable(v);
}

void PkbConcreteWriter::addProcedure(std::shared_ptr<Procedure> p) {
    this->writerManager->addProcedure(p);
}

void PkbConcreteWriter::addPrintStatement(std::shared_ptr<Statement> s) {
    this->writerManager->addStatement(s);
}

void PkbConcreteWriter::addReadStatement(std::shared_ptr<Statement> s) {
    this->writerManager->addStatement(s);
}

void PkbConcreteWriter::addAssignStatement(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs, std::shared_ptr<Expression> rhs) {
    this->writerManager->addAssignStatement(s, lhs, rhs);
}

void PkbConcreteWriter::addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect) {
    this->writerManager->addFollowsRelationship(s1, s2, isDirect);
}

void PkbConcreteWriter::addUsesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) {
    this->writerManager->addUsesRelationship(s, v);
}

void PkbConcreteWriter::addCallStatement(std::shared_ptr<Statement> s) {
    this->writerManager->addStatement(s);
}

void PkbConcreteWriter::addIfStatement(std::shared_ptr<Statement> s) {
    this->writerManager->addStatement(s);
}

void PkbConcreteWriter::addWhileStatement(std::shared_ptr<Statement> s) {
    this->writerManager->addStatement(s);
}

void PkbConcreteWriter::addModifiesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) {
    this->writerManager->addModifiesRelationship(s, v);
}

void PkbConcreteWriter::addParentRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2, bool isDirect) {
    this->writerManager->addParentRelationship(s1, s2, isDirect);
}