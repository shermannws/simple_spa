#include "SuchThatStrategy.h"
#include "QPS/Clauses/SuchThatClause.h"

Result SuchThatStrategy::evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const {
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
        res = evaluateSynSyn(pkbReader, leftRef, rightRef);
    } else if (isLeftSynonym && isRightInt) {
        res = evaluateSynInt(pkbReader, leftRef, rightRef);
    } else if (isLeftSynonym && isRightWildcard) {
        res = evaluateSynWild(pkbReader, leftRef, rightRef);
    } else if (isLeftSynonym && isRightIdent) {
        res = evaluateSynIdent(pkbReader, leftRef, rightRef);
    } else if (isLeftInt && isRightSynonym) {
        res = evaluateIntSyn(pkbReader, leftRef, rightRef);
    } else if (isLeftInt && isRightIdent) {
        res = evaluateIntIdent(pkbReader, leftRef, rightRef);
    } else if (isLeftInt && isRightWildcard) {
        res = evaluateIntWild(pkbReader,leftRef, rightRef);
    } else if (isLeftInt && isRightInt) {
        res = evaluateIntInt(pkbReader,leftRef, rightRef);
    } else if (isLeftWildcard && isRightInt) {
        res = evaluateWildInt(pkbReader,leftRef, rightRef);
    } else if (isLeftWildcard && isRightSynonym) {
        res = evaluateWildSyn(pkbReader,leftRef, rightRef);
    } else if (isLeftWildcard && isRightWildcard) {
        res = evaluateWildWild(pkbReader,leftRef, rightRef);
    } else if (isLeftIdent && isRightSynonym) {
        res = evaluateIdentSyn(pkbReader, leftRef, rightRef);
    } else if (isLeftIdent && isRightIdent) {
        res = evaluateIdentIdent(pkbReader, leftRef, rightRef);
    } else if (isLeftIdent && isRightWildcard) {
        res = evaluateIdentWild(pkbReader, leftRef, rightRef);
    }

    return res;
}

Result SuchThatStrategy::evaluateSynInt(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIntWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIntInt(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIntSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateWildSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateWildInt(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
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

Result SuchThatStrategy::evaluateIdentSyn(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIdentIdent(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}

Result SuchThatStrategy::evaluateIdentWild(std::shared_ptr<PkbReader> pkbReader, Ref &leftRef, Ref &rightRef) const {
    return {};
}
