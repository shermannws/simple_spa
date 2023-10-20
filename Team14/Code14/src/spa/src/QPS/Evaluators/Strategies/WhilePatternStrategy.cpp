#include "WhilePatternStrategy.h"

std::shared_ptr<Result> WhilePatternStrategy::evaluateClause(std::shared_ptr<Clause> clause) const {
    std::shared_ptr<PatternClause> patternClause = std::dynamic_pointer_cast<PatternClause>(clause);
    Ref firstArg = patternClause->getFirstParam();
    std::shared_ptr<Result> result = std::make_shared<Result>();

    if (firstArg.isRootType(RootType::Wildcard)) {
        auto tuples = pkbReader->getAllWhilePatternStmts();
        result->setTuples(tuples);
    } else if (firstArg.isRootType(RootType::Synonym)) {
        auto tuples = pkbReader->getAllWhileStmtVarPair();
        result->setTuples(tuples);
    } else {// ident
        Variable v = Variable(firstArg.getRep());
        auto tuples = pkbReader->getWhileStmtsByVar(v);
        result->setTuples(tuples);
    }

    return result;
}
