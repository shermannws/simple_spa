#include "WhilePatternStrategy.h"

WhilePatternStrategy::WhilePatternStrategy(std::shared_ptr<PkbReader> pkbReader)
    : PatternStrategy(std::move(pkbReader)) {}

std::shared_ptr<Result> WhilePatternStrategy::evaluateWildcard(ExpressionSpec &secondArg) const {
    std::shared_ptr<Result> result = std::make_shared<Result>();
    auto tuples = pkbReader->getAllWhilePatternStmts();
    result->setTuples(tuples);
    return result;
}

std::shared_ptr<Result> WhilePatternStrategy::evaluateSyn(ExpressionSpec &secondArg) const {
    std::shared_ptr<Result> result = std::make_shared<Result>();
    auto tuples = pkbReader->getAllWhileStmtVarPair();
    result->setTuples(tuples);
    return result;
}

std::shared_ptr<Result> WhilePatternStrategy::evaluateVarIdent(Ref &firstArg, ExpressionSpec &secondArg) const {
    std::shared_ptr<Result> result = std::make_shared<Result>();
    Variable v = Variable(firstArg.getRep());
    auto tuples = pkbReader->getWhileStmtsByVar(v);
    result->setTuples(tuples);
    return result;
}
