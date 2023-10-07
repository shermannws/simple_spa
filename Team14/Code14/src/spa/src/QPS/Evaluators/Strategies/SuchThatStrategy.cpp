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

    if (isLeftSynonym && isRightSynonym) {
        res = evaluateSynSyn(leftRef, rightRef);
    } else if (isLeftSynonym) {
        res = evaluateSynAny(leftRef, rightRef);
    } else if (isRightSynonym) {
        res = evaluateAnySyn(leftRef, rightRef);
    } else {
        res = evaluateBoolean(leftRef, rightRef);
    }
    return res;
}

