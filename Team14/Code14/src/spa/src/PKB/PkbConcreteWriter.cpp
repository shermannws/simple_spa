#include "PkbConcreteWriter.h"

PkbConcreteWriter::PkbConcreteWriter(std::shared_ptr<PkbWriterManager> writerManager) : writerManager(writerManager) {}

void PkbConcreteWriter::addConstant(std::shared_ptr<Constant> c) { this->writerManager->addConstant(c); }

void PkbConcreteWriter::addVariable(std::shared_ptr<Variable> v) { this->writerManager->addVariable(v); }

void PkbConcreteWriter::addProcedure(std::shared_ptr<Procedure> p) { this->writerManager->addProcedure(p); }

void PkbConcreteWriter::addPrintStatement(std::shared_ptr<Statement> s) { this->writerManager->addStatement(s); }

void PkbConcreteWriter::addReadStatement(std::shared_ptr<Statement> s) { this->writerManager->addStatement(s); }

void PkbConcreteWriter::addAssignStatement(std::shared_ptr<Statement> s) { this->writerManager->addStatement(s); }

void PkbConcreteWriter::addAssignPattern(std::shared_ptr<Statement> s, std::shared_ptr<Variable> lhs,
                                         std::shared_ptr<Expression> rhs) {
    this->writerManager->addAssignPattern(s, lhs, rhs);
}

void PkbConcreteWriter::addFollowsRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2,
                                               bool isDirect) {
    this->writerManager->addFollowsRelationship(s1, s2, isDirect);
}

void PkbConcreteWriter::addUsesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) {
    this->writerManager->addUsesRelationship(s, v);
}

void PkbConcreteWriter::addCallStatement(std::shared_ptr<Statement> s) { this->writerManager->addStatement(s); }

void PkbConcreteWriter::addIfStatement(std::shared_ptr<Statement> s) { this->writerManager->addStatement(s); }

void PkbConcreteWriter::addWhileStatement(std::shared_ptr<Statement> s) { this->writerManager->addStatement(s); }

void PkbConcreteWriter::addModifiesRelationship(std::shared_ptr<Statement> s, std::shared_ptr<Variable> v) {
    this->writerManager->addModifiesRelationship(s, v);
}

void PkbConcreteWriter::addParentRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2,
                                              bool isDirect) {
    this->writerManager->addParentRelationship(s1, s2, isDirect);
}

void PkbConcreteWriter::addCallsRelationship(std::shared_ptr<Procedure> p1, std::shared_ptr<Procedure> p2) {
    this->writerManager->addCallsRelationship(p1, p2);
}

void PkbConcreteWriter::addProcedureToStatementsMap(std::shared_ptr<Procedure> p,
                                                    std::vector<std::shared_ptr<Statement>> s) {
    this->writerManager->addProcedureToStatementsMap(p, s);
}

void PkbConcreteWriter::triggerTransitiveCalc() { this->writerManager->triggerTransitiveCalc(); }

void PkbConcreteWriter::addModifiesProcRelationship(std::shared_ptr<Procedure> p, std::shared_ptr<Variable> v) {
    this->writerManager->addModifiesProcRelationship(p, v);
}

void PkbConcreteWriter::addUsesProcRelationship(std::shared_ptr<Procedure> p, std::shared_ptr<Variable> v) {
    this->writerManager->addUsesProcRelationship(p, v);
}

void PkbConcreteWriter::addNextRelationship(std::shared_ptr<Statement> s1, std::shared_ptr<Statement> s2) {
    this->writerManager->addNextRelationship(s1, s2);
}

void PkbConcreteWriter::clearCache() { this->writerManager->clearCache(); }

void PkbConcreteWriter::addIfPattern(std::shared_ptr<Statement> s,
                                     std::shared_ptr<std::vector<std::shared_ptr<Variable>>> v) {
    this->writerManager->addIfPattern(s, v);
}

void PkbConcreteWriter::addWhilePattern(std::shared_ptr<Statement> s,
                                        std::shared_ptr<std::vector<std::shared_ptr<Variable>>> v) {
    this->writerManager->addWhilePattern(s, v);
}
