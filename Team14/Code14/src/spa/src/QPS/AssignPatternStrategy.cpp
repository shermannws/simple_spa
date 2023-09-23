#include "AssignPatternStrategy.h"

Result AssignPatternStrategy::evaluateClause(std::shared_ptr<Clause> clause, std::shared_ptr<PkbReader> pkbReader) const {
    std::shared_ptr<PatternClause> patternClause = std::dynamic_pointer_cast<PatternClause>(clause);
    Ref firstArg = patternClause->getFirstParam();
    ExpressionSpec secondArg = patternClause->getSecondParam();

    Result result;
    std::unordered_map<std::string, int> columns {{patternClause->getSyn(), 0}};
    if (firstArg.getRootType() == RootType::Synonym) {
        columns.insert({firstArg.getRep(), 1});
    }
    result.setSynIndices(columns);

    if (firstArg.getRootType() == RootType::Wildcard) { // first arg is wildcard
        if (secondArg.first == ExpressionSpecType::Wildcard) {
            auto resultRows = pkbReader->getAllAssign();
            result.setTuples(resultRows);
        } else {
            auto resultRows = pkbReader->getAssignStmtsByRhs(secondArg.second,  secondArg.first == ExpressionSpecType::PartialMatch);
            result.setTuples(resultRows);
        }
    } else if (firstArg.getRootType() == RootType::Synonym) { //Variable synonym
        if (secondArg.first == ExpressionSpecType::Wildcard) {
            auto resultRows = pkbReader->getAllAssignStmtVarPair();
            result.setTuples(resultRows);
        } else {
            auto resultRows = pkbReader->getAssignStmtsVarPairByRhs(secondArg.second, secondArg.first == ExpressionSpecType::PartialMatch);
            result.setTuples(resultRows);
        }
    } else { // first arg is character strings (ident)
        Variable lhsVariable = Variable(firstArg.getRep());
        if (secondArg.first == ExpressionSpecType::Wildcard) {
            auto resultRows = pkbReader->getAssignStmtsByLhs(lhsVariable);
            result.setTuples(resultRows);
        } else {
            auto resultRows = pkbReader->getAssignStmtsByLhsRhs(lhsVariable, secondArg.second, secondArg.first == ExpressionSpecType::PartialMatch);
            result.setTuples(resultRows);
        }
    }

    return result;
}
