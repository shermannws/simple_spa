#include "SuchThatStrategy.h"

#include "QPS/Clauses/SuchThatClause.h"
#include <utility>

SuchThatStrategy::SuchThatStrategy(std::shared_ptr<PkbReader> pkbReader)
    : pkbReader(std::move(pkbReader)) {}

std::shared_ptr<Result>
SuchThatStrategy::evaluateClause(std::shared_ptr<Clause> clause) const {
    std::shared_ptr<SuchThatClause> suchThat =
            std::dynamic_pointer_cast<SuchThatClause>(clause);
    Ref leftRef = suchThat->getFirstParam();
    Ref rightRef = suchThat->getSecondParam();
    bool isLeftSynonym = leftRef.isRootType(RootType::Synonym);
    bool isRightSynonym = rightRef.isRootType(RootType::Synonym);

    if (isLeftSynonym && isRightSynonym) {
        return evaluateSynSyn(leftRef, rightRef);
    }
    if (isLeftSynonym) { return evaluateSynAny(leftRef, rightRef); }
    if (isRightSynonym) { return evaluateAnySyn(leftRef, rightRef); }
    return evaluateBoolean(leftRef, rightRef);
}
