#include "AssignPatternStrategy.h"

std::shared_ptr<Result> AssignPatternStrategy::evaluateClause(std::shared_ptr<Clause> clause) const {
    std::shared_ptr<PatternClause> patternClause = std::dynamic_pointer_cast<PatternClause>(clause);
    Ref firstArg = patternClause->getFirstParam();
    ExpressionSpec secondArg = patternClause->getSecondParam();

    std::shared_ptr<Result> result = std::make_shared<Result>();

    if (firstArg.isRootType(RootType::Wildcard)) {
        if (secondArg.first == ExpressionSpecType::Wildcard) {
            auto resultRows = pkbReader->getAllAssign();
            result->setTuples(resultRows);
        } else {
            auto resultRows = pkbReader->getAssignStmtsByRhs(secondArg.second,
                                                             secondArg.first == ExpressionSpecType::PartialMatch);
            result->setTuples(resultRows);
        }
    } else if (firstArg.isRootType(RootType::Synonym)) {
        if (secondArg.first == ExpressionSpecType::Wildcard) {
            auto resultRows = pkbReader->getAllAssignStmtVarPair();
            result->setTuples(resultRows);
        } else {
            auto resultRows = pkbReader->getAssignStmtsVarPairByRhs(
                    secondArg.second, secondArg.first == ExpressionSpecType::PartialMatch);
            result->setTuples(resultRows);
        }
    } else {
        Variable lhsVariable = Variable(firstArg.getRep());
        if (secondArg.first == ExpressionSpecType::Wildcard) {
            auto resultRows = pkbReader->getAssignStmtsByLhs(lhsVariable);
            result->setTuples(resultRows);
        } else {
            auto resultRows = pkbReader->getAssignStmtsByLhsRhs(lhsVariable, secondArg.second,
                                                                secondArg.first == ExpressionSpecType::PartialMatch);
            result->setTuples(resultRows);
        }
    }

    return result;
}
