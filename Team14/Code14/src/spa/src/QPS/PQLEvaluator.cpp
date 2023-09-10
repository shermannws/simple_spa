#include "PQLEvaluator.h"

PQLEvaluator::PQLEvaluator(std::shared_ptr<PkbReader> pkbReader) :pkbReader(pkbReader),
    clauseHandler(std::make_shared<ClauseHandler>(pkbReader)){}

Result PQLEvaluator::Evaluate(Query& query) {

    // TODO iterate through clauses, get Strategy Type from clause type

    // just placeholder, if clause is AssignPatternType:
    clauseHandler->setStrategy(std::make_unique<AssignPatternStrategy>());
    Result result;
    clauseHandler->executeQuery(query, result);

    return result;
}



