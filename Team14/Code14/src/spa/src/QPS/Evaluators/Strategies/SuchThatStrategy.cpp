#include "SuchThatStrategy.h"
#include "QPS/Clauses/SuchThatClause.h"

Result SuchThatStrategy::evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const {
    std::shared_ptr<SuchThatClause> suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    Ref leftRef = suchThat->getFirstParam();
    Ref rightRef = suchThat->getSecondParam();
    Result res;
    // TODO: check interface segregation principle, make it non pure virtual?
    // TODO: make pkbReader a field of Strategies?
    if (leftRef.isSynonym() && rightRef.isSynonym()) {
        res = evaluateSynSyn(pkbReader, leftRef, rightRef);
    } else if (leftRef.isSynonym() && rightRef.isInteger()) {
        res = evaluateSynInt(pkbReader, leftRef, rightRef);
    } else if (leftRef.isSynonym() && rightRef.isWildcard()) {
        res = evaluateSynWild(pkbReader, leftRef, rightRef);
    } else if (leftRef.isSynonym() && rightRef.isIdent()) {
        res = evaluateSynIdent(pkbReader, leftRef, rightRef);
    } else if (leftRef.isInteger() && rightRef.isSynonym()) {
        res = evaluateIntSyn(pkbReader, leftRef, rightRef);
    } else if (leftRef.isInteger() && rightRef.isIdent()) {
        res = evaluateIntIdent(pkbReader, leftRef, rightRef);
    } else if (leftRef.isWildcard() && rightRef.isSynonym()) {
        res = evaluateWildSyn(pkbReader,leftRef, rightRef);
    } else if (leftRef.isInteger() && rightRef.isWildcard()) {
        res = evaluateIntWild(pkbReader,leftRef, rightRef);
    } else if (leftRef.isWildcard() && rightRef.isInteger()) {
        res = evaluateWildInt(pkbReader,leftRef, rightRef);
    } else if (leftRef.isInteger() && rightRef.isInteger()) {
        res = evaluateIntInt(pkbReader,leftRef, rightRef);
    } else if (leftRef.isWildcard() && rightRef.isWildcard()) {
        res = evaluateWildWild(pkbReader,leftRef, rightRef);
    }

    return res;
}

Result SuchThatStrategy::evaluateSynInt(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateWildSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateWildInt(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIntInt(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateWildWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIntIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateSynIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}
