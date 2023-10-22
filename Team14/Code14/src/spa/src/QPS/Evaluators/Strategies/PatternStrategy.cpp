#include "PatternStrategy.h"

#include "QPS/Clauses/PatternClause.h"
#include <utility>

PatternStrategy::PatternStrategy(std::shared_ptr<PkbReader> pkbReader) : pkbReader(std::move(pkbReader)) {}

std::shared_ptr<Result> PatternStrategy::evaluateClause(std::shared_ptr<Clause> clause) const {
    std::shared_ptr<PatternClause> pattern = std::dynamic_pointer_cast<PatternClause>(clause);
    Ref firstArg = pattern->getFirstParam();
    ExpressionSpec secondArg = pattern->getSecondParam();

    if (firstArg.isRootType(RootType::Wildcard)) {
        return evaluateWildcard(secondArg);
    } else if (firstArg.isRootType(RootType::Synonym)) {
        return evaluateSyn(secondArg);
    }
    return evaluateVarIdent(firstArg, secondArg);
}
