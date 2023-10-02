#include "SuchThatStrategy.h"

#include <utility>
#include "QPS/Clauses/SuchThatClause.h"

SuchThatStrategy::SuchThatStrategy(std::shared_ptr<PkbReader> pkbReader) : pkbReader(std::move(pkbReader)) {}

Result SuchThatStrategy::evaluateClause(std::shared_ptr<Clause> clause) const {
    std::shared_ptr<SuchThatClause> suchThat = std::dynamic_pointer_cast<SuchThatClause>(clause);
    Ref leftRef = suchThat->getFirstParam();
    Ref rightRef = suchThat->getSecondParam();
    Result res;
    bool isLeftSynonym = leftRef.isRootType(RootType::Synonym);
    bool isRightSynonym = rightRef.isRootType(RootType::Synonym);
    bool isLeftWildcard = leftRef.isRootType(RootType::Wildcard);
    bool isRightWildcard = rightRef.isRootType(RootType::Wildcard);
    bool isLeftIdent = leftRef.isRootType(RootType::Ident);
    bool isRightIdent = rightRef.isRootType(RootType::Ident);
    bool isLeftInt = leftRef.isRootType(RootType::Integer);
    bool isRightInt = rightRef.isRootType(RootType::Integer);

    // TODO: make pkbReader a field of Strategies?
    if (isLeftSynonym && isRightSynonym) {
        res = evaluateSynSyn(leftRef, rightRef);
    } else if (isLeftSynonym && isRightInt) {
        res = evaluateSynInt(leftRef, rightRef);
    } else if (isLeftSynonym && isRightWildcard) {
        res = evaluateSynWild(leftRef, rightRef);
    } else if (isLeftSynonym && isRightIdent) {
        res = evaluateSynIdent(leftRef, rightRef);
    } else if (isLeftInt && isRightSynonym) {
        res = evaluateIntSyn(leftRef, rightRef);
    } else if (isLeftInt && isRightIdent) {
        res = evaluateIntIdent(leftRef, rightRef);
    } else if (isLeftInt && isRightWildcard) {
        res = evaluateIntWild(leftRef, rightRef);
    } else if (isLeftInt && isRightInt) {
        res = evaluateIntInt(leftRef, rightRef);
    } else if (isLeftWildcard && isRightInt) {
        res = evaluateWildInt(leftRef, rightRef);
    } else if (isLeftWildcard && isRightSynonym) {
        res = evaluateWildSyn(leftRef, rightRef);
    } else if (isLeftWildcard && isRightWildcard) {
        res = evaluateWildWild(leftRef, rightRef);
    } else if (isLeftIdent && isRightSynonym) {
        res = evaluateIdentSyn(leftRef, rightRef);
    } else if (isLeftIdent && isRightIdent) {
        res = evaluateIdentIdent(leftRef, rightRef);
    } else if (isLeftIdent && isRightWildcard) {
        res = evaluateIdentWild(leftRef, rightRef);
    }

    return res;
}

Result SuchThatStrategy::evaluateSynInt(Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIntWild(Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIntInt(Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIntSyn(Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateWildSyn(Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateWildInt(Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateWildWild(Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIntIdent(Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateSynIdent(Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIdentSyn(Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIdentIdent(Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIdentWild(Ref &leftRef, Ref &rightRef) const {
    return {};
}

