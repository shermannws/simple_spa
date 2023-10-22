#include "IfPatternStrategy.h"

IfPatternStrategy::IfPatternStrategy(std::shared_ptr<PkbReader> pkbReader) : PatternStrategy(std::move(pkbReader)) {}

std::shared_ptr<Result> IfPatternStrategy::evaluateWildcard(ExpressionSpec &secondArg) const {
    std::shared_ptr<Result> result = std::make_shared<Result>();
    auto tuples = pkbReader->getAllIfPatternStmts();
    result->setTuples(tuples);
    return result;
}

std::shared_ptr<Result> IfPatternStrategy::evaluateSyn(ExpressionSpec &secondArg) const {
    std::shared_ptr<Result> result = std::make_shared<Result>();
    auto tuples = pkbReader->getAllIfStmtVarPair();
    result->setTuples(tuples);
    return result;
}

std::shared_ptr<Result> IfPatternStrategy::evaluateVarIdent(Ref &firstArg, ExpressionSpec &secondArg) const {
    std::shared_ptr<Result> result = std::make_shared<Result>();
    Variable v = Variable(firstArg.getRep());
    auto tuples = pkbReader->getIfStmtsByVar(v);
    result->setTuples(tuples);
    return result;
}
