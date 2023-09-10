#include "Qps.h"

#include <utility>

void Qps::process(std::string& query, std::list<std::string> &results, std::shared_ptr<PkbReader> pkbReader) {
    PQLParser parser = PQLParser(query);
    PQLEvaluator evaluator= PQLEvaluator(std::move(pkbReader));

    Query queryObj = parser.parse();
    Result result = evaluator.Evaluate(queryObj);

    // format result to string, then push_back to results list
}