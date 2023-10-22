#include "AssignPatternStrategy.h"

AssignPatternStrategy::AssignPatternStrategy(std::shared_ptr<PkbReader> pkbReader)
    : PatternStrategy(std::move(pkbReader)) {}

std::shared_ptr<Result> AssignPatternStrategy::evaluateWildcard(ExpressionSpec &secondArg) const {
    std::shared_ptr<Result> result = std::make_shared<Result>();
    if (secondArg.first == ExpressionSpecType::Wildcard) {
        auto resultRows = pkbReader->getAllAssign();
        result->setTuples(resultRows);
    } else {
        auto resultRows =
                pkbReader->getAssignStmtsByRhs(secondArg.second, secondArg.first == ExpressionSpecType::PartialMatch);
        result->setTuples(resultRows);
    }
    return result;
}

std::shared_ptr<Result> AssignPatternStrategy::evaluateSyn(ExpressionSpec &secondArg) const {
    std::shared_ptr<Result> result = std::make_shared<Result>();
    if (secondArg.first == ExpressionSpecType::Wildcard) {
        auto resultRows = pkbReader->getAllAssignStmtVarPair();
        result->setTuples(resultRows);
    } else {
        auto resultRows = pkbReader->getAssignStmtsVarPairByRhs(secondArg.second,
                                                                secondArg.first == ExpressionSpecType::PartialMatch);
        result->setTuples(resultRows);
    }
    return result;
}

std::shared_ptr<Result> AssignPatternStrategy::evaluateVarIdent(Ref &firstArg, ExpressionSpec &secondArg) const {
    std::shared_ptr<Result> result = std::make_shared<Result>();
    Variable lhsVariable = Variable(firstArg.getRep());
    if (secondArg.first == ExpressionSpecType::Wildcard) {
        auto resultRows = pkbReader->getAssignStmtsByLhs(lhsVariable);
        result->setTuples(resultRows);
    } else {
        auto resultRows = pkbReader->getAssignStmtsByLhsRhs(lhsVariable, secondArg.second,
                                                            secondArg.first == ExpressionSpecType::PartialMatch);
        result->setTuples(resultRows);
    }
    return result;
}
