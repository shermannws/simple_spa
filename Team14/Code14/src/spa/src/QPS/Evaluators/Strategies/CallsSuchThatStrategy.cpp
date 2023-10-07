#include "CallsSuchThatStrategy.h"

CallsSuchThatStrategy::CallsSuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : SuchThatStrategy(std::move(pkbReader)) {}

std::shared_ptr<Result> CallsSuchThatStrategy::evaluateSynSyn(Ref &leftRef, Ref &rightRef) const {
    std::shared_ptr<Result> res = std::make_shared<Result>();
    std::unordered_map<std::string, int> indices {{leftRef.getRep(), 0}, {rightRef.getRep(), 1}};
    res->setSynIndices(indices);
    //res->setTuples(pkbReader->getCalls());
    return res;
}

std::shared_ptr<Result> CallsSuchThatStrategy::evaluateSynAny(Ref &leftRef, Ref &rightRef) const {
    // rhs = procName, wildcard
}

std::shared_ptr<Result> CallsSuchThatStrategy::evaluateAnySyn(Ref &leftRef, Ref &rightRef) const {
    //lhs = procName, wildcard
}

std::shared_ptr<Result> CallsSuchThatStrategy::evaluateBoolean(Ref &leftRef, Ref &rightRef) const {
    // both wildcard
    // both non-wc
    // RHS non-wc
    // LHS non-wc

}
