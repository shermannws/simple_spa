#include "Qps.h"

#include <utility>

void Qps::process(std::string& query, std::list<std::string> &results, std::shared_ptr<PkbReader> pkbReader) {
    PQLParser parser = PQLParser(query);
    // PQLEvaluator evaluator= PQLEvaluator(std::move(pkbReader));
    PQLEvaluator evaluator; //temp constructor

    Query queryObj = parser.parse();
    Result result = evaluator.evaluate(queryObj);

    // format result to string, then push_back to results list
}